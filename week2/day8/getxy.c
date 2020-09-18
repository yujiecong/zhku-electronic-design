#include <stdio.h>
#include <sys/types.h>//open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//close、read、write
#include <string.h>//strlen
#include <linux/input.h>

int touch_fd;//定义为全局变量

//触摸屏初始化
int get_xy_open(void)
{
	touch_fd = open("/dev/input/event0",O_RDONLY);
	if(touch_fd < 0)
	{
		perror("open touch failed!");
		return -1;
	}
}


//关闭触摸屏
void get_xy_close(void)
{
	close(touch_fd);
}


//获取触摸的坐标值
int get_xy(int *x,int*y)
{
	//触摸屏初始化
	get_xy_open();
	
	struct input_event  ts_val;//创建结构体模型
	
	while(1)
	{
		read(touch_fd,&ts_val,sizeof(ts_val));//监测是否有触摸数据产生
		
		//坐标轴数据
		if(ts_val.type == EV_ABS)
		{
			//X轴
			if(ts_val.code ==  ABS_X)
			{
				*x = ts_val.value;
				printf("x=%d\n",*x);
			}
			
			//Y轴
			if(ts_val.code ==  ABS_Y)
			{
				*y = ts_val.value;
				printf("y=%d\n",*y);
			}
			
			
		}
		
		if(ts_val.type == EV_KEY)
			{
				if(ts_val.code == BTN_TOUCH)
				{
					printf("key = %d\n",ts_val.value);
					
					//松手结束循环
					if(ts_val.value == 0 )
						break;
				}
				
				
			}
		
	}
	get_xy_close();
	
	return 0;
}





