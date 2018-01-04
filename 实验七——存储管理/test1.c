#include <stdio.h>
#include <curses.h>
//#include <conio.h>

int main()
{
	char c;
	initscr();
	
	//linux中功能与此类似
	while (1)//不会显示
	{
		c=getchar(); //用getch反而不对
		if (c=='a')
		{
			printw("that's right\n");
			refresh();	//有延迟时间
			sleep(1);
			break;
		}
		else
		{
			printw("not right\n");
			refresh();
		}
	}
	
	endwin();
/*
   //initscr();
   //printw("12345");
   //refresh();	//“如果编辑窗口偶然被用户窗口重写了”就是指在原来的窗口的位置上重叠了其他窗口，将那个窗口（部分）覆盖了。
//“恢复编辑窗口的内容”即重新绘画被覆盖的部分使其显示出来。
	printf("123\n");
	char s[10];
	gets(s);
   char ch=_getch();
   //endwin();
   printf("12345\n");
   printf("c=%c\n",ch);
   printf("56789\n");
   getchar();
*/
   return 0;
}


