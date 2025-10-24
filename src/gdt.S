        # # # # # # # # # # # # # # # #
        #       DATA SECTION          #
        # # # # # # # # # # # # # # # #
        .section .data
        .global _desc
        .align  16
gdt0:   .quad   0                       # null descriptor
seg0:   .word   0xFFFF                  # kernel code segment
        .word   0x0000
        .byte   0x00
        .byte   0x9A
        .byte   0xCF
        .byte   0x00
seg1:   .word   0xFFFF                  # kernel data segment
        .word   0x0000
        .byte   0x00
        .byte   0x92
        .byte   0xCF
        .byte   0x00
_desc:  .word   (. - gdt0 - 1)
        .long   gdt0
