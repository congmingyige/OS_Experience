#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc,char *argv[])
{
	setpriority(PRIO_PROCESS,getpid(),atoi(argv[1]));
	while (1)
	{
		int i=0;
	}
	exit(0);
}
