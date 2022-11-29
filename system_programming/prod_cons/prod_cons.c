#include <pthread.h>   /* pthread_create */
#include <stdio.h>     /* printf */
#include <stdatomic.h> /* atomic_int */
#include <semaphore.h> /* seminit, sem_t */
#include <string.h>    /* strcpy */
#include <unistd.h>

#define ASCII_0 (48)
#define ASCII_9 (57)
#define NUM_OF_THREADS (15)
#define CBUFFER_SIZE (sizeof(int) * 10)

#include "prod_cons.h"
#include "dll.h"
#include "cbuffer.h"

enum Status
{
    SUCCESS = 0,
    FAIL = -1,
    TRUE = 1,
    FALSE = 0
};

/* exc1 */
static void *UnEven(void *arg);
static void *Even(void *arg);

/* exc2 */
static void *RemoveNode(void *arg);
static void *AddNode(void *arg);

/* exc3 */
static void *RemoveNodeSem(void *arg);
static void *AddNodeSem(void *arg);

/* exc4 */
static void *WriteCBuffer(void *arg);
static void *ReadCBuffer(void *arg);

/* exc5 */
static void *ReadCBuffer2Mutex(void *arg);
static void *WriteCBuffer2Mutex(void *arg);

/* exc6 */
static void *KingThread(void *arg);
static void *SubjectsThread(void *arg);

atomic_int g_flag = 0;
pthread_mutex_t g_lock;

pthread_mutex_t g_lock_write;
pthread_mutex_t g_lock_read;

dll_list_t *g_dll = NULL;
c_buffer_t *g_cbuffer = NULL;

sem_t g_sem = {0};

sem_t g_sem_cbuffer_write = {0};
sem_t g_sem_cbuffer_read = {0};

char g_massege[100] = {0};
pthread_cond_t g_cond_var;
atomic_int g_count_subjects = 0;

/* exc1 */
int Single_Write_Read()
{
    pthread_t read_tid = 0;
    pthread_t write_tid = 0;
    void *retval = NULL;

    if (SUCCESS !=
        pthread_create(&write_tid, NULL, &Even, NULL))
    {
        return FAIL;
    }

    if (SUCCESS !=
        pthread_create(&read_tid, NULL, &UnEven, NULL))
    {
        return FAIL;
    }

    if (SUCCESS != pthread_join(write_tid, &retval))
    {
        return FAIL;
    }

    if (SUCCESS != pthread_join(read_tid, &retval))
    {
        return FAIL;
    }

    printf("%d\n", g_flag);

    return SUCCESS;
}

/* exc2 */
int Multiple_Add_Remove()
{
    pthread_t add_tid[NUM_OF_THREADS] = {0};
    pthread_t remove_tid[NUM_OF_THREADS] = {0};
    void *retval = NULL;
    size_t i = 0;

    g_dll = DLLCreate();
    if (NULL == g_dll)
    {
        return FAIL;
    }

    pthread_mutex_init(&g_lock, NULL);

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (SUCCESS !=
            pthread_create(&add_tid[i], NULL, &AddNode, (void *)i))
        {
            return FAIL;
        }

        if (SUCCESS !=
            pthread_create(&remove_tid[i], NULL, &RemoveNode, NULL))
        {
            return FAIL;
        }
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (SUCCESS != pthread_join(add_tid[i], &retval))
        {
            return FAIL;
        }

        if (SUCCESS != pthread_join(remove_tid[i], &retval))
        {
            return FAIL;
        }
    }

    DLLDestroy(g_dll);
    g_dll = NULL;

    return SUCCESS;
}

/* exc3 */
int Multiple_Add_Remove_Sem()
{
    pthread_t add_tid[NUM_OF_THREADS] = {0};
    pthread_t remove_tid[NUM_OF_THREADS] = {0};
    void *retval = NULL;
    size_t i = 0;

    g_dll = DLLCreate();
    if (NULL == g_dll)
    {
        return FAIL;
    }

    pthread_mutex_init(&g_lock, NULL);
    sem_init(&g_sem, 0, 0);

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (SUCCESS !=
            pthread_create(&add_tid[i], NULL, &AddNodeSem, (void *)i))
        {
            return FAIL;
        }

        if (SUCCESS !=
            pthread_create(&remove_tid[i], NULL, &RemoveNodeSem, NULL))
        {
            return FAIL;
        }
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (SUCCESS != pthread_join(add_tid[i], &retval))
        {
            return FAIL;
        }

        if (SUCCESS != pthread_join(remove_tid[i], &retval))
        {
            return FAIL;
        }
    }

    DLLDestroy(g_dll);
    g_dll = NULL;

    return SUCCESS;
}

