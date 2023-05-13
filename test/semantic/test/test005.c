/* TEST 005: Declarators (parameters) */

struct str1{
  int x;
};

struct str2;

int a(int[]); // OK

int b(int[3]); // OK

int c(int()); // ERROR 

int d(struct str2); // OK

int d(struct str2){  // ERROR

}

int e(void); // OK

int f(void param); // ERROR

int g(void, int); // ERROR

int h(int, void); // ERROR

int i(static int, // ERROR
      extern short,  // ERROR
      register char,  // ERROR
      auto void*); // OK

int j(char x, char x); // ERROR