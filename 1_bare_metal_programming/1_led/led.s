.global _start

_start:
/*1.enable clock
 *2.IO mux of GPIO
 *3.Pad of GPIO
 *4.Write GPIO
 */
ldr r0, =0x020c4070
ldr r1, =0xffffffff
str r1, [r0]


ldr r0, =0x020e0068
ldr r1, =0x00000005
str r1, [r0]

ldr r0, =0x020e02f4
ldr r1, =0x00013008
str r1, [r0]

/* 4. Configure GPIO as output */
ldr r0, =0x0209c004        @ GPIO3_GDIR
ldr r1, =0x00000008        @ bit 3 = output
str r1, [r0]

mov r2, #0                 @ 初始化 r2 为低电平

ldr r0, =0x0209c000        @ GPIO3_DR
str r2, [r0]               @ 输出低电平

loop:
    bl delay_1s
    bl do_task
    b loop
delay_1s:
    mov r0, #0
    ldr r1, =0x100000 @0x400000 is 1 second
delay_loop:
    add r0, r0, #1
    cmp r0, r1
    bne delay_loop
    bx  lr
do_task:
    ldr r0, =0x0209c000
    str r2, [r0]
    eor r2, r2, #8
    bx lr
