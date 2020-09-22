//只供参考，代码无法编译运行，可能存在语法问题，需自行修改bug

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



int main()
{	
	//刷播放器界面图
	show_bmp("video.bmp",0,0);

	//创建管道
	mkfifo("/tmp/fifo", 0777);
	
	//播放音乐
	system("mplayer -slave -quiet -input  file=/tmp/fifo -geometry 40:40 -zoom -x 600 -y 360 Faded3.avi &");
	
	int i=0;
	int x=0, y=0;
	char *video_name[] = {"Faded3.avi", "xxxx.avi","xixixi.avi"};
	char cmd[256]={0};
	
	
	
	//以可读写方式打开管道
	int fifo_fd = open("/tmp/fifo", O_RDWR);
	if(fifo_fd == -1)
	{
		perror("open fifo fail");
		return -1;
	}
	
	while(1)
	{
		//获取触屏坐标
		get_xy(&x, &y);
		
		if(x>380 && y>385 && x<460 && y<470)
		{
			write(fifo_fd, "pause\n", strlen("pause\n")); 	//暂停/播放
			sleep(1);	//延时1秒播放和暂停
		}
		
		//下一个视频
		if(x>685 && y>385 && x<780 && y<470)
		{
			sprintf(cmd, "mplayer -slave -quiet -input  file=/tmp/fifo -geometry 40:40 -zoom -x 600 -y 360 %s &", video_name[i]);
			system("killall -9 mplayer &");	//结束已经打开的视频
			system(cmd);	//播放下一首
					
		}				
	}
	
	return 0;
}