extern int printf(const char* format, ...);

int main(int argc, const char** argv){

  int a = 1, b = 2, c = 3;
  int d = a + (b + (c + ((int[1024]){ [4] = 4 }[4])));
  int e;
  printf("a: %d, b: %d, c: %d, d:%d\n", a, b, c, d);
  printf("%p\n", (char*)&d - (char*)&e);

  return 0;
}