/* TEST 004: Simple arithmetic expressions */

int main(void){
  int a, b, c;

  a = b +  c;
  a = b -  c;
  a = b *  c;
  a = b /  c;
  a = b %  c;
  a = b << c;
  a = b >> c;
  a = b &  c;
  a = b ^  c;
  a = b |  c;

  a +=  b;
  a -=  b;
  a *=  b;
  a /=  b;
  a %=  b;
  a <<= b;
  a >>= b;
  a &=  b;
  a ^=  b;
  a |=  b;
}

/* EXPECTED OUTPUT:

.section    .text

main:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     $16, %rsp
    movl    (%rbp-8), %reg0
    add     (%rbp-12), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-8), %reg0
    sub     (%rbp-12), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-8), %reg0
    mul     (%rbp-12), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-8), %reg0
    div     (%rbp-12), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-8), %reg0
    mod     (%rbp-12), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-8), %reg0
    asl     (%rbp-12), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-8), %reg0
    asr     (%rbp-12), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-8), %reg0
    and     (%rbp-12), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-8), %reg0
    xor     (%rbp-12), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-8), %reg0
    or      (%rbp-12), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-4), %reg0
    add     (%rbp-8), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-4), %reg0
    sub     (%rbp-8), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-4), %reg0
    mul     (%rbp-8), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-4), %reg0
    div     (%rbp-8), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-4), %reg0
    mod     (%rbp-8), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-4), %reg0
    asl     (%rbp-8), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-4), %reg0
    asr     (%rbp-8), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-4), %reg0
    and     (%rbp-8), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-4), %reg0
    xor     (%rbp-8), %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-4), %reg0
    or      (%rbp-8), %reg0
    movl    %reg0, (%rbp-4)
    add     $16, %rsp
    popl    %rbp

.end*/