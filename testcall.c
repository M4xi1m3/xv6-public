// Test the lseek syscall

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void test() {
    printf(1, "Test called\n");
}

int main(int argc, char *argv[])
{
  printf(1, "start\n");

  call(test);

  printf(1, "end\n");

  exit();
}
