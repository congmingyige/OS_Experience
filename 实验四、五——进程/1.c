
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	printf("Current Process ID = %d\n",getpid());
	printf("Parent Process ID = %d\n",getppid());
	printf("Valid Group ID = %d\n",getegid());
	printf("Valid User ID = %d\n",geteuid());
	printf("Real Group ID = %d\n",getgid());
	printf("Real User ID = %d\n",getuid());
	return 0;
}
