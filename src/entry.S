        .intel_syntax noprefix

        .equ    STACK_SIZE, 0x10000     # 64K stack

        # # # # # # # # # # # # # # # #
        #       TEXT SECTION          #
        # # # # # # # # # # # # # # # #
        .section .text
        .global _start
_start:
        lgdt    [_desc]
        mov     esp, stack0             # initialize stack
        mov     ebp, esp
        push    ebx                     # phys address of multiboot info struct
        push    eax                     # magic number
        call    risx                    # should never return
        cli
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
        .skip   STACK_SIZE
stack0: .skip   STACK_SIZE              # stack for core 0
stack1:                                 # stack for core 1
