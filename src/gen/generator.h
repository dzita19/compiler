#ifndef _GENERATOR_H_
#define _GENERATOR_H_

extern const char* default_base_objs; // for static objs with no linkage
extern const char* default_base_strings; // for static objs with no linkage
extern const char* default_base_text; // for labels in text section
extern const char* default_base_switch; // for switch tables
extern const char* default_base_initloop; // for initloops

void GenerateOutputFile(void);

#endif