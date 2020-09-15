
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <unistd.h>
#include<string.h>
#include <sys/mman.h>
#define HEIGHT 480
#define WIDTH 800
void show(char path[],int screen,int *screenMap){
            //打开lcd
        
        if(screen==-1){
           perror("filded to open");
        }
        //屏幕虚拟内存
        
        
        //bmpfd信息
        int bmpfd=open(path,O_RDONLY);
        //读取bmp头部信息
        unsigned char bmpHead[54]={'0'};
        read(bmpfd,bmpHead,sizeof(bmpHead));
        //读取bmp长宽
        int bmpHeight=*((int *)&bmpHead[22]);
        int bmpWidth=*((int *)&bmpHead[18]);
        //printf("bmpHeight=%d,bmpWidth=%d \n",bmpHeight,bmpWidth);
        //屏幕像素信息
        int screenPixels[bmpHeight][bmpWidth];
        //只能读取480*800的bmp图片！
        char bmpPixels[WIDTH*HEIGHT*3];
        //读取bmp像素数据
        read(bmpfd,bmpPixels,sizeof(bmpPixels));
        unsigned char r,g,b,a,*bmpPixelsPointer=bmpPixels;
        unsigned int color=0;
        unsigned int x=0,y=0;
        for(y=0;y<HEIGHT;y++)
        {
                for(x=0;x<bmpWidth;x++){
                        b=*bmpPixelsPointer++;
                        g=*bmpPixelsPointer++;
                        r=*bmpPixelsPointer++;
                        a=0;
                        color=a<<24 |r<<16|g<<8|b;
                        screenPixels[y][x]=color;
                        *(screenMap+(HEIGHT-y-1)*800+x)=screenPixels[y][x];
                }
        };
        close(bmpfd);

}
void delay(double s){
    double i;
    for(i=0.;i<80009*s;i++);
}
void main(){
    //IMG00000.bmp
    
    char path[]="IMG00000.bmp";
    int index,j,k;
    int screen=open("/dev/fb0",O_RDWR);
    int *screenMap=mmap(NULL,HEIGHT*WIDTH*4,PROT_READ | PROT_WRITE,MAP_SHARED,screen,0);
    while (1){
        //从ASCII的48='0'开始
        for(index=48;index<56;index++){
            path[6]=(char )index;
            for(j=48;j<58;j++)
            {
                path[7]=(char )j;
                //printf("path=%s\n",path);
                show(path,screen,screenMap);
                //赋值
                delay(0.5);
                
            }

        }
    }
    close(screen);
    
    munmap(screenMap,HEIGHT*WIDTH*4);

    

        
}
