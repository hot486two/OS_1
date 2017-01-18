#ifndef _testOS_LIB
#define _testOS_LIB

extern int mysyscall(int, int, int);
extern int mysyscall4(int, int, int, int);

extern int ipc_send(int, int);
extern int ipc_get(int, int*);

extern int sem_p(int);
extern int sem_v(int);

extern int open(int, int);
extern int close(int);
extern int read(int, void*, int);
extern int write(int, void*, int);


extern void call_scheduler(void);

int testOS_ipc_send(int,int);
int testOS_ipc_get(int);

int testOS_sem_p(int);
int testOS_sem_v(int);

int testOS_open(int, int);
int testOS_close(int);	
int testOS_read(int, void*, int);
int testOS_write(int, void*, int);


#endif
