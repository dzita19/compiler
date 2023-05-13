/* TEST 014: Indirections (errors) */

int a;
const int b;
int c[a + 1]; // ERROR
int d[b + 1][a + 1]; // ERROR

int e[](void); // ERROR
int f[](); // ERROR
int g(int)(void); // ERROR
int h()(); // ERROR
int i[][]; // ERROR

struct str1;
struct str1 j[3]; // ERROR
struct str1 k[ ]; // ERROR

extern struct str1 l;
extern struct str1 m[3];

struct str1{
  int x;
}; // type completed

struct str1 n[3]; // OK
struct str1 o[ ] = { {0}, {1} }; // OK
const struct str1 p = { 2 };