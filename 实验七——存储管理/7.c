
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
//sudo apt-get install libncurses5-dev
//gcc -Wall 7.c -l curses -o 7 (-l : link)

/*another way :
1.选择两个行首位(末尾)作为起始和终止来维护
2.记录所有的'\n','\0'位置
	要初始化所有的'\n','\0'位置，如果文章比较长，则消耗时间
	处理方面，后续处理效率
后续扩展：带参数的自定义命令 chmod +x /path/to/xxx.c
*/
/*
*point_begin
...
(*point_l)xxx
	 xxx\n(*point_r)
...
\0
*/

const int showline=10;
char *point_l,*point_r,*point_begin;
int totallen;
struct node
{
	int value;
	struct node *pre;
	struct node *next;
}*pointer;
#include <locale.h>

//显示
void show()
{
//	move(0,0);	//移动光标到某个位置
	erase();	//清屏 不是clear()
//	printw("end=%d , r=%d\n",point_begin+totallen-1,point_r);
	refresh();

	char *p=point_l;
	if (p==point_begin)
		printw("--Begin of file--\n");
	while (p<point_r)	//[point_l,point_r]
	{
		printw("%c",*p);
		p++;
	}
	if (*(point_r+1)=='\0')
		printw("\n--End of file--\n");
	refresh();
}

//下移line行
void down(int line)
{
	while (line>0)
	{
		//行末位下移一行
		if (*(point_r+1)=='\0')
			break;
		point_r++;
		while (*point_r!='\n')
			point_r++;
		//行首位下移一行
		while (*point_l!='\n')
			point_l++;
		point_l++;
		line--;
	}
	show();
}

//上移n行
void up(int line)
{
	while (line>0)
	{
		//行首位上移一行
		if (point_l==point_begin)
			break;
		point_l--;
		if (point_l!=point_begin && *(point_l-1)!='\n')
		{
			point_l--;
			while (*point_l!='\n' && point_l!=point_begin)
				point_l--;
			if (point_l!=point_begin)
				point_l++;
		}
		//行末位上移一行
		//行末位必在行首位的后面，所以不要进行判断
		point_r--;
		while (*point_r!='\n')
			point_r--;
		line--;
	}
	show();
}

//到达末尾
void toEnd()
{
	point_r=point_begin+totallen-1;	//文件起始位置+文件大小=文件末尾('\0')
	point_l=point_r;
	int line=showline;
	while (line>0)
	{
		//行首位上移一行
		if (point_l==point_begin)
			break;
		point_l--;
		if (point_l!=point_begin && *(point_l-1)!='\n')
		{
			point_l--;
			while (*point_l!='\n' && point_l!=point_begin)
				point_l--;
			if (point_l!=point_begin)
				point_l++;
		}
		line--;
	}
	show();
}

//到达起始
void toHome()
{
	point_l=point_begin;
	point_r=point_l;
	//point_r到本行末位
	while (*point_r!='\n')
		point_r++;
	int line=showline-1;
	while (line>0)
	{
		//行末位下移一行
		if (*(point_r+1)=='\0')
			break;
		point_r++;
		while (*point_r!='\n')
			point_r++;
		line--;
	}
	show();
}

void pointer_add(int value)
{
	struct node *po=(struct node*) malloc (sizeof(struct node));
	po->next=NULL;
	po->pre=pointer;
	po->value=value;
	pointer->next=po;
	pointer=po;
}

void pointer_init()
{
	pointer=(struct node*) malloc (sizeof(struct node));
	pointer->pre=NULL;
	pointer->next=NULL;
	pointer->value=0;
}

