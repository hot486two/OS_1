#include <testOS.h>

TestOS_msg_mng msgmng;

int msg_ipc_send(int ipcnum, int data)
{
    if(ipcnum >= MAXMSG || ipcnum < 0){
        return -1;
    }
    msgmng.free_msg_pool[ipcnum].data = data;
    msgmng.free_msg_pool[ipcnum].flag = 1;

    return ipcnum;
}

int msg_ipc_get(int ipcnum, int *data)
{
    if(ipcnum >= MAXMSG || ipcnum < 0){
        return -1;
    }

    if(msgmng.free_msg_pool[ipcnum].flag == 0){
        return -2;
    }

    *data = msgmng.free_msg_pool[ipcnum].data;
    msgmng.free_msg_pool[ipcnum].flag = 0;
    msgmng.free_msg_pool[ipcnum].data = 0;

    return 0;
}
int msg_sem_init(int semnum, int s)
{
    semnum += SEMSTART;

    if(semnum > SEMEND || semnum < SEMSTART){
        return -1;
    }

    msgmng.free_msg_pool[semnum].flag = s;

    return 0;
}

int msg_sem_p(int semnum)
{
    semnum += SEMSTART;

    if(semnum > SEMEND || semnum < SEMSTART){
        return -1;
    }

    if(msgmng.free_msg_pool[semnum].flag <= 0){
        return -2;  
    }

    msgmng.free_msg_pool[semnum].flag--;

    return 0;
}

int msg_sem_v(int semnum)
{
    semnum += SEMSTART;

    if(semnum > SEMEND || semnum < SEMSTART){
        return -1;
    }

    msgmng.free_msg_pool[semnum].flag++;

    return 0;
}

void msg_init(void)
{
    int i;
    for (i = 0 ; i < MAXMSG ; i++){
        msgmng.free_msg_pool[i].data = 0;
        msgmng.free_msg_pool[i].flag = 0;
    }

    msgmng.init = msg_init;
    msgmng.ipc_send = msg_ipc_send;
    msgmng.ipc_get = msg_ipc_get;

    msgmng.sem_init = msg_sem_init;
    msgmng.sem_p = msg_sem_p;
    msgmng.sem_v = msg_sem_v;
}
