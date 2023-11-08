#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_call(void)
{
  uint handler;

  if (argint(0, (int*) &handler) < 0)
    return -1;
  
  struct proc* p = myproc();
  
  p->tf->eip = handler;

  return 0;
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// return the UTC date
int
sys_date(void)
{

  struct rtcdate* ptr;
  
  // Get the pointer to the struct rtcdate.
  if (argptr(0, (char**) &ptr, sizeof(struct rtcdate)) < 0) {
    return -1;
  }

  // Call the implementation of cmostime
  cmostime(ptr);

  // Everything went well, return 0
  return 0;
}

// Shutdown the system
int
sys_shutdown(void)
{
  // QEMU-specific method
  outw(0x604, 0x2000);
  for(;;);
  
  return 0;
}
