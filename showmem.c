#include <gtk/gtk.h>

GtkWidget *mem_window;

void show_mem_info (void) {
	
	mem_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (mem_window), "Storage Info");
	gtk_window_set_default_size (GTK_WINDOW (mem_window), 400, 150);
	gtk_window_set_position (GTK_WINDOW (mem_window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width (GTK_CONTAINER (mem_window), 20);

//	g_signal_connect (mem_window, 
//					  "destroy", 
//				      G_CALLBACK (gtk_main_quit), 
//				      NULL);

	GtkWidget *mem_box = gtk_vbox_new (FALSE,0);
	gtk_container_add (GTK_CONTAINER (mem_window), mem_box);

	GtkWidget *system_frame = gtk_frame_new ("System");
	GtkWidget *system_label = gtk_label_new ("总容量：102400M 已用：51200M 剩余：51200M");
	gtk_container_add (GTK_CONTAINER (system_frame), system_label);
	gtk_label_set_justify (GTK_LABEL (system_label), GTK_JUSTIFY_LEFT);
	gtk_box_pack_start (GTK_BOX (mem_box), system_frame, FALSE, FALSE, 5);

	GtkWidget *usb_frame = gtk_frame_new ("USB");
	GtkWidget *usb_label = gtk_label_new ("总容量：1024001M 已用：512001M 剩余：512001M");
	gtk_container_add (GTK_CONTAINER(usb_frame), usb_label);
	gtk_label_set_justify (GTK_LABEL(usb_label), GTK_JUSTIFY_LEFT);
	gtk_box_pack_start (GTK_BOX (mem_box), usb_frame, FALSE, FALSE, 5);

	GtkWidget *doppler_frame = gtk_frame_new ("Doppler");
	GtkWidget *doppler_label = gtk_label_new ("总容量：1024002M 已用：512002M 剩余：512002M");
	gtk_container_add (GTK_CONTAINER (doppler_frame), doppler_label);
	gtk_label_set_justify (GTK_LABEL (doppler_label), GTK_JUSTIFY_LEFT);
	gtk_box_pack_start (GTK_BOX (mem_box), doppler_frame, FALSE, FALSE, 5);

	gtk_widget_show_all (mem_window);

	return ;
}
