// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *argv[] = { "sh", 0 };

int
main(void)
{
  int pid, wpid;

  if(mkdir("dev") >= 0) {
    mknod("dev/console", 1, 1);
    mknod("dev/null", 2, 0);
    mknod("dev/zero", 2, 1);
    mknod("dev/mem", 2, 2);
    mknod("dev/kmem", 2, 3);
  }

  if(open("dev/console", O_RDWR) < 0){
    mknod("dev/console", 1, 1);
    open("dev/console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  for(;;){
    printf(1, "init: starting sh\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
