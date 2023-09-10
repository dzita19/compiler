.global strlen
.global strcpy
.global strdup
.global strcmp
.global strcat
.global memcpy
.global memmove
.global memset

.extern malloc
.extern free
.extern printf

.section    .text

strlen:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
.L1:
    movl    [%rbp+8], %reg0
    add     [%rbp-4], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
    cmp     0, %reg0
    jeq     .L2
    movl    [%rbp-4], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-4]
    jmp     .L1
.L2:
    movl    [%rbp-4], %reg0
    add     8, %rsp
    popl    %rbp
    ret     

strcpy:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
.L3:
    movl    [%rbp+12], %reg0
    add     [%rbp-4], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
    cmp     0, %reg0
    jeq     .L4
    movl    [%rbp+8], %reg0
    add     [%rbp-4], %reg0
    movl    [%rbp+12], %reg1
    add     [%rbp-4], %reg1
    movb    [%reg1], %reg1
    movb    %reg1, [%reg0]
    movl    [%rbp-4], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-4]
    jmp     .L3
.L4:
    movl    [%rbp+8], %reg0
    add     [%rbp-4], %reg0
    movb    0, %reg1
    movb    %reg1, [%reg0]
    movl    [%rbp+8], %reg0
    add     8, %rsp
    popl    %rbp
    ret     

strdup:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    sub     16, %rsp
    sub     16, %rsp
    movl    [%rbp+8], %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp]
    call    strlen
    add     16, %rsp
    add     1, %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp]
    call    malloc
    add     16, %rsp
    movl    %reg0, [%rbp-4]
    sub     16, %rsp
    movl    [%rbp-4], %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp]
    movl    [%rbp+8], %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp+4]
    call    strcpy
    add     16, %rsp
    movl    [%rbp-4], %reg0
    add     8, %rsp
    popl    %rbp
    ret     

strcmp:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
.L5:
    movl    [%rbp+8], %reg0
    add     [%rbp-4], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
    cmp     0, %reg0
    jeq     .L6
    movl    [%rbp+8], %reg0
    add     [%rbp-4], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
    movl    [%rbp+12], %reg1
    add     [%rbp-4], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    cmp     %reg1, %reg0
    jnq     .L7
    jmp     .L8
    jmp     .L8
.L7:
    movl    [%rbp+8], %reg0
    add     [%rbp-4], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
    movl    [%rbp+12], %reg1
    add     [%rbp-4], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    cmp     %reg1, %reg0
    jge     .L9
    movl    -1, %reg0
    jmp     .L10
    jmp     .L8
.L9:
    movl    1, %reg0
    jmp     .L10
.L8:
    movl    [%rbp-4], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-4]
    jmp     .L5
.L6:
    movl    0, %reg0
.L10:
    add     8, %rsp
    popl    %rbp
    ret     

strcat:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     16, %rsp
    sub     16, %rsp
    movl    [%rbp+8], %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp]
    call    strlen
    add     16, %rsp
    movl    %reg0, [%rbp-4]
    sub     16, %rsp
    movl    [%rbp+12], %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp]
    call    strlen
    add     16, %rsp
    movl    %reg0, [%rbp-8]
    movl    0, %reg0
    movl    %reg0, [%rbp-12]
.L11:
    movl    [%rbp-12], %reg0
    cmp     [%rbp-8], %reg0
    jge     .L12
    movl    [%rbp+8], %reg0
    movl    [%rbp-4], %reg1
    add     [%rbp-12], %reg1
    add     %reg1, %reg0
    movl    [%rbp+12], %reg1
    add     [%rbp-12], %reg1
    movb    [%reg1], %reg1
    movb    %reg1, [%reg0]
    movl    [%rbp-12], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-12]
    jmp     .L11
.L12:
    movl    [%rbp+8], %reg0
    movl    [%rbp-4], %reg1
    add     [%rbp-12], %reg1
    add     %reg1, %reg0
    movb    0, %reg1
    movb    %reg1, [%reg0]
    movl    [%rbp+8], %reg0
    add     16, %rsp
    popl    %rbp
    ret     

memcpy:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     40, %rsp
    movl    [%rbp+16], %reg0
    and     -4, %reg0
    asr     2, %reg0
    movl    %reg0, [%rbp-4]
    movl    [%rbp+16], %reg0
    and     3, %reg0
    asr     1, %reg0
    movl    %reg0, [%rbp-8]
    movl    [%rbp+16], %reg0
    and     1, %reg0
    movl    %reg0, [%rbp-12]
    movl    [%rbp+8], %reg0
    movl    %reg0, [%rbp-16]
    movl    [%rbp+12], %reg0
    movl    %reg0, [%rbp-20]
    movl    [%rbp-4], %reg0
    cmp     0, %reg0
    jeq     .L13
    movl    [%rbp-4], %reg0
    add     7, %reg0
    idiv    8, %reg0
    movl    %reg0, [%rbp-24]
    movl    [%rbp-4], %reg0
    and     7, %reg0
.section    .rodata
.LT1:
    .long   .L14
    .long   .L15
    .long   .L16
    .long   .L17
    .long   .L18
    .long   .L19
    .long   .L20
    .long   .L21
.section    .text
    cmp     8, %reg0
    jae     .L13
    lsl     2, %reg0
    add     .LT1, %reg0
    jmp     [%reg0]
.L14:
.L22:
    movl    [%rbp-16], %reg0
    movl    [%rbp-16], %reg1
    add     4, %reg1
    movl    %reg1, [%rbp-16]
    movl    [%rbp-20], %reg1
    movl    [%rbp-20], %reg2
    add     4, %reg2
    movl    %reg2, [%rbp-20]
    movl    [%reg1], %reg1
    movl    %reg1, [%reg0]
