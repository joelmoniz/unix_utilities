#include <stdio.h>
#include <unistd.h>

int main() { 
  int i=0;
  while(++i<7) {
    printf("."); 
    fflush(stdout);
    sleep(1);
  } 
  return 0;
}
