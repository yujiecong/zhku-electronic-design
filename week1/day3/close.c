#include <stdio.h>
#include <sys/types.h>//open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//close
int main()
{
	//打开文件
	int fd = open("./my.txt",O_RDONLY);
	printf("fd = %d\n",fd);
	
	//关闭文件
	int ret = close(fd);
	printf("ret = %d\n",ret);
	
	return 0;
}