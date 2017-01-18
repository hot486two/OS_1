CC = arm-linux-gcc
LD = arm-linux-ld
OC = arm-linux-objcopy

CFLAGS    = -nostdinc -I. -I./include 
CFLAGS   += -Wall -Wstrict-prototypes -Wno-trigraphs -O0
CFLAGS   += -fno-strict-aliasing -fno-common -pipe -mapcs-32 
CFLAGS   += -mcpu=xscale -mshort-load-bytes -msoft-float -fno-builtin

LDFLAGS   = -static -nostdlib -nostartfiles -nodefaultlibs -p -X -T ./main-ld-script
                
OCFLAGS = -O binary -R .note -R .comment -S

CFILES = testOS.c testOS_memory.c testOS_process.c testOS_user.c testOS_lib.S testOS_sys.c testOS_clib.c testOS_msg.c testOS_drv.c
HFILES = include/testOS_memory.h include/testOS.h include/testOS_process.h include/testOS_user.h include/testOS_lib.h include/testOS_sys.h include/syscalltbl.h include/testOS_msg.h include/testOS_drv.h

all: $(CFILES) $(HFILES)
	$(CC) -c $(CFLAGS) -o entry.o entry.S
	$(CC) -c $(CFLAGS) -o gpio.o gpio.c
	$(CC) -c $(CFLAGS) -o time.o time.c
	$(CC) -c $(CFLAGS) -o vsprintf.o vsprintf.c
	$(CC) -c $(CFLAGS) -o printf.o printf.c
	$(CC) -c $(CFLAGS) -o string.o string.c
	$(CC) -c $(CFLAGS) -o serial.o serial.c
	$(CC) -c $(CFLAGS) -o lib1funcs.o lib1funcs.S
	$(CC) -c $(CFLAGS) -o testOS.o testOS.c
	$(CC) -c $(CFLAGS) -o testOS_memory.o testOS_memory.c
	$(CC) -c $(CFLAGS) -o testOS_process.o testOS_process.c
	$(CC) -c $(CFLAGS) -o testOS_user.o testOS_user.c
	$(CC) -c $(CFLAGS) -o testOS_lib.o testOS_lib.S
	$(CC) -c $(CFLAGS) -o testOS_sys.o testOS_sys.c
	$(CC) -c $(CFLAGS) -o testOS_clib.o testOS_clib.c
	$(CC) -c $(CFLAGS) -o testOS_msg.o testOS_msg.c
	$(CC) -c $(CFLAGS) -o testOS_drv.o testOS_drv.c
	$(LD) $(LDFLAGS) -o testOS_elf entry.o gpio.o time.o vsprintf.o printf.o string.o serial.o lib1funcs.o testOS.o testOS_memory.o testOS_process.o testOS_user.o testOS_sys.o testOS_lib.o testOS_clib.o testOS_msg.o testOS_drv.o
	$(OC) $(OCFLAGS) testOS_elf testOS_img
	$(CC) -c $(CFLAGS) -o serial.o serial.c -D IN_GUMSTIX
	$(LD) $(LDFLAGS) -o testOS_gum_elf entry.o gpio.o time.o vsprintf.o printf.o string.o serial.o lib1funcs.o testOS.o testOS_memory.o testOS_process.o testOS_sys.o testOS_lib.o testOS_user.o testOS_clib.o testOS_msg.o testOS_drv.o
	$(OC) $(OCFLAGS) testOS_gum_elf testOS_gum_img


clean:
	rm *.o
	rm testOS_elf
	rm testOS_img
	rm testOS_gum_elf
	rm testOS_gum_img
