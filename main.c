#include <stdio.h>
#include <stdlib.h>

#include "diskscape.h"

int main(int argc, char *argv[]) {
    Entry entries[256];
    int count = 0;
    scan_dir(argv[1], entries, &count);
    qsort(entries, count, sizeof(Entry), compare);
    for (int i = 0; i < count; i++) {
        printf("%s: %lld bytes\n", entries[i].name, entries[i].size);
    }
    return 0;
}