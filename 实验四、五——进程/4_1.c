
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int status;
	if (!(pid=fork()))
	{
		printf("Hi I am child process!\n");
		sleep(10);//子进程会sleep 10s,一段时间内都不会结束，以便下面程序的执行
		return 0;
	}
	else
	{
		printf("send signal to child process (%d) \n",pid);
		sleep(1);
		kill(pid,SIGABRT);	//中止子进程
		wait(&status);	//wait()会暂时停止目前进程的执行，直到有信号来到或子进程结束
		if (WIFSIGNALED(status))	//如果子进程是因为信号而结束则此宏值为真
			printf("child process receive signal %d\n",WTERMSIG(status));	//取得子进程因进程而中止的信号代码
	}
	return 0;
}
/*
send signal to child process (5710) 
Hi I am child process!
child process receive signal 6
*/
