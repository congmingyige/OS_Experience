
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* out=fopen("shownumber","w");
	int i;
	for (i=1;i<1000;i++)
	{
		fprintf(out,"%d ",i);
		if (i%10==0)
			fprintf(out,"\n");
	}
	fclose(out);
	return 0;
}
