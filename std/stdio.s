.global putchar
.global printf

.extern get_variadic_param

.section    .data
TERM_OUT_CTRL:
    .long   983040
TERM_OUT_VAL:
    .long   983048
buffer:
    .zero   32

.section    .rodata
.LP1:
    .asciz  "(null)"
    .zero   1

.section    .text

putchar:
    pushl   %rbp
    movl    %rsp, %rbp
    movl    [TERM_OUT_VAL], %reg0
    movl    [%rbp+8], %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    0, %reg0
    popl    %rbp
    ret     

printstr:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    movl    [%rbp+8], %reg0
    cmp     0, %reg0
    jnq     .L1
    movl    .LP1, %reg0
    movl    %reg0, [%rbp+8]
.L1:
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
.L2:
    movl    [%rbp+8], %reg0
    add     [%rbp-4], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
    cmp     0, %reg0
    jeq     .L3
    movl    [%rbp-4], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-4]
    jmp     .L2
.L3:
    movl    [%rbp+16], %reg0
    cmp     0, %reg0
    jnq     .L4
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L5:
    movl    [%rbp-8], %reg0
    cmp     [%rbp+12], %reg0
    jge     .L4
    movl    [TERM_OUT_VAL], %reg0
    movl    32, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L5
.L4:
    movl    0, %reg0
    movl    %reg0, [%rbp-8]
.L6:
    movl    [%rbp-8], %reg0
    cmp     [%rbp-4], %reg0
    jge     .L7
    movl    [TERM_OUT_VAL], %reg0
    movl    [%rbp+8], %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L6
.L7:
    movl    [%rbp+16], %reg0
    cmp     1, %reg0
    jnq     .L8
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L9:
    movl    [%rbp-8], %reg0
    cmp     [%rbp+12], %reg0
    jge     .L8
    movl    [TERM_OUT_VAL], %reg0
    movl    32, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L9
.L8:
    movl    0, %reg0
    add     8, %rsp
    popl    %rbp
    ret     

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
    jge     .L10
    movl    1, %reg0
    movl    %reg0, [%rbp-8]
    movl    [%rbp+8], %reg0
    neg     %reg0
    movl    %reg0, [%rbp+8]
.L10:
.L11:
    movl    buffer, %reg0
    movl    [%rbp-4], %reg1
    movl    [%rbp-4], %reg2
    add     1, %reg2
    movl    %reg2, [%rbp-4]
    add     %reg1, %reg0
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
    jgt     .L11
    movb    [%rbp+16], %reg0
    sxbl    %reg0
    cmp     48, %reg0
    jnq     .L12
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jeq     .L13
    movl    [TERM_OUT_VAL], %reg0
    movl    45, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    jmp     .L14
.L13:
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L14
    movl    [TERM_OUT_VAL], %reg0
    movl    43, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L14:
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
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-12]
.L20:
    movl    [%rbp-12], %reg0
    cmp     0, %reg0
    jlt     .L21
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
    jmp     .L20
.L21:
    jmp     .L22
.L12:
    movl    [%rbp+20], %reg0
    cmp     0, %reg0
    jnq     .L23
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-12]
.L24:
    movl    [%rbp-12], %reg0
    movl    [%rbp-8], %reg1
    cmp     0, %reg1
    jnq     .L25
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L26
.L25:
    movl    [%rbp+12], %reg1
    sub     1, %reg1
    jmp     .L27
.L26:
    movl    [%rbp+12], %reg1
.L27:
    cmp     %reg1, %reg0
    jge     .L28
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
    jmp     .L24
.L28:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jeq     .L29
    movl    [TERM_OUT_VAL], %reg0
    movl    45, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    jmp     .L30
.L29:
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L30
    movl    [TERM_OUT_VAL], %reg0
    movl    43, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L30:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-12]
.L31:
    movl    [%rbp-12], %reg0
    cmp     0, %reg0
    jlt     .L32
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
    jmp     .L31
.L32:
    jmp     .L22
.L23:
    movl    [%rbp+20], %reg0
    cmp     1, %reg0
    jnq     .L22
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jeq     .L33
    movl    [TERM_OUT_VAL], %reg0
    movl    45, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    jmp     .L34
.L33:
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L34
    movl    [TERM_OUT_VAL], %reg0
    movl    43, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L34:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-12]
.L35:
    movl    [%rbp-12], %reg0
    cmp     0, %reg0
    jlt     .L36
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
    jmp     .L35
.L36:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-12]
.L37:
    movl    [%rbp-12], %reg0
    movl    [%rbp-8], %reg1
    cmp     0, %reg1
    jnq     .L38
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L39
.L38:
    movl    [%rbp+12], %reg1
    sub     1, %reg1
    jmp     .L40
.L39:
    movl    [%rbp+12], %reg1
.L40:
    cmp     %reg1, %reg0
    jge     .L22
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
    jmp     .L37
.L22:
    movl    0, %reg0
    add     16, %rsp
    popl    %rbp
    ret     

printdecu:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
.L41:
    movl    buffer, %reg0
    movl    [%rbp-4], %reg1
    movl    [%rbp-4], %reg2
    add     1, %reg2
    movl    %reg2, [%rbp-4]
    add     %reg1, %reg0
    movl    [%rbp+8], %reg1
    mod     10, %reg1
    add     48, %reg1
    and     255, %reg1
    movb    %reg1, [%reg0]
    movl    [%rbp+8], %reg0
    div     10, %reg0
    movl    %reg0, [%rbp+8]
    movl    [%rbp+8], %reg0
    cmp     0, %reg0
    ja      .L41
    movb    [%rbp+16], %reg0
    sxbl    %reg0
    cmp     48, %reg0
    jeq     .L42
    movl    [%rbp+20], %reg0
    cmp     0, %reg0
    jnq     .L43
.L42:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L44:
    movl    [%rbp-8], %reg0
    cmp     [%rbp+12], %reg0
    jge     .L45
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L44
.L45:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L46:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L47
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L46
.L47:
    jmp     .L48
.L43:
    movl    [%rbp+20], %reg0
    cmp     1, %reg0
    jnq     .L48
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L49:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L50
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L49
.L50:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L51:
    movl    [%rbp-8], %reg0
    cmp     [%rbp+12], %reg0
    jge     .L48
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L51
.L48:
    movl    0, %reg0
    add     8, %rsp
    popl    %rbp
    ret     

