// Memory driver

#include "types.h"
#include "defs.h"
#include "param.h"
#include "traps.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"

int
drvmemread(struct inode *ip, char *dst, uint off, int n)
{
  switch (ip->minor)
  {
    case 0:
      return 0;
    case 1:
      memset(dst, 0, n);
      return n;
    case 2:
      if (off < EXTMEM || off >= PHYSTOP)
        return -1;
      if (off + n >= PHYSTOP)
        n = off + n - PHYSTOP;
      memmove(dst, P2V(off), n);
      return n;
    case 3:
      return kmemread(dst, off, n);
    default:
      return -1;
  }
}

int
drvmemwrite(struct inode *ip, char *buf, uint off, int n)
{
  switch (ip->minor)
  {
    case 0:
    case 1:
      return n;
    case 2:
      if (off < EXTMEM || off >= PHYSTOP)
        return -1;
      if (off + n >= PHYSTOP)
        n = off + n - PHYSTOP;
      memmove(P2V(off), buf, n);
      return n;
    default:
      return -1;
  }
}

void
drvmeminit(void)
{
  devsw[DRVMEM].write = drvmemwrite;
  devsw[DRVMEM].read = drvmemread;
}