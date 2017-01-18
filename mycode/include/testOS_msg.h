#ifndef _testOS_MSG
#define _testOS_MSG

#define MAXMSG 255

#define ITCSTART 0
#define ITCEND 99
#define SEMSTART 100
#define SEMEND 199

typedef struct _testOS_free_msg {
    int data;
    int flag;
} TestOS_free_msg;

typedef struct _testOS_msg_mng {
    TestOS_free_msg free_msg_pool[MAXMSG];
    
    void (*init)(void);
    int (*ipc_send)(int, int);
    int (*ipc_get)(int, int*);
    int (*sem_init)(int, int);
    int (*sem_p)(int);
    int (*sem_v)(int);

} TestOS_msg_mng;

void msg_init(void);
int msg_ipc_send(int, int);
int msg_ipc_get(int, int*);

int msg_sem_init(int,int);
int msg_sem_p(int);
int msg_sem_v(int);



#endif
