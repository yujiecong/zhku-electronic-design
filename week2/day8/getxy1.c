//判断方向	
#include <stdio.h>
#include <sys/types.h>//open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//close、read、write
#include <string.h>//strlen
#include <linux/input.h>

int main()
{
	//打开触摸屏
	int touch_fd = open("/dev/input/event0",O_RDONLY);
	if(touch_fd < 0)
	{
		perror("open touch failed!");
		return -1;
	}
	
	struct input_event  ts_val;//创建结构体模型
	
	int point_x=0,point_y=0;//用来暂存x,y的随机值
	
	//定义
	int first_x,first_y;  
	
	while(1)
	{
		read(touch_fd,&ts_val,sizeof(ts_val));//监测是否有触摸数据产生
		
		//坐标轴数据
		if(ts_val.type == EV_ABS)
		{
			//X轴
			if(ts_val.code ==  ABS_X)
			{
				point_x = ts_val.value;
				//printf("x=%d\n",x);
			}
			
			//Y轴
			if(ts_val.code ==  ABS_Y)
			{
				point_y = ts_val.value;
				//printf("y=%d\n",y);
			}
			
			
		}
		
		//存储触摸屏的一瞬间的那个坐标值
		if(ts_val.type == EV_KEY && ts_val.code == BTN_TOUCH && ts_val.value == 1)
		{
			first_x = point_x;
			first_y = point_y;
			
			printf("xx=%d,yy=%d\n",first_x,first_y);
		}
		
		if(ts_val.type == EV_KEY && ts_val.code == BTN_TOUCH && ts_val.value == 0)
		{
			//判断滑动方向
			if((first_x - point_x) < -100)
			{
				printf("right\n");
			}
			
			if((first_x - point_x) > 100)
			{
				printf("left\n");
			}
			
		}
	}
	
	
	//关闭文件
	close(touch_fd);
	
	
	return 0;
}