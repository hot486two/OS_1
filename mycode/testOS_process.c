#include <testOS.h>

extern TestOS_mem_mng memmng;
TestOS_process_mng processmng;

#define STARTUSRCPSR    0x68000050

int process_create(void(*startFunc)(void))
{
    int process_idx = 0;
    unsigned int stack_top = 0;

    processmng.max_process_id++;
    process_idx = processmng.max_process_id;

    if(process_idx > MAXPROCESSNUM){
        return -1;
    }

    stack_top = memmng.alloc();

    if(stack_top == 0){
        return -2;
    }

    processmng.free_process_pool[process_idx].context_spsr = STARTUSRCPSR;
    processmng.free_process_pool[process_idx].context_sp = stack_top;
    processmng.free_process_pool[process_idx].context_pc = (unsigned int)startFunc;

    return process_idx;    
}

void process_init(void)
{
    int i;
    for(i = 0 ; i < MAXPROCESSNUM ; i++){
        processmng.free_process_pool[i].context_spsr = 0x00;
        memset(processmng.free_process_pool[i].context, 0, sizeof(unsigned int) * CONTEXTNUM);
        processmng.free_process_pool[i].context_sp = 0x00;
        processmng.free_process_pool[i].context_lr = 0x00;
        processmng.free_process_pool[i].context_pc = 0x00;
    }

    processmng.max_process_id = -1;

    processmng.init = process_init;
    processmng.create = process_create;
}
