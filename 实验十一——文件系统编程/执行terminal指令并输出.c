#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
	FILE *fstream=NULL;
	char buff[1024];
	memset(buff,0,sizeof(buff));
	if (NULL==(fstream=popen("ls","r")))
	{
		fprintf(stderr,"wrong");
		return -1;
	}
	while (NULL!=fgets(buff,sizeof(buff),fstream))
		printf("%s\n",buff);
	pclose(fstream);
	return 0;
}

