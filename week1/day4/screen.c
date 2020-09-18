#include <stdio.h>
#include <sys/types.h>//open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//close��read��write
int main()
{
	//��LCD�����豸
	int fd = open("/dev/fb0",O_RDWR);
	if(fd < 0)
	{
		perror("open lcd failed");
		return -1;
	}
	
	//д����
	int buf[800*480]={0};
	int i=0;
	for(i=0;i<800*480;i++)
	{
		buf[i]=0xff0000;//��ֵ��ɫ	
	}
	
	write(fd,buf,sizeof(buf));
	
	
	//�ر�LCD�����豸
	close(fd);
	
	return 0;
}