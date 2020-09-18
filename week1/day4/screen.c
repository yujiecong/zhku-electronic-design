#include <stdio.h>
#include <sys/types.h>//open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//close、read、write
int main()
{
	//打开LCD驱动设备
	int fd = open("/dev/fb0",O_RDWR);
	if(fd < 0)
	{
		perror("open lcd failed");
		return -1;
	}
	
	//写操作
	int buf[800*480]={0};
	int i=0;
	for(i=0;i<800*480;i++)
	{
		buf[i]=0xff0000;//赋值红色	
	}
	
	write(fd,buf,sizeof(buf));
	
	
	//关闭LCD驱动设备
	close(fd);
	
	return 0;
}