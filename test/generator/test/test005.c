/* TEST 005: Complex arithmetic expressions (spilling) */

int main(void){
  int a, b, c, d, e, f, g, h, i, j;
  a = b | c >> d + e * (f | g >> h + i * j);
}

/*EXPECTED OUTPUT:

.section    .text

main:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     $40, %rsp
    movl    (%rbp-8), %reg0
    movl    (%rbp-12), %reg1
    movl    (%rbp-16), %reg2
    sub     $16, %rsp
    movl    %reg0, (%rbp-44)
    movl    (%rbp-20), %reg0
    movl    %reg1, (%rbp-48)
    movl    (%rbp-24), %reg1
    movl    %reg2, (%rbp-52)
    movl    (%rbp-28), %reg2
    movl    %reg0, (%rbp-56)
    movl    (%rbp-32), %reg0
    sub     $16, %rsp
    movl    %reg1, (%rbp-60)
    movl    (%rbp-36), %reg1
    mul     (%rbp-40), %reg1
    add     %reg1, %reg0
    asr     %reg0, %reg2
    movl    (%rbp-60), %reg1
    add     $16, %rsp
    or      %reg2, %reg1
    movl    (%rbp-56), %reg0
    mul     %reg1, %reg0
    movl    (%rbp-52), %reg2
    add     %reg0, %reg2
    movl    (%rbp-48), %reg1
    asr     %reg2, %reg1
    movl    (%rbp-44), %reg0
    add     $16, %rsp
    or      %reg1, %reg0
    movl    %reg0, (%rbp-4)
    add     $40, %rsp
    popl    %rbp

.end*/