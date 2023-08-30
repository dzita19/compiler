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
    sub     32, %rsp
    movl    1, %reg0
    movl    %reg0, [%rbp-24]
    movl    2, %reg0
    movl    %reg0, [%rbp-20]
    movl    [%rbp-28], %reg0
    add     4, %reg0
    movl    %reg0, %reg1
    movl    [%rbp-4], %reg2
    movl    %reg2, [%reg1]
    movl    [%rbp-32], %reg0
    movl    [%reg0], %reg0
    add     4, %reg0
    movl    %reg0, %reg1
    movl    [%rbp-4], %reg2
    movl    %reg2, [%reg1]
    add     32, %rsp
    popl    %rbp
    ret     

.end