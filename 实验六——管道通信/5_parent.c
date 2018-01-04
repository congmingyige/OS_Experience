//读进程
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// system("./5_son >> result.txt 2>&1");	//run & output information
//pstree pid -p 	// see all son process of process ID=pid

main()
{
	char * FIFO="fifo";
	int fd;
	char str[100];

	//若没有有名管程，则创建，这样的好处是读进程可以获得读进程运行之前写进程发送的信息
	if (access(FIFO,F_OK)==-1)
	{
		unlink(FIFO);
		mkfifo(FIFO,0666);
	}

	fd=open(FIFO,O_RDONLY);
	while (1)
	{
		while (read(fd,str,100)<=0);	//一直读，直到读入数据
		printf("%s\n",str);
		/*
		if (read(fd,str,100)>0)
			printf("%s\n",str);
		*/
		/*
		read(fd,str,100);	//若没有FIFO读出端，则会输出一样的内容
		printf("%s\n",str);
		*/
	}
	close(fd);
}
/*
//写进程
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

main()
{
	char * FIFO="fifo";
	int fd;
	char str[100],str_pid[100],s[100];	//数组要开得足够大，否则输出的内容会出错

	//判断有名管道是否存在
	//若不存在，则每隔一段时间检查一次，直到存在
	if (access(FIFO,F_OK)==-1)
	{
		printf("FIFO waits...\n");
		while (access(FIFO,F_OK)==-1)
		{
			sleep(0.1);
		}
	}
	printf("FIFO comes\n");

	signal(SIGPIPE,SIG_IGN);
	fd=open(FIFO,O_WRONLY);
	while (1)
	{
		scanf("%s",str);
		if (strcmp(str,"exit")==0)	//若输入的是“exit”，则该写进程终止
			break;
//		printf("str = %s\n",str);

		strcpy(str_pid,"\nsent by process ");
		sprintf(s,"%d",getpid());
		strcat(str_pid,s);
//		printf("%s\n",str_pid);

		while (write(fd,str_pid,sizeof(str_pid))<=0) ;
		while (write(fd,str,sizeof(str))<=0) ;
		//若没有FIFO读出端，则会结束(无signal(SIGINT,SIG_IGN);)
	}
	close(fd);
}
/*
找出正在运行程序的进程PID
pidof 5_parent
*/

