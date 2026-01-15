#define EOF (-1)
#define BUFSIZE 1024
#define OPEN_MAX 20

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
    _READ = 01,
    _WRITE = 02,
    _UNBUF = 04,
    _EOF = 010,
    _ERR = 020
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)
#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar() getc(stdin)
#define putchar(x) putc(x, stdout)

#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>

#define PERMS 0666

int my_open(const char *name, int flags, int perms) {
    return syscal(SYS_open, name, flags, perms);
}

int my_create(const char *name, int perms) {
    return my_open(name, O_WRONLY | O_CREAT | O_TRUNC, perms);
}

FILE *fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if (fp->flag & (_READ | _WRITE) == 0) {
            break;
        }
    }

    if (fp >= _iob + OPEN_MAX) return NULL;
    if (*mode == 'w') {
        fd = my_create(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = my_open(name, O_WRONLY, 0)) == -1) {
            fd = my_create(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
        fd = my_open(name, O_RONLY, 0);
    }

    if (fd == -1) return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}
