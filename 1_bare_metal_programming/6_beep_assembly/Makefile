beep.bin:beep.s
	arm-linux-gnueabihf-gcc -g -c beep.s -o beep.o
	arm-linux-gnueabihf-ld -Ttext 0X87800000 beep.o -o beep.elf
	arm-linux-gnueabihf-objcopy -O binary -S -g beep.elf beep.bin
	arm-linux-gnueabihf-objdump -D beep.elf > beep.dis
clean:
	rm beep.bin  beep.dis  beep.elf  beep.o 
