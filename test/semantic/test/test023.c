/* TEST 023: Type cast */

int main(void){

  int   a; unsigned int   b;
  short c; unsigned short d;
  char  e; unsigned char  f;
  void* p;

  // both int rank
  a + a; // i32
  a + b; // u32
  b + a; // u32
  b + b; // u32
  ;;

  // one is higher rank
  a + c; // i32
  a + d; // i32
  a + e; // i32
  a + f; // i32
  b + c; // u32
  b + d; // u32
  b + e; // u32
  b + f; // u32
  ;;

  // both are below int rank
  c + d; // i32
  c + e; // i32
  c + f; // i32
  d + e; // i32
  d + f; // u32
  e + f; // i32
  ;;

  // one is ptr
  p + a; // u32
  p + b; // u32
  p + c; // u32
  p + d; // u32
  p + e; // u32
  p + f; // u32
  ;;

  a < b; // result is i32, operands are u32
  b < c;
  p > (const void*)a;
  p > (const void*)c;
  ;;

}