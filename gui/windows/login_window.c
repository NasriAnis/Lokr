#include <gtk/gtk.h>

#include "../include/login_window.h"

/* Function where we construct the GTK window
 * so that it is shown when the app is launched */
static void login_panel(GtkApplication *app, gpointer data)
{
  // initializinf `GtkWindow` pointer
  GtkWidget *window;

  /* create a new window and set arguments
   * tutle, size etc */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Lokr login");
  gtk_window_set_default_size (GTK_WINDOW (window), 300, 300);

  /* Show the gtk window via this function */
  gtk_window_present (GTK_WINDOW (window));
}

int show_login_panel(int argc, char** argv)
{
  /* GtkApplication declaration to app pointer
    * then initialized in `gtk_application_new` */
  GtkApplication *app;
  app = gtk_application_new("com.lockr.app", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "activate", G_CALLBACK (login_panel), NULL);

  /* when quiting the app this function returns and then the process 
    * is freed from memory using the `g_object_unref` function */
  int status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
