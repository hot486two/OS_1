#include <testOS.h>

extern TestOS_process_mng processmng;
extern TestOS_msg_mng msgmng;
void user_process_1(void)
{
    int a, b, c;

    a = 0;
    b = 1;
    c = a + b;
    while(1){
        printf("process1 - a:%p\tb:%p\tc:%p\n", &a, &b, &c);
	printf("before call Scheduler\n");
	call_scheduler();
	printf("after Scheduler\n");
        msleep(1000);
    }
}

void user_process_2(void)
{
    int a, b, c;

    a = 0;
    b = 2;
    c = a + b;
    while(1){
        printf("process2 - a:%p\tb:%p\tc:%p\n", &a, &b, &c);

        printf("IPC Count is %d\n", a);
        if (a == 3){
            testOS_ipc_send(2, 342);
            a = 1;
            printf("IPC send!!!\n");
        }
        a++;
        msleep(1000);
    }
}

void user_process_3(void)
{
    int a, b, c;

    a = 0;
    b = 3;
    c = a + b;
    while(1){
        c = testOS_ipc_get(2);
        printf("PROCESS3 - a:%p\tb:%p\tc:%p\n", &a, &b, &c);
        printf("IPC get!!!! ---> %d\n", c);

        msleep(1000);
    }
}
void user_process_4(void)
{
    int a, b, c;

    a = 1;
    b = 2;
    c = a + b;

    while(1){
        testOS_sem_p(5);
        printf("process4 enter critical section SEMAPHORE\n");
        printf("process4 - a:%p\tb:%p\tc:%p\n", &a, &b, &c);
        msleep(2000);
        testOS_sem_v(5);
        printf("process4 out critical section SEMAPHORE\n");
        msleep(4000);
    }
}

void user_process_5(void)
{
    int a, b, c;

    a = 1;
    b = 2;
    c = a + b;

    while(1){
        testOS_sem_p(5);
        printf("process5 enter critical section SEMAPHORE\n");
        printf("process5 - a:%p\tb:%p\tc:%p\n", &a, &b, &c);
        msleep(2000);
        testOS_sem_v(5);
        printf("process5 out critical section SEMAPHORE\n");
        msleep(4000);
    }
}

void user_process_6(void)
{
    int a, b, c;

    a = 1;
    b = 2;
    c = a + b;

    while(1){
        testOS_sem_p(5);
        printf("process6 enter critical section SEMAPHORE\n");
        printf("process6 - a:%p\tb:%p\tc:%p\n", &a, &b, &c);
        msleep(2000);
        testOS_sem_v(5);
        printf("process6 out critical section SEMAPHORE\n");
        msleep(4000);
    }
}
void testOS_user(void)
{
    processmng.create(user_process_1);
    processmng.create(user_process_2);
    processmng.create(user_process_3);
    processmng.create(user_process_4);
    processmng.create(user_process_5);
    processmng.create(user_process_6);
    msgmng.sem_init(5,2);
}
