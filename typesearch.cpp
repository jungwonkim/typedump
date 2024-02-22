#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int SEARCH_MORE   = 16;
int SEARCH_BUFFER = 2048;

template <typename T>
void search(int fd, T* needles, int count, const char* fmt) {
  T* buffer = (T*) malloc(SEARCH_BUFFER + count * sizeof(T));
  size_t total_readed = 0;
  while (1) {
    int readed = read(fd, buffer, SEARCH_BUFFER);
    if (readed == -1) {
      perror("read file");
      return;
    }
    if (readed == 0) break;
    T* end = buffer + readed / sizeof(T);
    for (T* p = buffer; p < end; p++) {
      for (int i = 0; i < count; i++) {
        if (p[i] == needles[i]) {
          if (i == count - 1) {
            size_t found = total_readed + (p - buffer) * sizeof(T);
            printf("[0x%lx, %lu] ", found, found);
            for (int j = 0; j < i + SEARCH_MORE; j++) printf(fmt, p[j]);
            printf("\n");
          }
        } else break;
      }
    }
    total_readed += readed;
  }
  free(buffer);
}

int main(int argc, char** argv) {
  if (argc < 4) {
    fprintf(stderr, "Usage:\n typesearch file type[char | (u|x)int | (u)long | float | double] search_values\n");
    return 1;
  }

  char* file = argv[1];
  char* type = argv[2];

  if (getenv("SEARCH_MORE"))   SEARCH_MORE   = atoi(getenv("SEARCH_MORE"));
  if (getenv("SEARCH_BUFFER")) SEARCH_BUFFER = atoi(getenv("SEARCH_BUFFER"));

  printf("[typesearch] file[%s] type[%s] $SEARCH_MORE[%d] $SEARCH_BUFFER[%d]\n", file, type, SEARCH_MORE, SEARCH_BUFFER);
  int fd = open(file, O_RDONLY);
  if (fd == -1) {
    perror("open file");
    return 1;
  }

  size_t count = argc - 3;

  if (strcmp(type, "char") == 0) {
    char* needles = new char[count];
    for (int i = 0; i < argc - 3; i++) needles[i] = static_cast<char>(atoi(argv[i + 3]));
    search<char>(fd, needles, count, "%d ");
  } else if (strcmp(type, "int") == 0) {
    int* needles = new int[count];
    for (int i = 0; i < argc - 3; i++) needles[i] = atoi(argv[i + 3]);
    search<int>(fd, needles, count, "%d ");
  } else if (strcmp(type, "uint") == 0) {
    unsigned int* needles = new unsigned int[count];
    for (int i = 0; i < argc - 3; i++) needles[i] = static_cast<unsigned int>(atoi(argv[i + 3]));
    search<unsigned int>(fd, needles, count, "%u ");
  } else if (strcmp(type, "xint") == 0) {
    unsigned int* needles = new unsigned int[count];
    for (int i = 0; i < argc - 3; i++) needles[i] = static_cast<unsigned int>(strtol(argv[i + 3], NULL, 16));
    search<unsigned int>(fd, needles, count, "%x ");
  } else if (strcmp(type, "float") == 0) {
    float* needles = new float[count];
    for (int i = 0; i < argc - 3; i++) needles[i] = static_cast<float>(atof(argv[i + 3]));
    search<float>(fd, needles, count, "%f ");
  } else if (strcmp(type, "double") == 0) {
    double* needles = new double[count];
    for (int i = 0; i < argc - 3; i++) needles[i] = atof(argv[i + 3]);
    search<double>(fd, needles, count, "%lf ");
  } else {
    fprintf(stderr, "Unknown type: %s\n", type);
    return 1;
  }

  return 0;
}

