
#include <stdio.h>

main()
{
	FILE * fp;
	char buffer[80];
	//建立管道I/O:popen()会调用fork()产生子进程，然后从子进程中调用/bin/sh -c 来执行参数command到指令(cat /etc/passwd)。"r":读取
	//"r":popen()会建立管道连到子进程的标准输出设备，然后返回一个文件指针
	fp=popen("cat /etc/passwd","r");	//cat:查看文件内容
	fgets(buffer,sizeof(buffer),fp);	//从fp中读入长度小于等于buffer字节到参数buffer所指的内存中(buffer数组)，fgets为一次读取一行
	printf("%s",buffer);			//输出数据
	pclose(fp);
}
