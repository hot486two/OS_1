#include <testOS.h>

extern TestOS_mem_mng memmng;
extern TestOS_process_mng processmng;
TestOS_free_process *testOS_current;	//현재 동작하는 프로세스의 PCB
TestOS_free_process *testOS_next;		//다음에 실행될 프로세스의 PCB
TestOS_free_process dummyTCB;		//커널 부팅후 쓰레기 값 처리를 위한 변수
int testOS_current_index;			//현재 실행중인 프로세스의 인덱스

int (*testOS_irq_vector[IRQNUM])(void);

void scheduler(void)
{
    testOS_current_index++;
    testOS_current_index %= (processmng.max_process_id + 1);
    testOS_next = &processmng.free_process_pool[testOS_current_index];
    testOS_current = testOS_next;
}

void swiHandler(unsigned int syscallnum)
{
    printf("system call %d\n", syscallnum);
}


void os_timer_init(void)
{
    ICCR = 0x01;

    ICMR |= (1 << 27);
    ICLR &= ~(1 << 27);

    OSCR = 0;
    OSMR1 = OSCR + 3686400;

    OSSR = OSSR_M1;
}

void os_timer_start(void)
{
    OIER |= (1<<1);
    OSSR = OSSR_M1;
}


void irq_enable(void)
{
    __asm__("msr    cpsr_c,#0x40|0x13");
}

void irq_disable(void)
{
    __asm__("msr    cpsr_c,#0xc0|0x13");
}
int sched_init(void)
{
    if(processmng.max_process_id < 0){
        return -1;
    }

    testOS_current = &dummyTCB;
    testOS_next = &processmng.free_process_pool[0];
    testOS_current_index = -1;

    return 0;
}	
void irqHandler(void)
{
    if( (ICIP&(1<<27)) != 0 ){
        OSSR = OSSR_M1;
        OSMR1 = OSCR + 3686400;

        scheduler();
    } 
}

void testOS_init(void)
{
    mem_init();
    process_init();
    msg_init();
    syscall_init();

    os_timer_init();
    os_timer_start();
}

int main(void)
{
    testOS_init();
    testOS_user();

    if(sched_init() < 0){
        printf("Kernel Pannic!\n");
        return -1;
    }
    

    int i;
    for(i = 0 ; i <= processmng.max_process_id ; i++){
        printf("PCB : process%d - init PC(%p) \t init SP(%p)\n", i+1, processmng.free_process_pool[i].context_pc, processmng.free_process_pool[i].context_sp);
    }

    printf("REAL func process1 : %p\n", user_process_1);
    printf("REAL func process2 : %p\n", user_process_2);
    printf("REAL func process3 : %p\n", user_process_3);
    irq_enable();
    while(1){
        msleep(1000);
    }

    return 0;
}
