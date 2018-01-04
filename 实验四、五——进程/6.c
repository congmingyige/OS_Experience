
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>

void print() {
	printf("Finished...\n");
}

int main(int argc,char * argv[])
{		
	pid_t pid;
	int status;
	int pri=atoi(argv[1]);//-20 -10 0 10 19
	while ((pid=fork())==-1) ;
	if (pid>0)
	{
		//printf("default_pri = %d\n",getpriority(PRIO_PROCESS,pid));
		setpriority(PRIO_PROCESS,pid,pri);
		//printf("current_pri = %d\n",pri);
		pid=waitpid(pid,&status,0);
		if (WIFEXITED(status)!=0)
			//printf("infomation of subproces(%d) : %d\n",pid,WEXITSTATUS(status));
			printf("infomation of subproces : %d\n",WEXITSTATUS(status));
		else
			printf("Subprocess does not end normally\n");
		//printf("finally_pri = %d\n",pri);
	}
	else
	{
		atexit(print);

		sleep(1);
		/*execlp:从PATH 环境变量所指的目录中查找符合参数file {"find"} 的文件名，找到后便执行该文件，然后将第二个以后的参数当做该文件的argv[0]、argv[1]……{"find","/","-name","hda*"}，最后一个参数必须用空指针(NULL)作结束{(char *)0}。
		执行：在根目录下寻找文件名开头为“hda”的文件*/
		execlp("find","find","/","-name","hda*",(char *)0);
		
		printf("End\n");

		exit(5);
	}
	return 0;
}
/*
把终端输出内容放置到txt: 
./6 | tee root_pri0.txt ： 只能得到标准输出
./6 -20 >> user_pri-20.txt 2>&1 ： 可得到标准输出和标准错误
./6 -20 2> /dev/null ： 终端输出忽略标准错误
*/


             20:02 2017/11/16