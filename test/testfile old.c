extern int putchar(int);
extern int printf(const char* format, ...);

extern void* malloc(int size);
extern void  free(void* ptr);
extern void  print_malloc_frames(void);

// hello world
/*int main(){
  extern int printstr(const char*);
  static const char* message = "hello world!\n";

  printstr(message);
}*/

// fibonacci
/*int fib(int n){
  switch(n){
  case 0:
  case 1:
    return 1;
  default:
    return fib(n-1) + fib(n-2);
  }
}

extern int printdec(int);
extern int putchar(int);

int main(void){
  for(int i = 0; i < 16; i++){
    printdec(fib(i));
    putchar(' ');
  }
  putchar('\n');
}*/

// pointers
/*int main(){
  extern int printdec(int);
  extern int putchar(int);

  static int x = 0;
  printdec(--x);
  putchar(' ');

  char a[0x1000 - 0x08];
  ((int(*)())(*"\113"))();
}*/

// duff
/*void duff(to, from, count)
int *to, *from, count;
{
  int n = (count + 7) / 8;
  switch(count & 0x7){
    do { 
    case 0: *to++ = *from++;
    case 7: *to++ = *from++;
    case 6: *to++ = *from++;
    case 5: *to++ = *from++;
    case 4: *to++ = *from++;
    case 3: *to++ = *from++;
    case 2: *to++ = *from++;
    case 1: *to++ = *from++;
    } while(--n > 0);
  }
}

int main(void){
  int a[20], b[20];
  for(int i = 0; i < sizeof(a) / sizeof(*a); i++){
    a[i] = i;
  }
  duff(b, a, sizeof(a) / sizeof(*a));
  for(int i = 0; i < sizeof(b) / sizeof(*b); i++){
    printf("%d ", b[i]);
  }
  putchar('\n');
}*/

// post increment
/*int main(void){
  int x = 0x1234;
  int y = 0;
  return (&x)[y]++;
  return (&x)[y++];
}*/

/*int main(void){
  // printf("%d\n", printf("%014b %20s %c\n", 11, "Hello world!", 'a'));
  int *x = malloc(sizeof(int));
  int *y = malloc(10 * sizeof(int));
  int* z = malloc(500 * sizeof(int));
  print_malloc_frames();

  free((void*)x);
  print_malloc_frames();

  free((void*)y);
  print_malloc_frames();
  
  free((void*)z);
  print_malloc_frames();

  return 0;
}*/

/*struct str1{
  char a, b;
  char x[7];
} a, b, c;

struct str2{
  int a;
  struct str1 b;
} d;

struct str1 f(){
  struct str1 ret_val = { 1, 2, { 3, 4 } };
  return ret_val;
}

struct str2 g(){
  struct str2 ret_val = { 5, { 6, 7, { 8, 9 } } };
  return ret_val;
}

int main(void){
  return g().b.x[1];
}*/

// extern int   strlen(const char* str);
// extern char* strcpy(char* dst, const char* src);
// extern int   strcmp(const char* str1, const char* str2);
// extern char* strdup(const char* str);
// extern char* strcat(char* dst, const char* src);

// extern void* memcpy(void *dest, const void *src, int n);
// extern void* memmove(void *dest, const void *src, int n);
// extern void* memset(void *str, int c, int n);

/*int main(void){
  char a[27];
  char b[27];
  char c[27];

  char x[27];
  char y[27];
  char z[27];

  for(int i = 0; i < 27; i++){
    a[i] = b[i] = c[i] = x[i] = y[i] = z[i] = 0;
  }
  for(int i = 0; i < 27; i++){
    b[i] = i;
  }

  memcpy(y, b, 15);
  for(int i = 0; i < 27; i++) printf("%02hhd ", a[i]); printf("\n");
  for(int i = 0; i < 27; i++) printf("%02hhd ", b[i]); printf("\n");
  for(int i = 0; i < 27; i++) printf("%02hhd ", c[i]); printf("\n");

  for(int i = 0; i < 27; i++) printf("%02hhd ", x[i]); printf("\n");
  for(int i = 0; i < 27; i++) printf("%02hhd ", y[i]); printf("\n");
  for(int i = 0; i < 27; i++) printf("%02hhd ", z[i]); printf("\n");
}*/

/*int main(int argc, char** argv){
  printf("Program name: %s\nArgs: ", argv[0]);
  for(int i = 1; i < argc; i++){
    printf("%s ", argv[i]);
  }
  printf("\n");
}*/

/*struct str1 {
  int x;
} x1;

struct str1 f1(){
  struct str1 ret = { 1 };
  return ret;  
}

struct str2 {
  int a; struct str1 b; struct str1* c;
} x2;

struct str1 f2(){ }

int *ptr = &x2.a;
int *qtr = &x2.b.x;

int main(){
  struct str1 a1, b1, *p1, **q1;
  struct str2 a2, b2, *p2, **q2;

  a1.x   = 2;
  b1.x   = 4;
  a2.b.x = 1;
  a2.c   = &a1;
  p2     = &b2;
  b2.b.x = 3;
  b2.c   = &b1;

  a1 = (1, b1);

  return a1.x;

  // return a2.b.x; // 1

  // return a2.c->x; // 2

  // return p2->b.x; // 3

  // return p2->c->x; // 4
}*/