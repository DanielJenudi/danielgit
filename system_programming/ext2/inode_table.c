/*
 * ext2root.c
 *
 * List entries in the root directory of the floppy disk
 *
 * Questions?
 * Emanuele Altieri
 * ealtieri@hampshire.edu
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "/usr/include/ext2fs/ext2_fs.h"

#define BASE_OFFSET 1024      /* locates beginning of the super block (first group) */
#define FD_DEVICE "/dev/ram0" /* the floppy disk device */
#define BLOCK_OFFSET(block) (block_size + (block - 1) * block_size)

static unsigned int block_size = 0; /* block size (to be calculated) */

void FindFileAndCopy(const char *drive_path, char *file_path, FILE *dest);

static void read_dir(int, const struct ext2_inode *, const struct ext2_group_desc *, char *, FILE *);
static void read_inode(int, int, const struct ext2_group_desc *, struct ext2_inode *);
static void print_file(int fd, const struct ext2_inode *, const struct ext2_group_desc *, FILE *);

int main(void)
{
    FILE *dest = fopen("dest.txt", "w");
    char file_path[] = "/ramdisk/d/hello.txt";

    FindFileAndCopy(FD_DEVICE, file_path, dest);

    fclose(dest);
    dest = NULL;

    exit(0);
} /* main() */

void FindFileAndCopy(const char *drive_path, char *file_path, FILE *dest)
{
    struct ext2_super_block super;
    struct ext2_group_desc group;
    struct ext2_inode inode;
    int fd;
    char *buffer_strtok = strtok(file_path + 1, "/");

    /* open floppy device */

    if ((fd = open(drive_path, O_RDONLY)) < 0)
    {
        perror(FD_DEVICE);
        exit(1); /* error while opening the floppy device */
    }

    /* read super-block */

    lseek(fd, BASE_OFFSET, SEEK_SET);
    read(fd, &super, sizeof(super));

    if (super.s_magic != EXT2_SUPER_MAGIC)
    {
        fprintf(stderr, "Not a Ext2 filesystem\n");
        exit(1);
    }

    block_size = 1024 << super.s_log_block_size;

    /* read group descriptor */

    lseek(fd, block_size, SEEK_SET);
    read(fd, &group, sizeof(group));

    /* show entries in the root directory */

    read_inode(fd, 2, &group, &inode); /* read inode 2 (root directory) */
    read_dir(fd, &inode, &group, buffer_strtok, dest);

    close(fd);
}

static void read_inode(int fd, int inode_no, const struct ext2_group_desc *group,
                       struct ext2_inode *inode)
{
    lseek(fd, BLOCK_OFFSET(group->bg_inode_table) + (inode_no - 1) * sizeof(struct ext2_inode),
          SEEK_SET);
    read(fd, inode, sizeof(struct ext2_inode));
} /* read_inode() */

static void read_dir(int fd, const struct ext2_inode *inode,
                     const struct ext2_group_desc *group, char *file_path, FILE *dest)
{
    void *block;

    if (S_ISDIR(inode->i_mode))
    {
        struct ext2_dir_entry_2 *entry;
        unsigned int size = 0;

        file_path = strtok(NULL, "/");

        if ((block = malloc(block_size)) == NULL)
        { /* allocate memory for the data block */
            fprintf(stderr, "Memory error\n");
            close(fd);
            exit(1);
        }

        lseek(fd, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET);
        read(fd, block, block_size); /* read block from disk*/

        entry = (struct ext2_dir_entry_2 *)block; /* first entry in the directory */
                                                  /* Notice that the list may be terminated with a NULL
                                                     entry (entry->inode == NULL)*/
        while ((size < inode->i_size) && entry->inode)
        {
            char file_name[EXT2_NAME_LEN + 1];
            memcpy(file_name, entry->name, entry->name_len);
            file_name[entry->name_len] = 0; /* append null character to the file name */

            printf("%10u %s\n", entry->inode, file_name);

            if (!strcmp(file_path, file_name))
            {
                read_inode(fd, entry->inode, group, (struct ext2_inode *)inode); /* read inode 2 (root directory) */
                read_dir(fd, inode, group, file_path, dest);

                free(block);
                block = NULL;

                return;
            }
            entry = (void *)entry + entry->rec_len;
            size += entry->rec_len;
        }

        free(block);
        block = NULL;
    }

    print_file(fd, inode, group, dest);

} /* read_dir() */

static void print_file(int fd, const struct ext2_inode *result,
                       const struct ext2_group_desc *group, FILE *dest)
{
    void *block;
    char buff[100] = {0};

    unsigned int size = 0;

    if ((block = malloc(block_size)) == NULL)
    { /* allocate memory for the data block */
        fprintf(stderr, "Memory error\n");
        close(fd);
        exit(1);
    }

    lseek(fd, BLOCK_OFFSET(result->i_block[0]), SEEK_SET);
    read(fd, block, block_size); /* read block from disk*/

    /* char file_name[EXT2_NAME_LEN + 1]; */
    memcpy(buff, block, 100);
    buff[100] = 0; /* append null character to the file name */

    fwrite(buff, 100, 1, dest);

    printf("buff: %s\n", buff);

    free(block);
    block = NULL;

} /* read_dir() */