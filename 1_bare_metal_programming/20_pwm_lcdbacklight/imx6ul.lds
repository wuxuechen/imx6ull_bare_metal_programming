ENTRY(_start)
SECTIONS{
    . = 0x87800000;
    .text : AT(0x87800000)
    {
        __text_start = .;
        KEEP(obj/start.o(.text))               /* 显式放在最前 */
        KEEP(*(.text))
        *(.text*)
        __text_end = .;

    }

    .rodata ALIGN(4) : {*(.rodata*)}
    /* ⭐ 必须加这一段 ⭐ */
    .ARM.exidx ALIGN(4) :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    }
    /* Data段，初始化全局变量 */
    __data_load = .;             /* ROM中存储data的起始地址 */
    __data_start = 0x80000000;   /* RAM中data运行起始地址 */
    .data ALIGN(4) : AT(__data_load)
    {
        *( .data )
    }
    __data_end = __data_start + SIZEOF(.data);

    /* BSS段，未初始化全局变量 */
    __bss_start = 0x80000000 + SIZEOF(.data);  /* 紧接data之后 */
    .bss (NOLOAD) : ALIGN(8) { *(.bss) *(.common) }
    __bss_end = __bss_start + SIZEOF(.bss);
}
