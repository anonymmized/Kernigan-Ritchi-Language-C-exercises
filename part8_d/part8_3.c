#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

int my_read(int fd, char *buf, int n) {
    return syscall(SYS_read, fd, buf, n);
}

int my_write(int fd, const char *buf, int n) {
    return syscall(SYS_write, fd, buf, n);
}

int my_open(const char *name, int flags, int perms) {
    return syscall(SYS_open, name, flags, perms);
}

int my_create(const char *name, int perms) {
    return open(name, O_WRONLY | O_CREAT | O_TRUNC, perms);
}

int my_close(int fd) {
    return syscall(SYS_close, fd);
}

int main() {
    int fd = my_create("log.txt", 0644);
    return 0;
}
    
