#include <stdio.h>
#include <sys/types.h>//open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//close��read��write
#include <string.h>//strlen
#include <linux/input.h>

int touch_fd;//����Ϊȫ�ֱ���

//��������ʼ��
int get_xy_open(void)
{
	touch_fd = open("/dev/input/event0",O_RDONLY);
	if(touch_fd < 0)
	{
		perror("open touch failed!");
		return -1;
	}
}


//�رմ�����
void get_xy_close(void)
{
	close(touch_fd);
}


//��ȡ����������ֵ
int get_xy(int *x,int*y)
{
	//��������ʼ��
	get_xy_open();
	
	struct input_event  ts_val;//�����ṹ��ģ��
	
	while(1)
	{
		read(touch_fd,&ts_val,sizeof(ts_val));//����Ƿ��д������ݲ���
		
		//����������
		if(ts_val.type == EV_ABS)
		{
			//X��
			if(ts_val.code ==  ABS_X)
			{
				*x = ts_val.value;
				printf("x=%d\n",*x);
			}
			
			//Y��
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
					
					//���ֽ���ѭ��
					if(ts_val.value == 0 )
						break;
				}
				
				
			}
		
	}
	get_xy_close();
	
	return 0;
}





