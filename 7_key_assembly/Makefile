key.bin:key.s
	arm-linux-gnueabihf-gcc -g -c key.s -o key.o
	arm-linux-gnueabihf-ld -Ttext 0X87800000 key.o -o key.elf
	arm-linux-gnueabihf-objcopy -O binary -S -g key.elf key.bin
	arm-linux-gnueabihf-objdump -D key.elf > key.dis
clean:
	rm key.bin  key.dis  key.elf  key.o 
