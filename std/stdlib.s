.global malloc
.global free
.global print_malloc_frames

.extern printf

.section    .data
HEAP_START:
    .long   262144
HEAP_END:
    .long   524288

.LP0:
    .long   0

.section    .rodata
.LP1:
    .asciz  "MALLOC FRAMES:\n"
.LP2:
    .asciz  "MALLOC FRAME: %p, %8s, size: %#010x, prev: %p, next: %p\n"
.LP3:
    .asciz  "FREE"
.LP4:
    .asciz  "NOT_FREE"
.LP5:
    .asciz  "TOTAL SIZE:   %#010x\n\n"
.LP6:
    .asciz  "WARNING: TOTAL SIZE DOESN'T MATCH THE HEAP SIZE!\n"

.end