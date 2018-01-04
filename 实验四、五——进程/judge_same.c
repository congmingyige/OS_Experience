
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str1[100]="";
char str2[100]="";

FILE* fp1;
FILE* fp2;

void output()
{
	fclose(fp1);
	fclose(fp2);
	exit(0);
}

int main(int argc,char * args[])
{
	//user / root	
	strcat(str1,args[1]);
	strcat(str2,args[2]);
	
	strcat(str1,"_pri");
	strcat(str2,"_pri");

	strcat(str1,args[3]);
	strcat(str2,args[4]);

	strcat(str1,".txt");
	strcat(str2,".txt");	

	fp1=fopen(str1,"r");
	fp2=fopen(str2,"r");
	//printf("open successfully\n");
	//printf("%s\n",str1);
	//printf("%s\n",str2);

	char s1[500],s2[500],*x,*y;
	int line=0;
	while (1)
	{
		//若到达文件末尾，会保持最后一次的输入
		x=fgets(s1,500,fp1);
		y=fgets(s2,500,fp2);
		if (x==NULL && y==NULL)
			break;
		line++;
		if (x==NULL)
		{
			printf("Line : %d\n",line);
			printf("%s : no data\n",str1);
			printf("%s : %s\n",str2,s2);
			output();
		}
		if (y==NULL)
		{
			printf("Line : %d\n",line);
			printf("%s : no data\n",str2);
			printf("%s : %s\n",str1,s1);
			output();			
		}
		if (strcmp(s1,s2)!=0)
		{
			printf("not same\n");
			printf("Line : %d\n",line);
			printf("%s : %s\n",str1,s1);
			printf("%s : %s\n",str2,s2);
			output();
		}
	}
	printf("same\n");
	output();
	return 0;
}

