#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void gen_char(int fd, off_t off, size_t len) {
    char* data = new char[len];
    size_t nbyte = len * sizeof(char);
    for (size_t i = 0; i < len; i++) data[i] = off + i;
    write(fd, data, nbyte);
    delete[] data;
}

void gen_int(int fd, off_t off, size_t len) {
    int* data = new int[len];
    size_t nbyte = len * sizeof(int);
    for (size_t i = 0; i < len; i++) data[i] = off + i;
    write(fd, data, nbyte);
    delete[] data;
}

void gen_float(int fd, off_t off, size_t len) {
    float* data = new float[len];
    size_t nbyte = len * sizeof(float);
    for (size_t i = 0; i < len; i++) data[i] = off + i;
    write(fd, data, nbyte);
    delete[] data;
}

void gen_double(int fd, off_t off, size_t len) {
    double* data = new double[len];
    size_t nbyte = len * sizeof(double);
    for (size_t i = 0; i < len; i++) data[i] = off + i;
    write(fd, data, nbyte);
    delete[] data;
}

int main(int argc, char** argv) {
    if (argc < 5) {
        fprintf(stderr, "Usage:\n typegen file type[char | int | float | double] offset length\n");
        return 1;
    }

    char* file = argv[1];
    char* type = argv[2];
    off_t off = atol(argv[3]);
    size_t len = atol(argv[4]);

    printf("[typegen] file[%s] type[%s] offset[%ld] length[%lu]\n", file, type, off, len);

    int fd = open(file, O_CREAT | O_WRONLY, 0666);
    if (fd == -1) {
        perror("open file");
        return 1;
    }

    if (strcmp(type, "char") == 0)          gen_char(fd, off, len);
    else if (strcmp(type, "int") == 0)      gen_int(fd, off, len);
    else if (strcmp(type, "float") == 0)    gen_float(fd, off, len);
    else if (strcmp(type, "double") == 0)   gen_double(fd, off, len);

    close(fd);

    return 0;
}

