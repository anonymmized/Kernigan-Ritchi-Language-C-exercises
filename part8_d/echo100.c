#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

int my_read(int fd, char *buf, int n) {
    return syscall(SYS_read, fd, buf, n);
}

int my_write(int fd, char *buf, int n) {
    return syscall(SYS_write, fd, buf, n);
}

int main() {
    char buf[10];
    int n = my_read(0, buf, sizeof(buf));
    if (n > 0) {
        my_write(1, buf, n);
    }
    return 0;
}
