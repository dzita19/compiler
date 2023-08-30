/* TEST 000: Arithmetic passing (IR) */

struct str1 {
  int pad, x, *p;
} str;

int  f();
int* g();

int main(){
  int a, b, c, *p, *q, *r;
  short sh; char ch;

  a;
  a = b;
  a = *p;
  a = str.x;
  a = *str.p;
  a = f();
  a = *(g());

  *p;
  *p = b;
  *p = *q;
  *p = str.x;
  *p = *str.p;
  *p = f();
  *p = *(g());

  a + b;
  -a;
  !a;
  a > 0;
  a && b;
  a > 0 ? b : c;
  a > 0 ? *p : *q;

  return a;
  return a + b;
  return a > 0 ? b : c;
}