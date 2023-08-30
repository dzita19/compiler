extern int   strlen(const char* str);
extern char* strcpy(char* dst, const char* src);
extern int   strcmp(const char* str1, const char* str2);
extern char* strdup(const char* str);
extern char* strcat(char* dst, const char* src);

extern void* memcpy(void *dest, const void *src, int n);
extern void* memmove(void *dest, const void *src, int n);
extern void* memset(void *str, int c, int n);