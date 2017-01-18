#ifndef _testOS_MEM
#define _testOS_MEM

#define MAXMEMBLK 40


typedef struct _testOS_mem_block {
    unsigned int block_start_addr;
    unsigned int block_end_addr;
    int is_used;
} TestOS_mem_block;

typedef struct _testOS_mem_mng {
    TestOS_mem_block free_mem_pool[MAXMEMBLK];

    void (*init)(void);
    unsigned int (*alloc)(void);
} TestOS_mem_mng;

void mem_init(void);
unsigned int mem_alloc(void);

#endif
