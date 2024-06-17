#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sched.h>

#define CC_PATH "../compiler/build/compiler"
#define AS_PATH "../sys-software/build/assembler"
#define LD_PATH "../sys-software/build/linker"

#define CMD_PARSE_ERROR (-1)
#define CMD_PARSE_INPUT   0
#define CMD_PARSE_OUTPUT  1

#define OUTPUT_DEFAULT  (-1)
#define OUTPUT_EXEC       0
#define OUTPUT_OBJ        1
#define OUTPUT_ASM        2

static int     parse_state    = 0;
static char*   output_path    = 0;
static char**  input_paths    = 0;
static int     input_size     = 0;
static int     output_format  = OUTPUT_DEFAULT;
static int     debug_enabled  = 0;
static int     link_with_lib  = 0;

static int exec_prog(const char **argv) {
  pid_t   my_pid;
  int     status;

  if((my_pid = fork()) == 0) {
    if (execve(argv[0], (char **)argv , NULL) == -1) {
      perror("child process execve failed [%m]");
      return 1;
    }
  }

  while(0 == waitpid(my_pid , &status , WNOHANG)) {
    sleep(0.001);
  }

  if(WIFEXITED(status) != 1 || WEXITSTATUS(status) != 0) {
    return 1;
  }

  return 0;
}

static void ParseCmdArgs(int argc, char** argv){

  for(int i = 1; i < argc; i++){
    switch(parse_state){
    case CMD_PARSE_ERROR: return;

    case CMD_PARSE_INPUT:{
      if(strcmp(argv[i], "-o") == 0){
        parse_state = CMD_PARSE_OUTPUT;
      }
      else if(strcmp(argv[i], "-dbg") == 0){
        debug_enabled = 1;
      }
      else if(strcmp(argv[i], "-lib") == 0){
        link_with_lib = 1;
      }
      else if(strcmp(argv[i], "-x") == 0){
        if(output_format == OUTPUT_DEFAULT) {
          output_format = OUTPUT_EXEC;
        }
        else{
          printf("Output format already specified.\n");
          parse_state = CMD_PARSE_ERROR;
        }
      }
      else if(strcmp(argv[i], "-c") == 0){
        if(output_format == OUTPUT_DEFAULT) {
          output_format = OUTPUT_OBJ;
        }
        else{
          printf("Output format already specified.\n");
          parse_state = CMD_PARSE_ERROR;
        }
      }
      else if(strcmp(argv[i], "-s") == 0){
        if(output_format == OUTPUT_DEFAULT) {
          output_format = OUTPUT_ASM;
        }
        else{
          printf("Output format already specified.\n");
          parse_state = CMD_PARSE_ERROR;
        }
      }
      else {
        input_paths[input_size++] = argv[i];
      }
    } break;

    case CMD_PARSE_OUTPUT:{
      if(strcmp(argv[i], "-o") == 0){
        parse_state = CMD_PARSE_ERROR;
      }
      else if(strcmp(argv[i], "-dbg") == 0){
        parse_state = CMD_PARSE_ERROR;
      }
      else if(strcmp(argv[i], "-lib") == 0){
        parse_state = CMD_PARSE_ERROR;
      }
      else if(strcmp(argv[i], "-x") == 0){
        parse_state = CMD_PARSE_ERROR;
      }
      else if(strcmp(argv[i], "-c") == 0){
        parse_state = CMD_PARSE_ERROR;
      }
      else if(strcmp(argv[i], "-s") == 0){
        parse_state = CMD_PARSE_ERROR;
      }
      else{
        if(output_path == 0) {
          output_path = argv[i];
          parse_state = CMD_PARSE_INPUT;
        }
        else {
          printf("Output file already specified.\n");
          parse_state = CMD_PARSE_ERROR;
        }
      }
    } break;
    }
  }
}

