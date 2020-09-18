//�жϷ���	
#include <stdio.h>
#include <sys/types.h>//open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//close��read��write
#include <string.h>//strlen
#include <linux/input.h>

int main()
{
	//�򿪴�����
	int touch_fd = open("/dev/input/event0",O_RDONLY);
	if(touch_fd < 0)
	{
		perror("open touch failed!");
		return -1;
	}
	
	struct input_event  ts_val;//�����ṹ��ģ��
	
	int point_x=0,point_y=0;//�����ݴ�x,y�����ֵ
	
	//����
	int first_x,first_y;  
	
	while(1)
	{
		read(touch_fd,&ts_val,sizeof(ts_val));//����Ƿ��д������ݲ���
		
		//����������
		if(ts_val.type == EV_ABS)
		{
			//X��
			if(ts_val.code ==  ABS_X)
			{
				point_x = ts_val.value;
				//printf("x=%d\n",x);
			}
			
			//Y��
			if(ts_val.code ==  ABS_Y)
			{
				point_y = ts_val.value;
				//printf("y=%d\n",y);
			}
			
			
		}
		
		//�洢��������һ˲����Ǹ�����ֵ
		if(ts_val.type == EV_KEY && ts_val.code == BTN_TOUCH && ts_val.value == 1)
		{
			first_x = point_x;
			first_y = point_y;
			
			printf("xx=%d,yy=%d\n",first_x,first_y);
		}
		
		if(ts_val.type == EV_KEY && ts_val.code == BTN_TOUCH && ts_val.value == 0)
		{
			//�жϻ�������
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
	
	
	//�ر��ļ�
	close(touch_fd);
	
	
	return 0;
}