//高精度乘法，求的是n！
#include <stdio.h>
int main()
{
	int n,a[200],carry,temp,i,j,dight=1;
	printf("Please input n:");
	scanf("%d",&n);
	if (n<0)
	{
		printf("Wrong input\n");
		return 0;
	}
	if (n>120)
	{
		printf("the result is too large.\n");
		return 0;
	}
	a[0]=1;
	for (i=2;i<=n;i++)
	{
		for (j=1,carry=0;j<=dight;++j)
		{
			//a(乘数1)的第j位与i(乘数2)相乘
			temp=a[j-1]*i+carry;
			//a的第j位(结果)取余
			a[j-1]=temp%10;
			//a的第j+1位获得进位
			carry=temp/10;	
		}
		//若存在进位(结果最高位carry大于10),则继续执行下去，
		//每次最高位的位数1，数值除以10，直到没有进位
		while (carry)
		{
			a[++dight-1]=carry%10;
			carry/=10;				
		}	
	}
	printf("Result is:\n%d != ",n);
	for (i=dight;i>=1;--i)
		printf("%d",a[i-1]);
	printf("\n");
	return 0;
}	
