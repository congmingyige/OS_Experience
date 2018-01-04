
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

main()
{
	int filedes[2];
	char buffer[80];
	//建立管道，若成功则返回零，否则返回-1
	if (pipe(filedes)<0)
		printf("pipe error");
	//无名管道由单个进程创建，用途是在一个父进程和子进程之间通信
	if (fork()>0)
	{
		char s[]="hello!\n";
		close(filedes[0]);	//父进程关闭该管道的读出端
		write(filedes[1],s,sizeof(s));	//写入
		close(filedes[1]);	//关闭其它管道
	}
	else
	{
		close(filedes[1]);	//子进程关闭同一管道的写入端
		read(filedes[0],buffer,80);	//读取
		printf("%s",buffer);	//输出从管道中读取的内容
		close(filedes[0]);	//关闭其它管道
	}
}
