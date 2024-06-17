extern int printf(const char* format, ...);

int f(){
  int x[5] = { 1, 2, 3, 4, 5, };
}

int g(){
  int x[5] = { };

  printf("x: ");
  for(int i = 0; i < sizeof(x) / sizeof(*x); i++){
    printf("%d ", x[i]);
  }
  printf("\n");
}

int main(void){
  f();
  g();
}