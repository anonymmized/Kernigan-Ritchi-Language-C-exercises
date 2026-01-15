#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

#define MAXWRITE 1000

int my_write(int fd, char *buf, int n) {
    return syscall(SYS_write, fd, buf, n);
}

int main(int argc, char *argv[]) {
    while (--argc > 0) {
        char *arg = *++argv;
        my_write(1, arg, strlen(arg));
        my_write(1, " ", 1);
    }
}
