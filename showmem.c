#include <gtk/gtk.h>
#include <pthread.h>

GtkWidget *mem_window;

// void init_window (void);
// void get_mem_file (void);
// void parser_mem_file (void);
// void show_mem_info (void);

void show_mem_info (void) {
	
	mem_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (mem_window), "Storage Info");
	gtk_widget_set_size_request (mem_window, 400, 300);
	gtk_window_set_position (GTK_WINDOW (mem_window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable (GTK_WINDOW (mem_window), FALSE);
	gtk_container_set_border_width (GTK_CONTAINER (mem_window), 10);

	GtkWidget *mem_box = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (mem_window), mem_box);

	GtkWidget *system_frame = gtk_frame_new ("System");
//	gtk_frame_set_shadow_type (GTK_FRAME (system_frame), GTK_SHADOW_NONE);
	GtkWidget *system_label = gtk_label_new (NULL);
	gtk_container_add (GTK_CONTAINER (system_frame), system_label);
	gtk_label_set_text (GTK_LABEL (system_label), 
						"总容量：102400M 已用：51200M 剩余：51200M");
	gtk_label_set_justify (GTK_LABEL (system_label), GTK_JUSTIFY_LEFT);
//	gtk_box_pack_start (GTK_BOX (mem_box), system_frame, FALSE, FALSE, 5);
	gtk_container_add (GTK_CONTAINER (mem_box), system_frame);

	GtkWidget *doppler_frame = gtk_frame_new ("Doppler");
//	gtk_frame_set_shadow_type (GTK_FRAME (doppler_frame), GTK_SHADOW_NONE);
//	GtkWidget *doppler_frame = gtk_frame_new (NULL);
	GtkWidget *doppler_label = gtk_label_new (NULL);
	gtk_container_add (GTK_CONTAINER (doppler_frame), doppler_label);
	gtk_label_set_text (GTK_LABEL (doppler_label), 
						"总容量：1024002M 已用：512002M 剩余：512002M");
	gtk_label_set_justify (GTK_LABEL (doppler_label), GTK_JUSTIFY_LEFT);
//	gtk_box_pack_start (GTK_BOX (mem_box), doppler_frame, FALSE, FALSE, 5);
	gtk_container_add (GTK_CONTAINER (mem_box), doppler_frame);

	GtkWidget *usb_frame = gtk_frame_new ("USB");
//	gtk_frame_set_shadow_type (GTK_FRAME (usb_frame), GTK_SHADOW_NONE);
//	GtkWidget *usb_frame = gtk_frame_new (NULL);
	GtkWidget *usb_label = gtk_label_new (NULL);
	gtk_container_add (GTK_CONTAINER(usb_frame), usb_label);
	gtk_label_set_text (GTK_LABEL (usb_label), 
						"总容量：1024001M 已用：512001M 剩余：512001M");
	gtk_label_set_justify (GTK_LABEL(usb_label), GTK_JUSTIFY_LEFT);
//	gtk_box_pack_start (GTK_BOX (mem_box), usb_frame, FALSE, FALSE, 5);
	gtk_container_add (GTK_CONTAINER (mem_box), usb_frame);

	GtkWidget *ok_button = gtk_button_new_with_label ("Ok");
	gtk_container_add (GTK_CONTAINER (mem_box), ok_button);

	g_signal_connect (mem_window,
				      "destroy",
					  G_CALLBACK (gtk_main_quit),
					  NULL);

	g_signal_connect_swapped (ok_button, "clicked",
							  G_CALLBACK (gtk_widget_destroy),
	                          mem_window);

	gtk_widget_show_all (mem_window);

	return ;
}

// void * get_mem_file (void *p) 
// {
// 	system ("/bin/bash getMem.sh");
// 	return p;
// }
// 
// void parser_mem_file (void) 
// {
// 	return ;
// }
// 
// void show_mem_info (void)
// {
// 	// 初始化窗口
// 	init_window ();
// 
// 	// 生成xml文件
// 	pthread_t get_mem_tid;
// 	int res = pthread_create (&get_mem_tid, NULL, get_mem_file, NULL);
// 	if (0 != res) {
// 		g_print ("pthread_create:%s \n", strerror (res));
// 		exit (-1);
// 	}
// 	res = pthread_join (get_mem_tid, NULL);
// 	if (0 != res) {
// 		g_print ("pthread_join:%s \n", strerror (res));
// 		exit (-1);
// 	}
// 
// 	// 解析文件
// 	
// 	// 显示信息
// 
// 	return ;
// }
