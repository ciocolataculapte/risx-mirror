        .intel_syntax noprefix

        # # # # # # # # # # # # # # # #
        #       TEXT SECTION          #
        # # # # # # # # # # # # # # # #
        .section .text
        .global _start
_start:
        # mov     esp, stack0             # initialize stack
        lgdt    [_desc]
        mov     ebp, esp
        push    eax                     # magic number
        push    ebx                     # phys address of multiboot info struct
        cli
        call    risx                    # should never return
_halt:  jmp     _halt

        # # # # # # # # # # # # # # # #
        #       DATA SECTION          #
        # # # # # # # # # # # # # # # #
        .section .data
_gdt0:  .quad   0                       # null required
_seg0:  .word   0xFFFF                  # segment limit first 0-15 bits
        .word   0x0000                  # base fisr 0-15 bits
        .byte   0x00                    # base 16-23 bits
        .byte   0x9A                    # access byte
        .byte   0b11001111              # flags
        .byte   0x00                    # base 24-s31 bits
_seg1:  .word   0xFFFF                  # segment limit first 0-15 bits
        .word   0x0000                  # base fisr 0-15 bits
        .byte   0x00                    # base 16-23 bits
        .byte   0x92                    # access byte
        .byte   0b11001111              # flags
        .byte   0x00                    # base 24-31 bits
_desc:  .word   (. - _gdt0 - 1)
        .long   _gdt0

        # # # # # # # # # # # # # # # #
        #       BSS SECTION           #
        # # # # # # # # # # # # # # # #
        .section .bss
        .align  16
top:    .skip   0x10000                 # 64K stack
stack0: .skip   0x10000                 # stack for core 0
stack1:                                 # stack for core 1
