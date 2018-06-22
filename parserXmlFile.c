#include <libxml/parser.h>  
#include <libxml/tree.h>  
  
int main(int argc, char* argv[])  
{  
    xmlDocPtr doc;           //定义解析文档指针  
    xmlNodePtr curNode;      //定义结点指针(你需要它为了在各个结点间移动)  
    xmlChar *szKey;          //临时字符串变量  
    char *szDocName;  
      
    if (argc <= 1)   
    {  
       printf("Usage: %s docname\n", argv[0]);  
       return(0);  
    }  
    szDocName = argv[1];  
    doc = xmlReadFile(szDocName,"GB2312",XML_PARSE_RECOVER); //解析文件  
    if (NULL == doc)  
    {    
       printf("Document not parsed successfully\n");      
       return -1;  
    }  
    curNode = xmlDocGetRootElement(doc); //确定文档根元素  
    if (NULL == curNode)  
    {  
       printf("empty document\n");  
       xmlFreeDoc(doc);  
       return -1;  
    }  
    if (xmlStrcmp(curNode->name, BAD_CAST "ioMsg"))  
    {  
       printf("document of the wrong type, root node != ioMsg\n");  
       xmlFreeDoc(doc);  
       return -1;  
    }  
    curNode = curNode->xmlChildrenNode;
    while(curNode != NULL)  
    {  
       //取出节点中的内容 
	   if (!xmlStrcmp(curNode->name, (const char *)"disk")) {
	       // szKey = xmlNodeGetContent(curNode);  
	       // printf("name[%s] content[%s] \n", curNode->name, szKey);  
		   xmlNodePtr propNodePtr = curNode->xmlChildrenNode;
		   while (NULL != propNodePtr)
		   {
		        szKey = xmlNodeGetContent (propNodePtr);
		    	printf ("name[%s] content[%s] \n", propNodePtr->name, szKey);
		    	xmlFree(szKey);
		    	propNodePtr = propNodePtr->next;
		   }
	   }
	   curNode = curNode->next; 
    }  
     xmlFreeDoc(doc);  
    return 0;     
}  
