#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "diskscape.h"
#include <math.h>

long long int disk_size(const char *path) {
    long long int size = 0;
    char full_path[1024];
    struct stat st;
    DIR* dir = opendir(path);
    if (dir == NULL) return -1;
    struct dirent* ent;
    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;
        if (ent->d_name[0] == '.') continue;
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
        if (entry->d_name[0] == '.') continue;
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

void format_size(long long int size, char *buf) {
    if (size < 1024) {
        sprintf(buf, "%lld bytes", size);
    }
    else if (size < 1024 * 1024) {
        sprintf(buf, "%.2f KB", (float)size / 1024);
    }
    else if (size < 1024 * 1024 * 1024) {
        sprintf(buf, "%.2f MB", (float)size / (1024 * 1024));
    }
    else {
        sprintf(buf, "%.2f GB", (float)size / (1024 * 1024 * 1024));
    }
}

void print_bar(int i, int count, Entry *entries)  {
    int color;
    if (i < count / 3) color = 31;
    else if (i < 2 * count / 3) color = 33;
    else color = 32;
    double log_max = log((double)entries[0].size + 1);
    double log_cur = log((double)entries[i].size + 1);
    int filled = (int)(log_cur / log_max * 20);
    printf("\033[%dm", color);
    for (int j = 0; j < filled; j++) printf("▓");
    printf("\033[0m");
    for (int j = filled; j < 20; j++) printf("░");
}