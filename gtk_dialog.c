
#include <gtk/gtk.h>

static void hello( GtkWidget *widget,
                   gpointer   data )
{
	GtkWidget *dialog;
	GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    
	g_print ("Hello World\n");
	// 创建对话框窗口
	dialog = gtk_dialog_new_with_buttons ("my dialog",
										  NULL,
										  flags,
										  ("_Ok"),
										  GTK_RESPONSE_ACCEPT,
										  ("_Cancel"),
										  GTK_RESPONSE_REJECT,
										  NULL);
    // 调整对话框大小
	gtk_widget_set_size_request (dialog,
				                 800,
								 600);

	gtk_widget_show (dialog);
}

static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    g_print ("delete event occurred\n");

    return TRUE;
}

static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    g_print ("destory \n");
    gtk_main_quit ();
}

int main( int   argc,
          char *argv[] )
{
    GtkWidget *window;
    GtkWidget *button;

    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    g_signal_connect (window, "delete-event",
		      G_CALLBACK (delete_event), NULL);
    
    g_signal_connect (window, "destroy",
		      G_CALLBACK (destroy), NULL);
    
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    button = gtk_button_new_with_label ("Hello World");
    
    g_signal_connect (button, "clicked",
		      G_CALLBACK (hello), NULL);
    
//    g_signal_connect_swapped (button, "clicked",
//			      G_CALLBACK (gtk_widget_destroy),
//                              window);
    
    gtk_container_add (GTK_CONTAINER (window), button);
    
    gtk_widget_show (button);
    
    gtk_widget_show (window);
    
    gtk_main ();
    
    return 0;
}
