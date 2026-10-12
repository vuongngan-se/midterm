#include "ls.h"
#include "print.h"

int opt_all = 0;
int opt_long = 0;

void list_directory(const char *dirpath) {
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror(dirpath);
        return;
    }

    struct dirent *entry;
    FileInfo files[1024];
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (!opt_all && entry->d_name[0] == '.') {
            continue;
        }

        files[count].name = strdup(entry->d_name);
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, entry->d_name);
        files[count].path = strdup(fullpath);

        if (lstat(fullpath, &files[count].st) != 0) {
            perror(fullpath);
        }
        count++;
    }
    closedir(dir);

    qsort(files, count, sizeof(FileInfo), cmp_name);

    if (opt_long) {
        print_long(files, count);
    } else {
        print_simple(files, count);
    }

    for (int i = 0; i < count; i++) {
        free(files[i].name);
        free(files[i].path);
    }
}

int main(int argc, char *argv[]) {
    int ch;
    while ((ch = getopt(argc, argv, "al")) != -1) {
        switch (ch) {
            case 'a':
                opt_all = 1;
                break;
            case 'l':
                opt_long = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-al] [file ...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    argc -= optind;
    argv += optind;

    if (argc == 0) {
        list_directory(".");
    } else {
        for (int i = 0; i < argc; i++) {
            list_directory(argv[i]);
        }
    }
    return 0;
}
