#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <unistd.h>
#include<string.h>
#include<math.h>
#include <sys/mman.h>
#define HEIGHT 480
#define WIDTH 800
void main(){
        //打开lcd
        int screen=open("/dev/fb0",O_RDWR);
        if(screen==-1){
           perror("filded to open");
        }
        //屏幕虚拟内存
        int *screenMap=mmap(NULL,HEIGHT*WIDTH*4,PROT_READ | PROT_WRITE,MAP_SHARED,screen,0);
        
        //bmpfd信息
        int bmpfd=open("mn.bmp",O_RDONLY);
        //读取bmp头部信息
        unsigned char bmpHead[54]={'0'};
        read(bmpfd,bmpHead,sizeof(bmpHead));
        //读取bmp长宽
        int bmpHeight=*((int *)&bmpHead[22]);
        int bmpWidth=*((int *)&bmpHead[18]);
        printf("bmpHeight=%d,bmpWidth=%d \n",bmpHeight,bmpWidth);
        //屏幕像素信息
        int screenPixels[bmpHeight][bmpWidth];
        //只能读取480*800的bmp图片！
        char bmpPixels[WIDTH*HEIGHT*3];
        //读取bmp像素数据
        read(bmpfd,bmpPixels,sizeof(bmpPixels));
        unsigned char r,g,b,a,*bmpPixelsPointer=bmpPixels;
        unsigned int color=0;
        unsigned int x=0,y=0;
        for(y=0;y<bmpHeight;y++)
        {
                for(x=0;x<bmpWidth;x++){
                        b=*bmpPixelsPointer++;
                        g=*bmpPixelsPointer++;
                        r=*bmpPixelsPointer++;
                        a=0;
                        color=a<<24 |r<<16|g<<8|b;
                        screenPixels[y][x]=color;
                        *(screenMap+y*800+x)=screenPixels[y][x];
                }
        };
        close(screen);
        close(bmpfd);
        munmap(screenMap,HEIGHT*WIDTH*4);
        
}
