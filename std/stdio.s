.section    .data
TERM_OUT_CTRL:
    .long   983040
TERM_OUT_VAL:
    .long   983048
buffer:
    .zero   32

.section    .text

printdec:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     16, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
    movl    0, %reg0
    movl    %reg0, [%rbp-8]
    movl    [%rbp+8], %reg0
    cmp     0, %reg0
    jge     .L1
    movl    1, %reg0
    movl    %reg0, [%rbp-8]
    movl    [%rbp+8], %reg0
    neg     %reg0
    movl    %reg0, [%rbp+8]
.L1:
.L2:
    movl    buffer, %reg0
    movl    [%rbp-4], %reg1
    add     1, %reg1
    movl    %reg1, [%rbp-4]
    add     [%rbp-4], %reg0
    movl    [%rbp+8], %reg1
    imod    10, %reg1
    add     48, %reg1
    and     255, %reg1
    movb    %reg1, [%reg0]
    movl    [%rbp+8], %reg0
    idiv    10, %reg0
    movl    %reg0, [%rbp+8]
    movl    [%rbp+8], %reg0
    cmp     0, %reg0
    jgt     .L2
    movb    [%rbp+16], %reg0
    sxbl    %reg0
    cmp     48, %reg0
    jnq     .L3
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jeq     .L4
    movl    [TERM_OUT_VAL], %reg0
    movl    45, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    jmp     .L5
.L4:
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L5
    movl    [TERM_OUT_VAL], %reg0
    movl    43, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L5:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-12]
.L6:
    movl    [%rbp-12], %reg0
    movl    [%rbp-8], %reg1
    cmp     0, %reg1
    jnq     .L7
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L8
.L7:
    movl    [%rbp+12], %reg1
    sub     1, %reg1
    jmp     .L9
.L8:
    movl    [%rbp+12], %reg1
.L9:
    cmp     %reg1, %reg0
    jge     .L10
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-12], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-12]
    jmp     .L6
.L10:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-12]
.L11:
    movl    [%rbp-12], %reg0
    cmp     0, %reg0
    jlt     .L12
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-12], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-12], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-12]
    jmp     .L11
.L12:
    jmp     .L13
.L3:
    movl    [%rbp+20], %reg0
    cmp     0, %reg0
    jnq     .L14
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-12]
.L15:
    movl    [%rbp-12], %reg0
    movl    [%rbp-8], %reg1
    cmp     0, %reg1
    jnq     .L16
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L17
.L16:
    movl    [%rbp+12], %reg1
    sub     1, %reg1
    jmp     .L18
.L17:
    movl    [%rbp+12], %reg1
.L18:
    cmp     %reg1, %reg0
    jge     .L19
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-12], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-12]
    jmp     .L15
.L19:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jeq     .L20
    movl    [TERM_OUT_VAL], %reg0
    movl    45, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    jmp     .L21
.L20:
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L21
    movl    [TERM_OUT_VAL], %reg0
    movl    43, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L21:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-12]
.L22:
    movl    [%rbp-12], %reg0
    cmp     0, %reg0
    jlt     .L23
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-12], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-12], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-12]
    jmp     .L22
.L23:
    jmp     .L13
.L14:
    movl    [%rbp+20], %reg0
    cmp     1, %reg0
    jnq     .L13
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jeq     .L24
    movl    [TERM_OUT_VAL], %reg0
    movl    45, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    jmp     .L25
.L24:
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L25
    movl    [TERM_OUT_VAL], %reg0
    movl    43, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L25:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-12]
.L26:
    movl    [%rbp-12], %reg0
    cmp     0, %reg0
    jlt     .L27
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-12], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-12], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-12]
    jmp     .L26
.L27:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-12]
.L28:
    movl    [%rbp-12], %reg0
    movl    [%rbp-8], %reg1
    cmp     0, %reg1
    jnq     .L29
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L30
.L29:
    movl    [%rbp+12], %reg1
    sub     1, %reg1
    jmp     .L31
.L30:
    movl    [%rbp+12], %reg1
.L31:
    cmp     %reg1, %reg0
    jge     .L13
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-12], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-12]
    jmp     .L28
.L13:
    movl    0, %reg0
    add     16, %rsp
    popl    %rbp
    ret     

.end