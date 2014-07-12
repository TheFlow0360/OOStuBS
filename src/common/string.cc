#include <common/string.h>

int strcmp(const char* a, const char* b){
  while(*a && *b){
    if(*a<*b)
      return -1;
    if(*a>*b)
      return 1;
    a++;
    b++;
  }
  return 0;
}

int strncmp(const char* a, const char* b, size_t n){
  while(*a && *b && n--){
    if(*a<*b)
      return -1;
    if(*a>*b)
      return 1;
    a++;
    b++;
  }
  return 0;
}
