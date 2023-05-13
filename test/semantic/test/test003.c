/* TEST 003: Declarators (functions) */

int a(void);

int a(void); // OK

int a(void){

} // OK

int a(void); // OK

int b(int, int);
int b(short, int); // ERROR (params)

int c(int, int);
short c(int, int); // ERROR (return types)

extern int d(void);
int d(void); // OK

static int e(void);
extern int e(void); // ERROR

static int f(void);
int f(void); // ERROR

int g(void){

}

int g(void){

} // ERROR (already defined)

