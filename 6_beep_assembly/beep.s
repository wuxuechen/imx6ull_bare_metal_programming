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


ldr r0, =0x0229000C
ldr r1, =0x00000005
str r1, [r0]

ldr r0, =0x02290050
ldr r1, =0x10B0
str r1, [r0]

ldr r0, =0x020AC004   @ GPIO5_GDIR
ldr r1, [r0]          @ 先读寄存器当前值
orr r1, r1, #0x2     @ 置 bit1 = 1 设为输出
str r1, [r0]

ldr r0, =0x020AC000   @ GPIO5_DR
ldr r1, [r0]          @ 读当前值
bic r1, r1, #0x2     @ 清除 bit1，输出低电平
str r1, [r0]


loop:
    bl delay_1s
    bl do_task
    b loop
delay_1s:
    mov r0, #0
    ldr r1, =0x100000 @ 100000 is 1 second
delay_loop:
   add r0, r0, #1
   cmp r0, r1
   bne delay_loop
   bx lr
do_task:
    ldr r0, =0x020AC000
    str r2, [r0]
    eor r2, r2, #2
    bx lr

