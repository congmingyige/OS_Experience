/* fork usage */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t child;
	if ((child=fork())==-1)	//创建进程不成功
	{
		perror("fork");	//将上一个函数发生错误的原因输出到标准设备
		exit(EXIT_FAILURE);
	}
	else if (child==0)	//子进程
	{
		puts("in child");
		printf("\tchild pid = %d\n",getpid());		//当前进程ID
		printf("\tchild ppid = %d\n",getppid());	//父进程ID
		exit(EXIT_SUCCESS);
	}
	else	//父进程
	{
		puts("in parent");
		printf("\tparent pid = %d\n",getpid());
		printf("\tparent ppid = %d\n",getppid());
	}
	exit(EXIT_SUCCESS);
}

