//读进程
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//工程 .h文件 extern 全局变量

//多个进程处理不同信息(创建进程：pid)


//test1.c : test

//一个进程用于读取客户端名称
//另一个进程用于获得信息，然后创建一个子进程，从char * fifo[]中选择一个管道输出


//全局变量设置为指针(etc. char *[])可以吗？


//多个并发服务端

main()
{
	char * result="result";
	char * client_name="client_name";

	char * fifo[100];	//指针数组
	char client[100][100];
	int fd,myfd,count=0;
	char name[500],info[500],namet[5000];

	//读入客户端信息
	pr=open("client_data.txt","r");
	fscanf(pr,"%d\n",count);
	for (int i=1;i<=count;i++)
		fscanf(pr,"%s\n",client[i]);
	close(pr);

	
	while ((pid_client_name==fork())==1) ;
	if (pid_client_name==0)
	{
		//创建和打开管道(客户端名称)
		//单独创建一个子进程处理
		//是因为 客户端名称 和客户端信息 同时处理易造成信息的混乱
	}
	

	if (access(client_name,F_OK)==-1)
		mkfifo(client_name,0666);
	fd=open(client_name,O_RDONLY);



	while (

	while (1)
	{
		while (read(fd,name,100)<=0) ;	//得到客户端名称

		while (read(
	
		//创建子进程：分支管道的信息处理 x->server server->y
		//这样可以避免传送信息的阻塞，提高效率
		while ((pid=fork())==-1) ;	
		if (pid==0)
		{
			count++;
			strcpy(client[count],name);
			myfd=open(client[count],O_RDWR);
	
			

			while (1)
			{
				while (read(myfd,name,500)<=0) ;
				
				if (strcmp(str,"getallpid")==0)
				{
					strcpy(namet,"");
					for (int i=1;i<=count;i++)
						strcpy(namet,client[i]);
					while (write(myfd,namet,sizeof(namet))<=0) ;
				}
				else
				{
					for (int i=1;i<=count;i++)
						if (strcmp(name,client[i])==0)
							break;
					if (i==count+1)
					{
							
					}

					while (read(myfd,info,500)<=0) ;

					while (write(myfd,info,500)<=0) ;
				}
			}
		}

	//记录客户端的数目和名称
	pr=open("client_data.txt","w");
	fprintf(pr,"%d\n",count);
	for (int i=1;i<=count;i++)
		fprintf(pr,"%s\n",client[i]);
	close(pr);

	close(fd);
}

//进程间通信
//https://www.cnblogs.com/nufangrensheng/p/3561190.html

