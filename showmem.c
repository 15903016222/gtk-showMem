#include <gtk/gtk.h>

void show_mem_info (void) {

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);    // 创建窗口

	gtk_widget_set_size_request (window, 400, 150);
	// 创建纵向盒状容器
	GtkWidget *vbox = gtk_vbox_new(TRUE, 10);      
	// 把纵向盒状容器放入窗口
	gtk_container_add(GTK_CONTAINER(window), vbox); 
 
	// label one
	// 创建标签
	GtkWidget *label_one = gtk_label_new("label one");
	// 设置标签的内容
	gtk_label_set_text (GTK_LABEL (label_one),
				"总容量：1024000-0M 已用：512000M 剩余：512000M");
	gtk_label_set_justify (GTK_LABEL (label_one), GTK_JUSTIFY_LEFT);
	// 将按钮放在布局容器里
	gtk_container_add(GTK_CONTAINER(vbox), label_one); 	
 
	// label two
	GtkWidget *label_two = gtk_label_new("label two");
	gtk_container_add(GTK_CONTAINER(vbox), label_two);
	gtk_label_set_text (GTK_LABEL (label_two),
				"0123456789");
 
	// label three
	GtkWidget *label_three = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(vbox), label_three);
	gtk_label_set_text (GTK_LABEL (label_three),
				"abcdefghijklmnopqrstuvwxyz");

	// 显示窗口控件
	gtk_widget_show_all(window);	

	return ;
}
