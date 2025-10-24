        .intel_syntax noprefix

        .equ    STACK_SIZE, 0x1000      # 64K stack
        .equ    CODE_SEG, seg0 - gdt0   # offset of code segment in GDT
        .equ    DATA_SEG, seg1 - gdt0   # offset of data segment in GDT

        # # # # # # # # # # # # # # # #
        #       TEXT SECTION          #
        # # # # # # # # # # # # # # # #
        .section .text
        .global _start
_start: lea     esp, stack0             # initialize stack
        mov     ebp, esp
        push    ebx                     # phys address of multiboot info struct
        push    eax                     # magic number

        lgdt    [desc]                  # load global descriptor table

        jmp     CODE_SEG:L1             # update code segment register
L1:     mov     ax, DATA_SEG            # update other segment registers
        mov     ds, ax
        mov     es, ax
        mov     fs, ax
        mov     gs, ax
        mov     ss, ax

        call    risx                    # should never return
        cli

halt:   jmp     halt

        # # # # # # # # # # # # # # # #
        #       DATA SECTION          #
        # # # # # # # # # # # # # # # #
        .section .data
gdt0:   .quad   0                       # null required
seg0:   .word   0xFFFF                  # segment limit first 0-15 bits
        .word   0x0000                  # base fisr 0-15 bits
        .byte   0x00                    # base 16-23 bits
        .byte   0x9A                    # access byte
        .byte   0b11001111              # flags
        .byte   0x00                    # base 24-s31 bits
seg1:   .word   0xFFFF                  # segment limit first 0-15 bits
        .word   0x0000                  # base fisr 0-15 bits
        .byte   0x00                    # base 16-23 bits
        .byte   0x92                    # access byte
        .byte   0b11001111              # flags
        .byte   0x00                    # base 24-31 bits
desc:   .word   (. - gdt0 - 1)
        .long   gdt0

        # # # # # # # # # # # # # # # #
        #       BSS SECTION           #
        # # # # # # # # # # # # # # # #
        .section .bss
        .align  16
_top:   .skip   STACK_SIZE
stack0: .skip   STACK_SIZE              # stack for core 0
stack1:                                 # stack for core 1
