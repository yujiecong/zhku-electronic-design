#include <stdio.h>

int mult_func(int m,int n);

//һ��.c�ļ�ֻ����һ��main����
//�������϶�������

int main()
{
	//�ӷ�
	printf("please input 2 number:\n");
	int a , b;
	scanf("%d %d",&a,&b);
	printf("result = %d\n",a+b);
	
	//�˷�
	printf("multiplication = %d\n",mult_func(a,b));	
	return 0;
}


//�Զ���˷�����
int mult_func(int m,int n)
{
	return m*n;
}