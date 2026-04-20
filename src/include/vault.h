#ifndef VAULT_H
#define VAULT_H

typedef struct {
  char *site;
  char *username;
  char *password;
} Entry;

int F_exist(char* file_name);
Entry* dump_all(char* file_name);
char** Cred_search(char* file_name);
int new_line(char *file_name, int num);
Entry* search(char* file_name,char* input, int search_type);
int F_write(char* file_name, char* input, int new_line);

#endif
