
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/resource.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>

void time_print(char *str,clock_t time)
{
	long tps=sysconf(_SC_CLK_TCK);
	printf("%s:%6.2f secs\n",str,(float)time/tps);
}

int main(int argc,char *argv[])
{
	clock_t start,end;
	struct tms t_start,t_end;
	int count=1000,count_=count;
	int pri=atoi(argv[1]);	//-20 -10 0 10 19
	pid_t pid;
	char str[50][50];
	int i,j;

	start=times(&t_start);
	while ((pid=fork())==-1) ;

	while (count)
	{
		count--;
		while ((pid=fork())==-1) ;
		if (pid>0)
		{
			//由父进程改变子进程的优先级
			setpriority(PRIO_PROCESS,pid,pri);
			exit(0);
		}
		else if (pid==0)
		{
			//printf("begin_priority = %d\n",getpriority(PRIO_PROCESS,getpid()));
			char c=(char)(count%100);
			for (i=0;i<50;i++)
				for (j=0;j<50;j++)
					str[i][j]=c;
			//printf("end_priority = %d\n",getpriority(PRIO_PROCESS,getpid()));
		}
	}	
	end=times(&t_end);
	//fork():子进程会拷贝父进程"fork()"语句之后的代码。while循环对父进程添加"exit(0)",让父进程结束，让子进程执行while循环。只有for循环结束(子进程的工作结束)，才能重新进行while循环，创建新的子进程。跳出while循环的是子进程，之前已执行"work()"函数count次。

	printf("total time including others(%d times) : " , count_);

	time_print("elapsed",end-start);

	puts("parent times");
	time_print("\tuser CPU",t_end.tms_utime);
	time_print("\tsys CPU",t_end.tms_stime);

	puts("child times");
	time_print("\tuser CPU",t_end.tms_cutime);
	time_print("\tsys CPU",t_end.tms_cstime);

	exit(0);
}


