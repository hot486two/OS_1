#include <syscalltbl.h>

.global mysyscall
mysyscall:
    swi SYS_MYSYSCALL 
    mov pc, lr

.global mysyscall4
mysyscall4:
    swi SYS_MYSYSCALL4
    mov pc, lr

.global ipc_send
ipc_send:
    swi SYS_IPCSEND
    mov pc, lr

.global ipc_get
ipc_get:
    swi SYS_IPCGET
    mov pc, lr

.global sem_p
sem_p:
    swi SYS_SEMP
    mov pc, lr

.global sem_v
sem_v:
    swi SYS_SEMV
    mov pc, lr

.global open
open:
    swi SYS_OPEN
    mov pc, lr

.global close
close:
    swi SYS_CLOSE
    mov pc, lr

.global read
read:
    swi SYS_READ
    mov pc, lr

.global write
write:
    swi SYS_WRITE
    mov pc, lr

.global call_scheduler
call_scheduler:
    swi SYS_CALLSCHED
    mov pc, lr
