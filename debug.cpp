#include <stdio.h>
#ifdef __DEBUG__
#define DEBUG(x) printf(x);
#else
#define DEBUG(x)
#endif

int main(void) {
  DEBUG("Hello World!\n");
  return 0;
}
