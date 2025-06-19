#include "kernel/types.h"
#include "user/user.h"

int main() {
  printf("Current uptime: %d\n", uptime());
  return 0;
}
