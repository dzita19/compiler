.global main

.extern putchar
.extern printf
.extern malloc
.extern free
.extern print_malloc_frames

.section    .text

main:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     24, %rsp
    movl    [%rbp-4], %reg0
    movl    [%rbp-4], %reg1
    add     1, %reg1
    movl    %reg1, [%rbp-4]
    movl    [%rbp-4], %reg0
.section    .rodata
.LT1:
    .long   .L1
    .long   .L1
.section    .text
    sub     1, %reg0
    cmp     2, %reg0
    jae     .L2
    lsl     2, %reg0
    add     .LT1, %reg0
    jmp     [%reg0]
.L1:
    movl    3, %reg0
    movl    %reg0, [%rbp-4]
.L2:
    add     24, %rsp
    popl    %rbp
    ret     

.end