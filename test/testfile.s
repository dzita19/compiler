.global main

.extern putchar
.extern printf
.extern malloc
.extern free
.extern print_malloc_frames
.extern strlen
.extern strcpy
.extern strcmp
.extern strdup
.extern strcat
.extern memcpy
.extern memmove
.extern memset

.section    .text

main:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    movl    15, %reg0
    movl    %reg0, [%rbp-4]
    movl    [%rbp-4], %reg0
.section    .rodata
.LT1:
    .long   .L1
    .long   .L2
    .long   .L3
.section    .text
    sub     1, %reg0
    cmp     3, %reg0
    jae     .L4
    lsl     2, %reg0
    add     .LT1, %reg0
    jmp     [%reg0]
.L4:
.section    .rodata
.LT2:
    .long   .L2
    .long   .L5
    .long   .L6
    .long   .L1
.section    .text
    sub     6, %reg0
    cmp     4, %reg0
    jae     .L7
    lsl     2, %reg0
    add     .LT2, %reg0
    jmp     [%reg0]
.L7:
.section    .rodata
.LT3:
    .long   .L3
.section    .text
    sub     8, %reg0
    cmp     1, %reg0
    jae     .L5
    lsl     2, %reg0
    add     .LT3, %reg0
    jmp     [%reg0]
.L1:
    movl    1, %reg0
    jmp     .L8
.L6:
    jmp     .L5
.L3:
    movl    2, %reg0
    jmp     .L8
.L2:
    jmp     .L5
.L5:
    movl    3, %reg0
.L8:
    add     8, %rsp
    popl    %rbp
    ret     

.end