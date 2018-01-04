
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

main()
{
	char buffer[80];
	int fd;
	char * FIFO;
	unlink(FIFO);		//删除文件(如果之前存在)
	mkfifo(FIFO,0666);	//建立有名管道
	//6=4+2 读+写的权限
	//文件所有组，文件所有组所在用户的其它文件，除此之外
	if (fork()>0)
	{
		char s[]="hello!\n";
		fd=open(FIFO,O_WRONLY);	//打开文件，O_WRONLY：以只写方式打开文件。返回文件描述词
		write(fd,s,sizeof(s));	//将数据写入已打开的文件内,sizeof(s):数据的长度。使用open()函数返回到文件描述词
		close(fd);
	}
	else
	{
		fd=open(FIFO,O_RDONLY);	//打开文件，O_RDONLY：以只读方式打开文件
		read(fd,buffer,80);	//由已打开的文件读取数据
		printf("%s",buffer);	//输出数据
		close(fd);
	}
}
