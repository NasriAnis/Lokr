#include <gtk/gtk.h>

#include "../include/signup_window.h"
#include "../src/include/auth.h"

typedef struct {
    GtkWidget *user_entry;
    GtkWidget *pass_entry;
} LoginData;

static void test_credentials(GtkButton *button, gpointer user_data){
  LoginData *login = (LoginData *)user_data;
  const char *username = gtk_editable_get_text(GTK_EDITABLE(login->user_entry));
  const char *password = gtk_editable_get_text(GTK_EDITABLE(login->pass_entry));

  create_user((char *)username, (char *)password);

  // kill the window and return to the main function
  GtkRoot *root = gtk_widget_get_root(GTK_WIDGET(button));
  GtkApplication *app = gtk_window_get_application(GTK_WINDOW(root));
  g_application_quit(G_APPLICATION(app));

  g_free(login);
}

/* Function where we construct the GTK window
 * so that it is shown when the app is launched */
static void signup_panel(GtkApplication *app, gpointer data)
{
  // initializinf `GtkWindow` pointer
  GtkWidget *box;
  GtkWidget *label;
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *entry_username;
  GtkWidget *entry_password;

  LoginData *loginptr = g_malloc(sizeof(LoginData));

  /* create a new window and set arguments
   * tutle, size etc */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Lokr singup");
  gtk_window_set_default_size (GTK_WINDOW (window), 300, 300);

  /* Create a box */
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_window_set_child(GTK_WINDOW(window), box);

  /* Create user entry */
  label = gtk_label_new("username");
  gtk_widget_set_halign(label, GTK_ALIGN_START);
  gtk_box_append(GTK_BOX(box), label);

  entry_username = gtk_entry_new();
  gtk_box_append(GTK_BOX(box), entry_username);

  /* Create password entry */
  label = gtk_label_new("password");
  gtk_widget_set_halign(label, GTK_ALIGN_START);
  gtk_box_append(GTK_BOX(box), label);

  entry_password = gtk_entry_new();
  gtk_box_append(GTK_BOX(box), entry_password);

  // credentials retrieved from login pannel
  loginptr->user_entry = entry_username;
  loginptr->pass_entry = entry_password;

  /* Create a button */
  button = gtk_button_new_with_label("Login");
  g_signal_connect(button, "clicked", G_CALLBACK(test_credentials), loginptr);
  gtk_box_append(GTK_BOX (box), button);

  /* Show the gtk window via this function */
  gtk_window_present (GTK_WINDOW (window));
}

int show_signup_panel(int argc, char** argv)
{
  /* GtkApplication declaration to app pointer
    * then initialized in `gtk_application_new` */
  GtkApplication *app;
  app = gtk_application_new("com.lockr.app", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "activate", G_CALLBACK (signup_panel), NULL);

  /* when quiting the app this function returns and then the process 
    * is freed from memory using the `g_object_unref` function */
  int status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
