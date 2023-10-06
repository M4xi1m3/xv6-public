// Test the lseek syscall

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define MAX 512
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

int main(int argc, char *argv[])
{
  if (argc != 4) {
    printf(2, "usage: %s file o n\n", argv[0]);
    exit();
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    printf(2, "%s: cannot open %s\n", argv[0], argv[1]);
    exit();
  }

  int o = atoi(argv[2]);
  int n = atoi(argv[3]);
  int ref = (o >= 0) ? SEEK_SET : SEEK_END;

  if (lseek(fd, o, ref) < 0) {
    printf(2, "%s: cannot lseek %d from %s\n", argv[0], o, (ref == SEEK_SET) ? "SEEK_SET" : "SEEK_END");

    if (close(fd) < 0)
      printf(2, "%s: cannot open %s\n", argv[0], argv[1]);

    exit();
  }
  printf(2, "%s: %s fd=%d o=%d ref=%d\n", argv[0], argv[1], fd, o, ref);

  int r = 0;
  char buf[MAX];

  while(n > 0 && (r = read(fd, buf, MIN(n, sizeof(buf)))) > 0)
  {
    write(1, buf, r);
    n -= r;
  }

  if (close(fd) < 0)
  {
    printf(2, "%s: cannot open %s\n", argv[0], argv[1]);
    exit();
  }

  exit();
}
