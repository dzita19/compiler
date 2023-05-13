/* TEST 000: Declarators (identifier namespaces) */

int a; // ordinary namespace

struct a; // tag namespace

struct a{
  int a; // member namespace
};

int a(void); // ordinary namespace - ERROR

int main(void){
  int a; // not an error

  struct a x; // struct a from global scope

  struct a; // redeclared struct a in this scope

  struct a* p; // pointer to redeclared struct a

  *p; // ERROR - incomplete type

  struct a{
    int x;
  }; // type definition

  *p; // ok

  {
    int a; // redefinition - inner scope
  }
}