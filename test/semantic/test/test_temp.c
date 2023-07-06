int a;

struct str1{
  short x[3];
};

struct str2 {
  char x;
  int y[3];
  struct str1 z;
} b;

// int c[(char)257];

int f();

int main(){
  // static int x;

  // static int *p = &a + 2;

  // static int* q = &((&b)->y[1]);

  int arr[3];

  arr; // should be int*
  main;
  &arr;
  &main;

  int* x;
  x = arr;
  arr + 1;
  arr - 2;
  x += 3;
  x -= 4;
  x++;
  x--;

  (char*)arr;
  *arr;

  main();
  arr == arr;
  arr != arr;
  arr < arr;

  arr[1];

  (arr ? arr : arr) && arr;
  char c;
  c && &c;

  struct str2 d;
  &d.z.x[1];

  c = c && c;
  x = 3 - 3;

  x = (arr, arr, arr);
  
  f(arr, (arr, arr));

  (*f)() + f();
  (**f) + 1;
  ((int(*)())((int*)f + 1))();

  &arr; // arr
  arr; // arr
  (&arr[0]); // arr + 0
  (&arr)[0]; // arr
  arr[0]; // arr[0]
  
  static char* string = (char*)"TEST STRING" + (short)(unsigned char)-1; // "TEST_STRING" + 255
}