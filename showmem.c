#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <gtk/gtk.h>

struct disk_info {
	xmlChar *name;	
	xmlChar *total;	
	xmlChar *used;	
	xmlChar *free;	
};

struct dialog {
	GtkWidget *mem_window;
	GtkWidget *mem_box;

	GtkWidget *system_frame;
	GtkWidget *system_label;

	GtkWidget *doppler_frame;
	GtkWidget *doppler_label;

	GtkWidget *usb_frame;
	GtkWidget *usb_label;

	GtkWidget *ok_button;
};

struct memory_dialog {
	struct dialog    mem_ui;
	struct disk_info mem_info;
};

void  show_mem_info (void);
static void  init_window (struct memory_dialog *dialog);
static void *get_mem_file (void *);
static void  parser_mem_file (struct memory_dialog *dialog);

static void free_mem (GtkWidget *widget, gpointer data)
{
	struct memory_dialog *mem_dialog = (struct memory_dialog *)data;

	free (mem_dialog);
	mem_dialog = NULL;

	return ;
}

static void init_window (struct memory_dialog *dialog) {
	struct memory_dialog *mem_dialog = dialog;

	mem_dialog->mem_ui.mem_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (mem_dialog->mem_ui.mem_window), 
						  "Storage Info");
	gtk_widget_set_size_request (mem_dialog->mem_ui.mem_window, 400, 300);
	gtk_window_set_position (GTK_WINDOW (mem_dialog->mem_ui.mem_window), 
							 GTK_WIN_POS_CENTER);
	gtk_window_set_resizable (GTK_WINDOW (mem_dialog->mem_ui.mem_window), FALSE);
	gtk_container_set_border_width (GTK_CONTAINER (mem_dialog->mem_ui.mem_window), 10);

	mem_dialog->mem_ui.mem_box = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (mem_dialog->mem_ui.mem_window), 
					   mem_dialog->mem_ui.mem_box);

	mem_dialog->mem_ui.system_frame = gtk_frame_new ("System");
	mem_dialog->mem_ui.system_label = gtk_label_new (NULL);
	gtk_container_add (GTK_CONTAINER (mem_dialog->mem_ui.system_frame), 
						mem_dialog->mem_ui.system_label);
	gtk_label_set_justify (GTK_LABEL (mem_dialog->mem_ui.system_label), 
						   GTK_JUSTIFY_LEFT);
	gtk_container_add (GTK_CONTAINER (mem_dialog->mem_ui.mem_box), 
				       mem_dialog->mem_ui.system_frame);

	mem_dialog->mem_ui.doppler_frame = gtk_frame_new ("Doppler");
	mem_dialog->mem_ui.doppler_label = gtk_label_new (NULL);
	gtk_container_add (GTK_CONTAINER (mem_dialog->mem_ui.doppler_frame), 
						mem_dialog->mem_ui.doppler_label);
	gtk_label_set_justify (GTK_LABEL (mem_dialog->mem_ui.doppler_label), 
						GTK_JUSTIFY_LEFT);
	gtk_container_add (GTK_CONTAINER (mem_dialog->mem_ui.mem_box), 
						mem_dialog->mem_ui.doppler_frame);

	mem_dialog->mem_ui.usb_frame = gtk_frame_new ("USB");
	mem_dialog->mem_ui.usb_label = gtk_label_new (NULL);
	gtk_container_add (GTK_CONTAINER(mem_dialog->mem_ui.usb_frame), 
						mem_dialog->mem_ui.usb_label);
	gtk_label_set_justify (GTK_LABEL(mem_dialog->mem_ui.usb_label), 
						GTK_JUSTIFY_LEFT);
	gtk_container_add (GTK_CONTAINER (mem_dialog->mem_ui.mem_box), 
						mem_dialog->mem_ui.usb_frame);

	mem_dialog->mem_ui.ok_button = gtk_button_new_with_label ("Ok");
	gtk_container_add (GTK_CONTAINER (mem_dialog->mem_ui.mem_box), 
						mem_dialog->mem_ui.ok_button);

	g_signal_connect (mem_dialog->mem_ui.mem_window,
					  "destroy",
					  G_CALLBACK (gtk_main_quit),
					  NULL);

	g_signal_connect (mem_dialog->mem_ui.ok_button, 
				      "clicked",
				      G_CALLBACK (free_mem),
				      mem_dialog);

	g_signal_connect_swapped (mem_dialog->mem_ui.ok_button, 
				              "clicked",
				              G_CALLBACK (gtk_widget_destroy),
				              mem_dialog->mem_ui.mem_window);

	gtk_widget_show_all (mem_dialog->mem_ui.mem_window);

	return ;
}

