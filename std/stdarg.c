// params are aligned to 4byte address
void* get_variadic_param(int* variadic_cntr, int size){
  static const int align = 4;
  size  = (size + align - 1) / align * align;
  int start_addr = (*variadic_cntr + align - 1) / align * align;
  *variadic_cntr += size;

  return (void*)(*(int*)(&(&start_addr)[1]) + 8 + start_addr);
  // __asm__("    movl    [%rbp],   %reg0");
  // __asm__("    add     8,        %reg0");
  // __asm__("    add     [%rbp-4], %reg0");
}

// params are not aligned to 4byte address
/*void* get_variadic_param(int* variadic_cntr, int size, int align){
  int start_addr = (*variadic_cntr + align - 1) / align * align;
  *variadic_cntr += size;

  return (void*)(*(int*)(&(&start_addr)[1]) + 8 + start_addr);
  // __asm__("    movl    [%rbp],   %reg0");
  // __asm__("    add     8,        %reg0");
  // __asm__("    add     [%rbp-4], %reg0");
}*/