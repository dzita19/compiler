.global malloc
.global free
.global print_malloc_frames

.extern printf

.section    .data
HEAP_START:
    .long   262144
HEAP_END:
    .long   524288

.LP0:
    .long   0

.section    .rodata
.LP1:
    .asciz  "MALLOC FRAMES:\n"
.LP2:
    .asciz  "MALLOC FRAME: %p, %8s, size: %#010x, prev: %p, next: %p\n"
.LP3:
    .asciz  "FREE"
.LP4:
    .asciz  "NOT_FREE"
.LP5:
    .asciz  "TOTAL SIZE:   %#010x\n\n"
.LP6:
    .asciz  "WARNING: TOTAL SIZE DOESN'T MATCH THE HEAP SIZE!\n"

.section    .text

malloc:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    movl    [.LP0], %reg0
    cmp     0, %reg0
    jnq     .L1
    movl    1, %reg0
    movl    %reg0, [.LP0]
    movl    [HEAP_START], %reg0
    movl    %reg0, [%rbp-4]
    movl    [%rbp-4], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-4], %reg0
    movl    [HEAP_END], %reg1
    sub     [HEAP_START], %reg1
    sub     16, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-4], %reg0
    movl    0, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-4], %reg0
    movl    0, %reg1
    movl    %reg1, [%reg0]
.L1:
    movl    [%rbp+8], %reg0
    add     15, %reg0
    and     -16, %reg0
    movl    %reg0, [%rbp+8]
    movl    [HEAP_START], %reg0
    movl    %reg0, [%rbp-4]
.L2:
    movl    [%rbp-4], %reg0
    cmp     0, %reg0
    jeq     .L3
    movl    [%rbp-4], %reg0
    movl    [%reg0], %reg0
    cmp     0, %reg0
    jeq     .L4
    movl    [%rbp-4], %reg0
    add     4, %reg0
    movl    [%reg0], %reg0
    movl    [%rbp+8], %reg1
    add     16, %reg1
    cmp     %reg1, %reg0
    jb      .L4
    movl    [%rbp-4], %reg0
    movl    16, %reg1
    add     [%rbp+8], %reg1
    add     %reg1, %reg0
    movl    %reg0, [%rbp-8]
    movl    [%rbp-8], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    movl    [%rbp-4], %reg1
    add     4, %reg1
    movl    [%reg1], %reg1
    movl    16, %reg2
    add     [%rbp+8], %reg2
    sub     %reg2, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    movl    [%rbp-4], %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-8], %reg0
    movl    [%rbp-4], %reg1
    add     12, %reg1
    movl    [%reg1], %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-4], %reg0
    movl    0, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-4], %reg0
    movl    [%rbp+8], %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-4], %reg0
    movl    [%rbp-8], %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-4], %reg0
    add     16, %reg0
    jmp     .L5
.L4:
    movl    [%rbp-4], %reg0
    add     12, %reg0
    movl    [%reg0], %reg0
    movl    %reg0, [%rbp-4]
    jmp     .L2
.L3:
    movl    0, %reg0
.L5:
    add     8, %rsp
    popl    %rbp
    ret     

free:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     16, %rsp
    movl    [%rbp+8], %reg0
    sub     16, %reg0
    movl    %reg0, [%rbp-4]
    movl    [%rbp-4], %reg0
    movl    1, %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-4], %reg0
    add     12, %reg0
    movl    [%reg0], %reg0
    movl    %reg0, [%rbp-8]
    movl    [%rbp-4], %reg0
    add     8, %reg0
    movl    [%reg0], %reg0
    movl    %reg0, [%rbp-12]
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jeq     .L6
    movl    [%rbp-8], %reg0
    movl    [%reg0], %reg0
    cmp     0, %reg0
    jeq     .L6
    movl    [%rbp-8], %reg0
    add     12, %reg0
    movl    [%reg0], %reg0
    cmp     0, %reg0
    jeq     .L7
    movl    [%rbp-8], %reg0
    add     12, %reg0
    movl    [%reg0], %reg0
    movl    [%rbp-4], %reg1
    movl    %reg1, [%reg0]
