/* TEST 009: Declarators (typenames) */

struct str1;

int main(void){
  sizeof(int*); // OK
  sizeof(int[][]); // ERROR
  sizeof(int()[]); // ERROR
  sizeof(int*); // OK
  sizeof(struct str1); // ERROR
  sizeof(aaa); // ERROR
  sizeof(int[]); // ERROR
  sizeof(char[3]); // OK
}