int main(int argc, char** argv){
  input_paths = malloc(sizeof(char*) * argc);
  int retval = 0;

  ParseCmdArgs(argc, argv);

  if(output_format == OUTPUT_DEFAULT) {
    output_format = OUTPUT_EXEC;
  }

  if(input_size == 0 || output_path == 0){
    parse_state = CMD_PARSE_ERROR;
  }
  if(output_format != OUTPUT_EXEC && link_with_lib){
    parse_state = CMD_PARSE_ERROR;
  }
  if(output_format != OUTPUT_EXEC && input_size != 1){
    parse_state = CMD_PARSE_ERROR;
  }

  // only regular state 
  if(parse_state == CMD_PARSE_INPUT){
    if(output_format == OUTPUT_ASM){
      if(debug_enabled) {
        const char* cc_args[] = { CC_PATH, "-o", output_path, input_paths[0], "-dbg", NULL };
        retval = exec_prog(cc_args);
        if(retval) printf("Error compiling file %s.\n", input_paths[0]);
        // else printf("Assembler file %s successfully created.\n", output_path);
      }
      else {
        const char* cc_args[] = { CC_PATH, "-o", output_path, input_paths[0],         NULL };
        retval = exec_prog(cc_args);
        if(retval) printf("Error compiling file %s.\n", input_paths[0]);
        // else printf("Assembler file %s successfully created.\n", output_path);
      }
    }
    else if(output_format == OUTPUT_OBJ){
      static const char* temp_asm_path = "temp/temp.s";
      if(debug_enabled) {
        const char* cc_args[]   = { CC_PATH, "-o", temp_asm_path, input_paths[0],   "-dbg", NULL };
        if(exec_prog(cc_args) == 0){
          const char* as_args[] = { AS_PATH, "-o", output_path,  temp_asm_path,     "-dbg", NULL };
          retval = exec_prog(as_args);
          if(retval) printf("Error assembling file %s.\n", input_paths[0]);
          // else printf("Object file %s successfully created.\n", output_path);
        }
        else {
          retval = 1;
          printf("Error compiling file %s.\n", input_paths[0]);
        }
      }
      else {
        const char* cc_args[]   = { CC_PATH, "-o", temp_asm_path, input_paths[0],           NULL };
        if(exec_prog(cc_args) == 0){
          const char* as_args[] = { AS_PATH, "-o", output_path,  temp_asm_path,             NULL };
          retval = exec_prog(as_args);
          if(retval) printf("Error assembling file %s.\n", input_paths[0]);
          // else printf("Object file %s successfully created.\n", output_path);
          remove(temp_asm_path); // delete temp file
        }
        else {
          retval = 1;
          printf("Error compiling file %s.\n", input_paths[0]);
        }
      }
    }
    else if(output_format == OUTPUT_EXEC){
      char* temp_asm_path = malloc(sizeof(char) * strlen("temp/temp") + 6); // temp/temp123.s\0
      char* temp_obj_path = malloc(sizeof(char) * strlen("temp/temp") + 6);

      int errors = 0;

      // compile
      for(int i = 0; i < input_size; i++){
        sprintf(temp_asm_path, "temp/temp%03d.s", i);
        sprintf(temp_obj_path, "temp/temp%03d.o", i);

        if(debug_enabled){
          const char* cc_args[]   = { CC_PATH, "-o", temp_asm_path, input_paths[i],   "-dbg", NULL };
          if(exec_prog(cc_args) == 0){
            const char* as_args[] = { AS_PATH, "-o", temp_obj_path, temp_asm_path,            NULL };
            errors = exec_prog(as_args);
            if(errors) printf("Error assembling file %s.\n", input_paths[i]);
          }
          else {
            errors = 1;
            printf("Error compiling file %s.\n", input_paths[i]);
          }
        }
        else{
          const char* cc_args[]   = { CC_PATH, "-o", temp_asm_path, input_paths[i],           NULL };
          if(exec_prog(cc_args) == 0){
            const char* as_args[] = { AS_PATH, "-o", temp_obj_path, temp_asm_path,            NULL };
            errors = exec_prog(as_args);
            if(errors) printf("Error assembling file %s.\n", input_paths[i]);
            remove(temp_asm_path); // delete temp file
          }
          else {
            errors = 1;
            printf("Error compiling file %s.\n", input_paths[i]);
          }
        }
      }

      // link
      if(errors == 0){
        const char*  stdlib_files[] = { "std/stdlib.o", "std/stdio.o", "std/string.o", "std/stdarg.o" };
        const char** ld_args = malloc(sizeof(char*) * (input_size + 5 + sizeof(stdlib_files) / sizeof(*stdlib_files)));

          // LD_PATH, output_path, ... (input_paths), crt0.o, [stdlib files], NULL
        ld_args[0] = LD_PATH;
        ld_args[1] = "-o";
        ld_args[2] = output_path;
        ld_args[3] = "std/crt0.o";
        for(int i = 0; i < input_size; i++) {
          sprintf(temp_obj_path, "temp/temp%03d.o", i);
          ld_args[i + 4] = strdup(temp_obj_path); // ALLOCATED
        }
        for(int i = 0; i < sizeof(stdlib_files) / sizeof(*stdlib_files); i++){
          ld_args[input_size + 4 + i] = link_with_lib ? stdlib_files[i] : NULL;
        }
        ld_args[input_size + 4 + sizeof(stdlib_files) / sizeof(*stdlib_files)] = NULL;

        retval = exec_prog(ld_args);
        for(int i = 0; i < input_size; i++) {
          if(debug_enabled == 0) remove(ld_args[i + 4]); // delete temp file
          free((void*)ld_args[i + 4]);
        }
        if(retval) printf("Error linking files.\n");
        // else printf("Executable file %s successfully created.\n", output_path);
        free(ld_args);
      }
      else {
        retval = 1;
      }

      free(temp_asm_path);
      free(temp_obj_path);
    }
  }
  else{
    printf("Invalid arguments.\n");
    printf("Recommended input: -o <output_file> {<input_file>} [*output_format*] [*flags*]\n"
           "\tOutput formats: -x (to exec), -c (to obj), -s (to asm)\n"
           "\tFlags:          -dbg (debug output), -lib (link with stdlib--)\n");
    retval = 1;
  }

  free(input_paths);
  return retval;
}