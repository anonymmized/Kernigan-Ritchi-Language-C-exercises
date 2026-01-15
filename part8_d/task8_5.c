#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>

#ifndef DIRSIZ
#define DIRSIZ 14
#endif

#define NAME_MAX 14
#define MAX_PATH 1024

typedef struct {
    long ino;
    char name[NAME_MAX+1];
}Dirent;

void fsize(const char *name);
void dirwalk(const char *dir, void (*fcn)(const char *));

void dirwalk(const char *dir, void (*fcn)(const char *)) {
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: cannot open %s\n", dir);
        return;
    }

    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue;
        }
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) {
            fprintf(stderr, "dirwalk: too long name %s/%s\n", dir, dp->d_name);
            return;
        } else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

static void print_filetype_and_perms(mode_t m) {
    if (S_ISREG(m)) putchar('-');
    else if (S_ISDIR(m)) putchar('d');
    else if (S_ISLNK(m)) putchar('l');
    else if (S_ISCHR(m)) putchar('c');
    else if (S_ISBLK(m)) putchar('b');
    else if (S_ISFIFO(m)) putchar('p');
    else if (S_ISSOCK(m)) putchar('s');
    else putchar('?');

    putchar((m & S_IRUSR) ? 'r' : '-');
    putchar((m & S_IWUSR) ? 'w' : '-');
    putchar((m & S_IXUSR) ? 'x' : '-');

    putchar((m & S_IRGRP) ? 'r' : '-');
    putchar((m & S_IWGRP) ? 'w' : '-');
    putchar((m & S_IXGRP) ? 'x' : '-');

    putchar((m & S_IROTH) ? 'r' : '-');
    putchar((m & S_IWOTH) ? 'w' : '-');
    putchar((m & S_IXOTH) ? 'x' : '-');
}

static void print_time(const char *label, time_t t) {
    char buf[64];
    struct tm *tm = localtime(&t);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm);
    printf("%s: %s\n", label, buf);
}

void fsize(const char *name) {
    struct stat st;

    if (stat(name, &st) < 0) {
        printf("fsize: can't access %s\n", name);
        return;
    }

    if (S_ISDIR(st.st_mode)) {
        dirwalk(name, fsize);
    }

    printf("============================================\n");
    printf("path: %s\n", name);

    printf("inode: %lu\n", (unsigned long)st.st_ino);

    printf("type+terms: ");
    print_filetype_and_perms(st.st_mode);
    printf("\t(mode=%lu)\n", (unsigned long)st.st_mode);
    printf("links: %lu\n", (unsigned long)st.st_nlink);
    printf("uid: %lu\n", (unsigned long)st.st_uid);
    printf("gid: %lu\n", (unsigned long)st.st_gid);

    printf("size: %lld bytes\n", (long long)st.st_size);
    print_time("atime", st.st_atime);
    print_time("mtime", st.st_mtime);
    print_time("ctime", st.st_ctime);
}



int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_or_dir> [more...]\n", argv[0]);
        return 1;
    }
    while (--argc > 0) {
        fsize(argv[argc]);
    }
    return 0;
}
