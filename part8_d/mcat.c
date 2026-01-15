#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

#define MAXLINE 1000

int my_read(int fd, char *buf, int n) {
    return syscall(SYS_read, fd, buf, n);
}

int my_write(int fd, char *buf, int n) {
    return syscall(SYS_write, fd, buf, n);
}

int my_open(const char *name, int flags, int perms) {
    return syscall(SYS_open, name, flags, perms);
}

int my_close(int fd) {
    return syscall(SYS_close, fd);
}

int main(int argc, char *argv[]) {
    int n;
    char buf[MAXLINE];
    int f = my_open(*++argv, O_RDONLY, 0);
    while ((n = my_read(f, buf, MAXLINE)) > 0) {
        my_write(1, buf, n);
    }
    return 0;
}
