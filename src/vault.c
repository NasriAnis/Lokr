#include "vault.h"
#include <stdio.h>
#include <string.h>

FILE *fptr;

FILE *F_open(char* file_name, char* type){
  fptr = fopen(file_name, type);
  if (!fptr) {
      perror("fopen");
      return fptr;
  }
  return fptr;
} // dont forget to close

int F_exist(char *file_name) {
  fptr = F_open(file_name, "r");
  if (fptr == NULL) {
    return 1;
  }
  fclose(fptr);
  return 0;
}

int F_write(char *file_name, char *input, int new_line) {
  fptr = F_open(file_name, "a");
  fputs(input, fptr);
  for (int i = 0; new_line > i; i++){
    fputc('\n', fptr);
  }
  fclose(fptr);
  return 0;
}

int new_line(char *file_name, int num){
  fptr = F_open(file_name, "a");
  for (int i = 0; num > i; i++){
    fputc('\n', fptr);
  }
  fclose(fptr);
  return 0;
}

int F_search(char *file_name, char *in_to_search, char* word) {
  fptr = F_open(file_name, "r");

  while (fscanf(fptr, "%255s", word) == 1) {
      if (strcmp(word, in_to_search) == 0) {
        fscanf(fptr, "%255s", word);
        return 0;
      }
  }
  fclose(fptr);
  return 1;
}
