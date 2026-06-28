#include <stdio.h>

long long int disk_size(const char *path);

int main(int argc, char *argv[]) {
    long long int size = disk_size(argv[1]);
    printf("Size: %lld bytes\n", size);
    return 0;
}