.L21:
    movl    [%rbp-16], %reg0
    movl    [%rbp-16], %reg1
    add     4, %reg1
    movl    %reg1, [%rbp-16]
    movl    [%rbp-20], %reg1
    movl    [%rbp-20], %reg2
    add     4, %reg2
    movl    %reg2, [%rbp-20]
    movl    [%reg1], %reg1
    movl    %reg1, [%reg0]
.L20:
    movl    [%rbp-16], %reg0
    movl    [%rbp-16], %reg1
    add     4, %reg1
    movl    %reg1, [%rbp-16]
    movl    [%rbp-20], %reg1
    movl    [%rbp-20], %reg2
    add     4, %reg2
    movl    %reg2, [%rbp-20]
    movl    [%reg1], %reg1
    movl    %reg1, [%reg0]
.L19:
    movl    [%rbp-16], %reg0
    movl    [%rbp-16], %reg1
    add     4, %reg1
    movl    %reg1, [%rbp-16]
    movl    [%rbp-20], %reg1
    movl    [%rbp-20], %reg2
    add     4, %reg2
    movl    %reg2, [%rbp-20]
    movl    [%reg1], %reg1
    movl    %reg1, [%reg0]
.L18:
    movl    [%rbp-16], %reg0
    movl    [%rbp-16], %reg1
    add     4, %reg1
    movl    %reg1, [%rbp-16]
    movl    [%rbp-20], %reg1
    movl    [%rbp-20], %reg2
    add     4, %reg2
    movl    %reg2, [%rbp-20]
    movl    [%reg1], %reg1
    movl    %reg1, [%reg0]
.L17:
    movl    [%rbp-16], %reg0
    movl    [%rbp-16], %reg1
    add     4, %reg1
    movl    %reg1, [%rbp-16]
    movl    [%rbp-20], %reg1
    movl    [%rbp-20], %reg2
    add     4, %reg2
    movl    %reg2, [%rbp-20]
    movl    [%reg1], %reg1
    movl    %reg1, [%reg0]
.L16:
    movl    [%rbp-16], %reg0
    movl    [%rbp-16], %reg1
    add     4, %reg1
    movl    %reg1, [%rbp-16]
    movl    [%rbp-20], %reg1
    movl    [%rbp-20], %reg2
    add     4, %reg2
    movl    %reg2, [%rbp-20]
    movl    [%reg1], %reg1
    movl    %reg1, [%reg0]
.L15:
    movl    [%rbp-16], %reg0
    movl    [%rbp-16], %reg1
    add     4, %reg1
    movl    %reg1, [%rbp-16]
    movl    [%rbp-20], %reg1
    movl    [%rbp-20], %reg2
    add     4, %reg2
    movl    %reg2, [%rbp-20]
    movl    [%reg1], %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-24], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-24]
    movl    [%rbp-24], %reg0
    cmp     0, %reg0
    jgt     .L22
.L13:
    movl    [%rbp-16], %reg0
    movl    %reg0, [%rbp-24]
    movl    [%rbp-20], %reg0
    movl    %reg0, [%rbp-28]
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jeq     .L23
    movl    [%rbp-24], %reg0
    movl    [%rbp-24], %reg1
    add     2, %reg1
    movl    %reg1, [%rbp-24]
    movl    [%rbp-28], %reg1
    movl    [%rbp-28], %reg2
    add     2, %reg2
    movl    %reg2, [%rbp-28]
    movw    [%reg1], %reg1
    movw    %reg1, [%reg0]
.L23:
    movl    [%rbp-24], %reg0
    movl    %reg0, [%rbp-32]
    movl    [%rbp-28], %reg0
    movl    %reg0, [%rbp-36]
    movl    [%rbp-12], %reg0
    cmp     0, %reg0
    jeq     .L24
    movl    [%rbp-32], %reg0
    movl    [%rbp-32], %reg1
    add     1, %reg1
    movl    %reg1, [%rbp-32]
    movl    [%rbp-36], %reg1
    movl    [%rbp-36], %reg2
    add     1, %reg2
    movl    %reg2, [%rbp-36]
    movb    [%reg1], %reg1
    movb    %reg1, [%reg0]
.L24:
    movl    [%rbp+8], %reg0
    add     40, %rsp
    popl    %rbp
    ret     

memmove:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    sub     16, %rsp
    movl    [%rbp+16], %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp]
    call    malloc
    add     16, %rsp
    movl    %reg0, [%rbp-4]
    sub     16, %rsp
    movl    [%rbp-4], %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp]
    movl    [%rbp+12], %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp+4]
    movl    [%rbp+16], %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp+8]
    call    memcpy
    add     16, %rsp
    sub     16, %rsp
    movl    [%rbp+8], %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp]
    movl    [%rbp-4], %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp+4]
    movl    [%rbp+16], %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp+8]
    call    memcpy
    add     16, %rsp
    sub     16, %rsp
    movl    [%rbp-4], %reg0
    movl    [%reg0], %reg1
    movl    %reg1, [%rsp]
    call    free
    add     16, %rsp
    movl    [%rbp+8], %reg0
    add     8, %rsp
    popl    %rbp
    ret     

memset:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
.L25:
    movl    [%rbp-4], %reg0
    cmp     [%rbp+16], %reg0
    jge     .L26
    movl    [%rbp+8], %reg0
    add     [%rbp-4], %reg0
    movl    [%rbp+12], %reg1
    and     255, %reg1
    movb    %reg1, [%reg0]
    movl    [%rbp-4], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-4]
    jmp     .L25
.L26:
    movl    [%rbp+8], %reg0
    add     8, %rsp
    popl    %rbp
    ret     

.end