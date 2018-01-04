#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#define ENTER 13
int main(void)
{
    char *passwd="12345678";
    char pass[9];
    int i=0;
    initscr();        //初始化
    printw("Please Enter passwd:");        //输出提示
    refresh();        //刷新一下屏幕,不然无法在屏幕上输出文字
    while(i!=8&&(pass[i]=getchar())!=ENTER)
    {
        //printw("%d",pass[i]);
        printw("*");        //输入字符输出星号,这里也可以什么都不做,这样输入无回显
        refresh();
        ++i;
    }
    pass[i]='\0';
    if(strcmp(passwd,pass)==0)
        printw("\nRight!\n");
    else
        printw("\nWorng!\n");
    printw("Enter anykey to exit. . .");
    refresh();
    getchar();
    endwin();        //释放
    return 0;
}

