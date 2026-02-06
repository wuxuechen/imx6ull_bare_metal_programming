.global _start

_start:
/*1.enable clock
 *2.IO mux of GPIO
 *3.Pad of GPIO
 *4.Write GPIO
 */
ldr r0, =0x020C4070
ldr r1, =0xffffffff
str r1, [r0]
ldr r0, =0x020C4074
ldr r1, =0xffffffff
str r1, [r0]
ldr r0, =0x020C407C
ldr r1, =0xffffffff
str r1, [r0]

// 2.IO mux of GPIO
//2.1 GPIO for beep
ldr r0, =0x0229000C
ldr r1, =0x00000005
str r1, [r0]
//2.2 GPIO for key 
ldr r0, =0x020E008C
ldr r1, =0x00000005
str r1, [r0]
//2.3 GPIO for led
ldr r0, =0x020e0068
ldr r1, =0x00000005
str r1, [r0]

// 3.Pad of GPIO
//3.1 pad of beep
ldr r0, =0x02290050
ldr r1, =0x10B0
str r1, [r0]
//3.2 pad of key
ldr r0, =0x020E0318
ldr r1, =0x1F080
str r1, [r0]
//3.3 pad of led
ldr r0, =0x020e02f4
ldr r1, =0x00013008
str r1, [r0]


// Write GPIO
ldr r0, =0x020AC004   @ GPIO5_GDIR
ldr r1, [r0]          @ 先读寄存器当前值
orr r1, r1, #0x2     @ 置 bit1 = 1 设为输出
str r1, [r0]
/* 4. Configure GPIO as output */
ldr r0, =0x0209c004        @ GPIO3_GDIR
ldr r1, =0x00000008        @ bit 3 = output
str r1, [r0]

ldr r0, =0x0209c000        @ GPIO3_DR
ldr     r2, [r0]              @ 读取当前值
orr     r2, r2, #(1 << 3)     @ 设置 bit1 为高电平，禁用蜂鸣器
str     r2, [r0]              @ 写回寄存器

// read GPIO
ldr r0, =0x0209C004   @ GPIO1_IO18 GDIR
ldr r1, [r0]          @ 先读寄存器当前值
bic r1, r1, #(1 << 18)    @ 清除 bit18（配置为输入
str r1, [r0]

ldr r0, =0x020AC000   @ GPIO5_DR
ldr r1, [r0]          @ 读当前值
orr r1, r1, #(1 << 1)     @ 设置 bit1（GPIO5_IO01 输出为高电平）   bic r1, r1, #0x2  清除 bit1，输出低电平
str r1, [r0]


loop:
    bl delay_10ms
    bl do_task
    b loop
delay_10ms:
    mov r0, #0
    ldr r1, =0x100 @ 100000 is 1 second
delay_loop:
    add r0, r0, #1
    cmp r0, r1
    bne delay_loop
    bx lr
do_task:
    ldr     r0, =0x0209C000       @ 读取 GPIO1_IO18 寄存器地址
    ldr     r1, [r0]              @ 读取当前值
    lsr     r1, r1, #18           @ 逻辑右移 18 位，将 bit18 移到 bit0
    ands    r1, r1, #1            @ 屏蔽其他位，只留下最低位（bit0） 如果按下的话，r1=0， 
    beq     is_button_pressed    @ 如果按键按下，跳转到 is_button_pressed

    @ 按键被按下，启用蜂鸣器
    ldr     r0, =0x020AC000       @ GPIO5_DR 寄存器地址
    ldr     r2, [r0]              @ 读取当前值
    orr     r2, r2, #(1 << 1)     @ 设置 bit1 为高电平，禁用蜂鸣器
    str     r2, [r0]              @ 写回寄存器
    
    ldr     r0, =0x0209c000        @ 
    ldr     r2, [r0]              @ 读取当前值
    orr     r2, r2, #(1 << 3)     @ 设置 bit1 为高电平，禁用蜂鸣器
    str     r2, [r0]              @ 写回寄存器
    bx      lr                    @ 返回

is_button_pressed:
    @ 按键未按下，禁用蜂鸣器
    ldr     r0, =0x020AC000       @ GPIO5_DR 寄存器地址
    ldr     r2, [r0]              @ 读取当前值
    bic     r2, r2, #(1 << 1)     @ 清除 bit1，为低电平，启用蜂鸣器
    str     r2, [r0]              @ 写回寄存器
    
    ldr     r0, =0x0209c000        @ 
    ldr     r2, [r0]              @ 读取当前值
    bic     r2, r2, #(1 << 3)     @ 设置 bit1 为高电平，禁用蜂鸣器
    str     r2, [r0]              @ 写回寄存器
    bx      lr                    @ 返回
