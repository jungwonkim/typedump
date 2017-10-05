#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void dump_char(int fd, off_t off, size_t len) {
    char* data = new char[len];
    size_t nbyte = len * sizeof(char);
    pread(fd, data, nbyte, off);
    for (size_t i = 0; i < len; i++) printf("[%7lu] [%10d]\n", i, data[i]);
    delete[] data;
}

void dump_int(int fd, off_t off, size_t len) {
    int* data = new int[len];
    size_t nbyte = len * sizeof(int);
    pread(fd, data, nbyte, off);
    for (size_t i = 0; i < len; i++) printf("[%7lu] [%10d]\n", i, data[i]);
    delete[] data;
}

void dump_float(int fd, off_t off, size_t len) {
    float* data = new float[len];
    size_t nbyte = len * sizeof(float);
    pread(fd, data, nbyte, off);
    for (size_t i = 0; i < len; i++) printf("[%7lu] [%10f]\n", i, data[i]);
    delete[] data;
}

void dump_double(int fd, off_t off, size_t len) {
    double* data = new double[len];
    size_t nbyte = len * sizeof(double);
    pread(fd, data, nbyte, off);
    for (size_t i = 0; i < len; i++) printf("[%7lu] [%10lf]\n", i, data[i]);
    delete[] data;
}

int main(int argc, char** argv) {
    if (argc < 5) {
        fprintf(stderr, "usage: $ %s path mode off len\n", argv[0]);
        return 1;
    }

    char* path = argv[1];
    char* mode = argv[2];
    off_t off = atol(argv[3]);
    size_t len = atol(argv[4]);

    printf("[intdump] path[%s] mode[%s] off[%ld] len[%lu]\n", path, mode, off, len);

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open file");
        return 1;
    }

    if (strcmp(mode, "char") == 0)          dump_char(fd, off, len);
    else if (strcmp(mode, "int") == 0)      dump_int(fd, off, len);
    else if (strcmp(mode, "float") == 0)    dump_float(fd, off, len);
    else if (strcmp(mode, "double") == 0)   dump_double(fd, off, len);

    close(fd);

    return 0;
}

