/* TEST 002: Declarators (linkage, declaration) */

int i;
extern int i; // OK

int j;
static int j; // ERROR

extern int k;
int k; // OK

extern int l;
static int l; // OK

static int m;
int m; // ERROR

static int n;
extern int n; // OK

static extern int o; // ERROR