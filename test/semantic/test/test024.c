/* TEST 024: Pointers vs Arrays */

struct str1{
  char x; int y; short z; 
};

int main(void){
  int **a, b[3][4];
  static struct str1 *c[] = { (struct str1*)1, 0, };
  struct str1 *d[] = { 0, (struct str1*)a };
  extern struct str1 *e[];
  struct str1 f[3][4];
  ;;

  a[1];
  b[1];
  ;;

  a[1][3]; // addition of (addition of (value of a) and 0x04) and 0x0c
  b[2][1]; // value of y+0x24
  ;;

  c[1][3];
  d[1][3];
  e[1][3]; // addition of (value of e+0x04) and 0x24
  f[1][3]; // value of f+0x54
  ;;

  a += 1;
  a[1] += 1;
  c += 1; // ERROR
  c[1] += 1;
  d[1] += 1;
  ;;

  a = (void*)(a - a); // a-a is divided by 4
  a -= 4; // 4 is multiplied by 4
  4 + a; // +16
  a + 4; // +16

}