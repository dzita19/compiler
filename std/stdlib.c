struct malloc_frame{
  int is_free;
  int size;
  struct malloc_frame *prev;
  struct malloc_frame *next;
};

static const void* HEAP_START = (void*)0x00040000;
static const void* HEAP_END   = (void*)0x00080000;

extern int printf(const char* format, ...);

void* malloc(unsigned size){
  // printf("ENTER MALLOC\n");
  static int initialized = 0;

  if(initialized == 0){
    initialized = 1;
    // printf("ENTER MALLOC INIT\n");

    struct malloc_frame* initial = (struct malloc_frame*)HEAP_START;
    initial->is_free = 1;
    initial->size    = HEAP_END - HEAP_START - sizeof(struct malloc_frame);
    initial->prev    = 0;
    initial->next    = 0;
  }
  size = (size + 15) & ~0x0f;

  for(struct malloc_frame* curr_frame = (struct malloc_frame*)HEAP_START; curr_frame; curr_frame = curr_frame->next){

    // printf("CURRENT FRAME AT %p, is_free: %d, size: %d, prev: %p, next: %p\n", 
    //   curr_frame, curr_frame->is_free, curr_frame->size, curr_frame->prev, curr_frame->next);

    // curr_frame is to be returned, new_frame is allocated as a free partition
    if(curr_frame->is_free && curr_frame->size >= size + sizeof(struct malloc_frame)){

      // cast to void* (size is in bytes)
      struct malloc_frame* new_frame = (void*)curr_frame + (sizeof(struct malloc_frame) + size);
      new_frame->is_free  = 1;
      new_frame->size     = curr_frame->size - (sizeof(struct malloc_frame) + size);
      new_frame->prev     = curr_frame;
      new_frame->next     = curr_frame->next;

      curr_frame->is_free = 0;
      curr_frame->size    = size;
      curr_frame->next    = new_frame;

      return (void*)curr_frame + sizeof(struct malloc_frame);
    }

  }

  return (void*)0;
}

void free(void* ptr){
  struct malloc_frame* frame = ptr - sizeof(struct malloc_frame);
  frame->is_free = 1;
  
  struct malloc_frame* next_frame = frame->next;
  struct malloc_frame* prev_frame = frame->prev;

  // merge with next
  if(next_frame && next_frame->is_free){
    if(next_frame->next) next_frame->next->prev = frame;
    frame->next  = next_frame->next;
    frame->size += next_frame->size + sizeof(struct malloc_frame);
  }

  // merge with prev
  if(prev_frame && prev_frame->is_free){
    if(frame->next) frame->next->prev = prev_frame;
    prev_frame->next  = frame->next;
    prev_frame->size += frame->size + sizeof(struct malloc_frame);
  }
} 

void print_malloc_frames(void){
  extern int printf(const char* format, ...);
  printf("MALLOC FRAMES:\n");
  int total_size = 0;
  for(struct malloc_frame* curr_frame = (struct malloc_frame*)HEAP_START; curr_frame; curr_frame = curr_frame->next){
    total_size += curr_frame->size + sizeof(struct malloc_frame);
    printf("MALLOC FRAME: %p, %8s, size: %#010x, prev: %p, next: %p\n", 
      curr_frame, curr_frame->is_free ? "FREE" : "NOT_FREE", curr_frame->size, curr_frame->prev, curr_frame->next);
  }
  printf("TOTAL SIZE:   %#010x\n\n", total_size);
  if(total_size != HEAP_END - HEAP_START) printf("WARNING: TOTAL SIZE DOESN'T MATCH THE HEAP SIZE!\n");
}