/* TEST 007: Arrays, functions, pointers */

int main(void){
  int *a, b[3], *c[3], (*d)[3];

  a = b;
  a = c[0];
  c[0] = a;
  c[1] = b;
  d = &b;
}