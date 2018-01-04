
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <dirent.h>
#include <sys/types.h>

#include <string.h>
#include <stdio.h>

//source destination的存储空间是连在一起的,所以不能对source数组增添内容，否则会影响destination数组
void dfs(char source[],char destination[])
{
	DIR *dir;
	struct dirent *ptr;
	struct stat buf;
	int fd;
	char sourceNew[100];
	char destinationNew[100];
	int lens=strlen(source);
	int lend=strlen(destination);
	int len;
	char buffer[1024];
	int fd1;

	char auth[5];
	int u=0,g=0,o=0;

	fd=open(source,O_RDONLY);
	fstat(fd,&buf);

	if (buf.st_mode & S_IRUSR)
		u+=4;
	if (buf.st_mode & S_IWUSR)
		u+=2;
	if (buf.st_mode & S_IXUSR)
		u+=1;
	if (buf.st_mode & S_IRGRP)
		g+=4;
	if (buf.st_mode & S_IWGRP)
		g+=2;
	if (buf.st_mode & S_IXGRP)
		g+=1;
	if (buf.st_mode & S_IROTH)
		o+=4;
	if (buf.st_mode & S_IWOTH)
		o+=2;
	if (buf.st_mode & S_IXOTH)
		o+=1;
	printf("%d %d %d\n",u,g,o);
	auth[0]='0';
	auth[1]=u+48;
	auth[2]=g+48;
	auth[3]=o+48;
	auth[4]='\0';

	mkdir(destination,auth);
	chown(destinationNew,buf.st_uid,buf.st_gid);
	chmod(destination,(buf.st_mode & S_ISGID) | (buf.st_mode & S_ISUID) | (buf.st_mode & S_ISVTX));
	printf("folder : copy from ' %s ' to ' %s ' \n",source,destination);
	if (S_ISLNK(buf.st_mode))	//不能buf.st_mode & S_ISLNK
	{
		printf("folder: ' %s ' symbolic link ,pass \n",source);
		return ;
	}
	close(fd);

	dir=opendir(source);
	while ((ptr=readdir(dir))!=NULL)
	{
		//printf("d_name:%s\n",ptr->d_name);
		if (strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)
			continue;

		strcpy(sourceNew,source);
		strcat(sourceNew,"/");
		sourceNew[lens+1]='\0';
		strcat(sourceNew,ptr->d_name);
		sourceNew[lens+1+strlen(ptr->d_name)]='\0';

		strcpy(destinationNew,destination);
		strcat(destinationNew,"/");
		destinationNew[lend+1]='\0';
		strcat(destinationNew,ptr->d_name);
		destinationNew[lend+1+strlen(ptr->d_name)]='\0';

		fd=open(sourceNew,O_RDONLY);
		fstat(fd,&buf);

		
		//buf.st_mode & xxx
//		printf("%d\n",buf.st_mode);
//		buf.st_uid
//		buf.st_gid

		//if (buf.st_size & S_IFLNK)
			//show but not copy, can then continue

		//chown		

//		if (buf.st_size & S_IRUSR)
			//
		//chmod

		//目录
		if (S_ISDIR(buf.st_mode))
			dfs(sourceNew,destinationNew);
			//information of folder
		//文件
		else
		{
			if (S_ISLNK(buf.st_mode))
			{
				printf("file: ' %s ' symbolic link ,pass \n",sourceNew);
				continue;
			}

			if (buf.st_mode & S_IRUSR)
				u+=4;
			if (buf.st_mode & S_IWUSR)
				u+=2;
			if (buf.st_mode & S_IXUSR)
				u+=1;
			if (buf.st_mode & S_IRGRP)
				g+=4;
			if (buf.st_mode & S_IWGRP)
				g+=2;
			if (buf.st_mode & S_IXGRP)
				g+=1;
			if (buf.st_mode & S_IROTH)
				o+=4;
			if (buf.st_mode & S_IWOTH)
				o+=2;
			if (buf.st_mode & S_IXOTH)
				o+=1;
			auth[0]='0';
			auth[1]=u+48;
			auth[2]=g+48;
			auth[3]=o+48;
			auth[4]='\0';

			//fd1=open(destinationNew,O_WRONLY);
			//chown(destinationNew,buf.st_uid,buf.st_gid);
			//chmod(destinationNew,(buf.st_mode & S_ISGID) | (buf.st_mode & S_ISUID) | (buf.st_mode & S_ISVTX));
			//fstat(fd1,&buf1);
			//buf1.st_mode = buf1.st_mode | (buf.st_mode & S_ISUID);
			//buf1.st_mode = buf1.st_mode | (buf.st_mode & S_ISGID);
			printf("\t\t%d\n",buf.st_mode & S_ISUID);

			while (len=read(fd,buffer,1024))
				write(fd1,buffer,len);
			close(fd1);
			printf("flle : copy from ' %s ' to ' %s \n",sourceNew,destinationNew);
		}
		close(fd);
	}
	closedir(dir);
}

int main(int argc,char *argv[])
{
	struct stat buf;
	int fd;
	if (argc!=3)
	{
		printf("number of input is wrong\n");
		return 0;
	}

	fd=open(argv[1],O_RDONLY);
	fstat(fd,&buf);
	if (!S_ISDIR(buf.st_mode)) {
		printf("the first input is not dirctory\n");
		return 0;
	}
	close(fd);
	
	fd=open(argv[2],O_RDONLY);
	fstat(fd,&buf);
	if (!S_ISDIR(buf.st_mode))
	{
		printf("the second input is not dirctory\n");
		return 0;
	}
	close(fd);

	printf("%s\n",argv[1]);
	printf("%s\n",argv[2]);

	//多个'/'不影响文件路径的访问
	//要求输入的都是'/xx/xxx/'才行，如果有多个'/'则需用程序除去;argv[2]的末尾不是'\'
	char *x;
	int len;
	x=strrchr(argv[1],'/');
	*x='\0';
	if (strcmp(argv[1],argv[2])==0)
	{
		printf("can't copy in the same directory, not ok!\n");
		return 0;
	}
	*x='/';

	len=strlen(argv[2]);
	strcat(argv[2],x);
	argv[2][len+strlen(x)]='\0';	
	//printf("%s\n",argv[2]);

	dfs(argv[1],argv[2]);
	return 0;
}

