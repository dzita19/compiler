/* TEST 003: Variable referencing */

int x, y;

int main(void){
  int a, b;
  static int d, e;

  x = y;
  x = b;
  x = e;

  a = y;
  a = b;
  a = e;

  d = y;
  d = b;
  d = e;
}

/*EXPECTED OUTPUT:

.section    .data
x:
    .zero   4
y:
    .zero   4

.LP0:
    .zero   4
    .zero   4

.section    .text

main:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     $8, %rsp
    movl    y, %reg0
    movl    %reg0, x
    movl    (%rbp-8), %reg0
    movl    %reg0, x
    movl    .LP0+4, %reg0
    movl    %reg0, x
    movl    y, %reg0
    movl    %reg0, (%rbp-4)
    movl    (%rbp-8), %reg0
    movl    %reg0, (%rbp-4)
    movl    .LP0+4, %reg0
    movl    %reg0, (%rbp-4)
    movl    y, %reg0
    movl    %reg0, .LP0
    movl    (%rbp-8), %reg0
    movl    %reg0, .LP0
    movl    .LP0+4, %reg0
    movl    %reg0, .LP0
    add     $8, %rsp
    popl    %rbp

.end*/