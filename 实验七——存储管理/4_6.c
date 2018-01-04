
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	struct stat buf;
	int fd;
	//用户的关键信息被存放在系统的/etc/passwd文件中
	fd=open("/etc/passwd",O_RDONLY);	//打开文件
	fstat(fd,&buf);	//传入的参数为已打开的文件描述词
	printf("/etc/passwd file size = %ld\n",buf.st_size);	//typedef long _off_t;
	return 0;
}
