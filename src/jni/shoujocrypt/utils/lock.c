#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <lock.h>

int create_lock(const char *path) {
    int fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0644);

    if (fd == -1) {
        perror("Lock file already exists");
        return -1;
    }

    close(fd);    
    return 0;
}