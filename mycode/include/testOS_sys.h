#ifndef _testOS_SYS
#define _testOS_SYS

#include <syscalltbl.h>

//#define SYSCALLNUM 255

void syscall_init(void);


int sys_mysyscall(int, int, int);
int sys_mysyscall4(int, int, int, int);

int sys_ipcsend(int,int);
int sys_ipcget(int,int*);

int sys_semp(int);
int sys_semv(int);

int sys_open(int, int);
int sys_close(int);
int sys_read(int, void*, int);
int sys_write(int, void*, int);


extern void sys_scheduler(void);

#endif
