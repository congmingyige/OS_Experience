
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
//gcc -o test test.c -l curses

int main()
{
	char ch;
	initscr();
	ch=getch();
//	printf("%c\n",ch);
	refresh();
	getchar();
/*
	initscr();
	move(5,15);
	printf("hello,world\n");
	refresh();
	endwin();
	exit(EXIT_SUCCESS);
*/
/*
	printf("Input a char acter:\n");
	ch=getch();
	printf("c=%c\n",ch);
	usleep(10000);
*/
	endwin();
	return 0;
}
