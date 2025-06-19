#include "kernel/types.h"
#include "user/user.h"

int main() {
  int fd[2];
  int fd1[2];
  pipe(fd);
  pipe(fd1);
  char buf[1];
  char buf1[1];
  
  int pid = fork();

  if (0 > pid) {
    printf("fork error\n");
    exit(1);
  } else if (0 == pid) {
    close(fd[1]);
    read(fd[0], buf, 1);
    close(fd[0]);
    printf("%d: received ping\n", getpid());
    close(fd1[0]);
    write(fd1[1], buf, 1);
    close(fd1[1]);
  } else {
    close(fd[0]);
    write(fd[1], "x", 1); 
    close(fd[1]);
    close(fd1[1]);
    read(fd1[0], buf1, 1);
    close(fd1[0]);
    printf("%d: received pong\n", getpid());
  }

  exit(0);
}
