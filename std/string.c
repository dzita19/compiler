extern void* malloc(int size);
extern void  free(void* ptr);
extern int   printf(const char* format, ...);

int strlen(const char* str){
  int len;
  for(len = 0; str[len]; len++);
  return len;
}

char* strcpy(char* dst, const char* src){
  int i;
  for(i = 0; src[i]; i++) dst[i] = src[i];
  dst[i] = '\0';
  return dst;
}

char* strdup(const char* str){
  char* ret = malloc((strlen(str) + 1) * sizeof(char));
  strcpy(ret, str);
  return ret;
}

int strcmp(const char* str1, const char* str2){
  for(int i = 0; str1[i]; i++){
    if(str1[i] == str2[i]) continue;
    else if(str1[i] < str2[i]) return -1;
    else return +1;
  }
  return 0;
}

char* strcat(char* dst, const char* src){
  int len_dst = strlen(dst);
  int len_src = strlen(src);
  int i;

  for(i = 0; i < len_src; i++) dst[len_dst + i] = src[i];
  dst[len_dst + i] = '\0';
  return dst;
}



void* memcpy(void *dest, const void *src, int n){
  int longs = (n & ~0x03) >> 2;
  int words = (n &  0x03) >> 1;
  int bytes = (n &  0x01) >> 0;

  int*       long_dest = (int*)      dest;
  const int* long_src  = (const int*)src;
  if(longs){
    int iterations = (longs + 7) / 8;
    switch(longs & 0x07){
      case 0: do { *long_dest++ = *long_src++;
      case 7: *long_dest++ = *long_src++;
      case 6: *long_dest++ = *long_src++;
      case 5: *long_dest++ = *long_src++;
      case 4: *long_dest++ = *long_src++;
      case 3: *long_dest++ = *long_src++;
      case 2: *long_dest++ = *long_src++;
      case 1: *long_dest++ = *long_src++;
              } while(--iterations > 0);
    }
  }

  short*       word_dest   = (short*)      long_dest;
  const short* word_src    = (const short*)long_src;
  if(words)   *word_dest++ = *word_src++;

  char*        byte_dest   = (char*)      word_dest;
  const char*  byte_src    = (const char*)word_src;
  if(bytes)   *byte_dest++ = *byte_src++;

  return dest;
}

void* memmove(void *dest, const void *src, int n){
  void* temp = malloc(n * sizeof(char));
  memcpy(temp, src,  n);
  memcpy(dest, temp, n);
  free(temp);
  return dest;
}

void* memset(void *str, int c, int n){
  for(int i = 0; i < n; i++){
    ((char*)str)[i] = c;
  }
  return str;
}