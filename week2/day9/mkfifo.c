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
	//判断文件是否存在
	//存在===》0 ===》假 ===》if内容不执行
	//不存在===》-1 ===》真  ====》if内容执行
	if(access("/tmp/fifo",F_OK))
	{
		//创建管道文件
		ret = mkfifo("/tmp/fifo",0777);
		if(ret == -1)
		{
			printf("mkfifo error!\n");
		}
	}
	
	//访问管道文件
	fd = open("/tmp/fifo",O_RDWR);
	if( fd < 0)
	{
		printf("open fifo error!\n");
	}
	
	
	//关闭
	close(fd);
	
	return -1;
}