.L7:
    movl    [%rbp-4], %reg0
    movl    [%rbp-8], %reg1
    add     12, %reg1
    movl    [%reg1], %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-4], %reg0
    movl    [%rbp-4], %reg1
    movl    [%reg1], %reg1
    movl    [%rbp-8], %reg2
    add     20, %reg2
    movl    [%reg2], %reg2
    add     %reg2, %reg1
    movl    %reg1, [%reg0]
.L6:
    movl    [%rbp-12], %reg0
    cmp     0, %reg0
    jeq     .L8
    movl    [%rbp-12], %reg0
    movl    [%reg0], %reg0
    cmp     0, %reg0
    jeq     .L8
    movl    [%rbp-4], %reg0
    add     12, %reg0
    movl    [%reg0], %reg0
    cmp     0, %reg0
    jeq     .L9
    movl    [%rbp-4], %reg0
    add     12, %reg0
    movl    [%reg0], %reg0
    movl    [%rbp-12], %reg1
    movl    %reg1, [%reg0]
.L9:
    movl    [%rbp-12], %reg0
    movl    [%rbp-4], %reg1
    add     12, %reg1
    movl    [%reg1], %reg1
    movl    %reg1, [%reg0]
    movl    [%rbp-12], %reg0
    movl    [%rbp-12], %reg1
    movl    [%reg1], %reg1
    movl    [%rbp-4], %reg2
    add     20, %reg2
    movl    [%reg2], %reg2
    add     %reg2, %reg1
    movl    %reg1, [%reg0]
.L8:
    add     16, %rsp
    popl    %rbp
    ret     

print_malloc_frames:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     8, %rsp
    sub     16, %rsp
    movl    .LP1, %reg0
    movl    %reg0, [%rsp]
    call    printf
    add     16, %rsp
    movl    0, %reg0
    movl    %reg0, [%rbp-4]
    movl    [HEAP_START], %reg0
    movl    %reg0, [%rbp-8]
.L10:
    movl    [%rbp-8], %reg0
    cmp     0, %reg0
    jeq     .L11
    movl    [%rbp-4], %reg0
    movl    [%rbp-8], %reg1
    add     20, %reg1
    movl    [%reg1], %reg1
    add     %reg1, %reg0
    movl    %reg0, [%rbp-4]
    sub     32, %rsp
    movl    .LP2, %reg0
    movl    %reg0, [%rsp]
    movl    [%rbp-8], %reg0
    movl    %reg0, [%rsp+4]
    movl    [%rbp-8], %reg0
    movl    [%reg0], %reg0
    cmp     0, %reg0
    jeq     .L12
    movl    .LP3, %reg0
    jmp     .L13
.L12:
    movl    .LP4, %reg0
.L13:
    movl    %reg0, [%rsp+8]
    movl    [%rbp-8], %reg0
    add     4, %reg0
    movl    [%reg0], %reg0
    movl    %reg0, [%rsp+12]
    movl    [%rbp-8], %reg0
    add     8, %reg0
    movl    [%reg0], %reg0
    movl    %reg0, [%rsp+16]
    movl    [%rbp-8], %reg0
    add     12, %reg0
    movl    [%reg0], %reg0
    movl    %reg0, [%rsp+20]
    call    printf
    add     32, %rsp
    movl    [%rbp-8], %reg0
    add     12, %reg0
    movl    [%reg0], %reg0
    movl    %reg0, [%rbp-8]
    jmp     .L10
.L11:
    sub     16, %rsp
    movl    .LP5, %reg0
    movl    %reg0, [%rsp]
    movl    [%rbp-4], %reg0
    movl    %reg0, [%rsp+4]
    call    printf
    add     16, %rsp
    movl    [%rbp-4], %reg0
    movl    [HEAP_END], %reg1
    sub     [HEAP_START], %reg1
    cmp     %reg1, %reg0
    jeq     .L14
    sub     16, %rsp
    movl    .LP6, %reg0
    movl    %reg0, [%rsp]
    call    printf
    add     16, %rsp
.L14:
    add     8, %rsp
    popl    %rbp
    ret     

.end