//写进程
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

//查看历史记录功能(txt放置信息)

main(int argc,char * argv[])
{
	char * client_name="client_name";
	char * MYFIFO=argv[1];	//指向某个地址，若该地址的信息改变，MYFIFO也会改变
	int fd,myfd,pid;
	char name[500],info[500],namet[5000];

	printf("client_name = %s\n",client_name);
	signal(SIGPIPE,SIG_IGN);

	//创建服务端和该客户端的管道
	if (access(MYFIFO,F_OK)==-1)
		mkfifo(MYFIFO,0666);
	myfd=open(MYFIFO,O_RDWR);

	//给服务端发送信号,告知该客户端的存在
	if (access(client_name,F_OK)==-1)
	{
		printf("client waits...\n");
		while (access(client_name,F_OK)==-1)
		{
			sleep(0.1);
		}
	}
	printf("client comes\n");

	fd=open(client_name,O_WRONLY);
	while (write(fd,MYFIFO,sizeof(MYFIFO))<=0) ;
	close(fd);

	while ((pid=fork())==-1) ;
	//父进程：写入信号给其它进程
	if (pid>0)
	{
		printf("To : \n");
		scanf("%s",name);
		if (strcmp(name,"exit")==0)	//若输入的是“exit”，则该写进程终止
			break;
		else if (strcmp(name,"getallpid")==0)	//获得所有进程的id(fifo)
		{
			while (write(myfd,"getallpid",sizeof("getallpid"))<=0) ;
			while (read(myfd,namet,5000)<=0) ;
			printf("%s\n",namet);
		}
		else
		{
			scanf("%s\n",info);			
			
			while (write(myfd,name,sizeof(name))<=0) ;
			while (write(myfd,info,sizeof(info))<=0) ;
		}
	}
	//子进程：读出其它进程传送的信号
	else
	{
		while (read(myfd,info,100)<=0) ;
		printf("%s\n",info);
	}
	close(myfd);
}