printhexlw:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
.L52:
    movl    [%rbp+8], %reg0
    and     15, %reg0
    movl    %reg0, [%rbp-8]
    movl    buffer, %reg0
    movl    [%rbp-4], %reg1
    movl    [%rbp-4], %reg2
    add     1, %reg2
    movl    %reg2, [%rbp-4]
    add     %reg1, %reg0
    movl    [%rbp-8], %reg1
    cmp     10, %reg1
    jge     .L53
    movl    [%rbp-8], %reg1
    add     48, %reg1
    jmp     .L54
.L53:
    movl    [%rbp-8], %reg1
    sub     10, %reg1
    add     97, %reg1
.L54:
    and     255, %reg1
    movb    %reg1, [%reg0]
    movl    [%rbp+8], %reg0
    lsr     4, %reg0
    movl    %reg0, [%rbp+8]
    movl    [%rbp+8], %reg0
    cmp     0, %reg0
    ja      .L52
    movb    [%rbp+16], %reg0
    sxbl    %reg0
    cmp     48, %reg0
    jnq     .L55
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L56
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_VAL], %reg0
    movl    120, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L56:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L57:
    movl    [%rbp-8], %reg0
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L58
    movl    [%rbp+12], %reg1
    sub     2, %reg1
    jmp     .L59
.L58:
    movl    [%rbp+12], %reg1
.L59:
    cmp     %reg1, %reg0
    jge     .L60
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L57
.L60:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L61:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L62
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L61
.L62:
    jmp     .L63
.L55:
    movl    [%rbp+20], %reg0
    cmp     0, %reg0
    jnq     .L64
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L65:
    movl    [%rbp-8], %reg0
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L66
    movl    [%rbp+12], %reg1
    sub     2, %reg1
    jmp     .L67
.L66:
    movl    [%rbp+12], %reg1
.L67:
    cmp     %reg1, %reg0
    jge     .L68
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L65
.L68:
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L69
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_VAL], %reg0
    movl    120, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L69:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L70:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L71
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L70
.L71:
    jmp     .L63
.L64:
    movl    [%rbp+20], %reg0
    cmp     1, %reg0
    jnq     .L63
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L72
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_VAL], %reg0
    movl    120, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L72:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L73:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L74
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L73
.L74:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L75:
    movl    [%rbp-8], %reg0
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L76
    movl    [%rbp+12], %reg1
    sub     2, %reg1
    jmp     .L77
.L76:
    movl    [%rbp+12], %reg1
.L77:
    cmp     %reg1, %reg0
    jge     .L63
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L75
.L63:
    movl    0, %reg0
    add     8, %rsp
    popl    %rbp
    ret     

printhexup:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
.L78:
    movl    [%rbp+8], %reg0
    and     15, %reg0
    movl    %reg0, [%rbp-8]
    movl    buffer, %reg0
    movl    [%rbp-4], %reg1
    movl    [%rbp-4], %reg2
    add     1, %reg2
    movl    %reg2, [%rbp-4]
    add     %reg1, %reg0
    movl    [%rbp-8], %reg1
    cmp     10, %reg1
    jge     .L79
    movl    [%rbp-8], %reg1
    add     48, %reg1
    jmp     .L80
.L79:
    movl    [%rbp-8], %reg1
    sub     10, %reg1
    add     65, %reg1
.L80:
    and     255, %reg1
    movb    %reg1, [%reg0]
    movl    [%rbp+8], %reg0
    lsr     4, %reg0
    movl    %reg0, [%rbp+8]
    movl    [%rbp+8], %reg0
    cmp     0, %reg0
    ja      .L78
    movb    [%rbp+16], %reg0
    sxbl    %reg0
    cmp     48, %reg0
    jnq     .L81
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L82
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_VAL], %reg0
    movl    88, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L82:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L83:
    movl    [%rbp-8], %reg0
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L84
    movl    [%rbp+12], %reg1
    sub     2, %reg1
    jmp     .L85
.L84:
    movl    [%rbp+12], %reg1
.L85:
    cmp     %reg1, %reg0
    jge     .L86
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L83
.L86:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L87:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L88
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L87
.L88:
    jmp     .L89
.L81:
    movl    [%rbp+20], %reg0
    cmp     0, %reg0
    jnq     .L90
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L91:
    movl    [%rbp-8], %reg0
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L92
    movl    [%rbp+12], %reg1
    sub     2, %reg1
    jmp     .L93
.L92:
    movl    [%rbp+12], %reg1
.L93:
    cmp     %reg1, %reg0
    jge     .L94
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L91
.L94:
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L95
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_VAL], %reg0
    movl    88, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L95:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L96:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L97
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L96
.L97:
    jmp     .L89
.L90:
    movl    [%rbp+20], %reg0
    cmp     1, %reg0
    jnq     .L89
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L98
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_VAL], %reg0
    movl    88, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L98:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L99:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L100
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L99
.L100:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L101:
    movl    [%rbp-8], %reg0
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L102
    movl    [%rbp+12], %reg1
    sub     2, %reg1
    jmp     .L103
.L102:
    movl    [%rbp+12], %reg1
.L103:
    cmp     %reg1, %reg0
    jge     .L89
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L101
.L89:
    movl    0, %reg0
    add     8, %rsp
    popl    %rbp
    ret     

printoct:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
.L104:
    movl    buffer, %reg0
    movl    [%rbp-4], %reg1
    movl    [%rbp-4], %reg2
    add     1, %reg2
    movl    %reg2, [%rbp-4]
    add     %reg1, %reg0
    movl    [%rbp+8], %reg1
    and     7, %reg1
    add     48, %reg1
    and     255, %reg1
    movb    %reg1, [%reg0]
    movl    [%rbp+8], %reg0
    lsr     3, %reg0
    movl    %reg0, [%rbp+8]
    movl    [%rbp+8], %reg0
    cmp     0, %reg0
    ja      .L104
    movb    [%rbp+16], %reg0
    sxbl    %reg0
    cmp     48, %reg0
    jnq     .L105
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L106
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L106:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L107:
    movl    [%rbp-8], %reg0
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L108
    movl    [%rbp+12], %reg1
    sub     1, %reg1
    jmp     .L109
.L108:
    movl    [%rbp+12], %reg1
.L109:
    cmp     %reg1, %reg0
    jge     .L110
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L107
.L110:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L111:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L112
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L111
.L112:
    jmp     .L113
.L105:
    movl    [%rbp+20], %reg0
    cmp     0, %reg0
    jnq     .L114
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L115:
    movl    [%rbp-8], %reg0
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L116
    movl    [%rbp+12], %reg1
    sub     1, %reg1
    jmp     .L117
.L116:
    movl    [%rbp+12], %reg1
.L117:
    cmp     %reg1, %reg0
    jge     .L118
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L115
.L118:
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L119
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L119:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L120:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L121
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L120
.L121:
    jmp     .L113
.L114:
    movl    [%rbp+20], %reg0
    cmp     1, %reg0
    jnq     .L113
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L122
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L122:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L123:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L124
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L123
.L124:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L125:
    movl    [%rbp-8], %reg0
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L126
    movl    [%rbp+12], %reg1
    sub     1, %reg1
    jmp     .L127
.L126:
    movl    [%rbp+12], %reg1
.L127:
    cmp     %reg1, %reg0
    jge     .L113
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L125
.L113:
    movl    0, %reg0
    add     8, %rsp
    popl    %rbp
    ret     

printbin:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
.L128:
    movl    buffer, %reg0
    movl    [%rbp-4], %reg1
    movl    [%rbp-4], %reg2
    add     1, %reg2
    movl    %reg2, [%rbp-4]
    add     %reg1, %reg0
    movl    [%rbp+8], %reg1
    and     1, %reg1
    add     48, %reg1
    and     255, %reg1
    movb    %reg1, [%reg0]
    movl    [%rbp+8], %reg0
    lsr     1, %reg0
    movl    %reg0, [%rbp+8]
    movl    [%rbp+8], %reg0
    cmp     0, %reg0
    ja      .L128
    movb    [%rbp+16], %reg0
    sxbl    %reg0
    cmp     48, %reg0
    jnq     .L129
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L130
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_VAL], %reg0
    movl    98, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L130:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L131:
    movl    [%rbp-8], %reg0
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L132
    movl    [%rbp+12], %reg1
    sub     2, %reg1
    jmp     .L133
.L132:
    movl    [%rbp+12], %reg1
.L133:
    cmp     %reg1, %reg0
    jge     .L134
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L131
.L134:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L135:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L136
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L135
.L136:
    jmp     .L137
.L129:
    movl    [%rbp+20], %reg0
    cmp     0, %reg0
    jnq     .L138
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L139:
    movl    [%rbp-8], %reg0
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L140
    movl    [%rbp+12], %reg1
    sub     2, %reg1
    jmp     .L141
.L140:
    movl    [%rbp+12], %reg1
.L141:
    cmp     %reg1, %reg0
    jge     .L142
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L139
.L142:
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L143
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_VAL], %reg0
    movl    98, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L143:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L144:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L145
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L144
.L145:
    jmp     .L137
.L138:
    movl    [%rbp+20], %reg0
    cmp     1, %reg0
    jnq     .L137
    movl    [%rbp+24], %reg0
    cmp     0, %reg0
    jeq     .L146
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_VAL], %reg0
    movl    98, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
.L146:
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L147:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L148
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L147
.L148:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L149:
    movl    [%rbp-8], %reg0
    movl    [%rbp+24], %reg1
    cmp     0, %reg1
    jeq     .L150
    movl    [%rbp+12], %reg1
    sub     2, %reg1
    jmp     .L151
.L150:
    movl    [%rbp+12], %reg1
.L151:
    cmp     %reg1, %reg0
    jge     .L137
    movl    [TERM_OUT_VAL], %reg0
    movb    [%rbp+16], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L149
.L137:
    movl    0, %reg0
    add     8, %rsp
    popl    %rbp
    ret     

printptr:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     16, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
    movl    0, %reg0
    movl    %reg0, [%rbp-8]
.L152:
    movl    [%rbp-8], %reg0
    cmp     8, %reg0
    jge     .L153
    movl    [%rbp+8], %reg0
    and     15, %reg0
    movl    %reg0, [%rbp-12]
    movl    buffer, %reg0
    movl    [%rbp-4], %reg1
    movl    [%rbp-4], %reg2
    add     1, %reg2
    movl    %reg2, [%rbp-4]
    add     %reg1, %reg0
    movl    [%rbp-12], %reg1
    cmp     10, %reg1
    jge     .L154
    movl    [%rbp-12], %reg1
    add     48, %reg1
    jmp     .L155
.L154:
    movl    [%rbp-12], %reg1
    sub     10, %reg1
    add     97, %reg1
.L155:
    and     255, %reg1
    movb    %reg1, [%reg0]
    movl    [%rbp+8], %reg0
    lsr     4, %reg0
    movl    %reg0, [%rbp+8]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L152
.L153:
    movl    [%rbp+16], %reg0
    cmp     0, %reg0
    jnq     .L156
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L157:
    movl    [%rbp-8], %reg0
    movl    [%rbp+12], %reg1
    sub     2, %reg1
    cmp     %reg1, %reg0
    jge     .L158
    movl    [TERM_OUT_VAL], %reg0
    movl    32, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L157
.L158:
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_VAL], %reg0
    movl    120, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L159:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L160
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L159
.L160:
    jmp     .L161
.L156:
    movl    [%rbp+16], %reg0
    cmp     1, %reg0
    jnq     .L161
    movl    [TERM_OUT_VAL], %reg0
    movl    48, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_VAL], %reg0
    movl    120, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-4], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
.L162:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jlt     .L163
    movl    [TERM_OUT_VAL], %reg0
    movl    buffer, %reg1
    add     [%rbp-8], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L162
.L163:
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rbp-8]
.L164:
    movl    [%rbp-8], %reg0
    movl    [%rbp+12], %reg1
    sub     2, %reg1
    cmp     %reg1, %reg0
    jge     .L161
    movl    [TERM_OUT_VAL], %reg0
    movl    32, %reg1
    movl    %reg1, [%reg0]
    movl    [TERM_OUT_CTRL], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L164
.L161:
    movl    0, %reg0
    add     16, %rsp
    popl    %rbp
    ret     

printf:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     56, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-20]
    movl    0, %reg0
    movl    %reg0, [%rbp-24]
    movl    0, %reg0
    movl    %reg0, [%rbp-28]
    movl    0, %reg0
    movl    %reg0, [%rbp-32]
    movl    0, %reg0
    movl    %reg0, [%rbp-36]
    movl    4, %reg0
    movl    %reg0, [%rbp-40]
    movl    0, %reg0
    movl    %reg0, [%rbp-44]
    movl    4, %reg0
    movl    %reg0, [%rbp-48]
    movl    0, %reg0
    movl    %reg0, [%rbp-52]
.L165:
    movl    [%rbp+8], %reg0
    add     [%rbp-52], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
    cmp     0, %reg0
    jeq     .L166
    movl    [%rbp-24], %reg0
.section    .rodata
.LT1:
    .long   .L167
    .long   .L168
    .long   .L169
    .long   .L170
    .long   .L171
    .long   .L172
    .long   .L173
    .long   .L174
.section    .text
    cmp     8, %reg0
    jae     .L175
    lsl     2, %reg0
    add     .LT1, %reg0
    jmp     [%reg0]
.L174:
    movl    [%rbp-20], %reg0
    jmp     .L176
    jmp     .L175
.L167:
    movl    [%rbp+8], %reg0
    add     [%rbp-52], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
.section    .rodata
.LT2:
    .long   .L177
.section    .text
    sub     37, %reg0
    cmp     1, %reg0
    jae     .L178
    lsl     2, %reg0
    add     .LT2, %reg0
    jmp     [%reg0]
.L177:
    movl    1, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L179
.L178:
    sub     16, %rsp
    movl    [%rbp+8], %reg0
    add     [%rbp-52], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
    movl    %reg0, [%rsp]
    call    putchar
    add     16, %rsp
    jmp     .L179
.L179:
    jmp     .L175
.L168:
    movl    [%rbp+8], %reg0
    add     [%rbp-52], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
.section    .rodata
.LT3:
    .long   .L180
.section    .text
    sub     32, %reg0
    cmp     1, %reg0
    jae     .L181
    lsl     2, %reg0
    add     .LT3, %reg0
    jmp     [%reg0]
.L181:
.section    .rodata
.LT4:
    .long   .L182
    .long   .L183
    .long   .L184
.section    .text
    sub     3, %reg0
    cmp     3, %reg0
    jae     .L185
    lsl     2, %reg0
    add     .LT4, %reg0
    jmp     [%reg0]
.L185:
.section    .rodata
.LT5:
    .long   .L186
    .long   .L183
    .long   .L187
    .long   .L183
    .long   .L183
    .long   .L188
    .long   .L189
    .long   .L189
    .long   .L189
    .long   .L189
    .long   .L189
    .long   .L189
    .long   .L189
    .long   .L189
    .long   .L189
.section    .text
    sub     8, %reg0
    cmp     15, %reg0
    jae     .L190
    lsl     2, %reg0
    add     .LT5, %reg0
    jmp     [%reg0]
.L190:
.section    .rodata
.LT6:
    .long   .L191
.section    .text
    sub     45, %reg0
    cmp     1, %reg0
    jae     .L192
    lsl     2, %reg0
    add     .LT6, %reg0
    jmp     [%reg0]
.L192:
.section    .rodata
.LT7:
    .long   .L191
    .long   .L191
    .long   .L191
.section    .text
    sub     10, %reg0
    cmp     3, %reg0
    jae     .L193
    lsl     2, %reg0
    add     .LT7, %reg0
    jmp     [%reg0]
.L193:
.section    .rodata
.LT8:
    .long   .L194
    .long   .L191
.section    .text
    sub     6, %reg0
    cmp     2, %reg0
    jae     .L195
    lsl     2, %reg0
    add     .LT8, %reg0
    jmp     [%reg0]
.L195:
.section    .rodata
.LT9:
    .long   .L196
.section    .text
    sub     4, %reg0
    cmp     1, %reg0
    jae     .L197
    lsl     2, %reg0
    add     .LT9, %reg0
    jmp     [%reg0]
.L197:
.section    .rodata
.LT10:
    .long   .L191
    .long   .L191
.section    .text
    sub     3, %reg0
    cmp     2, %reg0
    jae     .L198
    lsl     2, %reg0
    add     .LT10, %reg0
    jmp     [%reg0]
.L198:
.section    .rodata
.LT11:
    .long   .L191
    .long   .L183
    .long   .L191
.section    .text
    sub     4, %reg0
    cmp     3, %reg0
    jae     .L199
    lsl     2, %reg0
    add     .LT11, %reg0
    jmp     [%reg0]
.L199:
.section    .rodata
.LT12:
    .long   .L191
.section    .text
    sub     5, %reg0
    cmp     1, %reg0
    jae     .L183
    lsl     2, %reg0
    add     .LT12, %reg0
    jmp     [%reg0]
.L184:
    sub     16, %rsp
    movl    [%rbp+8], %reg0
    add     [%rbp-52], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
    movl    %reg0, [%rsp]
    call    putchar
    add     16, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L200
.L187:
    movl    [%rbp-32], %reg0
    or      1, %reg0
    movl    %reg0, [%rbp-32]
    jmp     .L200
.L186:
    movl    [%rbp-32], %reg0
    or      2, %reg0
    movl    %reg0, [%rbp-32]
    jmp     .L200
.L188:
    movl    [%rbp-32], %reg0
    or      4, %reg0
    movl    %reg0, [%rbp-32]
    jmp     .L200
.L182:
    movl    [%rbp-32], %reg0
    or      8, %reg0
    movl    %reg0, [%rbp-32]
    jmp     .L200
.L180:
    movl    [%rbp-32], %reg0
    or      16, %reg0
    movl    %reg0, [%rbp-32]
    jmp     .L200
.L189:
    movl    2, %reg0
    movl    %reg0, [%rbp-24]
    movl    [%rbp-52], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-52]
    jmp     .L200
.L194:
    movl    4, %reg0
    movl    %reg0, [%rbp-24]
    movl    [%rbp-52], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-52]
    jmp     .L200
.L196:
    movl    5, %reg0
    movl    %reg0, [%rbp-24]
    movl    [%rbp-52], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-52]
    jmp     .L200
.L191:
    movl    6, %reg0
    movl    %reg0, [%rbp-24]
    movl    [%rbp-52], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-52]
    jmp     .L200
.L183:
    movl    7, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L200
.L200:
    jmp     .L175
.L169:
    movl    [%rbp+8], %reg0
    add     [%rbp-52], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
.section    .rodata
.LT13:
    .long   .L201
    .long   .L201
    .long   .L201
    .long   .L201
    .long   .L201
    .long   .L201
    .long   .L201
    .long   .L201
    .long   .L201
    .long   .L201
.section    .text
    sub     48, %reg0
    cmp     10, %reg0
    jae     .L202
    lsl     2, %reg0
    add     .LT13, %reg0
    jmp     [%reg0]
.L202:
.section    .rodata
.LT14:
    .long   .L203
.section    .text
    sub     40, %reg0
    cmp     1, %reg0
    jae     .L204
    lsl     2, %reg0
    add     .LT14, %reg0
    jmp     [%reg0]
.L204:
.section    .rodata
.LT15:
    .long   .L203
    .long   .L203
    .long   .L203
.section    .text
    sub     10, %reg0
    cmp     3, %reg0
    jae     .L205
    lsl     2, %reg0
    add     .LT15, %reg0
    jmp     [%reg0]
.L205:
.section    .rodata
.LT16:
    .long   .L206
    .long   .L203
.section    .text
    sub     6, %reg0
    cmp     2, %reg0
    jae     .L207
    lsl     2, %reg0
    add     .LT16, %reg0
    jmp     [%reg0]
.L207:
.section    .rodata
.LT17:
    .long   .L208
.section    .text
    sub     4, %reg0
    cmp     1, %reg0
    jae     .L209
    lsl     2, %reg0
    add     .LT17, %reg0
    jmp     [%reg0]
.L209:
.section    .rodata
.LT18:
    .long   .L203
    .long   .L203
.section    .text
    sub     3, %reg0
    cmp     2, %reg0
    jae     .L210
    lsl     2, %reg0
    add     .LT18, %reg0
    jmp     [%reg0]
.L210:
.section    .rodata
.LT19:
    .long   .L203
    .long   .L211
    .long   .L203
.section    .text
    sub     4, %reg0
    cmp     3, %reg0
    jae     .L212
    lsl     2, %reg0
    add     .LT19, %reg0
    jmp     [%reg0]
.L212:
.section    .rodata
.LT20:
    .long   .L203
.section    .text
    sub     5, %reg0
    cmp     1, %reg0
    jae     .L211
    lsl     2, %reg0
    add     .LT20, %reg0
    jmp     [%reg0]
.L201:
    movl    [%rbp-36], %reg0
    imul    10, %reg0
    movl    %reg0, [%rbp-36]
    movl    [%rbp-36], %reg0
    movl    [%rbp+8], %reg1
    add     [%rbp-52], %reg1
    movb    [%reg1], %reg1
    sxbl    %reg1
    sub     48, %reg1
    add     %reg1, %reg0
    movl    %reg0, [%rbp-36]
    jmp     .L213
.L206:
    movl    4, %reg0
    movl    %reg0, [%rbp-24]
    movl    [%rbp-52], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-52]
    jmp     .L213
.L208:
    movl    5, %reg0
    movl    %reg0, [%rbp-24]
    movl    [%rbp-52], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-52]
    jmp     .L213
.L203:
    movl    6, %reg0
    movl    %reg0, [%rbp-24]
    movl    [%rbp-52], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-52]
    jmp     .L213
.L211:
    movl    7, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L213
.L213:
    jmp     .L175
.L170:
    movl    [%rbp+8], %reg0
    add     [%rbp-52], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
.section    .rodata
.LT21:
    .long   .L214
.section    .text
    sub     88, %reg0
    cmp     1, %reg0
    jae     .L215
    lsl     2, %reg0
    add     .LT21, %reg0
    jmp     [%reg0]
.L215:
.section    .rodata
.LT22:
    .long   .L214
    .long   .L216
    .long   .L214
.section    .text
    sub     10, %reg0
    cmp     3, %reg0
    jae     .L217
    lsl     2, %reg0
    add     .LT22, %reg0
    jmp     [%reg0]
.L217:
.section    .rodata
.LT23:
    .long   .L218
    .long   .L214
.section    .text
    sub     6, %reg0
    cmp     2, %reg0
    jae     .L219
    lsl     2, %reg0
    add     .LT23, %reg0
    jmp     [%reg0]
.L219:
.section    .rodata
.LT24:
    .long   .L214
.section    .text
    sub     7, %reg0
    cmp     1, %reg0
    jae     .L220
    lsl     2, %reg0
    add     .LT24, %reg0
    jmp     [%reg0]
.L220:
.section    .rodata
.LT25:
    .long   .L214
.section    .text
    sub     6, %reg0
    cmp     1, %reg0
    jae     .L221
    lsl     2, %reg0
    add     .LT25, %reg0
    jmp     [%reg0]
.L221:
.section    .rodata
.LT26:
    .long   .L214
.section    .text
    sub     3, %reg0
    cmp     1, %reg0
    jae     .L216
    lsl     2, %reg0
    add     .LT26, %reg0
    jmp     [%reg0]
.L218:
    movl    1, %reg0
    movl    %reg0, [%rbp-40]
    movl    6, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L222
.L214:
    movl    6, %reg0
    movl    %reg0, [%rbp-24]
    movl    [%rbp-52], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-52]
    jmp     .L222
.L216:
    movl    7, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L222
.L222:
    jmp     .L175
.L171:
    movl    [%rbp+8], %reg0
    add     [%rbp-52], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
.section    .rodata
.LT27:
    .long   .L223
.section    .text
    sub     88, %reg0
    cmp     1, %reg0
    jae     .L224
    lsl     2, %reg0
    add     .LT27, %reg0
    jmp     [%reg0]
.L224:
.section    .rodata
.LT28:
    .long   .L223
    .long   .L225
    .long   .L223
.section    .text
    sub     10, %reg0
    cmp     3, %reg0
    jae     .L226
    lsl     2, %reg0
    add     .LT28, %reg0
    jmp     [%reg0]
.L226:
.section    .rodata
.LT29:
    .long   .L227
    .long   .L223
.section    .text
    sub     6, %reg0
    cmp     2, %reg0
    jae     .L228
    lsl     2, %reg0
    add     .LT29, %reg0
    jmp     [%reg0]
.L228:
.section    .rodata
.LT30:
    .long   .L223
.section    .text
    sub     7, %reg0
    cmp     1, %reg0
    jae     .L229
    lsl     2, %reg0
    add     .LT30, %reg0
    jmp     [%reg0]
.L229:
.section    .rodata
.LT31:
    .long   .L223
.section    .text
    sub     6, %reg0
    cmp     1, %reg0
    jae     .L230
    lsl     2, %reg0
    add     .LT31, %reg0
    jmp     [%reg0]
.L230:
.section    .rodata
.LT32:
    .long   .L223
.section    .text
    sub     3, %reg0
    cmp     1, %reg0
    jae     .L225
    lsl     2, %reg0
    add     .LT32, %reg0
    jmp     [%reg0]
.L227:
    movl    2, %reg0
    movl    %reg0, [%rbp-40]
    movl    3, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L231
.L223:
    movl    6, %reg0
    movl    %reg0, [%rbp-24]
    movl    [%rbp-52], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-52]
    jmp     .L231
.L225:
    movl    7, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L231
.L231:
    jmp     .L175
.L172:
    movl    [%rbp+8], %reg0
    add     [%rbp-52], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
.section    .rodata
.LT33:
    .long   .L232
.section    .text
    sub     88, %reg0
    cmp     1, %reg0
    jae     .L233
    lsl     2, %reg0
    add     .LT33, %reg0
    jmp     [%reg0]
.L233:
.section    .rodata
.LT34:
    .long   .L232
    .long   .L234
    .long   .L232
.section    .text
    sub     10, %reg0
    cmp     3, %reg0
    jae     .L235
    lsl     2, %reg0
    add     .LT34, %reg0
    jmp     [%reg0]
.L235:
.section    .rodata
.LT35:
    .long   .L232
.section    .text
    sub     7, %reg0
    cmp     1, %reg0
    jae     .L236
    lsl     2, %reg0
    add     .LT35, %reg0
    jmp     [%reg0]
.L236:
.section    .rodata
.LT36:
    .long   .L237
.section    .text
    sub     3, %reg0
    cmp     1, %reg0
    jae     .L238
    lsl     2, %reg0
    add     .LT36, %reg0
    jmp     [%reg0]
.L238:
.section    .rodata
.LT37:
    .long   .L232
.section    .text
    sub     3, %reg0
    cmp     1, %reg0
    jae     .L239
    lsl     2, %reg0
    add     .LT37, %reg0
    jmp     [%reg0]
.L239:
.section    .rodata
.LT38:
    .long   .L232
.section    .text
    sub     6, %reg0
    cmp     1, %reg0
    jae     .L240
    lsl     2, %reg0
    add     .LT38, %reg0
    jmp     [%reg0]
.L240:
.section    .rodata
.LT39:
    .long   .L232
.section    .text
    sub     3, %reg0
    cmp     1, %reg0
    jae     .L234
    lsl     2, %reg0
    add     .LT39, %reg0
    jmp     [%reg0]
.L237:
    movl    4, %reg0
    movl    %reg0, [%rbp-40]
    movl    6, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L241
.L232:
    movl    6, %reg0
    movl    %reg0, [%rbp-24]
    movl    [%rbp-52], %reg0
    sub     1, %reg0
    movl    %reg0, [%rbp-52]
    jmp     .L241
.L234:
    movl    7, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L241
.L241:
    jmp     .L175
.L173:
    movl    [%rbp+8], %reg0
    add     [%rbp-52], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
.section    .rodata
.LT40:
    .long   .L242
.section    .text
    sub     88, %reg0
    cmp     1, %reg0
    jae     .L243
    lsl     2, %reg0
    add     .LT40, %reg0
    jmp     [%reg0]
.L243:
.section    .rodata
.LT41:
    .long   .L244
    .long   .L245
    .long   .L246
.section    .text
    sub     10, %reg0
    cmp     3, %reg0
    jae     .L247
    lsl     2, %reg0
    add     .LT41, %reg0
    jmp     [%reg0]
.L247:
.section    .rodata
.LT42:
    .long   .L246
.section    .text
    sub     7, %reg0
    cmp     1, %reg0
    jae     .L248
    lsl     2, %reg0
    add     .LT42, %reg0
    jmp     [%reg0]
.L248:
.section    .rodata
.LT43:
    .long   .L249
    .long   .L250
.section    .text
    sub     6, %reg0
    cmp     2, %reg0
    jae     .L251
    lsl     2, %reg0
    add     .LT43, %reg0
    jmp     [%reg0]
.L251:
.section    .rodata
.LT44:
    .long   .L252
    .long   .L253
    .long   .L254
.section    .text
    sub     4, %reg0
    cmp     3, %reg0
    jae     .L255
    lsl     2, %reg0
    add     .LT44, %reg0
    jmp     [%reg0]
.L255:
.section    .rodata
.LT45:
    .long   .L256
.section    .text
    sub     5, %reg0
    cmp     1, %reg0
    jae     .L253
    lsl     2, %reg0
    add     .LT45, %reg0
    jmp     [%reg0]
.L246:
    movl    0, %reg0
    movl    %reg0, [%rbp-44]
    movl    0, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L257
.L254:
    movl    1, %reg0
    movl    %reg0, [%rbp-44]
    movl    0, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L257
.L256:
    movl    2, %reg0
    movl    %reg0, [%rbp-44]
    movl    0, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L257
.L242:
    movl    3, %reg0
    movl    %reg0, [%rbp-44]
    movl    0, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L257
.L244:
    movl    5, %reg0
    movl    %reg0, [%rbp-44]
    movl    0, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L257
.L249:
    movl    4, %reg0
    movl    %reg0, [%rbp-44]
    movl    0, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L257
.L245:
    movl    6, %reg0
    movl    %reg0, [%rbp-44]
    movl    0, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L257
.L252:
    movl    7, %reg0
    movl    %reg0, [%rbp-44]
    movl    0, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L257
.L250:
    movl    8, %reg0
    movl    %reg0, [%rbp-44]
    movl    0, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L257
.L253:
    movl    7, %reg0
    movl    %reg0, [%rbp-24]
    jmp     .L257
.L257:
    movl    [%rbp-44], %reg0
.section    .rodata
.LT46:
    .long   .L258
    .long   .L259
    .long   .L260
    .long   .L261
    .long   .L262
    .long   .L263
    .long   .L264
    .long   .L265
    .long   .L266
.section    .text
    cmp     9, %reg0
    jae     .L267
    lsl     2, %reg0
    add     .LT46, %reg0
    jmp     [%reg0]
.L258:
    sub     16, %rsp
    movl    %rbp-48, %reg0
    movl    %reg0, [%rsp]
    movl    [%rbp-40], %reg0
    movl    %reg0, [%rsp+4]
    call    get_variadic_param
    add     16, %rsp
    movl    %reg0, [%rbp-56]
    sub     32, %rsp
    movl    [%rbp-40], %reg0
    cmp     4, %reg0
    jnq     .L268
    movl    [%rbp-56], %reg0
    movl    [%reg0], %reg0
    jmp     .L269
.L268:
    movl    [%rbp-40], %reg0
    cmp     2, %reg0
    jnq     .L270
    movl    [%rbp-56], %reg0
    movw    [%reg0], %reg0
    sxwl    %reg0
    jmp     .L271
.L270:
    movl    [%rbp-56], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
.L271:
.L269:
    movl    %reg0, [%rsp]
    movl    [%rbp-36], %reg0
    movl    %reg0, [%rsp+4]
    movl    [%rbp-32], %reg0
    and     4, %reg0
    cmp     0, %reg0
    jeq     .L272
    movl    48, %reg0
    jmp     .L273
