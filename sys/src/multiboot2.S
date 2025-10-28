        .intel_syntax noprefix

        .equ    MAGIC, 0xE85250D6
#if defined(__i386__)
        .equ    ARCH, 0                 # 32-bit protected mode x86
#elif defined(__mips__)
        .equ    ARCH, 4                 # 32-bit MIPS
#else
#error "Unsupported architecture"
#endif
        .equ    LENGTH, (mbend - mbhead)
        .equ    CHECKSUM, (-(MAGIC + ARCH + (mbend - mbhead)))

        .section .multiboot2
        .global multiboot2_header

        .align  8                       # aligned to 8 bytes
mbhead: .long   MAGIC                   # multiboot 2 header
        .long   ARCH
        .long   LENGTH
        .long   CHECKSUM
mbfoot: .word   0                       # last required tag
        .word   0
        .long   8
mbend:
