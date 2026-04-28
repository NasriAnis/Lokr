#include <gtk/gtk.h>

#include "../include/view_vault.h"
#include "../include/main_window.h"
#include "../include/credential_handling.h"

#include "glib-object.h"

static void main_window(GtkApplication *app, gpointer data);


// wrapper funcxtion calling the main window
int show_main_window(int argc, char** argv){
  GtkApplication *app;
  app = gtk_application_new("com.lockr.app", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "activate", G_CALLBACK (main_window), NULL);

  int status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

// main window GUI builder function
static void main_window(GtkApplication *app, gpointer data){
  GtkWidget *paned, *sidebar, *btn_show_all,
  *scrolled_window, *content_area, *main_window,
  *btn_add_pass;

  Window *window_ptr = g_malloc(sizeof(Window));

  // Initialize window
  main_window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (main_window), "Lokr vault");
  gtk_window_set_default_size (GTK_WINDOW (main_window), 700, 600);

  // initialize the panned box
  paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_paned_set_position(GTK_PANED(paned), 150);
  gtk_window_set_child(GTK_WINDOW(main_window), paned);

  // create a right sidebar inside the panned box + buttons inside
  sidebar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_hexpand(sidebar, FALSE);
  gtk_widget_set_size_request(sidebar, 150, -1);
  gtk_paned_set_start_child(GTK_PANED(paned), sidebar);

  btn_show_all = gtk_button_new_with_label("Show All Data");
  g_signal_connect(btn_show_all, "clicked", G_CALLBACK(view_vault_window), window_ptr);
  gtk_box_append(GTK_BOX(sidebar), btn_show_all);

  btn_add_pass = gtk_button_new_with_label("add passwords");
  g_signal_connect(btn_add_pass, "clicked", G_CALLBACK(add_password_window), window_ptr);
  gtk_box_append(GTK_BOX(sidebar), btn_add_pass);

  // Create the stack to host the right stuff
  GtkWidget *stack = gtk_stack_new();
  gtk_widget_set_hexpand(stack, TRUE);
  gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
  gtk_stack_set_transition_duration(GTK_STACK(stack), 200);
  gtk_paned_set_end_child(GTK_PANED(paned), stack);

  // initialize the right scrooled bar for content
  scrolled_window = gtk_scrolled_window_new();

  // Create a box inside the scrolled window to hold password rows
  content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), content_area);
  gtk_stack_add_named(GTK_STACK(stack), scrolled_window, "vault");

  GtkWidget *add_pass_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_stack_add_named(GTK_STACK(stack), add_pass_area, "add_pass");

  gtk_stack_set_visible_child_name(GTK_STACK(stack), "vault");

  // save pointers used in other functions
  window_ptr->add_pass_area = add_pass_area;
  window_ptr->content_area  = content_area;
  window_ptr->window        = main_window;
  window_ptr->stack         = stack;

  gtk_window_present (GTK_WINDOW (main_window));
}
