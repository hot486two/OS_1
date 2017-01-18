#include <testOS.h>
extern TestOS_msg_mng msgmng;
extern TestOS_mem_mng memmng;
extern TestOS_drv_mng drvmng;

unsigned int testOS_syscallvec[SYSCALLNUM];

int sys_mysyscall(int a, int b, int c)
{
    printf("My Systemcall - %d , %d , %d\n", a, b, c);
    return 333;
}

int sys_mysyscall4(int a, int b, int c, int d)
{
    printf("My Systemcall4 - %d , %d , %d , %d\n", a, b, c, d);
    return 3413;
}

int sys_ipcsend(int ipcnum, int data)
{
    return msgmng.ipc_send(ipcnum, data);
}

int sys_ipcget(int ipcnum, int *data)
{
    return msgmng.ipc_get(ipcnum, data);
}

int sys_semp(int semnum)
{
    return msgmng.sem_p(semnum);
}
int sys_semv(int semnum)
{
    return msgmng.sem_v(semnum);
}
int sys_open(int drvnum, int mode)
{
    if(drvnum > DRVLIMIT || drvnum < 0){
        return -1;
    }

    if(drvmng.free_drv_pool[drvnum].usecount < 0){
        return -1;
    }

    drvmng.free_drv_pool[drvnum].usecount++;

    return drvmng.free_drv_pool[drvnum].testOS_fops->open(drvnum, mode); 
}

int sys_close(int drvnum)
{
    if(drvnum > DRVLIMIT || drvnum < 0){
        return -1;
    }

    drvmng.free_drv_pool[drvnum].usecount--;

    return drvmng.free_drv_pool[drvnum].testOS_fops->close(drvnum);
}

int sys_read(int drvnum, void *buf, int size)
{
    if(drvnum > DRVLIMIT || drvnum < 0){
        return -1;
    }

    return drvmng.free_drv_pool[drvnum].testOS_fops->read(drvnum, buf, size);
}

int sys_write(int drvnum, void *buf, int size)
{
     if(drvnum > DRVLIMIT || drvnum < 0){
        return -1;
    }

    return drvmng.free_drv_pool[drvnum].testOS_fops->write(drvnum, buf, size);
}
void syscall_init(void)
{
    testOS_syscallvec[SYS_MYSYSCALL] = (unsigned int)sys_mysyscall; 
    testOS_syscallvec[SYS_MYSYSCALL4] = (unsigned int)sys_mysyscall4; 
    testOS_syscallvec[SYS_IPCSEND] = (unsigned int)sys_ipcsend; 
    testOS_syscallvec[SYS_IPCGET] = (unsigned int)sys_ipcget;
    testOS_syscallvec[SYS_SEMP] = (unsigned int)sys_semp; 
    testOS_syscallvec[SYS_SEMV] = (unsigned int)sys_semv;  
    testOS_syscallvec[SYS_OPEN] = (unsigned int)sys_open;
    testOS_syscallvec[SYS_CLOSE] = (unsigned int)sys_close;
    testOS_syscallvec[SYS_READ] = (unsigned int)sys_read;
    testOS_syscallvec[SYS_WRITE] = (unsigned int)sys_write;

}
