/* TEST 004: Declarators (no linkage) */

int main(void){
  int a;
  int a; // ERROR (already defined)

  static int b;
  static int b; // ERROR (already defined)

  extern int c;
  extern int c; // OK

  auto int d;

  auto int e;
  register int e; // ERROR (already defined)
}