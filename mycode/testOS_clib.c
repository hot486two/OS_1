#include <testOS.h>

extern TestOS_free_process *testOS_current;

int testOS_ipc_send(int ipcnum, int data)
{
    return ipc_send(ipcnum, data);
}

int testOS_ipc_get(int ipcnum)
{
    int ret_value = 0;
    int data = 0;
    while(1){
        ret_value = ipc_get(ipcnum, &data);
        if(ret_value == 0){
            return data;
        }else if(ret_value == -1){
            return ret_value;
        }else{
            call_scheduler();
        }
    }
}

int testOS_sem_p(int semnum)
{
    int ret_value = 0;
    while(1){
        ret_value = sem_p(semnum);
        if(ret_value == 0){
            return 0;
        }else if(ret_value == -1){
            return -1;
        }else{
            call_scheduler();
        }
    }
}

int testOS_sem_v(int semnum)
{
    return sem_v(semnum);
}

int testOS_open(int drvnum, int mode)
{
    return open(drvnum, mode);
}

int testOS_close(int drvnum)
{
    return close(drvnum);
}

int testOS_read(int drvnum, void *buf, int size)
{
    int ret_value = 0;
    while(1){
        ret_value = read(drvnum, buf, size);
        if(ret_value >= 0){
            return ret_value;
        }else if(ret_value == -1){
            return -1;
        }else{
            call_scheduler();
        }
    }
}

int testOS_write(int drvnum, void *buf, int size)
{
    return write(drvnum, buf, size);
}
