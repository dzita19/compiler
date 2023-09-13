extern int putchar(int);
extern int printf(const char* format, ...);

extern void* malloc(int size);
extern void  free(void* ptr);
extern void  print_malloc_frames(void);

extern int   strlen(const char* str);
extern char* strcpy(char* dst, const char* src);
extern int   strcmp(const char* str1, const char* str2);
extern char* strdup(const char* str);
extern char* strcat(char* dst, const char* src);

extern void* memcpy(void *dest, const void *src, int n);
extern void* memmove(void *dest, const void *src, int n);
extern void* memset(void *str, int c, int n);

int main(void){
  int x = 15;
  switch(x){
    case 1:
    case 10:  return 1;
    case 9:  break;
    case 3:
    case 15: return 2;
    case 2:
    case 7:  break;
  }

  return 3;
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