
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <exception>
#include <linux/nbd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <assert.h>
#include <sys/wait.h>
#include <errno.h>
#include <err.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <thread>
#include <chrono>
#include <semaphore>

#include "nbd.hpp"
#include "fd_wrapper.hpp"
#include "reactor.hpp"

#ifndef BUSE_DEBUG
#define BUSE_DEBUG (0)
#endif

/*
 * These helper functions were taken from cliserv.h in the nbd distribution.
 */
#ifdef WORDS_BIGENDIAN
u_int64_t ntohll(u_int64_t a)
{
    return a;
}
#else
u_int64_t ntohll(u_int64_t a)
{
    u_int32_t lo = a & 0xffffffff;
    u_int32_t hi = a >> 32U;
    lo = ntohl(lo);
    hi = ntohl(hi);
    return ((u_int64_t)lo) << 32U | hi;
}
#endif
#define htonll ntohll

namespace ilrd
{
    static int set_sigaction(int sig, const struct sigaction *act);
    static void ReadCallback(int sk, const struct buse_operations *aop, void *userdata);
    static void disconnect_nbd(int m_nbd);
    static const size_t mb_size = 1048576;
    static void BlockSignals();
    static void ConfigureNbd(int sk, int nbd);
    static void EnableSignals();
    static int PrepareNbd(std::string dev_file, const struct buse_operations *aop);

    NbdComm::NbdComm(std::string dev_file, const struct buse_operations *aop)
        : m_aop(aop), m_nbd(-1)
    {
        int sp[2];
        int nbd, err, sk;

        err = socketpair(AF_UNIX, SOCK_STREAM, 0, sp);
        if (err == -1)
        {
            std::cout << "socketpair failed.\n";
        }

        nbd = PrepareNbd(dev_file, aop);

        m_pid = fork();

        if (m_pid == 0)
        {
            std::cout << getpid() << "child \n";

            BlockSignals();

            close(sp[0]);
            sk = sp[1];

            ConfigureNbd(sk, nbd);

            std::cout << "~~~~~~~~final exit\n";

            exit(0);
        }
        else
        {
            std::cout << getpid() << "parent \n";
        }

        /* Parent handles termination signals by terminating nbd device. */
        assert(m_nbd == -1);
        m_nbd = nbd;

        EnableSignals();

        close(sp[1]);
        m_socket = FileDesc(sp[0]);
    }

    static int PrepareNbd(std::string dev_file, const struct buse_operations *aop)
    {
        int err, nbd;
        nbd = open(dev_file.c_str(), O_RDWR);
        if (nbd == -1)
        {
            throw std::runtime_error("couldn't open nbd.\n");
        }

        if (aop->blksize)
        {
            if (ioctl(nbd, NBD_SET_BLKSIZE, aop->blksize) == -1)
            {
                throw std::runtime_error("couldn't NBD_SET_BLKSIZE nbd.\n");
            }
        }
        if (aop->size)
        {
            if (ioctl(nbd, NBD_SET_SIZE, aop->size) == -1)
            {
                throw std::runtime_error("couldn't NBD_SET_SIZE nbd.\n");
            }
        }
        if (aop->size_blocks)
        {
            if (ioctl(nbd, NBD_SET_SIZE_BLOCKS, aop->size_blocks) == -1)
            {
                throw std::runtime_error("couldn't NBD_SET_SIZE_BLOCKS nbd.\n");
            }
        }

        err = ioctl(nbd, NBD_CLEAR_SOCK);
        if (err == -1)
        {
            throw std::runtime_error("ioctl(nbd, NBD_CLEAR_SOCK) failed.\n");
        }

        return nbd;
    }

    static void BlockSignals()
    {
        sigset_t sigset;
        if (
            sigfillset(&sigset) != 0 ||
            sigprocmask(SIG_SETMASK, &sigset, NULL) != 0)
        {
            throw std::runtime_error("error: failed to block signals in child");
        }
    }

    static void EnableSignals()
    {
        struct sigaction act;
        act.sa_handler = disconnect_nbd;
        act.sa_flags = SA_RESTART;
        if (
            sigemptyset(&act.sa_mask) != 0 ||
            sigaddset(&act.sa_mask, SIGINT) != 0 ||
            sigaddset(&act.sa_mask, SIGTERM) != 0)
        {
            throw std::runtime_error("failed to prepare signal mask in parent");
        }
        if (
            set_sigaction(SIGINT, &act) != 0 ||
            set_sigaction(SIGTERM, &act) != 0)
        {
            throw std::runtime_error("failed to register signal handlers in parent");
        }
    }

    static void ConfigureNbd(int sk, int nbd)
    {
        int flags, err;

        if (ioctl(nbd, NBD_SET_SOCK, sk) == -1)
        {
            throw std::runtime_error("ioctl(nbd, NBD_SET_SOCK, sk) failed.");
        }
        else
        {

#if defined NBD_SET_FLAGS
            flags = 0;
#if defined NBD_FLAG_SEND_TRIM
            flags |= NBD_FLAG_SEND_TRIM;
#endif
#if defined NBD_FLAG_SEND_FLUSH
            flags |= NBD_FLAG_SEND_FLUSH;
#endif
            if (flags != 0 && ioctl(nbd, NBD_SET_FLAGS, flags) == -1)
            {
                throw std::runtime_error("ioctl(nbd, NBD_SET_FLAGS failed.\n");
            }
#endif
            std::cout << " ~~~~~~~~~~~~~~~~~~~~ NBD_DO_IT \n";

            err = ioctl(nbd, NBD_DO_IT);
            if (err == -1)
            {
                throw std::runtime_error("NBD_DO_IT terminated with error");
            }
        }
        if (
            ioctl(nbd, NBD_CLEAR_QUE) == -1 ||
            ioctl(nbd, NBD_CLEAR_SOCK) == -1)
        {
            throw std::runtime_error("failed to perform nbd cleanup actions");
        }
        std::cout << " ~~~~~~~~~~~~~~~~~~~~ NBD_DO_IT exit\n";
    }

    NbdComm::~NbdComm() noexcept
    {
        std::cout << "enter dtor\n";

        disconnect_nbd(m_nbd);

        std::cout << "~~~~~~~~~~~~wait dtor\n";

        int status = 0;
        if (wait(&status) == -1)
        {
            std::cout << "failed to wait to child process\n";
        }
        if (WEXITSTATUS(status) != 0)
        {
            std::cout << "exit status returned\n";
        }

        std::cout << "exit successfully\n";
    }

    FileDesc NbdComm::GetNbdSocket()
    {
        return m_socket;
    }

    /* Signal handler to gracefully disconnect from nbd kernel driver. */
    static void disconnect_nbd(int m_nbd)
    {
        char buf[] = "stop";
        write(0, buf, sizeof(buf));

        if (m_nbd != -1)
        {
            if (ioctl(m_nbd, NBD_DISCONNECT) == -1)
            {
                std::cerr << "failed to request disconect on nbd device";
            }
            else
            {
                m_nbd = -1;
                std::cout << "sucessfuly requested disconnect on nbd device\n";
            }
        }
    }

    /* Sets signal action like regular sigaction but is suspicious. */
    static int set_sigaction(int sig, const struct sigaction *act)
    {
        struct sigaction oact;
        int r = sigaction(sig, act, &oact);
        if (r == 0 && oact.sa_handler != SIG_DFL)
        {
            throw std::runtime_error("overriden non-default signal handler ");
        }
        return r;
    }

}