.L272:
    movl    32, %reg0
.L273:
    and     255, %reg0
    movb    %reg0, [%rsp+8]
    movl    [%rbp-32], %reg0
    and     1, %reg0
    cmp     0, %reg0
    jeq     .L274
    movl    1, %reg0
    jmp     .L275
.L274:
    movl    0, %reg0
.L275:
    movl    %reg0, [%rsp+12]
    movl    [%rbp-32], %reg0
    and     2, %reg0
    cmp     0, %reg0
    jeq     .L276
    movl    1, %reg0
    jmp     .L277
.L276:
    movl    0, %reg0
.L277:
    movl    %reg0, [%rsp+16]
    call    printdec
    add     32, %rsp
    jmp     .L267
.L259:
    sub     16, %rsp
    movl    %rbp-48, %reg0
    movl    %reg0, [%rsp]
    movl    [%rbp-40], %reg0
    movl    %reg0, [%rsp+4]
    call    get_variadic_param
    add     16, %rsp
    movl    %reg0, [%rbp-56]
    sub     16, %rsp
    movl    [%rbp-40], %reg0
    cmp     4, %reg0
    jnq     .L278
    movl    [%rbp-56], %reg0
    movl    [%reg0], %reg0
    jmp     .L279
.L278:
    movl    [%rbp-40], %reg0
    cmp     2, %reg0
    jnq     .L280
    movl    [%rbp-56], %reg0
    movw    [%reg0], %reg0
    zxwl    %reg0
    jmp     .L281
.L280:
    movl    [%rbp-56], %reg0
    movb    [%reg0], %reg0
    zxbl    %reg0
.L281:
.L279:
    movl    %reg0, [%rsp]
    movl    [%rbp-36], %reg0
    movl    %reg0, [%rsp+4]
    movl    [%rbp-32], %reg0
    and     4, %reg0
    cmp     0, %reg0
    jeq     .L282
    movl    48, %reg0
    jmp     .L283
.L282:
    movl    32, %reg0
.L283:
    and     255, %reg0
    movb    %reg0, [%rsp+8]
    movl    [%rbp-32], %reg0
    and     1, %reg0
    cmp     0, %reg0
    jeq     .L284
    movl    1, %reg0
    jmp     .L285
.L284:
    movl    0, %reg0
.L285:
    movl    %reg0, [%rsp+12]
    call    printdecu
    add     16, %rsp
    jmp     .L267
.L260:
    sub     16, %rsp
    movl    %rbp-48, %reg0
    movl    %reg0, [%rsp]
    movl    [%rbp-40], %reg0
    movl    %reg0, [%rsp+4]
    call    get_variadic_param
    add     16, %rsp
    movl    %reg0, [%rbp-56]
    sub     32, %rsp
    movl    [%rbp-40], %reg0
    cmp     4, %reg0
    jnq     .L286
    movl    [%rbp-56], %reg0
    movl    [%reg0], %reg0
    jmp     .L287
.L286:
    movl    [%rbp-40], %reg0
    cmp     2, %reg0
    jnq     .L288
    movl    [%rbp-56], %reg0
    movw    [%reg0], %reg0
    zxwl    %reg0
    jmp     .L289
.L288:
    movl    [%rbp-56], %reg0
    movb    [%reg0], %reg0
    zxbl    %reg0
.L289:
.L287:
    movl    %reg0, [%rsp]
    movl    [%rbp-36], %reg0
    movl    %reg0, [%rsp+4]
    movl    [%rbp-32], %reg0
    and     4, %reg0
    cmp     0, %reg0
    jeq     .L290
    movl    48, %reg0
    jmp     .L291
.L290:
    movl    32, %reg0
.L291:
    and     255, %reg0
    movb    %reg0, [%rsp+8]
    movl    [%rbp-32], %reg0
    and     1, %reg0
    cmp     0, %reg0
    jeq     .L292
    movl    1, %reg0
    jmp     .L293
.L292:
    movl    0, %reg0
.L293:
    movl    %reg0, [%rsp+12]
    movl    [%rbp-32], %reg0
    and     8, %reg0
    cmp     0, %reg0
    jeq     .L294
    movl    1, %reg0
    jmp     .L295
.L294:
    movl    0, %reg0
.L295:
    movl    %reg0, [%rsp+16]
    call    printhexlw
    add     32, %rsp
    jmp     .L267
.L261:
    sub     16, %rsp
    movl    %rbp-48, %reg0
    movl    %reg0, [%rsp]
    movl    [%rbp-40], %reg0
    movl    %reg0, [%rsp+4]
    call    get_variadic_param
    add     16, %rsp
    movl    %reg0, [%rbp-56]
    sub     32, %rsp
    movl    [%rbp-40], %reg0
    cmp     4, %reg0
    jnq     .L296
    movl    [%rbp-56], %reg0
    movl    [%reg0], %reg0
    jmp     .L297
.L296:
    movl    [%rbp-40], %reg0
    cmp     2, %reg0
    jnq     .L298
    movl    [%rbp-56], %reg0
    movw    [%reg0], %reg0
    zxwl    %reg0
    jmp     .L299
.L298:
    movl    [%rbp-56], %reg0
    movb    [%reg0], %reg0
    zxbl    %reg0
.L299:
.L297:
    movl    %reg0, [%rsp]
    movl    [%rbp-36], %reg0
    movl    %reg0, [%rsp+4]
    movl    [%rbp-32], %reg0
    and     4, %reg0
    cmp     0, %reg0
    jeq     .L300
    movl    48, %reg0
    jmp     .L301
.L300:
    movl    32, %reg0
.L301:
    and     255, %reg0
    movb    %reg0, [%rsp+8]
    movl    [%rbp-32], %reg0
    and     1, %reg0
    cmp     0, %reg0
    jeq     .L302
    movl    1, %reg0
    jmp     .L303
.L302:
    movl    0, %reg0
.L303:
    movl    %reg0, [%rsp+12]
    movl    [%rbp-32], %reg0
    and     8, %reg0
    cmp     0, %reg0
    jeq     .L304
    movl    1, %reg0
    jmp     .L305
.L304:
    movl    0, %reg0
.L305:
    movl    %reg0, [%rsp+16]
    call    printhexup
    add     32, %rsp
    jmp     .L267
