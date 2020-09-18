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
	if(fd < 0)
	{
		printf("open file failed\n");
		return -1;//一般情况用负数表示失败错误问题。
	}
	
	//读文件
	char buf[1024]={0};//初始化数组为0
	//int number = read(fd,buf,1024);
	int number = read(fd,buf,sizeof(buf));//数组名表示首元素的地址char *
	if(number < 0)
	{
		printf("read file failed\n");
		return -1;
	}
	printf("成功读取%d个字符\n",number);
	
	//写文件
	char wbuf[]="nihao!";
	number = write(fd,wbuf,strlen(wbuf));
	if(number < 0)
	{
		printf("write file failed\n");
		return -1;
	}
	printf("成功写入%d个字符\n",number);
	
	//关闭文件
	close(fd);
	
	return 0;
}