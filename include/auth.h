#ifndef AUTH_H
#define AUTH_H

typedef struct {
  char username[70];
  char passwd[70];
} user_t;

int authenticate(char* password_buffer, char* username_buffer);
void create_user(char* username, char* password);

#endif
