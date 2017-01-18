#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <pxa255.h>
#include <time.h>
#include <gpio.h>
#include <stdio.h>
#include <string.h>
#include "testOS_memory.h"
#include "testOS_process.h"
#include "testOS_user.h"
#include "testOS_sys.h"
#include "syscalltbl.h"
#include "testOS_msg.h"
#include "testOS_drv.h"

#define IRQNUM	64
#define IRQ0	0
#define IRQ1	1
#define IRQ2	2
#define IRQ3	3
#define IRQ4	4
#define IRQ5	5
#define IRQ6	6
#define IRQ7	7
#define IRQ8	8
#define IRQ63	63


void testOS_init(void);
void testOS_user(void);

#endif
