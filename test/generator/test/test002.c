/* TEST 002: Auto data allocation (addresses and initializers) */

struct str1 {
  char x, y[2];
};

struct str2 {
  struct str1 a;
  int b;
};

int main(){
  int   a = 1; // -4
  int   b = 2; // -8
  char  c = 3; // -9
  short d = 4; // -12
  char  e = (unsigned)5; // -13
  static int f = 6; // doesn't affect auto data
  static int g = 7; // doesn't affect auto data
  extern int h;     // doesn't affect auto data
  int   i = 8;  // -20
  int   j[3] = { 9, 10, 11 }; // -32
  struct str1 k = { 1, { 2, 3 } };        // -35
  struct str2 l = { { 1, { 2, 3 } }, 4 }; // -44
}

/*EXPECTED OUTPUT:

.section    .data

.LP0:
    .long   6
    .long   7

.section    .text

main:
    pushl   %rbp
    movl    %rsp, %rbp
    sub     $48, %rsp
    movl    $1, %reg0
    movl    %reg0, (%rbp,-4)
    movl    $2, %reg0
    movl    %reg0, (%rbp,-8)
    movb    $3, %reg0
    movb    %reg0, (%rbp,-9)
    movw    $4, %reg0
    movw    %reg0, (%rbp,-12)
    movb    $5, %reg0
    movb    %reg0, (%rbp,-13)
    movl    $8, %reg0
    movl    %reg0, (%rbp,-20)
    movl    $9, %reg0
    movl    %reg0, (%rbp,-32)
    movl    $10, %reg0
    movl    %reg0, (%rbp,-28)
    movl    $11, %reg0
    movl    %reg0, (%rbp,-24)
    movb    $1, %reg0
    movb    %reg0, (%rbp,-35)
    movb    $2, %reg0
    movb    %reg0, (%rbp,-34)
    movb    $3, %reg0
    movb    %reg0, (%rbp,-33)
    movb    $1, %reg0
    movb    %reg0, (%rbp,-44)
    movb    $2, %reg0
    movb    %reg0, (%rbp,-43)
    movb    $3, %reg0
    movb    %reg0, (%rbp,-42)
    movl    $4, %reg0
    movl    %reg0, (%rbp,-40)
    add     $48, %rsp
    popl    %rbp

.end*/