/* exc4 */
int Multipe_CBuffer()
{
    pthread_t add_tid[NUM_OF_THREADS] = {0};
    pthread_t remove_tid[NUM_OF_THREADS] = {0};
    void *retval = NULL;
    size_t i = 0;

    g_cbuffer = CBufferCreate(CBUFFER_SIZE);
    if (NULL == g_cbuffer)
    {
        return FAIL;
    }

    pthread_mutex_init(&g_lock_write, NULL);
    pthread_mutex_init(&g_lock_read, NULL);

    sem_init(&g_sem_cbuffer_write, 0, CBUFFER_SIZE);
    sem_init(&g_sem_cbuffer_read, 0, 0);

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (SUCCESS !=
            pthread_create(&add_tid[i], NULL, &WriteCBuffer, (void *)i))
        {
            return FAIL;
        }

        if (SUCCESS !=
            pthread_create(&remove_tid[i], NULL, &ReadCBuffer, NULL))
        {
            return FAIL;
        }
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (SUCCESS != pthread_join(add_tid[i], &retval))
        {
            return FAIL;
        }

        if (SUCCESS != pthread_join(remove_tid[i], &retval))
        {
            return FAIL;
        }
    }

    CBufferDestroy(g_cbuffer);
    g_cbuffer = NULL;

    return SUCCESS;
}

/* exc5 */
int Multipe_CBuffer2Mutex()
{
    pthread_t add_tid[NUM_OF_THREADS] = {0};
    pthread_t remove_tid[NUM_OF_THREADS] = {0};
    void *retval = NULL;
    size_t i = 0;

    g_cbuffer = CBufferCreate(CBUFFER_SIZE);
    if (NULL == g_cbuffer)
    {
        return FAIL;
    }

    pthread_mutex_init(&g_lock_write, NULL);
    pthread_mutex_init(&g_lock_read, NULL);

    sem_init(&g_sem_cbuffer_write, 0, CBUFFER_SIZE);
    sem_init(&g_sem_cbuffer_read, 0, 0);

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (SUCCESS !=
            pthread_create(&add_tid[i], NULL, &WriteCBuffer2Mutex, (void *)i))
        {
            return FAIL;
        }

        if (SUCCESS !=
            pthread_create(&remove_tid[i], NULL, &ReadCBuffer2Mutex, NULL))
        {
            return FAIL;
        }
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (SUCCESS != pthread_join(add_tid[i], &retval))
        {
            return FAIL;
        }

        if (SUCCESS != pthread_join(remove_tid[i], &retval))
        {
            return FAIL;
        }
    }

    CBufferDestroy(g_cbuffer);
    g_cbuffer = NULL;

    return SUCCESS;
}

/* exc6 */
int Send_Massege_To_The_World()
{
    pthread_t king_tid = {0};
    pthread_t subjects_tid[NUM_OF_THREADS] = {0};
    void *retval = NULL;
    size_t i = 0;

    pthread_cond_init(&g_cond_var, NULL);
    pthread_mutex_init(&g_lock, NULL);
    sem_init(&g_sem, 0, 0);

    if (SUCCESS !=
        pthread_create(&king_tid, NULL, &KingThread, NULL))
    {
        return FAIL;
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (SUCCESS !=
            pthread_create(&subjects_tid[i], NULL, &SubjectsThread, NULL))
        {
            return FAIL;
        }
    }

    while (NUM_OF_THREADS != g_count_subjects)
        ;

    pthread_cond_broadcast(&g_cond_var);

    if (SUCCESS != pthread_join(king_tid, &retval))
    {
        return FAIL;
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (SUCCESS != pthread_join(subjects_tid[i], &retval))
        {
            return FAIL;
        }
    }

    CBufferDestroy(g_cbuffer);
    g_cbuffer = NULL;

    return SUCCESS;
}

/* exc1 */
static void *UnEven(void *arg)
{
    size_t i = 0;

    (void)arg;

    while (i < 10)
    {
        if (1 == (g_flag % 2))
        {
            ++g_flag;
            ++i;
        }
    }
    return NULL;
}

