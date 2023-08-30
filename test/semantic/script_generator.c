#include <stdio.h>

int main(void){
  FILE* run_script = fopen("test/semantic/run.sh", "w");
  FILE* clean_script = fopen("test/semantic/clean.sh", "w");

  static const char* cc_path   = "build/compiler";
  static const char* test_path = "test/semantic/test";
  static const char* out_path  = "test/semantic/test";
  static const char* dbg_path  = "test/semantic/test";

  #define TEST_COUNT 16

  for(int i = 0; i < TEST_COUNT; i++){
    fprintf(run_script, "%s %s/test%03d.s %s/test%03d.c > %s/output%03d.txt\n", 
      cc_path, test_path, i, out_path, i, dbg_path, i);
    fprintf(clean_script, "rm %s/test%03d.txt\n", out_path, i);
    fprintf(clean_script, "rm %s/output%03d.txt\n", dbg_path, i);
  }

  fclose(run_script);
  fclose(clean_script);

  return 0;
}