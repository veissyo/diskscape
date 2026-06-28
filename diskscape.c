#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "diskscape.h"

long long int disk_size(const char *path) {
    long long int size = 0;
    char full_path[1024];
    struct stat st;
    DIR* dir = opendir(path);
    if (dir == NULL) return -1;
    struct dirent* ent;
    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;
        snprintf(full_path, sizeof(full_path), "%s/%s", path, ent->d_name);
        lstat(full_path, &st);
        if (S_ISDIR(st.st_mode)) {
            size += st.st_size; 
            size += disk_size(full_path);
        } else if (S_ISREG(st.st_mode)) {
            size += st.st_size;
        }
    }
    closedir(dir);
    return size;
}

void scan_dir(const char *path, Entry *entries, int *count) {
    char full_path[1024];
    DIR* dir = opendir(path);
    if (dir == NULL) return;
    struct dirent* entry;
    struct stat st;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        strcpy(entries->name, entry->d_name);
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        lstat(full_path, &st);
        if (S_ISDIR(st.st_mode)) {
            entries->size = disk_size(full_path);
        }
        else if (S_ISREG(st.st_mode)) {
            entries->size = st.st_size;
        }
        entries++;
        *count += 1;
    }
}

int compare(const void *a, const void *b) {
    const Entry *A = (const Entry *)a;
    const Entry *B = (const Entry *)b;
    if (A->size > B->size) return -1;
    if (A->size < B->size) return 1;
    return 0;
}