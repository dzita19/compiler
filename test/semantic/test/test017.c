/* TEST 017: Functions, function pointers */

int a(void);

int b(void, void); // ERROR

int c(int x, int x); // ERROR

int d(int (*x)(void), int (*x)(void));

int e(int (*x)(int (*y)(int z)), int (*y)(int (*z)(void))){

} // only x and y are in symtab

int f(x, y, z)
    int x; char y, z; {
  return 1;
}

int g(x, y, z); // x, y and z are not in symtab

int h(x, y, z){ // ERROR - nonprototype function needs redeclaration of parameters

}

int (*i)(int x); // x is not in symtab

int (*j(int x))(int y); // y is not in symtab

int k(void){
  int x();
  int (*y)();
}

int (*l)(int x), (*(*m)(int x))(char y);