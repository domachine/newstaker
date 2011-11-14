
#include <string.h>

#include "ui.h"


/*
  Handles the delete event if it
  occurs in the main window.
*/
static gboolean
handle_delete_event (GtkWidget *, GdkEvent *, gpointer);

/*
  Releases all resources.
*/
static void
handle_destroy (GtkWidget *, gpointer data);

/*
  Handle the vi keybindings.

  Maybe this should be done using a
  GtkIMContext. But this time I'm too lazy
  to implement one :-).
*/
static void
handle_key_press_event (GtkWidget *widget,
                        GdkEventKey *event,
                        gpointer data);


int
main(int argc, char *argv[])
{
  ui_t *ui;

  gtk_init (&argc, &argv);

  ui = create_user_interface ();

  /*
    Connect signals.
  */
  g_signal_connect (ui->main_window, "delete-event",
                    G_CALLBACK (handle_delete_event), NULL);
  g_signal_connect (ui->main_window, "destroy",
                    G_CALLBACK (handle_destroy), ui);
  g_signal_connect (ui->main_window, "key-press-event",
                    G_CALLBACK (handle_key_press_event), ui);

  gtk_widget_show_all (ui->main_window);

  /*
    Enter main loop.
  */
  gtk_main ();

  return 0;
}


gboolean
handle_delete_event (GtkWidget *widget,
                     GdkEvent *event, gpointer data)
{
  /* Nothing fancy this time. */
  return FALSE;
}

void
handle_destroy (GtkWidget *widget, gpointer data)
{
  /* Release the user interface object. */
  g_free (data);
  gtk_main_quit ();
}

static void
handle_key_press_event (GtkWidget *widget,
                        GdkEventKey *event,
                        gpointer data)
{
  g_printf ("Huhu\n");
}
