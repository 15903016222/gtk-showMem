#include <gtk/gtk.h>	// 头文件
#include "showmem.h"

extern GtkWidget *mem_window;

int main(int argc, char *argv[]) 
{ 
	gtk_init(&argc, &argv); 	// 初始化
 
	/*
	 *  显示存储模块的信息 开始
	 */
	show_mem_info ();

	gtk_main(); 	// 主事件循环
 
    return 0; 
} 
