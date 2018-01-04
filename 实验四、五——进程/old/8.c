
#include <stdio.h>
#include <stdlib.h>

void exit_print()
{
	
	
}

void process_build()
{
	printf("please input new command\n");
}

void process_show()
{
	pstree -p
	ls -al / >>myfile.txt

	system("gnome-terminal -e pstree -p xxxx")
	system("ls -l > xxx.txt")	//如果有内容则覆盖掉以前有的内容
	当创建子进程时把id放到容器里，当子进程结束时
}

int mode=0;

int main()
{
	pid_t parent_process=getpid();
	while (1)
	{
		printf("please input new command");
		scanf("%c",&c);
		
(c=getchar())!='n'
		while ((pid=fork())!=-1) ;
		mode=1;
		if (pid==0)
		{
			while 
			//sleep(1);

			signal(1,mode);

		//			不等待新进程结束
			exit(0);
		}
	}
	return 0;
}