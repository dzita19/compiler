build/cc std/stdlib.c    -o std/stdlib.o      -c      
build/cc std/stdio.c     -o std/stdio.o       -c      
build/cc std/string.c    -o std/string.o      -c      
build/cc std/stdarg.c    -o std/stdarg.o      -c      
build/cc test/testfile.c -o test/testfile.hex -x -lib
"../sys software/build/emulator" test/testfile.hex #-args Hello World !!!