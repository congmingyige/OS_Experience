
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

/*
fork之后，从 fork 处开始父子进程并行执行，公有变量的值也在 fork 处被复制（当时的值），则父子进程分别使用各自的复本（而非共享）。
*/

char str[100]="aaa";	//仍然不行

main()
{
	//char str[100]="aaa";
	int pid;
	while ((pid=fork())==-1) ;
	if (pid>0)
	{
		while (1)
		{
			printf("OK\n");
			printf("str = %s\n",str);
			sleep(5);
		}
	}
	else
	{
		while (1)
		{
			scanf("%s\n",str);
		}
	}
}
