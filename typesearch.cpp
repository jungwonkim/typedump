#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int SEARCH_MORE   = 64;
int SEARCH_BUFFER = 2048;

template <typename T>
void search_type(int fd, T* search, int count) {
  T* buffer = (T*) malloc(SEARCH_BUFFER * sizeof(T));
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
      int all_match = 1;
      for (int i = 0; i < count; i++) {
        if (p[i] == search[i]) {
          if (all_match && i == count - 1) {
            size_t found = total_readed + (p - buffer) * sizeof(T);
            printf("[0x%lx, %lu] ", found, found);
            for (int j = 0; j < i + SEARCH_MORE; j++) printf("%d ", p[j]);
            printf("\n");
          }
        } else {
          all_match = 0;
          break;
        }
      }
    }
    total_readed += readed;
  }
  free(buffer);
}

int main(int argc, char** argv) {
  if (argc < 4) {
    fprintf(stderr, "Usage:\n typesearch file type[char | (u)int | (u)long | pointer | float | double] search_values\n");
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

  size_t search_len = argc - 3;

  if (strcmp(type, "int") == 0) {
    int *search = (int*) malloc(search_len * sizeof(int));
    for (int i = 0; i < argc - 3; i++) search[i] = atoi(argv[i + 3]);
    search_type<int>(fd, search, search_len);
  } else if (strcmp(type, "uint") == 0) {
    unsigned int *search = (unsigned int*) malloc(search_len * sizeof(unsigned int));
    for (int i = 0; i < argc - 3; i++) search[i] = atoi(argv[i + 3]);
    search_type<unsigned int>(fd, search, search_len);
  }

  return 0;
}

