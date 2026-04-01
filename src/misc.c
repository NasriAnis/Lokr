#include <stdio.h>
#include <string.h>

void f_gets(char* input){
  fgets(input, sizeof(input), stdin);
  input[strcspn(input, "\n")] = '\0';
}

void str_cpy(char* input, char* buffer){
  strncpy(input, buffer, sizeof(input) - 1);
  input[sizeof(input) - 1] = '\0';
}

int tokenize(char* input, char** tokens){
  int count = 0;

  char *token = strtok(input, " ");
  while (token != NULL){
    tokens[count++] = token;
    token = strtok(NULL, " ");
  }
  return count;
}