static void *get_mem_file (void *p) 
{
	system ("/bin/bash getMem.sh");
	return p;
}

static void create_xml_file (void)
{
	pthread_t get_mem_tid;
	int res = pthread_create (&get_mem_tid, NULL, get_mem_file, NULL);
	if (0 != res) {
		g_print ("pthread_create:%s \n", strerror (res));
		exit (-1);
	}
	res = pthread_join (get_mem_tid, NULL);
	if (0 != res) {
		g_print ("pthread_join:%s \n", strerror (res));
		exit (-1);
	}

	return ;
}

static void set_mem_label_text (struct memory_dialog *dialog)
{
	struct memory_dialog *mem_dialog = dialog;
	gchar content[215] = {0};

	sprintf (content, "总容量：%s  已用：%s  可用：%s", 
			 mem_dialog->mem_info.total, 
			 mem_dialog->mem_info.used, 
			 mem_dialog->mem_info.free);

	if (!strcmp (mem_dialog->mem_info.name, "system")) {
		gtk_label_set_text (GTK_LABEL (mem_dialog->mem_ui.system_label), 
							content);
	} 
	else if (!strcmp (mem_dialog->mem_info.name, "doppler")) {
		gtk_label_set_text (GTK_LABEL (mem_dialog->mem_ui.doppler_label), 
							content);
	} 
	else if (!strcmp (mem_dialog->mem_info.name, "usb")) {
		gtk_label_set_text (GTK_LABEL (mem_dialog->mem_ui.usb_label), 
							content);
	} 

	return ;
}

static void parser_mem_file (struct memory_dialog *dialog) 
{
	struct memory_dialog *mem_dialog = dialog;

	xmlDocPtr doc;
	xmlNodePtr curNode;
	struct disk_info info = {NULL};

	doc = xmlReadFile ("/tmp/mem.xml", "GB2312", XML_PARSE_RECOVER);
	if (NULL == doc)  
	{    
		printf("Document not parsed successfully\n");      
		return ;  
	}  
	curNode = xmlDocGetRootElement(doc); //确定文档根元素  
	if (NULL == curNode)  
	{  
		g_print ("empty document\n");  
		xmlFreeDoc(doc);  
		return ;  
	}
	curNode = curNode->xmlChildrenNode;
	while (NULL != curNode) {
		if (!xmlStrcmp (curNode->name, (const char *)"disk")) {
			xmlNodePtr tmpNodePtr = curNode->xmlChildrenNode;
			while (NULL != tmpNodePtr) {
				if (!strcmp (tmpNodePtr->name, "name")) {
					mem_dialog->mem_info.name = xmlNodeGetContent (tmpNodePtr);
				} 
				else if (!strcmp (tmpNodePtr->name, "total")) {
					mem_dialog->mem_info.total = xmlNodeGetContent (tmpNodePtr);
				} 
				else if (!strcmp (tmpNodePtr->name, "used")) {
					mem_dialog->mem_info.used = xmlNodeGetContent (tmpNodePtr);
				} 
				else if (!strcmp (tmpNodePtr->name, "free")) {
					mem_dialog->mem_info.free = xmlNodeGetContent (tmpNodePtr);
				} 
				tmpNodePtr = tmpNodePtr->next;
			}
			g_print ("name[%s], total[%s], used[%s], free[%s] \n", 
						mem_dialog->mem_info.name, 
						mem_dialog->mem_info.total, 
						mem_dialog->mem_info.used, 
						mem_dialog->mem_info.free);
			set_mem_label_text (mem_dialog);
			xmlFree (mem_dialog->mem_info.name);
			xmlFree (mem_dialog->mem_info.total);
			xmlFree (mem_dialog->mem_info.used);
			xmlFree (mem_dialog->mem_info.free);
		}
		curNode = curNode->next;
	}
	xmlFreeDoc (doc);

	return ;
}

void show_mem_info (void)
{
	struct memory_dialog *mem_dialog = NULL;
	mem_dialog = malloc (sizeof (struct memory_dialog));
	if (NULL == mem_dialog) {
		exit (-1);
	}

	// 初始化窗口
	init_window (mem_dialog);

	// 生成xml文件
	create_xml_file ();

	// 解析文件 并显示
	parser_mem_file (mem_dialog);

	return ;
}
