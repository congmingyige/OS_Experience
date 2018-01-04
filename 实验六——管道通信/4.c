
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void main(int argc,char * argv[])
{
	int filedes1[2],filedes2[2];
	pid_t pid;
	if (argc!=4)
	{
		printf("wrong input!\n");
		exit(0);
	}
	while (pipe(filedes1)<0) ;
	while (pipe(filedes2)<0) ;
	while ((pid=fork())==-1) ;
	//printf("creating successfully...\n");
	//父进程
	if (pid>0)
	{
		close(filedes1[0]);	//父进程关闭管道1的读出端
		close(filedes2[1]);	//父进程关闭管道1的写入端
		/*
		printf("1 : %s\n",argv[1]);
		printf("2 : %s\n",argv[2]);
		printf("3 : %s\n",argv[3]);
		*/
		char xx[10],yy[10],sym[10],result[20];
		strcpy(xx,argv[1]);
		strcpy(yy,argv[2]);
		strcpy(sym,argv[3]);
	
		write(filedes1[1],xx,sizeof(xx));
		write(filedes1[1],yy,sizeof(yy));
		write(filedes1[1],sym,sizeof(sym));
		close(filedes1[1]);	//父进程关闭管道1的写入端

		read(filedes2[0],result,20);	//设置的写入字节数必须足够大
		printf("result = %s\n",result);	//字符串转整形
		close(filedes2[0]);	//父进程关闭管道2的读出端

//若把argv[1],argv[2],argv[3]直接写入，argv[1]写入成功，而argv[2],argv[3]写入不成功
	}
	//子进程
	else
	{
		close(filedes1[1]);	//子进程关闭管道1的写入端
		close(filedes2[0]);	//子进程关闭管道2的读出端
		int x,y,z=0;
		char xx[10],yy[10],sym[10],result[20];

		read(filedes1[0],xx,10);
		read(filedes1[0],yy,10);
		read(filedes1[0],sym,10);
		close(filedes1[0]);	//子进程关闭管道1的读出端
		/*
		printf("xx = %s\n",xx);
		printf("yy = %s\n",yy);
		printf("sym = %s\n",sym);
		*/
		x=atoi(xx);
		y=atoi(yy);
		//整形转字符串:sprintf “%d"指的是10进制
		//linux平台下不能使用“itoa(z,result,10);”

		if (strcmp(sym,"+")==0)
		{
			z=x+y;
			sprintf(result,"%d",z);	
		}
		else if (strcmp(sym,"-")==0)
		{
			z=x-y;
			sprintf(result,"%d",z);
		}
		else if (strcmp(sym,"x")==0)	//不能使用"*",因为无法识别
		{
			z=x*y;
			sprintf(result,"%d",z);
		}
		else if (strcmp(sym,"/")==0)
		{
			if (y==0)
				sprintf(result,"divided by zero");
			else
			{
				z=x/y;	//这里是整除，etc. 7/3=2
				sprintf(result,"%d",z);
			}
		}
		else
		{
			sprintf(result,"no this symbol");
		}
		//printf("z=%d\n",z);
		
		write(filedes2[1],result,sizeof(result));
		close(filedes2[1]);	//子进程关闭管道2的写入端

	}
}
