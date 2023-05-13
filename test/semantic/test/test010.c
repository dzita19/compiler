/* TEST 010: Declarators (enums) */

enum a{
  A, B = 14, C
};

enum b{
  D, E, F = -19, G, // OK
  A = 10 // ERROR
};

int H;

enum d{
  H = -5, // ERROR
  I // OK
};

typedef int J;

enum e{
  J, // ERROR
};

enum e f = 0; // OK

enum h {
  K = 25, L = K
};