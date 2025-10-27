# These macros are borrowed from xv6's kernel's source code, which is
# distributed under the following license:
#
# Copyright (c) 2006-2018 Frans Kaashoek, Robert Morris, Russ Cox,
#                         Massachusetts Institute of Technology
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#define SEG_NULLASM                                                            \
        .word 0, 0;                                                            \
        .byte 0, 0, 0, 0

#define SEG_ASM(type,base,lim)                                                 \
        .word (((lim) >> 12) & 0xFFFF), ((base) & 0xFFFF);                     \
        .byte (((base) >> 16) & 0xFF), (0x90 | (type)),                        \
                (0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xFF)

#define STA_X 0x8                       // Executable segment
#define STA_W 0x2                       // Writeable (non-executable segments)
#define STA_R 0x2                       // Readable (executable segments)

        # # # # # # # # # # # # # # # #
        #       DATA SECTION          #
        # # # # # # # # # # # # # # # #
        .section .data
        .global _desc
        .align  16
gdt0:   SEG_NULLASM
seg0:   SEG_ASM(STA_X | STA_R, 0x0, 0xFFFFFFFF)
seg1:   SEG_ASM(STA_W, 0x0, 0xFFFFFFFF)
_desc:  .word   (. - gdt0 - 1)
        .long   gdt0
