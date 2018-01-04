
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int status,i;
	if (fork()==0)
	{
		printf("This is the child process . pid = %d\n",getpid());
		exit(5);
	}
	else
	{
		sleep(1);	//因为sleep 1s,所以上面的代码先运行完
		printf("This is the parent process , wait for child...\n");
		pid=wait(&status);	//wait()会暂时停止目前进程的执行，直到有信号来到或子进程结束，这里返回子进程的pid
		i=WEXITSTATUS(status);	//取得子进程exit()返回的结束代码
		printf("child's pid = %d. exit status = %d\n",pid,i);
	}
	return 0;
}
/*
This is the child process . pid =5624
This is the parent process ,wait for child...
child's pid = 5624. exit status = 5
*/

