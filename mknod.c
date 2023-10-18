// Create a device inode

#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  if (argc != 4) {
    printf(2, "usage: %s name major minor\n", argv[0]);
    exit();
  }

  int major = atoi(argv[2]);
  int minor = atoi(argv[3]);

  if (mknod(argv[1], major, minor) < 0) {
    printf(2, "%s: failed to create %s\n", argv[0], argv[1]);
    exit();
  }

  exit();
}
