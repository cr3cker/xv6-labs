#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: sleep <time>\n");
    exit(1);
  } 

  int arg = atoi(argv[1]);
  sleep(arg);

  exit(0);  
}
