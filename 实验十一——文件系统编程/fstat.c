#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc,char* argv[])
{
	struct stat buf;
	int fd;
	///etc/passwd
	printf("%s\n",argv[1]);
	fd=open(argv[1],O_RDONLY);
	fstat(fd,&buf);
	printf("st_dev: %d\n",buf.st_dev);
	printf("st_ino: %d\n",buf.st_ino);
	printf("st_mode: %d\n",buf.st_mode);
	printf("st_nlink: %d\n",buf.st_nlink);
	printf("st_uid: %d\n",buf.st_uid);
	printf("st_gid: %d\n",buf.st_gid);
	printf("st_rdev: %d\n",buf.st_rdev);
	printf("st_blksize: %d\n",buf.st_blksize);
	printf("st_blocks: %d\n",buf.st_blocks);
	printf("st_atime: %d\n",buf.st_atime);
	printf("st_mtime: %d\n",buf.st_mtime);
	printf("st_ctime: %d\n",buf.st_ctime);

	return 0;
}