.L262:
    sub     16, %rsp
    movl    %rbp-48, %reg0
    movl    %reg0, [%rsp]
    movl    [%rbp-40], %reg0
    movl    %reg0, [%rsp+4]
    call    get_variadic_param
    add     16, %rsp
    movl    %reg0, [%rbp-56]
    sub     32, %rsp
    movl    [%rbp-40], %reg0
    cmp     4, %reg0
    jnq     .L306
    movl    [%rbp-56], %reg0
    movl    [%reg0], %reg0
    jmp     .L307
.L306:
    movl    [%rbp-40], %reg0
    cmp     2, %reg0
    jnq     .L308
    movl    [%rbp-56], %reg0
    movw    [%reg0], %reg0
    zxwl    %reg0
    jmp     .L309
.L308:
    movl    [%rbp-56], %reg0
    movb    [%reg0], %reg0
    zxbl    %reg0
.L309:
.L307:
    movl    %reg0, [%rsp]
    movl    [%rbp-36], %reg0
    movl    %reg0, [%rsp+4]
    movl    [%rbp-32], %reg0
    and     4, %reg0
    cmp     0, %reg0
    jeq     .L310
    movl    48, %reg0
    jmp     .L311
.L310:
    movl    32, %reg0
.L311:
    and     255, %reg0
    movb    %reg0, [%rsp+8]
    movl    [%rbp-32], %reg0
    and     1, %reg0
    cmp     0, %reg0
    jeq     .L312
    movl    1, %reg0
    jmp     .L313
.L312:
    movl    0, %reg0
.L313:
    movl    %reg0, [%rsp+12]
    movl    [%rbp-32], %reg0
    and     8, %reg0
    cmp     0, %reg0
    jeq     .L314
    movl    1, %reg0
    jmp     .L315
.L314:
    movl    0, %reg0
.L315:
    movl    %reg0, [%rsp+16]
    call    printoct
    add     32, %rsp
    jmp     .L267
.L263:
    sub     16, %rsp
    movl    %rbp-48, %reg0
    movl    %reg0, [%rsp]
    movl    [%rbp-40], %reg0
    movl    %reg0, [%rsp+4]
    call    get_variadic_param
    add     16, %rsp
    movl    %reg0, [%rbp-56]
    sub     32, %rsp
    movl    [%rbp-40], %reg0
    cmp     4, %reg0
    jnq     .L316
    movl    [%rbp-56], %reg0
    movl    [%reg0], %reg0
    jmp     .L317
.L316:
    movl    [%rbp-40], %reg0
    cmp     2, %reg0
    jnq     .L318
    movl    [%rbp-56], %reg0
    movw    [%reg0], %reg0
    zxwl    %reg0
    jmp     .L319
.L318:
    movl    [%rbp-56], %reg0
    movb    [%reg0], %reg0
    zxbl    %reg0
.L319:
.L317:
    movl    %reg0, [%rsp]
    movl    [%rbp-36], %reg0
    movl    %reg0, [%rsp+4]
    movl    [%rbp-32], %reg0
    and     4, %reg0
    cmp     0, %reg0
    jeq     .L320
    movl    48, %reg0
    jmp     .L321
.L320:
    movl    32, %reg0
.L321:
    and     255, %reg0
    movb    %reg0, [%rsp+8]
    movl    [%rbp-32], %reg0
    and     1, %reg0
    cmp     0, %reg0
    jeq     .L322
    movl    1, %reg0
    jmp     .L323
.L322:
    movl    0, %reg0
.L323:
    movl    %reg0, [%rsp+12]
    movl    [%rbp-32], %reg0
    and     8, %reg0
    cmp     0, %reg0
    jeq     .L324
    movl    1, %reg0
    jmp     .L325
.L324:
    movl    0, %reg0
.L325:
    movl    %reg0, [%rsp+16]
    call    printbin
    add     32, %rsp
    jmp     .L267
.L264:
    sub     16, %rsp
    movl    %rbp-48, %reg0
    movl    %reg0, [%rsp]
    movl    1, %reg0
    movl    %reg0, [%rsp+4]
    call    get_variadic_param
    add     16, %rsp
    movl    %reg0, [%rbp-56]
    sub     16, %rsp
    movl    [%rbp-56], %reg0
    movb    [%reg0], %reg0
    sxbl    %reg0
    movl    %reg0, [%rsp]
    call    putchar
    add     16, %rsp
    jmp     .L267
.L265:
    sub     16, %rsp
    movl    %rbp-48, %reg0
    movl    %reg0, [%rsp]
    movl    4, %reg0
    movl    %reg0, [%rsp+4]
    call    get_variadic_param
    add     16, %rsp
    movl    %reg0, [%rbp-56]
    sub     16, %rsp
    movl    [%rbp-56], %reg0
    movl    [%reg0], %reg0
    movl    %reg0, [%rsp]
    movl    [%rbp-36], %reg0
    movl    %reg0, [%rsp+4]
    movl    [%rbp-32], %reg0
    and     1, %reg0
    cmp     0, %reg0
    jeq     .L326
    movl    1, %reg0
    jmp     .L327
.L326:
    movl    0, %reg0
.L327:
    movl    %reg0, [%rsp+8]
    call    printstr
    add     16, %rsp
    jmp     .L267
.L266:
    sub     16, %rsp
    movl    %rbp-48, %reg0
    movl    %reg0, [%rsp]
    movl    4, %reg0
    movl    %reg0, [%rsp+4]
    call    get_variadic_param
    add     16, %rsp
    movl    %reg0, [%rbp-56]
    sub     16, %rsp
    movl    [%rbp-56], %reg0
    movl    [%reg0], %reg0
    movl    %reg0, [%rsp]
    movl    [%rbp-36], %reg0
    movl    %reg0, [%rsp+4]
    movl    [%rbp-32], %reg0
    and     1, %reg0
    cmp     0, %reg0
    jeq     .L328
    movl    1, %reg0
    jmp     .L329
.L328:
    movl    0, %reg0
.L329:
    movl    %reg0, [%rsp+8]
    call    printptr
    add     16, %rsp
    jmp     .L267
.L267:
    movl    0, %reg0
    movl    %reg0, [%rbp-32]
    movl    0, %reg0
    movl    %reg0, [%rbp-36]
    movl    4, %reg0
    movl    %reg0, [%rbp-40]
    movl    0, %reg0
    movl    %reg0, [%rbp-44]
    movl    [%rbp-20], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-20]
    jmp     .L175
.L175:
    movl    [%rbp-52], %reg0
    add     1, %reg0
    movl    %reg0, [%rbp-52]
    jmp     .L165
.L166:
    movl    [%rbp-20], %reg0
.L176:
    add     56, %rsp
    popl    %rbp
    ret     

.end