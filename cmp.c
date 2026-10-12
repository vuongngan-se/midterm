#include "ls.h"

int cmp_name(const void *a, const void *b) {
    const FileInfo *fa = (const FileInfo *)a;
    const FileInfo *fb = (const FileInfo *)b;
    return strcmp(fa->name, fb->name);
}

int cmp_mtime(const void *a, const void *b) {
    const FileInfo *fa = (const FileInfo *)a;
    const FileInfo *fb = (const FileInfo *)b;
    if (fb->st.st_mtime > fa->st.st_mtime) return 1;
    if (fb->st.st_mtime < fa->st.st_mtime) return -1;
    return cmp_name(a, b);
}
