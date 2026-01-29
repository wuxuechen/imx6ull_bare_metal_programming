CROSS_COMPILE ?= arm-linux-gnueabihf-
TARGET        ?= key

CC      := $(CROSS_COMPILE)gcc
LD      := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
LIBPATH := /usr/lib/gcc-cross/arm-linux-gnueabihf/11/libgcc.a

# 包含路径
INCDIRS := imx6ul \
           bsp/led \
           bsp/beep \
           bsp/key \
           bsp/gpio \
           bsp/delay \
           bsp/exit \
           bsp/epittimer \
           bsp/keyfilter \
           bsp/uart \
           sdtio/include\
           bsp/int

# 源码路径
SRCDIRS := project \
           bsp/led \
           bsp/beep \
           bsp/key \
           bsp/gpio \
           bsp/delay \
           bsp/exit \
           bsp/epittimer \
           bsp/keyfilter \
           bsp/uart \
           stdio/lib \
           bsp/int

# 将路径转为 -I 参数
INCLUDE := $(patsubst %, -I %, $(INCDIRS))

# 查找源文件
SFILES  := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.S))
CFILES  := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

# 提取文件名（去除路径）
SFILENDIR := $(notdir $(SFILES))
CFILENDIR := $(notdir $(CFILES))

# 映射到 obj 目录下的对象文件
SOBJS := $(patsubst %, obj/%, $(SFILENDIR:.S=.o))
COBJS := $(patsubst %, obj/%, $(CFILENDIR:.c=.o))

# 修复点 1：确保 SOBJS 和 COBJS 之间有空格
OBJS  := $(SOBJS) $(COBJS)

# 设置搜索路径，以便 make 能找到不在当前目录的 .c/.S 文件
VPATH := $(SRCDIRS)

.PHONY: all clean obj

# 默认目标
all: obj $(TARGET).bin

# 创建目录：使用 mkdir -p 确保安全
obj:
	@mkdir -p obj

# 链接
$(TARGET).bin : $(OBJS)
	$(LD) -Timx6ul.lds -o $(TARGET).elf $^ $(LIBPATH)
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

# 汇编编译
$(SOBJS) : obj/%.o : %.S | obj
	$(CC) -Wall -nostdlib -fno-builtin -c -O0 $(INCLUDE) -o $@ $<

# C 编译
$(COBJS) : obj/%.o : %.c | obj
	$(CC) -Wall -Wa,-mimplicit-it=thumb -nostdlib -fno-builtin -c -O0 $(INCLUDE) -o $@ $<

# 修复点 2：更干净的清理
clean:
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin obj
