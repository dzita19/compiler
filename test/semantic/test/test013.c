/* TEST 013: Specifiers (redeclarations, definitions) */

struct a;

struct a {
  int x;
}; // definition

struct a; // no redeclaration

struct b {
  int y;
};

int c(void){
  struct b d; // no redeclaration
  const struct b; // no redeclaration
  static struct b; // no redeclaration
}

int e(void){
  struct b; // redeclaration
  struct b* f;
}

struct b; // no redeclaration

int g(void){
  struct b{
    int x;
  } h[3]; // redeclaration
}

struct i; // undefined

int j(void){
  struct i; // redeclaration
}

struct { int a, b; } k;