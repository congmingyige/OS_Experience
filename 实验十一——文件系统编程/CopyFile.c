#include <stdio.h>  
#include <dirent.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
  
char buff[1024];  
int len;  
int main(int argc, char const *argv[])  
{  
    char const *src_path = argv[1];  
    char const *des_path = argv[2];  
    int fd,fd2;  

	printf("%s\n",des_path);  

    fd = open(src_path,O_RDONLY,S_IRUSR|S_IWUSR|S_IXUSR); 
    fd2 = open(des_path,O_WRONLY | O_CREAT,S_IRUSR|S_IWUSR|S_IXUSR);  
    while((len = read(fd,buff,1024))!=0)  
    {  
        write(fd2,buff,len);  
    }  
	close(fd);
	close(fd2);
    return 0;  
}  


