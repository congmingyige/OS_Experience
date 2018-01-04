
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/resource.h>

void time_print(char *str,clock_t time)
{
	long tps=sysconf(_SC_CLK_TCK);
	printf("%s:%6.2f secs\n",str,(float)time/tps);
}

int main(int argc,char *argv[])
{
	clock_t start,end;
	struct tms t_start,t_end;
	int pid;
	int pri=atoi(argv[1]);	//-20 -10 0 10 19
	char str[50][50];
	int i,j,k;

	start=times(&t_start);
		
	while ((pid=fork())==-1) ;
	/*
	if (pid>0)
	{
		printf("Test*** parent process : %d\n",getpid());
		printf("Test*** child process : %d\n",pid);	
	}
	*/
	if (pid>0)
	{
		setpriority(PRIO_PROCESS,pid,pri); //由父进程改变子进程的优先级
		exit(0);
	}
	else if (pid==0)
	{
//一个时间片结束后，会保存上下文，等待下一次又获得时间片，继续执行之前的程序 (优先级越低的进程越难获得资源，两个相邻时间片间隔越长，从而总运行时间越长)
		//sleep(1);	//不用加也能修改子进程优先级成功

		printf("begin priority = %d\n",getpriority(PRIO_PROCESS,pid));
		//exit(0);
		for (k=1;k<=1000000;k++)
			for (i=1;i<=50;i++)
				for (j=1;j<=50;j++)
					str[i][j]='a';
		printf("end priority = %d\n",getpriority(PRIO_PROCESS,pid));
					
	}
	end=times(&t_end);

	time_print("elapsed",end-start);

	puts("parent times");
	time_print("\tuser CPU",t_end.tms_utime);
	time_print("\tsys CPU",t_end.tms_stime);

	puts("child times");
	time_print("\tuser CPU",t_end.tms_cutime);
	time_print("\tsys CPU",t_end.tms_cstime);
//	printf("Test***  pid = %d\n",getpid());
	exit(0);
}


