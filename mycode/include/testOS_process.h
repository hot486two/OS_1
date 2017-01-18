#ifndef _testOS_PROCESS
#define _testOS_PROCESS

#define MAXPROCESSNUM  40
#define CONTEXTNUM  13

typedef struct _testOS_free_process {
    unsigned int context_spsr;          
    unsigned int context[CONTEXTNUM]; 
    unsigned int context_sp;          
    unsigned int context_lr;         
    unsigned int context_pc;        
} TestOS_free_process;

typedef struct _testOS_process_mng {
    TestOS_free_process free_process_pool[MAXPROCESSNUM];

    int max_process_id;

    void (*init)(void);
    int (*create)(void(*startFunc)(void));
} TestOS_process_mng;

void process_init(void);
int process_create(void(*startFunc)(void));

#endif
