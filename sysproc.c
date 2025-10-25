#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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

extern int vgaprint(void);

int
sys_vgaprint(void)
{
	unsigned short * vga_buf = (unsigned short*)P2V(0xB8000);
//	int character = -1;
	int x=0, y=0,left_byte =-1, right_byte= -1;

//	unsigned char bytes2[4] = {'\0','\0','\0','\0'};
//	char* bytes_2_ptr = (char *)&bytes2[0]; 
//	vga_buf[1] = 0xF041;
//	vga_buf[2] = 0x0F42;

	argint(0,&x);
	argint(1,&y);
	argint(2,&left_byte);
	argint(3,&right_byte);

	int full_short = (left_byte << 8) | right_byte;
	int ROW = 25;
	int COLUMN = 80;
	int pos = x*COLUMN + y;
	
//	unsigned short *sptr = (unsigned short*) &bytes2[0];
	if(x >= ROW || y >= COLUMN)
	{
		return -1;
	}

	vga_buf[pos] = (unsigned short) full_short;

	return full_short;

}
