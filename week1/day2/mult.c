#include <stdio.h>

int mult_func(int m,int n);

//一个.c文件只能有一个main函数
//代码自上而下运行

int main()
{
	//加法
	printf("please input 2 number:\n");
	int a , b;
	scanf("%d %d",&a,&b);
	printf("result = %d\n",a+b);
	
	//乘法
	printf("multiplication = %d\n",mult_func(a,b));	
	return 0;
}


//自定义乘法函数
int mult_func(int m,int n)
{
	return m*n;
}