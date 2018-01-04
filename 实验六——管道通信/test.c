
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char name[10]="abcd";
	char *t;
	t=name;
	strcpy(name,"az");
	printf("%s\n",t);
}
