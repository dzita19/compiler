/* TEST 006: Arithmetic assigns */

int main(void){
  int a, b, c, d;
  a += b += c += d;
  a += (b, c);
  a += b * c - d;
}

/*.section    .text

main:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     $16, %rsp
    movl    (%rbp-4), %reg0
    movl    (%rbp-8), %reg1
    movl    (%rbp-12), %reg2
    add     (%rbp-16), %reg2
    movl    %reg2, (%rbp-12)
    add     (%rbp-12), %reg1
    movl    %reg1, (%rbp-8)
    add     (%rbp-8), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-4), %reg0
    add     (%rbp-12), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-4), %reg0
    movl    (%rbp-8), %reg1
    mul     (%rbp-12), %reg1
    sub     (%rbp-16), %reg1
    add     %reg1, %reg0
    movl    %reg0, (%rbp-4)
    add     $16, %rsp
    popl    %rbp

.end*/