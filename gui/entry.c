#include <gtk/gtk.h>

#include "include/login_window.h"
#include "include/signup_window.h"

#include "../src/include/vault.h"

int main()
{
  if (F_exist("user.bin") != 0) {
    show_signup_panel(0, NULL);
  } else {
    show_login_panel(0, NULL);
  }
  return 0;
}
