.global get_variadic_param

.section    .rodata
.LP1:
    .asciz  "    movl    [%rbp],   %reg0"
.LP2:
    .asciz  "    add     8,        %reg0"
.LP3:
    .asciz  "    add     [%rbp-4], %reg0"

.section    .text

get_variadic_param:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    movl    [%rbp+8], %reg0
    movl    [%reg0], %reg0
    add     [%rbp+16], %reg0
    sub     1, %reg0
    idiv    [%rbp+16], %reg0
    imul    [%rbp+16], %reg0
    movl    %reg0, [%rbp-4]
    movl    [%rbp+8], %reg0
    movl    [%rbp+8], %reg1
    movl    [%reg1], %reg1
    add     [%rbp+12], %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp],   %reg0
    add     8,        %reg0
    add     [%rbp-4], %reg0
    add     8, %rsp
    popl    %rbp
    ret     

.end