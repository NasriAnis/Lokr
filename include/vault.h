#ifndef VAULT_H
#define VAULT_H

int F_exist(char* file_name);
int F_write(char* file_name, char* input, int new_line);
int new_line(char *file_name, int num);
char** F_search(char* file_name,char* input, char* output, int search_type, int fetch_line);

#endif
