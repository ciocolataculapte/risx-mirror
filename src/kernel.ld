ENTRY(_start)

SECTIONS
{
    . = 2M;

    .text : {
        . = ALIGN(16);
        KEEP(*(.multiboot2))
        KEEP(*(.text))
    }

    .rodata : {
        . = ALIGN(16);
        KEEP(*(.rodata))
    }

    .data : {
        . = ALIGN(16);
        KEEP(*(.data))
    }

    .bss : {
        . = ALIGN(16);
        KEEP(*(.bss))
        KEEP(*(COMMON))
    }
}
