/* TEST 022: Logic */
int main(void){  
  int a, b;
  a > b;
  a < b;
  a >= b;
  a <= b;
  a == b;
  a != b;

  int* c; const int* d;
  void* e;
  char* f;

  c < d; // OK
  c < e; // ERROR
  e > c; // ERROR
  c < 0; // ERROR
  0 > c; // ERROR
  c < f; // ERROR
  ;;

  c == d; // OK
  c == e; // OK
  e == c; // OK
  c == 0; // OK
  0 == c; // OK
  c == f; // ERROR
  ;;

  a < 0 && b >= 0;

  a && b;
  a || b;

  // FOLDS, CONSTANTS
  int x;

  x > 0x7FFFFFFF; // fold 0 
  x > 0x7FFFFFFFU;
  x > 0xFFFFFFFF; 
  x > 0xFFFFFFFFU; // fold 0

  x < 0x00000000; // fold 0
  x < 0x00000000U;
  x < 0x80000000; 
  x < 0x80000000U; // fold 0

  x >= 0x00000000;
  x >= 0x00000000U; // fold 1
  x >= 0x80000000; // fold 1
  x >= 0x80000000U;

  x <= 0x7FFFFFFF; // fold 1
  x <= 0x7FFFFFFFU;
  x <= 0xFFFFFFFF;
  x <= 0xFFFFFFFFU; // fold 1

  x && 0; // fold 0
  x && 1; // neutral
  x && x;
  0 && x; // fold 0
  1 && x; // neutral

  x || 0; // neutral
  x || 1; // fold 1
  x || x;
  0 || x; // neutral
  1 || x; // fold 1
}