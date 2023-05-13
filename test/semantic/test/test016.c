/* TEST 016: Indirections (compatible and composite types) */

int a[];
int a[3]; // OK

int (*b)[];
int (*b)[3]; // OK
int (*b)[5]; // ERROR

int (*c)();
int (*c)(int a, int b); // OK
int (*c)(); // OK
int (*c)(signed, signed); // OK
int (*c)(void); // ERROR

int (*d)(int(*)(), char(*)[3]); // OK
int (*d)(int(*)(short*), char(*)[]); // OK

int e(){

}

int e(void); // ERROR - prototype redeclaration after non-prototype definition

int f(void){

}

int f(); // OK

int g[] = { 0, 1, 2 };
int g[2]; // ERROR
int g[3]; // OK