/* TEST 000: Static data allocation (extern padding) */

char  x = 1;
int   y = 2; // check padding
short z = 3;

int main(void){
  static int   a = 4;
  static char  b = 5;
  static short c = 6;
}

/*EXPECTED OUTPUT:

.section    .data
x:
    .byte   1
    .zero   3
y:
    .long   2
z:
    .word   3
    .zero   2

.LP0:
    .long   4
    .byte   5
    .zero   1
    .word   6
    .byte   7
    .zero   3

.section    .text

main:
    pushl   %rbp
    movl    %rsp, %rbp
    popl    %rbp

.end*/