#include <stdio.h>

int main(void){
  FILE* run_script = fopen("test/semantic/run.sh", "w");
  FILE* clean_script = fopen("test/semantic/clean.sh", "w");

  const char* cc_path   = "build/compiler";
  const char* test_path = "test/semantic/test";
  const char* out_path  = "test/semantic/test";

  const int TEST_COUNT = 16;

  for(int i = 0; i < TEST_COUNT; i++){
    fprintf(run_script, "build/compiler %1$s/test%3$03d.c > %2$s/output%3$03d.txt\n", test_path, out_path, i);
    fprintf(clean_script, "rm %1$s/output%2$03d.txt\n", out_path, i);
  }

  return 0;
}