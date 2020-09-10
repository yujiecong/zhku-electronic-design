/*  把LCD屏幕理解成一个文件   一个硬件安装到操作系统会生成一个驱动设备文件
	1.我们打开LCD屏幕
	2.根据资料这个屏幕容纳800*480个像素点 我们把像素点写入到lcd文件中
	3.关闭文件
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//用了一个简单的延时函数，构建了一个不断变大变小的圆
void delay(int num)
{
  int i,j;
  for(i=0;i<num;i++)
    for(j=0;j<0x800;j++);
}
main ()
{
	int r=240,_=1,status=2;
	for (;;){
	
		if(_%240==0)
			status++;
		if (status%2==0)
			r--;
		else
			r++;
		_++;
		int lcd_fd; 
    // 1.我们打开LCD屏幕
		lcd_fd = open("/dev/fb0",O_RDWR);
		if(lcd_fd == -1)
		{
			printf("open lcd failed\n");
		}
		#ARGB格式
		// 2.LCD屏幕的分辨率800*480 所以他能容纳800*480个像素点
		int lcd_color[800*480]; //800*480*4 
		
		
		// FOR把所有的元素数据都赋值为 绿色 0x0000FF00
		int i,j,pos;
		int x=400,y=240;
		int color=rand();
		
		
			for(i = 0; i < 800; i++)
			{
				for (j=0;j<480;j++)
				{
					pos=i+j*800;
					if ( (i-x)*(i-x)+(j-y)*(j-y)<=r*r)
						{
						lcd_color[pos] = color; 
						}
				}
			
			}
			
			write(lcd_fd, lcd_color, 800*480*4);	
			// 3.把准备好的像素点写入到LCD文件中
			int ret = write(lcd_fd, lcd_color, 800*480*4);
			if(ret == -1)
			{
				printf("write failed\n");
			}
			memset(lcd_color, 0x00, 800*480*4);


			// 关闭文件
			close(lcd_fd);
			delay(10);
		

	}
	
}
