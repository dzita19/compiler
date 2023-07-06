/* TEST 020: Initializers */

struct s1 {
  int x, y;
};

struct s2 {
  char a; struct s1 b; char c[3];
};

struct s2 a = { 0, { 1, 2 }, { 3, 4, 5 } };

union u1 { int x; struct { char a, b; } y; };

union u1 b = { 1, { 2, 3 } };

union u2 { char x[4]; int y; };

union u2 c = { { 0, 1, 2, 3 }, 4 };

int main(void){
  struct s2 a = { 0, { 1, 2 }, { 3, 4, 5 } };
  struct s2 b = a;
  struct s1 c = { 1, 2 };
  struct s2 d = { 0, c, { 1, 2 } };
}

int f(void){
  struct s1 a;
  struct s2 b = { 1, a, };
}

struct {
  int a, b;
} d = { 0 };

struct s2 e = { 0, 0, 0, 0, 0, 0, 0, 0, }; // 3 ERRORS