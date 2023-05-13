/* TEST 008: Declarators (typedefs) */

typedef int a;

typedef short a; // ERROR

typedef int b;

typedef int b; // ERROR

typedef struct str1 c;

struct str1 {
  int a;
};

c d = { 0 }; // OK

typedef int e = 0; // ERROR