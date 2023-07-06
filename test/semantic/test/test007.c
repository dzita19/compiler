/* TEST 007: Declarators (members) */

struct str1{
  int a, // OK 
  b[]; // ERROR
};

struct str2{
  int a[3], *b; // OK
};

struct str3;

struct str4{
  struct str3 a; // ERROR
};

struct str5{
  struct str3* a; // OK
};

struct str6{
  struct str6 a; // ERROR
};

struct str7{
  struct str7* a; // OK
}

struct str8{
  int a(); // ERROR
};

struct str9{
  int (*a)(void); // OK
};

struct str10{
  struct str10{
    int x;
  } x;
};

struct str11{
  struct str11* x;
  struct str12* y;
  struct str11 {
    int a;
  } z;
};