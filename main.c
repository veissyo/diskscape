#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "diskscape.h"

int main(int argc, char *argv[]) {
    int hide_empty = 0;
    int top = 0;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--hide-empty") == 0) hide_empty = 1;
        if (strcmp(argv[i], "--top") == 0) {
            top = atoi(argv[++i]);
        }
    }
    Entry entries[256];
    char buf[32];
    int count = 0;
    scan_dir(argv[1], entries, &count);
    qsort(entries, count, sizeof(Entry), compare);
    for (int i = 0; i < count; i++) {
        char buf[32];
        format_size(entries[i].size, buf);
        if (hide_empty && entries[i].size == 0) continue;
        printf("%-10s ", entries[i].name);
        print_bar(i, count, entries);
        printf("  %s\n", buf);
        if (top > 0 && i >= top - 1) break;
    }
    return 0;
}