#ifndef MISC_H
#define MISC_H

#include <stdlib.h>

void trim(char *str);
int f_gets(char* input, size_t size);
void str_cpy(char* input, char* buffer);
int tokenize(char* input, char** tokens);
void print_hex(const unsigned char* data, size_t len);

#endif
