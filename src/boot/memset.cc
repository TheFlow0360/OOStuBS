#include <stddef.h>

extern "C" void memset(void *s, int c, size_t n){
  for(size_t i=0;i<n;i++)
    reinterpret_cast<char*>(s)[i]=c;
}
