#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int ret,fd;

int main()
{
	//�ж��ļ��Ƿ����
	//����===��0 ===���� ===��if���ݲ�ִ��
	//������===��-1 ===����  ====��if����ִ��
	if(access("/tmp/fifo",F_OK))
	{
		//�����ܵ��ļ�
		ret = mkfifo("/tmp/fifo",0777);
		if(ret == -1)
		{
			printf("mkfifo error!\n");
		}
	}
	
	//���ʹܵ��ļ�
	fd = open("/tmp/fifo",O_RDWR);
	if( fd < 0)
	{
		printf("open fifo error!\n");
	}
	
	
	//�ر�
	close(fd);
	
	return -1;
}