/* TEST 018: Initializers (errors) */

int a = 0; // OK

struct str1 {
  int x; 
};

struct str2;

struct str2 b = 1; // ERROR

struct str2 c = { 2 }; // ERROR

struct str2 d = { { 3 } }; // ERROR

struct str2 {
  void* x;
  struct str1 y;
} e = { 0, { 0 } }; // OK

struct str2 f = { { 4 }, { 5 } }; // ERROR
struct str2 g = { 0, 6 };         // ERROR
struct str2 h = { 0, { 7 }, 8 }; // ERROR

int i[3] = { 1, 2, 3, 4 }; // ERROR
int j[3] = { { 5 }, 6 }; // ERROR
int k[3] = { 1 }; // OK