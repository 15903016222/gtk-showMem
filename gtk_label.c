#include <gtk/gtk.h>	// 头文件
 
int main(int argc, char *argv[]) 
{ 
	gtk_init(&argc, &argv); 	// 初始化
 
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);    // 创建窗口
 
	GtkWidget *vbox = gtk_vbox_new(TRUE, 10);       // 创建纵向盒状容器
	gtk_container_add(GTK_CONTAINER(window), vbox); // 把纵向盒状容器放入窗口
 
	// label one
	GtkWidget *label_one = gtk_label_new("label one");	// 创建标签
	gtk_container_add(GTK_CONTAINER(vbox), label_one); 	// 将按钮放在布局容器里
 
	// label two
	GtkWidget *label_two = gtk_label_new("label one");
	const char *str = gtk_label_get_label( GTK_LABEL(label_two) ); // 获得标签的内容
	printf("str = %s\n", str);
 
	gtk_container_add(GTK_CONTAINER(vbox), label_two); // 将按钮放在布局容器里
 
	// label three
	GtkWidget *label_three = gtk_label_new("label three");
	gtk_label_set_text( GTK_LABEL(label_three), "change the label text"); // 设置内容
 
	gtk_container_add(GTK_CONTAINER(vbox), label_three); // 将按钮放在布局容器里
 
	gtk_widget_show_all(window);	// 显示窗口控件
 
	gtk_main(); 	// 主事件循环
 
    return 0; 
} 

