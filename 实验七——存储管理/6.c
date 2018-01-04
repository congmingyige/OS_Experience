
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

int main()
{
	int fd;
	void *start;
	struct stat sb;
	//用户的关键信息被存放在系统的/etc/passwd文件中
	//fd=open("etc/passwd",O_RDONLY);
	fd=open("3",O_RDONLY);	//打开文件
	fstat(fd,&sb);				//传入的参数为已打开的文件描述词
	//通过文件描述词获得文件状态:st_size
	start=mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fd,0);
//	void *mmap(void *start,size_t length,int prot,int flags,int fd,off_t offsize)
//	prot代表映射区域的保护方式 MAP_PRIVATE 对此区域作的任何修改都不会写回原来的文件内容
//	参数offset为文件映射的偏移量，通常设置为0，代表从文件最前方开始对应，offset必须是分页大小的整数倍
	if (start==MAP_FAILED)			//判断是否映射成功
		return 1;
	//start指向/etc路径下的passwd文件的起始地址，文件末尾有'\0',使输出终止，这里输出的是文件的所有内容
//	printf("%s\n",(char *)start);

	char * p=(char *)start;
	printf("--begin--\n");
	while (*p!='\0')
	{
		printf("%d ",(int)(*p));
		p++;
	}
	printf("--end--\n");
	munmap(start,sb.st_size);		//解除映射
//	int munmap(void *start,size_t length)
	return 0;
}

