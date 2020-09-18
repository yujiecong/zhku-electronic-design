//先读后写
#include <stdio.h>
#include <sys/types.h>//open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//close、read、write
#include <string.h>//strlen

int main()
{
	//打开文件
	int fd = open("./my.txt",O_RDWR);
	printf("fd = %d\n",fd);
	
	//写文件
	char wbuf[]="nihao!";
	int number = write(fd,wbuf,strlen(wbuf));
	printf("成功写入%d个字符\n",number);
	
	//读文件
	char buf[1024]={0};//初始化数组为0
	number = read(fd,buf,sizeof(buf));//数组名表示首元素的地址char *
	printf("成功读取%d个字符\n",number);
	
	
	
	//关闭文件
	int ret = close(fd);
	printf("ret = %d\n",ret);
	
	
	return 0;
}