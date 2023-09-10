extern int putchar(int);
extern int printf(const char* format, ...);

extern void* malloc(int size);
extern void  free(void* ptr);
extern void  print_malloc_frames(void);

struct str1 {
  char x; int y;
};

struct str2 {
  char a; struct str1 b;
};

struct str2 f(){
  struct str2 a = { 1, { 2, 3 }};
  return a;
}

int main(void){
  return f().b.y;
}

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

  // a1.x   = 2;
  // b1.x   = 4;
  // a2.b.x = 1;
  // a2.c   = &a1;
  // p2     = &b2;
  // b2.b.x = 3;
  // b2.c   = &b1;

  a1 = ptr == 0 ? b1 : *p1;

  // a1 = (1, b1);

  // printf("%d\n", a1);

  // return a1.x;

  **q1;

  return a2.b.x; // 1

  return a2.c->x; // 2

  return p2->b.x; // 3

  return p2->c->x; // 4
}*/