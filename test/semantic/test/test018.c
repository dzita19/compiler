/* TEST 018: Initializers (static, const expr) */

char* a = (char*)((int*)"AAA" + 1); // OK - not made yet

char* b = "BBB" - 4 + 7; // OK

char* c = 0; // OK

enum {
  A = 4, B, C
};

int d = A + B * 1;

int* e = &d;

int* f = (int*)((char*)((short*)((int*)0 + 1) + 2) + 3); // 11

int main(void){
  static int g;
  static int* h = &g;
  static int* i = &g + "CCC"; // ERROR
}

int (*j)(void) = 0;
int (*k)(void) = (int(*)(void))1 + 1; // ERROR 
// TWO LINE\
                COMMENT\

int l = j;