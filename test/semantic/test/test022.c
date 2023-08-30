/* TEST 022: Arithmetic, bitwise (integers) */

int main(void){
  int a, b;
  a + b;
  a - b;
  a * b;
  a / b;
  a % b;

  a += b;
  a -= b;
  a *= b;
  a /= b;
  a %= b;

  a | b;
  a ^ b;
  a & b;

  a |= b;
  a ^= b;
  a &= b;

  char c; 
  c + a; // check types

  struct str1 {
    int x, y;
  } d;

  a + d;
  c - d;
  a * d;
  c | d;

  int* e, *f;
  e + a;
  a + e;
  e - a;
  a - e;
  e + f;
  e - f;

  a + (int)d; // ERROR
  e + (int)f; // OK

  3 + 4U;

  3 + (unsigned char)'d';

  char* g;
  g + 3; // check if 3 is multiplied by 4

  char h; short i;

  h * i; // cast into signed 

  (unsigned)4 - h; // cast into unsigned

  a + i; // cast into signed

  int *j, *k;

  j - k; // unsigned

  j + '\0'; // cast '\0' into unsigned
  k - 4; // cast 4 into unsigned 

  // FOLDS, NEUTRALS
  int x;

  x + 0; // neutral
  x - 0; // neutral
  x + 1;
  x - 1;

  x * 0; // fold 0
  x * 1; // neutral
  x * 2;
  x / 1; // neutral
  x % 1; // fold 0

  x << 0; // neutral
  x >> 0; // neutral
  x << 1;
  x >> 1;

  x & 0; // fold 0
  x & 0xFFFFFFFF; // neutral
  x ^ 0; // neutral
  x ^ 0xFFFFFFFF;
  x | 0; // neutral
  x | 0xFFFFFFFF; // fold 0xFFFFFFFF

}