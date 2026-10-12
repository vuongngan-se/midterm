#include "print.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_simple(FileInfo *files, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s\n", files[i].name);
    }
}

void print_long(FileInfo *files, int count) {
    for (int i = 0; i < count; i++) {
        struct passwd *pw = getpwuid(files[i].st.st_uid);
        struct group  *gr = getgrgid(files[i].st.st_gid);
        char time_buf[32];

        strftime(time_buf, sizeof(time_buf), "%b %e %H:%M", localtime(&files[i].st.st_mtime));

        printf("%10o %2ld %s %s %8lld %s %s\n",
               (unsigned int)files[i].st.st_mode,
               (long)files[i].st.st_nlink,
               pw ? pw->pw_name : "unknown",
               gr ? gr->gr_name : "unknown",
               (long long)files[i].st.st_size,
               time_buf,
               files[i].name);
    }
}
