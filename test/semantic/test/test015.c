/* TEST 015: Indirections (nested indirections) */

int a(int, int(*)(void));

int (*b)(int(*x)[], char*(**)[]);

int (*c(int x))(char y);

int d(int (*)(int (*)(int (*)(void))));

const int e(void);

const int f();

const int (*g)();

const int (*h(void))();