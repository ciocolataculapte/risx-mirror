        .intel_syntax noprefix

        .equ    STACK_SIZE, 0x1000      # 64K stack
        .equ    CODE_SEG_OFFSET, 0x08
        .equ    DATA_SEG_OFFSET, 0x10

        # # # # # # # # # # # # # # # #
        #       TEXT SECTION          #
        # # # # # # # # # # # # # # # #
        .section .text
        .global _start
_start: lea     esp, stack0             # initialize stack
        mov     ebp, esp
        push    ebx                     # phys address of multiboot info struct
        push    eax                     # magic number

        cli
        lgdt    [desc]                  # load global descriptor table

        jmp     CODE_SEG_OFFSET:L1      # update code segment register
L1:     mov     ax, DATA_SEG_OFFSET     # update other segment registers
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
