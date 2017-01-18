#!/bin/sh
rm testOSimg -f
rm testOS.jffs2 -f  
./mkimage -A arm -O linux -T kernel -C none -a a0008000 -e a0008000 -n 'testOS' -d testOS_gum_img uImage
mv uImage kernel/boot/
   
mkfs.jffs2 -e 0x20000 -d kernel -p -o testOS.jffs2
  
dd if=u-boot.bin of=testOSimg bs=1k conv=notrunc
dd if=testOS.jffs2 of=testOSimg bs=1k conv=notrunc seek=180 
 
#qemu error.. So I add this way
dd if=/dev/zero of=final_testOSimg bs=1k count=16k
dd if=testOSimg of=final_testOSimg bs=1k conv=notrunc
qemu-system-arm -M connex -pflash final_testOSimg -nographic
