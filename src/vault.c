#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/vault.h"

FILE *F_open(char* file_name, char* type){
  FILE *fptr;
  fptr = fopen(file_name, type);
  if (!fptr) {
      perror("fopen");
      return fptr;
  }
  return fptr;
} // dont forget to close

int F_exist(char *file_name) {
  FILE *fptr;
  fptr = F_open(file_name, "r");
  if (fptr == NULL) {
    return 1;
  }
  fclose(fptr);
  return 0;
}

int F_write(char *file_name, char *input, int new_line) {
  FILE *fptr;
  fptr = F_open(file_name, "a");
  fputs(input, fptr);
  for (int i = 0; new_line > i; i++){
    fputc('\n', fptr);
  }
  fclose(fptr);
  return 0;
}

int new_line(char *file_name, int num){
  FILE *fptr;
  fptr = F_open(file_name, "a");
  for (int i = 0; num > i; i++){
    fputc('\n', fptr);
  }
  fclose(fptr);
  return 0;
}

char** Cred_search(char* file_name){
  FILE *fptr;
  fptr = F_open(file_name, "r");
  char** results = malloc(sizeof(char*));

    char word1[256]; char word2[256];
    fscanf(fptr, "%255s %255s", word1, word2);

    results = realloc(results, 2 * sizeof(char*));
    results[0] = strdup(word1);
    results[1] = strdup(word2);

    return results;
}

Entry* search(char* file_name,char* input, int search_type){
  FILE *fptr;
  fptr = F_open(file_name, "r");

  int flag;
  int i = 0;
  Entry *results = NULL;

  char word1[256];
  char word2[256];
  char word3[256];
  char line[4024];

  while (fgets(line, sizeof(line), fptr) != NULL) {

    if (sscanf(line, "%255s %255s %255s", word1, word2, word3) != 3){
      continue;
    }

    // disable the flag
    flag = 0;

    if (search_type == 1){
      if (strcmp(word1, input) == 0) {
        flag = 1;
      }
    }
    else if (search_type == 2){
      if (strcmp(word2, input) == 0) {
        flag = 1;
      }
    }

    if (flag == 1){
      Entry *tmp = realloc(results, (i + 1) * sizeof(Entry));

      if (!tmp){free(results); return NULL;}
      results = tmp;

      results[i].site = strdup(word1);
      results[i].username = strdup(word2);
      results[i].password = strdup(word3);

      i = i + 1;
    }
  }

  Entry *tmp = realloc(results, (i + 1) * sizeof(Entry));
  if (!tmp) { free(results); return NULL; }
  results = tmp;

  // sentinel end delimitter
  results[i] = (Entry){NULL, NULL, NULL};

  return results;
}

Entry* dump_all(char* file_name){
  FILE *fptr;
  fptr = F_open(file_name, "r");

  int i = 0;
  Entry *results = NULL;

  char word1[256];
  char word2[256];
  char word3[256];
  char line[4024];

  while (fgets(line, sizeof(line), fptr) != NULL) {
    if (sscanf(line, "%255s %255s %255s", word1, word2, word3) != 3){
      continue;
    }
    Entry *tmp = realloc(results, (i + 1) * sizeof(Entry));

    if (!tmp){free(results); return NULL;}
    results = tmp;

    results[i].site = strdup(word1);
    results[i].username = strdup(word2);
    results[i].password = strdup(word3);

    i = i + 1;
  }

  Entry *tmp = realloc(results, (i + 1) * sizeof(Entry));
  if (!tmp) { free(results); return NULL; }
  results = tmp;

  // sentinel end delimitter
  results[i] = (Entry){NULL, NULL, NULL};

  return results;
}
