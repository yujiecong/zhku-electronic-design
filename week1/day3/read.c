#include <stdio.h>
#include <sys/types.h>//open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//close、read

int main()
{
	//打开文件
	int fd = open("./my.txt",O_RDONLY);
	printf("fd = %d\n",fd);
	
	//读文件
	char buf[1024]={0};//初始化数组为0
	int number = read(fd,buf,sizeof(buf));//数组名表示首元素的地址char *
	printf("成功读取%d个字符\n",number);
	
	
	//关闭文件
	int ret = close(fd);
	printf("ret = %d\n",ret);
	
	
	return 0;
}