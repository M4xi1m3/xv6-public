// Test the lseek syscall

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "signal.h"

void test() {
  printf(1, "Child: Signa handled\n");
  exit();
}

int main(int argc, char *argv[])
{
  printf(1, "start\n");

  signal(test);

  int pid;
  switch(pid = fork())
  {
    case -1:
      printf(2, "Fork error\n");
      exit();
    case 0:
      printf(2, "Child: started");
      for(;;) sleep(1000);
      break;
    default:
      printf(2, "Parent: killing\n");
      kill(pid, SIGUSR1);
      printf(2, "Parent: waiting\n");
      wait();
  }

  exit();
}
