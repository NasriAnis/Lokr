#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

int f_gets(char* input, size_t size){
  // This function adds a null terminator
  // at the new line of a string
  if(fgets(input, size, stdin) == NULL) {
    return -1;  // Error
  }
 
  // If newline exists, input fits
  if(strchr(input, '\n')) {
    input[strcspn(input, "\n")] = '\0';
    return 1;  // Success
  } else {
    // Flush remaining input
    int c;
    while((c = getchar()) != '\n' && c != EOF);
    input[0] = '\0';
    return 0;  // Input too long
  }
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

void trim(char *str) {
    // trim leading spaces
    int start = 0;
    while (isspace((unsigned char)str[start]))
        start++;

    // shift string left
    if (start > 0)
        memmove(str, str + start, strlen(str) - start + 1);

    // trim trailing spaces
    int end = strlen(str) - 1;
    while (end >= 0 && isspace((unsigned char)str[end]))
        str[end--] = '\0';
}

// debugging purpose function
void print_hex(const unsigned char* data, size_t len){
  for(size_t i = 0; i < len; i++){
    printf("%02x", data[i]);
  }
  printf("\n");
}
