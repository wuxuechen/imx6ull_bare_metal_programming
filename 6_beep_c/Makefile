CROSS_COMPILE ?= arm-linux-gnueabihf-
TARGET ?= beep

CC :=$(CROSS_COMPILE)gcc
LD :=$(CROSS_COMPILE)ld
OBJCOPY :=$(CROSS_COMPILE)objcopy
OBJDUMP :=$(CROSS_COMPILE)objdump

INCDIRS := imx6ul\
	   bsp/led\
	   bsp/beep
SRCDIRS := project\
	   bsp/led\
	   bsp/beep
INCLUDE :=$(patsubst %, -I %, $(INCDIRS))

SFILES := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.S))
CFILES := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SFILENDIR := $(notdir $(SFILES))
CFILENDIR := $(notdir $(CFILES))

SOBJS :=$(patsubst %, obj/%, $(SFILENDIR:.S=.o))
COBJS :=$(patsubst %, obj/%, $(CFILENDIR:.c=.o))
$(info SOBJS = $(SOBJS))
$(info COBJS = $(COBJS))
OBJS :=$(SOBJS)$(COBJS)

VPATH :=$(SRCDIRS)

.PHONY:clean
$(TARGET).bin : $(OBJS)
	$(LD) -Timx6ul.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis
$(SOBJS) : obj/%.o : %.S
	$(CC) -Wall -nostdlib -c -O0 $(INCLUDE) -o $@ $<
$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -nostdlib -c -O0 $(INCLUDE) -o $@ $<
clean:
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin $(SOBJS) $(COBJS)
