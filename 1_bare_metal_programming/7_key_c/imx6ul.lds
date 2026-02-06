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
    .data ALIGN(4) : {*(.data)}
    __bss_start = .;
    .bss ALIGN(4) :{*(.bss) *(COMMON)}
    __bss_end = .;
}
