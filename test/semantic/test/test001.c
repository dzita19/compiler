/* TEST 001: Declarators (linkage, definition) */

struct a;
struct a a = { 0, 0 }; // define incomplete - ERROR

int b = 0;
int b = 1; // define defined - ERROR

int c;
int c = 2; // define declared - OK

int d;
short d = 3; // different type - ERROR

static int e;
int e = 4; // different linkage - ERROR

int f;
static int f = 5; // different linkage - ERROR

extern int g;
static int g = 6; // linkage changed to static - OK

extern int h;
int h = 7; // same linkage - OK

auto int i; // ERROR - illegal storage spec

register char j; // ERROR - illegal storage spec