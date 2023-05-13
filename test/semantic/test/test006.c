/* TEST 006: Declarators (param redeclarator) */

int a(a,b,c)
int a;
char b, c; { } // OK

int b(a,b)
int a; char b, c; { } // ERROR

int c(a,b,c,d)
int a; char b, c; { } // ERROR

int d(a,b,c,d)
static int a; // ERROR
extern char b; // ERROR
auto short c; // ERROR
register void* d; // OK
{ }

int e(a,b,c)
int a[], b[3], *c; { } // OK

int f(a,b,c)
int a(void); // ERROR 
int b(void)(int, char); // ERROR 
char c(); // ERROR
{ }