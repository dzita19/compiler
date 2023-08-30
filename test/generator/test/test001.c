/* TEST 001: Static data allocation (internal padding, initial values) */

struct str1 {
  char a; 
  short b[2]; 
  int c;
};

struct str2 {
  short a;
  struct str1 b;
  struct str1 c[2];
  char d;
  int e;
  short f;
};

struct str1 x1 = { 1, { 2, 3 }, 4 };
struct str2 y1 = { 1, { 2, { 3 } }, { { 4 }, { 5, { 6, 7 }, 8 } }, 9, 10, 11 };

/*EXPECTED OUTPUT:

.section    .data
x1:
    .byte   1
    .zero   1
    .word   2
    .word   3
    .zero   2
    .long   4
y1:
    .word   1
    .zero   2
    .byte   2
    .zero   1
    .word   3
    .zero   8
    .byte   4
    .zero   11
    .byte   5
    .zero   1
    .word   6
    .word   7
    .zero   2
    .long   8
    .byte   9
    .zero   3
    .long   10
    .word   11
    .zero   2

.LP0:

.section    .text

.end*/