static void *Even(void *arg)
{
    size_t i = 0;

    (void)arg;

    while (i < 10)
    {
        if (0 == (g_flag % 2))
        {
            ++g_flag;
            ++i;
        }
    }

    return NULL;
}

/* exc2 */
static void *AddNode(void *arg)
{
    long data = (long)arg * (long)arg;

    data %= 10;

    pthread_mutex_lock(&g_lock); /* lock */

    DLLInsertBefore(DLLBegin(g_dll), (void *)data);
    printf("create node\n");

    pthread_mutex_unlock(&g_lock); /* unlock */

    return NULL;
}

static void *RemoveNode(void *arg)
{
    int flag = FALSE;
    struct timespec sleeper = {0, 1000000L};

    (void)arg;

    while (flag != TRUE)
    {
        pthread_mutex_lock(&g_lock); /* lock */

        if (FALSE == DLLIsEmpty(g_dll))
        {
            flag = TRUE;
            DLLPopBack(g_dll);
            printf("remove node\n");
        }

        pthread_mutex_unlock(&g_lock); /* unlock */
        nanosleep(&sleeper, NULL);
    }

    return NULL;
}

/* exc3 */
static void *AddNodeSem(void *arg)
{
    long data = (long)arg * (long)arg;

    data %= 10;

    pthread_mutex_lock(&g_lock); /* lock */

    DLLInsertBefore(DLLBegin(g_dll), (void *)data);
    printf("create node\n");

    pthread_mutex_unlock(&g_lock); /* unlock */

    sem_post(&g_sem);

    return NULL;
}

static void *RemoveNodeSem(void *arg)
{
    (void)arg;

    sem_wait(&g_sem);

    pthread_mutex_lock(&g_lock); /* lock */

    DLLPopBack(g_dll);
    printf("remove node\n");

    pthread_mutex_unlock(&g_lock); /* unlock */

    return NULL;
}

/* exc4 */
static void *WriteCBuffer(void *arg)
{
    int data = (long)arg * (long)arg;

    data %= 10;

    sem_wait(&g_sem_cbuffer_write);
    pthread_mutex_lock(&g_lock); /* lock */

    CBufferWrite(g_cbuffer, &data, sizeof(int));
    printf("write %d\n", data);

    pthread_mutex_unlock(&g_lock); /* unlock */

    sem_post(&g_sem_cbuffer_read);

    return NULL;
}

static void *ReadCBuffer(void *arg)
{
    int data = 0;
    (void)arg;

    sem_wait(&g_sem_cbuffer_read);
    pthread_mutex_lock(&g_lock); /* lock */

    CBufferRead(g_cbuffer, &data, sizeof(int));
    printf("read %d\n", data);

    pthread_mutex_unlock(&g_lock); /* unlock */

    sem_post(&g_sem_cbuffer_write);

    return NULL;
}

/* exc5 */
static void *WriteCBuffer2Mutex(void *arg)
{
    int data = (long)arg * (long)arg;

    data %= 10;

    sem_wait(&g_sem_cbuffer_write);

    pthread_mutex_lock(&g_lock_read); /* lock */

    CBufferWrite(g_cbuffer, &data, sizeof(int));
    printf("write %d\n", data);

    pthread_mutex_unlock(&g_lock_read); /* unlock */

    sem_post(&g_sem_cbuffer_read);

    return NULL;
}

static void *ReadCBuffer2Mutex(void *arg)
{
    int data = 0;
    (void)arg;

    sem_wait(&g_sem_cbuffer_read);

    pthread_mutex_lock(&g_lock_write); /* lock */

    CBufferRead(g_cbuffer, &data, sizeof(int));
    printf("read %d\n", data);

    pthread_mutex_unlock(&g_lock_write); /* unlock */

    sem_post(&g_sem_cbuffer_write);

    return NULL;
}

/* exc6 */
static void *KingThread(void *arg)
{
    char str[] = "hello subjects. give my your cow's";
    (void)arg;

    printf("start\n");

    strcpy(g_massege, str);

    sem_post(&g_sem);

    pthread_mutex_lock(&g_lock); /* lock */
    pthread_cond_wait(&g_cond_var, &g_lock);
    pthread_mutex_unlock(&g_lock); /* lock */

    printf("finish\n");

    return NULL;
}

static void *SubjectsThread(void *arg)
{
    (void)arg;

    sem_wait(&g_sem);

    printf("%s\n", g_massege);
    ++g_count_subjects;

    sem_post(&g_sem);

    return NULL;
}
