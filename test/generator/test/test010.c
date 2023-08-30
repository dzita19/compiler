// TEST 001: Struct passing (IR) 

struct str1{
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

struct str1 main(void){
  int i;
  
  a;

  a, b;
  a = b;
  f();
  i > 0 ? a : b;
  g().b;
  
  a = (b, c);
  a = b = c;
  a = f();
  a = i > 0 ? b : c;
  a = g().b;

  a, (b, c);
  a, (b = c);
  a, f();
  a, i > 0 ? b : c;
  a, g().b;

  i > 0 ? (a, b) : (b, c);
  i > 0 ? (a = b) : (b = c);
  i > 0 ? f() : f();
  i > 0 ? (i > 0 ? a : b) : (i > 0 ? b : c);
  i > 0 ? g().b : g().b;

  f(a);
  f((a, b));
  f(a = b);
  f(f());
  f(i > 0 ? a : b);
  f(g().b);

  return a;
  return a, b;
  return a = b;
  return f();
  return i > 0 ? a : b;
  return g().b;
}