int main(int argc,char *argv[])
{
	int fd;
	void *start;
	struct stat sb;
	int value;
	if (argc!=2)
	{
		printf("wrong input\n");
		return 2;
	}
	fd=open(argv[1],O_RDONLY);
	setlocale(LC_ALL,"");	//还是无法显示中文，且读取中文文章有时会出现翻页失败
	fstat(fd,&sb);
	start=mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fd,0);
	if (start==MAP_FAILED)
	{
		if (access(argv[1],0)==0)
			printf("this file is empty\n");
		else
			printf("No this file\n");
		return 1;
	}
	point_l=(char *)start;
	point_begin=point_l;
	totallen=sb.st_size;	//文件的大小
	initscr();		//初始化屏幕
	//ncurses();		//终止输入在屏幕显示
	refresh();		//刷新物理屏幕
	toHome();
	pointer_init();
	while (1)
	{
/*
		//测试字符的ascii码
		while (1)
		{
			printw("c=%d\n",(int)getchar());
			refresh();
		}
*/
		switch(getchar())	//linux下用getch()反而会显式显示
		{
			case 27:
				switch(getchar())
				{
					case 91:
						switch(getchar())
						{
						
							case 65:	//up
								//printw("up\n");
								//refresh();
								pointer_add(-showline);
								up(showline);
								break;
							case 66:	//down
								//printw("down\n");
								//refresh();
								pointer_add(showline);
								down(showline);
								break;
							case 68:	//left turn back
								//printw("left\n");
								//refresh();
								if (pointer->value==0)
									break;
								value=-pointer->value;
								switch(value)
								{
									case -1000:
										toHome();
										break;
									case 1000:
										toEnd();
										break;
									default:
										if (value<0)
											up(-value);
										else
											down(value);
										break;
								}
								pointer=pointer->pre;
								break;
							case 67:	//right turn forward
								//printw("right\n");
								//refresh();
								if (pointer->next==NULL)
									break;
								pointer=pointer->next;
								value=pointer->value;
								switch(value)
								{
									case -1000:
										toHome();
										break;
									case 1000:
										toEnd();
										break;
									default:
										if (value<0)
											up(-value);
										else
											down(value);
										break;
								}
								break;
							case 53:	//PgUp
								getchar();
								//printw("PgUp\n");
								//refresh();
								pointer_add(-showline);
								up(showline);
								break;
							case 54:	//PgDn
								getchar();
								//printw("PgDn\n");
								//refresh();
								pointer_add(showline);
								down(showline);
								break;
						}
						break;
					case 79:	//Home
						switch(getchar())
						{
							case 72:
								//printw("Home\n");
								//refresh();
								pointer_add(-1000);
								toHome();
								break;
							case 70:
								//printw("End\n");
								//refresh();
								pointer_add(1000);
								toEnd();
								break;
						}
						break;
				}
				break;
			case 113:	//'q'
				//printw("exit\n");
				//refresh();
				endwin();	//重置屏幕，方便下次使用
				munmap(start,sb.st_size);
				return 0;
				break;
			case 117:	//'u'
				//printw("PgUp half\n");
				//refresh();
				pointer_add(-showline/2);
				up(showline/2);
				break;
			case 100:	//'d'
				//printw("PgDn half\n");
				//refresh();
				pointer_add(showline/2);
				down(showline/2);
				break;
			case 127:	//Backspace
				//printw("one line backward\n");
				//refresh();
				pointer_add(-1);
				up(1);				
				break;
			case 32:	//Space
				//printw("one line forward\n");
				//refresh();
				pointer_add(1);
				down(1);
				break;
		}
	}
	endwin();	//重置屏幕，方便下次使用
	munmap(start,sb.st_size);
	return 0;
}

/*
//介绍：https://www.cnblogs.com/dandingyy/archive/2012/08/23/2651644.html
　curses工作在屏幕，窗口和子窗口之上。屏幕是设备全部可用显示面积（对终端是该窗口内所有可用字符位置），窗口与具体例程有关。如基本的stdscr窗口等。

　　curses使用两个数据结构映射终端屏幕，stdscr和curscr。stdscr是“标准屏幕”（逻辑屏幕），在curses函数库产生输出时就刷新，是默认输出窗口（用户不会看到该内容）。curscr是“当前屏幕”（物理屏幕），在调用refresh函数是，函数库会将curscr刷新为stdscr的样子。

　　使用initscr();和endwin();两个函数对函数库进行初始化和重置。
*/

