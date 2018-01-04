/* process using time */

#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

void time_print(char *,clock_t);

int main(void)
{
	int time=10000;//重复若干次
	clock_t start,end;
	struct tms t_start,t_end;

	start=times(&t_start);
	while (time)
	{
		system("grep the /usr/doc/*/* > /dev/null 2> /dev/null"); /*不能增添或删除空格*/
		time--;
	}

	end=times(&t_end);

	time_print("elapsed",end-start); /*进程运行总时间：终止时间-起始时间*/
	puts("parent times");
	time_print("\tuser CPU",t_end.tms_utime); /*进程花在执行用户模式代码上的时间*/
	time_print("\tsys CPU",t_end.tms_stime); /*进程花在执行内核代码上的时间*/
	
	puts("child times");
	time_print("\tuser CPU",t_end.tms_cutime); /*子进程花在执行用户模式代码上的时间*/
	time_print("\tsys CPU",t_end.tms_cstime); /*子进程花在执行内核代码上的时间*/
	
	exit(EXIT_SUCCESS);

	return 0;
}

void time_print(char *str,clock_t time)
{
	long tps=sysconf(_SC_CLK_TCK);
	printf("%s:%6.2f secs\n",str,(float)time/tps); /*time:时钟嘀嗒数，tps:时钟嘀嗒频率*/
}

