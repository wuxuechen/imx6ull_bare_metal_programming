SECTIONS{
    . = 0x87800000;
    .text :
    {
        start.o
        main.o
        *(.text)
    }
    .rodata ALIGN(4) : {*(.rondata*)}
    .data ALIGN(4) : {*(.data)}
    __bbs_start = .;
    .bbs ALIGN(4) :{*(.bss) *(COMMON)}
    __bbs_end = .;
}
