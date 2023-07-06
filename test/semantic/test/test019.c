/* TEST 019: Initializers (static, auto) */

struct str1{
  int a, *b, c[3];
};

int main(){
  int a = 14 * 7;
  int b = a * 4;
  int *c = &b + (int)(&a - 1);

  int d = 4 - b * *c + (char)4;

  const int e = 0;

  struct str1 f = { 0, 0, { 1, 2, 3 }};
  static struct str1 g = { 0, 0, { 1, 2, 3 }};

  int h = 'a';

  int* i = "AAA"; // ERROR
  int* j = (int*)"AAA"; // OK

  char* k = &a; // ERROR
  int* l = &e; // OK - const address to non const pointer
  const int* m = &a; // OK (warning?)

  static const volatile int* n = 1; // ERROR
  static const volatile int* o = (const volatile int*)1; // OK

  static const volatile int* p = (const volatile int*)1 + 3; // OK - 13
}