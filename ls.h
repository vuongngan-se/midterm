#ifndef _LS_H_
#define _LS_H_

#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char *name;
    char *path;
    struct stat st;
} FileInfo;

extern int opt_all;
extern int opt_long;

int cmp_name(const void *a, const void *b);
int cmp_mtime(const void *a, const void *b);

#endif /* _LS_H_ */
