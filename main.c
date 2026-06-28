#include <stdio.h>
#include <stdlib.h>

#include "diskscape.h"

int main(int argc, char *argv[]) {
    Entry entries[256];
    char buf[32];
    int count = 0;
    scan_dir(argv[1], entries, &count);
    qsort(entries, count, sizeof(Entry), compare);
    for (int i = 0; i < count; i++) {
        char buf[32];
        format_size(entries[i].size, buf);
        printf("%-10s ", entries[i].name);
        print_bar(i, count, entries);
        printf("  %s\n", buf);
    }
    return 0;
}