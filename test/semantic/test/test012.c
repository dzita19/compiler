/* TEST 012: Specifiers (illegal combinations) */

struct A{
  int x;
}; // OK

struct B{
  int x;
}; // OK

struct A struct B a; // ERROR

int struct A b; // ERROR

struct A short c; // ERROR

struct C{
  int x;
} // OK
struct A d; // ERROR

struct D{
  int x;
} // OK 
int e; // ERROR

struct E{
  int x;
} // OK
struct F{
  int x;
} // won't be added to symtab
f; // ERROR

typedef int g;

struct E g; // ERROR

g struct E F; // ERROR

typedef struct G{
  int x;
} h; // OK