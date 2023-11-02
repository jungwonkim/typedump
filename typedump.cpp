#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void dump_char(int fd, off_t off, size_t len) {
  char* data = new char[len];
  size_t nbyte = len * sizeof(char);
  pread(fd, data, nbyte, off);
  for (size_t i = 0; i < len; i++) printf("[%8lu] [%16d] [%c]\n", i, data[i], data[i]);
  delete[] data;
}

void dump_int(int fd, off_t off, size_t len) {
  int* data = new int[len];
  size_t nbyte = len * sizeof(int);
  pread(fd, data, nbyte, off);
  for (size_t i = 0; i < len; i++) printf("[%8lu] [%16d]\n", i, data[i]);
  delete[] data;
}

void dump_uint(int fd, off_t off, size_t len) {
  unsigned int* data = new unsigned int[len];
  size_t nbyte = len * sizeof(unsigned int);
  pread(fd, data, nbyte, off);
  for (size_t i = 0; i < len; i++) printf("[%8lu] [%16u]\n", i, data[i]);
  delete[] data;
}

void dump_long(int fd, off_t off, size_t len) {
  long* data = new long[len];
  size_t nbyte = len * sizeof(long);
  pread(fd, data, nbyte, off);
  for (size_t i = 0; i < len; i++) printf("[%8lu] [%32ld]\n", i, data[i]);
  delete[] data;
}

void dump_ulong(int fd, off_t off, size_t len) {
  unsigned long* data = new unsigned long[len];
  size_t nbyte = len * sizeof(unsigned long);
  pread(fd, data, nbyte, off);
  for (size_t i = 0; i < len; i++) printf("[%8lu] [%32lu]\n", i, data[i]);
  delete[] data;
}

void dump_pointer(int fd, off_t off, size_t len) {
  void** data = new void*[len];
  size_t nbyte = len * sizeof(void*);
  pread(fd, data, nbyte, off);
  for (size_t i = 0; i < len; i++) printf("[%8lu] [%32p]\n", i, data[i]);
  delete[] data;
}

void dump_float(int fd, off_t off, size_t len) {
  float* data = new float[len];
  size_t nbyte = len * sizeof(float);
  pread(fd, data, nbyte, off);
  for (size_t i = 0; i < len; i++) printf("[%8lu] [%16f]\n", i, data[i]);
  delete[] data;
}

void dump_double(int fd, off_t off, size_t len) {
  double* data = new double[len];
  size_t nbyte = len * sizeof(double);
  pread(fd, data, nbyte, off);
  for (size_t i = 0; i < len; i++) printf("[%8lu] [%16lf]\n", i, data[i]);
  delete[] data;
}

int main(int argc, char** argv) {
  if (argc < 5) {
    fprintf(stderr, "Usage:\n typedump file type[char | (u)int | (u)long | pointer | float | double] offset length\n");
    return 1;
  }

  char* file = argv[1];
  char* type = argv[2];
  off_t off = atol(argv[3]);
  size_t len = atol(argv[4]);

  printf("[typedump] file[%s] type[%s] offset[%ld] length[%lu]\n", file, type, off, len);

  int fd = open(file, O_RDONLY);
  if (fd == -1) {
    perror("open file");
    return 1;
  }

  if (strcmp(type, "char") == 0)          dump_char(fd, off, len);
  else if (strcmp(type, "int") == 0)      dump_int(fd, off, len);
  else if (strcmp(type, "uint") == 0)     dump_uint(fd, off, len);
  else if (strcmp(type, "long") == 0)     dump_long(fd, off, len);
  else if (strcmp(type, "ulong") == 0)    dump_ulong(fd, off, len);
  else if (strcmp(type, "pointer") == 0)  dump_pointer(fd, off, len);
  else if (strcmp(type, "float") == 0)    dump_float(fd, off, len);
  else if (strcmp(type, "double") == 0)   dump_double(fd, off, len);

  close(fd);

  return 0;
}

