#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <unistd.h>
#include<string.h>
#include <sys/mman.h>
#define HEIGHT 480
#define WIDTH 800
char* Int2String(int num,char *str)//10进制 
{
    int i = 0;//指示填充str 
    if(num<0)//如果num为负数，将num变正 
    {
        num = -num;
        str[i++] = '-';
    } 
    //转换 
    do
    {
        str[i++] = num%10+48;//取num最低位 字符0~9的ASCII码是48~57；简单来说数字0+48=48，ASCII码对应字符'0' 
        num /= 10;//去掉最低位    
    }while(num);//num不为0继续循环
    
    str[i] = '\0';
    
    //确定开始调整的位置 
    int j = 0;
    if(str[0]=='-')//如果有负号，负号不用调整 
    {
        j = 1;//从第二位开始调整 
        ++i;//由于有负号，所以交换的对称轴也要后移1位 
    }
    //对称交换 
    for(;j<i/2;j++)
    {
        //对称交换两端的值 其实就是省下中间变量交换a+b的值：a=a+b;b=a-b;a=a-b; 
        str[j] = str[j] + str[i-1-j];
        str[i-1-j] = str[j] - str[i-1-j];
        str[j] = str[j] - str[i-1-j];
    } 
    
    return str;//返回转换后的值 
}
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
    char a[1],b[1];
    int screen=open("/dev/fb0",O_RDWR);
    int *screenMap=mmap(NULL,HEIGHT*WIDTH*4,PROT_READ | PROT_WRITE,MAP_SHARED,screen,0);
    while (1){
        for(index=0;index<8;index++){
            for(j=0;j<10;j++)
            {
                if(index==7 && j==6){
                    break;
                }
                path[6]=*Int2String(index,a);
                path[7]=*Int2String(j,b);
                //printf("path=%s\n",path);
                show(path,screen,screenMap);
                //赋值
                delay(1);
                
            }

        }
    }
    close(screen);
    
    munmap(screenMap,HEIGHT*WIDTH*4);

    

        
}
