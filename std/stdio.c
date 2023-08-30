static const int TERM_OUT_CTRL = 0x000F0000;
static const int TERM_OUT_VAL  = 0x000F0008;

int putchar(int c){
  *(int*)TERM_OUT_VAL  = c;
  *(int*)TERM_OUT_CTRL = 1;
  return 0;
}

static int printstr(const char* str, int width, int padding){
  if(str == 0) str = "(null)";

  int length = 0;
  for(length = 0; str[length]; length++);

  if(padding == 0){
    for(int i = length; i < width; i++){
      *(int*)TERM_OUT_VAL  = ' ';
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  for(int i = 0; i < length; i++) {
    *(int*)TERM_OUT_VAL  = str[i];
    *(int*)TERM_OUT_CTRL = 1;
  }
  if(padding == 1){
    for(int i = length; i < width; i++){
      *(int*)TERM_OUT_VAL  = ' ';
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  return 0;
}

static char buffer[32];

static int printdec(int val, int width, char padding, int align, int sign){
  int size = 0;
  int negative = 0;
  if(val < 0){
    negative = 1;
    val = -val;
  }
  do{
    buffer[size++] = (val % 10) + '0';
    val /= 10;
  } while(val > 0);

  if(padding == '0'){ // sign padding number
    if(negative){
      *(int*)TERM_OUT_VAL  = '-';
      *(int*)TERM_OUT_CTRL = 1;
    }
    else if(sign){
      *(int*)TERM_OUT_VAL  = '+';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size; i < (negative || sign ? width - 1 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  else if(align == 0) { // right align - padding sign number
    for(int i = size; i < (negative || sign ? width - 1 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
    if(negative){
      *(int*)TERM_OUT_VAL  = '-';
      *(int*)TERM_OUT_CTRL = 1;
    }
    else if(sign){
      *(int*)TERM_OUT_VAL  = '+';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  else if(align == 1){ // left align - sign number padding
    if(negative){
      *(int*)TERM_OUT_VAL  = '-';
      *(int*)TERM_OUT_CTRL = 1;
    }
    else if(sign){
      *(int*)TERM_OUT_VAL  = '+';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size; i < (negative || sign ? width - 1 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  return 0;
}

static int printdecu(unsigned val, int width, char padding, int align){
  int size = 0;
  do{
    buffer[size++] = (val % 10) + '0';
    val /= 10;
  } while(val > 0);

  if(padding == '0' || align == 0){ // padding number
    for(int i = size; i < width; i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  else if(align == 1){ // left align - number padding
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size; i < width; i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  return 0;
}

static int printhexlw(unsigned val, int width, char padding, int align, int hash){
  int size = 0;
  do{
    int digit = val & 0x0f;
    buffer[size++] = digit < 10 ? digit + '0' : digit - 10 + 'a';
    val >>= 4;
  } while(val > 0);

  if(padding == '0'){ // hash padding number
    if(hash){
      *(int*)TERM_OUT_VAL  = '0';
      *(int*)TERM_OUT_CTRL = 1;
      *(int*)TERM_OUT_VAL  = 'x';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size; i < (hash ? width - 2 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  else if(align == 0){ // rigth align - padding hash number
    for(int i = size; i < (hash ? width - 2 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
    if(hash){
      *(int*)TERM_OUT_VAL  = '0';
      *(int*)TERM_OUT_CTRL = 1;
      *(int*)TERM_OUT_VAL  = 'x';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  else if(align == 1){ // left align - hash number padding
    if(hash){
      *(int*)TERM_OUT_VAL  = '0';
      *(int*)TERM_OUT_CTRL = 1;
      *(int*)TERM_OUT_VAL  = 'x';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size; i < (hash ? width - 2 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  return 0;
}

static int printhexup(unsigned val, int width, char padding, int align, int hash){
  int size = 0;
  do{
    int digit = val & 0x0f;
    buffer[size++] = digit < 10 ? digit + '0' : digit - 10 + 'A';
    val >>= 4;
  } while(val > 0);

  if(padding == '0'){ // hash padding number
    if(hash){
      *(int*)TERM_OUT_VAL  = '0';
      *(int*)TERM_OUT_CTRL = 1;
      *(int*)TERM_OUT_VAL  = 'X';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size; i < (hash ? width - 2 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  else if(align == 0){ // rigth align - padding hash number
    for(int i = size; i < (hash ? width - 2 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
    if(hash){
      *(int*)TERM_OUT_VAL  = '0';
      *(int*)TERM_OUT_CTRL = 1;
      *(int*)TERM_OUT_VAL  = 'X';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  else if(align == 1){ // left align - hash number padding
    if(hash){
      *(int*)TERM_OUT_VAL  = '0';
      *(int*)TERM_OUT_CTRL = 1;
      *(int*)TERM_OUT_VAL  = 'X';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size; i < (hash ? width - 2 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  return 0;
}

static int printoct(unsigned val, int width, char padding, int align, int hash){
  int size = 0;
  do{
    buffer[size++] = (val & 0x07) + '0';
    val >>= 3;
  } while(val > 0);

  if(padding == '0'){ // hash padding number
    if(hash){
      *(int*)TERM_OUT_VAL  = '0';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size; i < (hash ? width - 1 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  else if(align == 0){ // rigth align - padding hash number
    for(int i = size; i < (hash ? width - 1 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
    if(hash){
      *(int*)TERM_OUT_VAL  = '0';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  else if(align == 1){ // left align - hash number padding
    if(hash){
      *(int*)TERM_OUT_VAL  = '0';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size; i < (hash ? width - 1 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  return 0;
}

static int printbin(unsigned val, int width, char padding, int align, int hash){
  int size = 0;
  do{
    buffer[size++] = (val & 0x01) + '0';
    val >>= 1;
  } while(val > 0);

  if(padding == '0'){ // hash padding number
    if(hash){
      *(int*)TERM_OUT_VAL  = '0';
      *(int*)TERM_OUT_CTRL = 1;
      *(int*)TERM_OUT_VAL  = 'b';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size; i < (hash ? width - 2 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  else if(align == 0){ // rigth align - padding hash number
    for(int i = size; i < (hash ? width - 2 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
    if(hash){
      *(int*)TERM_OUT_VAL  = '0';
      *(int*)TERM_OUT_CTRL = 1;
      *(int*)TERM_OUT_VAL  = 'b';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  else if(align == 1){ // left align - hash number padding
    if(hash){
      *(int*)TERM_OUT_VAL  = '0';
      *(int*)TERM_OUT_CTRL = 1;
      *(int*)TERM_OUT_VAL  = 'b';
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size; i < (hash ? width - 2 : width); i++){
      *(int*)TERM_OUT_VAL  = padding;
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  return 0;
}

static int printptr(unsigned val, int width, int align){
  int size = 0;
  for(int i = 0; i < 8; i++){
    int digit = val & 0x0f;
    buffer[size++] = digit < 10 ? digit + '0' : digit - 10 + 'a';
    val >>= 4;
  }

  if(align == 0){ // rigth align - padding hash number
    for(int i = size; i < width - 2; i++){
      *(int*)TERM_OUT_VAL  = ' ';
      *(int*)TERM_OUT_CTRL = 1;
    }
    
    *(int*)TERM_OUT_VAL  = '0';
    *(int*)TERM_OUT_CTRL = 1;
    *(int*)TERM_OUT_VAL  = 'x';
    *(int*)TERM_OUT_CTRL = 1;
    
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  else if(align == 1){ // left align - hash number padding
    *(int*)TERM_OUT_VAL  = '0';
    *(int*)TERM_OUT_CTRL = 1;
    *(int*)TERM_OUT_VAL  = 'x';
    *(int*)TERM_OUT_CTRL = 1;
    
    for(int i = size - 1; i >= 0; i--){
      *(int*)TERM_OUT_VAL  = buffer[i];
      *(int*)TERM_OUT_CTRL = 1;
    }
    for(int i = size; i < width - 2; i++){
      *(int*)TERM_OUT_VAL  = ' ';
      *(int*)TERM_OUT_CTRL = 1;
    }
  }
  return 0;
}

int printf(const char* format, ...){
  typedef enum states{
    BASIC,
    FLAGS,
    WIDTH,
    LEN1,
    LEN2,
    LEN4,
    TYPE,
    ERROR,
  } states;

  typedef enum types{
    DEC,
    DECU,
    HEXLW,
    HEXUP,
    OCT,
    BIN,
    CHAR,
    STR,
    PTR,
  } types;

  typedef enum flag{
    MINUS      = 1 << 0,
    PLUS       = 1 << 1,
    ZERO       = 1 << 2,
    HASH       = 1 << 3,
    BLANK      = 1 << 4,
  } flag;

  char buffer[16];
  int printed  = 0;

  states state  = BASIC;
  int    cntr   = 0; // buffer size
  int    flags  = 0;
  int    width  = 0;
  int    length = sizeof(const char*);
  types  type   = 0;

  extern void* get_variadic_param(int* variadic_cntr, int size);
  int    variadic_cntr = 4; // skip format string

  for(int i = 0; format[i]; i++){
    switch(state){
    case ERROR:{
      return printed;
    } break;
    case BASIC:{
      switch(format[i]){
      case '%': state = FLAGS;      break;
      default:  putchar(format[i]); break;
      }
    } break;
    case FLAGS:{
      switch(format[i]){
      case '%': putchar(format[i]); state = BASIC; break;

      case '-':  flags |= MINUS;      break;
      case '+':  flags |= PLUS;       break;
      case '0':  flags |= ZERO;       break;
      case '#':  flags |= HASH;       break;
      case ' ':  flags |= BLANK;      break;

      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': state = WIDTH; i--; break;

      case 'h': state = LEN2;  i--; break;
      case 'l': state = LEN4;  i--; break;

      case 'd':
      case 'i':
      case 'u':
      case 'x':
      case 'X':
      case 'o':
      case 'b':
      case 'c':
      case 's':
      case 'p': state = TYPE;  i--; break;
      
      default : state = ERROR; break;
      }
    } break;
    case WIDTH:{
      switch(format[i]){
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': width *= 10; width += format[i] - '0'; break;

      case 'h': state = LEN2; i--; break;
      case 'l': state = LEN4; i--; break;

      case 'd':
      case 'i':
      case 'u':
      case 'x':
      case 'X':
      case 'o':
      case 'b':
      case 'c':
      case 's':
      case 'p': state = TYPE; i--; break;
      
      default : state = ERROR; break;
      }
    } break;
    case LEN1:{
      switch(format[i]){
      case 'h': length = 1; state = TYPE; break;

      case 'd':
      case 'i':
      case 'u':
      case 'x':
      case 'X':
      case 'o':
      case 'b': state = TYPE; i--; break;
      
      default : state = ERROR; break;
      }
    } break;
    case LEN2:{
      switch(format[i]){
      case 'h': length = 2; state = LEN1; break;

      case 'd':
      case 'i':
      case 'u':
      case 'x':
      case 'X':
      case 'o':
      case 'b': state = TYPE; i--; break;
      
      default : state = ERROR; break;
      }
    } break;
    case LEN4:{
      switch(format[i]){
      case 'l': length = 4; state = TYPE; break;

      case 'd':
      case 'i':
      case 'u':
      case 'x':
      case 'X':
      case 'o':
      case 'b': state = TYPE; i--; break;

      default : state = ERROR; break;
      }
    } break;
    case TYPE:{
      switch(format[i]){
      case 'd':
      case 'i': type  = DEC;   state = BASIC; break;
      case 'u': type  = DECU;  state = BASIC; break;
      case 'x': type  = HEXLW; state = BASIC; break;
      case 'X': type  = HEXUP; state = BASIC; break;
      case 'b': type  = BIN;   state = BASIC; break;
      case 'o': type  = OCT;   state = BASIC; break;
      case 'c': type  = CHAR;  state = BASIC; break;
      case 's': type  = STR;   state = BASIC; break;
      case 'p': type  = PTR;   state = BASIC; break;

      default : state = ERROR; break;
      }

      switch(type){
      case DEC:{
        void* ptr_to_val = get_variadic_param(&variadic_cntr, length);
        printdec(length == 4 ? 
            *(signed int*)  ptr_to_val : length == 2 ? 
            *(signed short*)ptr_to_val : 
            *(signed char*) ptr_to_val, 
          width, flags & ZERO ? '0' : ' ', flags & MINUS ? 1 : 0, flags & PLUS ? 1 : 0); 
      } break;
      case DECU:{ 
        void* ptr_to_val = get_variadic_param(&variadic_cntr, length);
        printdecu(length == 4 ? 
            *(unsigned int*)  ptr_to_val : length == 2 ? 
            *(unsigned short*)ptr_to_val : 
            *(unsigned char*) ptr_to_val, 
          width, flags & ZERO ? '0' : ' ', flags & MINUS ? 1 : 0);
      } break;
      case HEXLW:{
        void* ptr_to_val = get_variadic_param(&variadic_cntr, length);
        printhexlw(length == 4 ? 
            *(unsigned int*)  ptr_to_val : length == 2 ? 
            *(unsigned short*)ptr_to_val : 
            *(unsigned char*) ptr_to_val, 
          width, flags & ZERO ? '0' : ' ', flags & MINUS ? 1 : 0, flags & HASH ? 1 : 0);
      } break;
      case HEXUP:{
        void* ptr_to_val = get_variadic_param(&variadic_cntr, length);
        printhexup(length == 4 ? 
            *(unsigned int*)  ptr_to_val : length == 2 ? 
            *(unsigned short*)ptr_to_val : 
            *(unsigned char*) ptr_to_val, 
          width, flags & ZERO ? '0' : ' ', flags & MINUS ? 1 : 0, flags & HASH ? 1 : 0);
      } break;
      case OCT:{
        void* ptr_to_val = get_variadic_param(&variadic_cntr, length);
        printoct(length == 4 ? 
            *(unsigned int*)  ptr_to_val : length == 2 ? 
            *(unsigned short*)ptr_to_val : 
            *(unsigned char*) ptr_to_val, 
          width, flags & ZERO ? '0' : ' ', flags & MINUS ? 1 : 0, flags & HASH ? 1 : 0);
      } break;
      case BIN:{
        void* ptr_to_val = get_variadic_param(&variadic_cntr, length);
        printbin(length == 4 ? 
            *(unsigned int*)  ptr_to_val : length == 2 ? 
            *(unsigned short*)ptr_to_val : 
            *(unsigned char*) ptr_to_val, 
          width, flags & ZERO ? '0' : ' ', flags & MINUS ? 1 : 0, flags & HASH ? 1 : 0);
      } break;
      case CHAR:{
        void* ptr_to_val = get_variadic_param(&variadic_cntr, 1);
        putchar(*(char*)ptr_to_val);
      } break;
      case STR:{
        void* ptr_to_val = get_variadic_param(&variadic_cntr, 4);
        printstr(*(const char**)ptr_to_val, width, flags & MINUS ? 1 : 0);
      } break;
      case PTR:{ 
        void* ptr_to_val = get_variadic_param(&variadic_cntr, 4);
        printptr(*(unsigned int*)ptr_to_val, width, flags & MINUS ? 1 : 0);
      } break;
      }

      flags  = 0;
      width  = 0;
      length = 4;
      type   = 0;
      printed++;
    } break;
    }
  }

  return printed;
}