#ifndef DISKSCAPE_H
#define DISKSCAPE_H

typedef struct {
    char name[1024];
    long long int size;
} Entry;

long long int disk_size(const char *path);
void scan_dir(const char *path, Entry *entries, int *count);
int compare(const void *a, const void *b);
void format_size(long long int size, char *buf);
void print_bar(int i, int count, Entry *entries);

#endif