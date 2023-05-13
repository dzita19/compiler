/* TEST 019: Initializers (static, auto) */

struct str1{
  int a, *b, c[3];
};

int main(){
  int a;
  const int* b = &a; // OK
  const int* c;
  c = &a;

  const int d;
  int* e = &d;
  int* f;
  f = &d;
}