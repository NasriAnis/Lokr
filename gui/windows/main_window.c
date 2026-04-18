#include <gtk/gtk.h>

static void main_window(GtkApplication *app, gpointer data);
static void view_vault(GtkButton *button, gpointer *window_ptr);

typedef struct{
  GtkWidget *window;
} Window;

int show_main_window(int argc, char** argv)
{
  GtkApplication *app;
  app = gtk_application_new("com.lockr.app", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "activate", G_CALLBACK (main_window), NULL);

  int status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

static void main_window(GtkApplication *app, gpointer data)
{
  GtkWidget *box;
  GtkWidget *label;
  GtkWidget *main_window;
  GtkWidget *button;

  Window *window_ptr = g_malloc(sizeof(Window));

  main_window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (main_window), "Lokr vault");
  gtk_window_set_default_size (GTK_WINDOW (main_window), 700, 600);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_window_set_child(GTK_WINDOW(main_window), box);

  label = gtk_label_new("Welcome to Lockr");
  gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(box), label);

  window_ptr->window = main_window;

  button = gtk_button_new_with_label("View Vault");
  g_signal_connect(button, "clicked", G_CALLBACK(view_vault), window_ptr);
  gtk_box_append(GTK_BOX (box), button);

  gtk_widget_set_valign(box, GTK_ALIGN_START);
  gtk_widget_set_halign(box, GTK_ALIGN_START);

  gtk_window_present (GTK_WINDOW (main_window));
}

static void view_vault(GtkButton *button, gpointer *windowptr)
{
  Window *window_ptr = (Window *)windowptr;
  GtkWidget *main_window = window_ptr->window;

  GtkWidget *box;
  GtkWidget *label;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_window_set_child(GTK_WINDOW(main_window), box);

  label = gtk_label_new("Welcome to Lockr");
  gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(box), label);

  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);

  gtk_window_present (GTK_WINDOW (main_window));
}
