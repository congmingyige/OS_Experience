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
	fg 将进程切换到前台(front)
	bg 将进程切换到后台运行(back)
	jobs 列出作业控制的内容(仅显示在该进程终端下创建的进程)
	ctrl+Z 挂起进程
	ctrl+C 结束进程
	kill %
	kill %1 %2 %3
	killall -9 5_son 5_parent
	killall -9 5*
	killall -9 *
*/
