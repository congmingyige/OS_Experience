
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
	system("ls -l > xxx.txt")	//����������򸲸ǵ���ǰ�е�����
	�������ӽ���ʱ��id�ŵ���������ӽ��̽���ʱ
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

		//			���ȴ��½��̽���
			exit(0);
		}
	}
	return 0;
}