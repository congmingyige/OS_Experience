
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>

int main()
{
	pid_t pid;
	int status,pri;
	while ((pid=fork())==-1) ;
	if (pid>0)
	{
		pri=getpriority(PRIO_PROCESS,pid);
		//printf("previous_pri = %d\n",pri);
		pri=-20;//-20 -10 0 10 20
		setpriority(PRIO_PROCESS,pid,pri);
		//printf("current_pri = %d\n",pri);
		pid=waitpid(pid,&status,0);
		if (WIFEXITED(status)!=0)
			//printf("infomation of subproces(%d) : %d\n",pid,WEXITSTATUS(status));
			printf("infomation of subproces : %d\n",WEXITSTATUS(status));
		else
			printf("Subprocess does not end normally\n");
	}
	else
	{
		sleep(1);	//直到父进程设置子进程优先级的语句执行完毕
		//从PATH环境变量中查找文件并执行
		execlp("find","find","/","-name","hda*",(char *)0);
		exit(5);
	}
	return 0;
}
//把终端输出内容放置到txt: ./6 | tee root_pri0.txt
//补第二题！！！
