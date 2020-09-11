# zhku-electronic-design
# Description
电子类大三的课程设计  

> 校企合作的粤嵌开发板，顺便吐槽一句,这个讲师跟培训班的一样..
__嗯。。有个女老师挺好看的！！好喜欢!!__

## Requirement
我用的是vscode加老师发的环境，等以后有机会想自己配置。。

## Contributor
__电子181余杰聪__
## Maintainer
__电子181余杰聪__

## Content
### 0.熟悉常用的头文件
```
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<string.h>
#include<linux/input.h>
```
### 1.学习使用文件操作写入屏幕(screen.c)
 * /dev/fb0是屏幕文件，可以写入数据操控显示
 * 一个像素是由ARGB格式组成，所以要写入32个字节，在最后write时记得×4
 * 常用头文件
```
#include<fcntl.h>//open close
#include<unistd.h>// write
```
### 2.学习操控触摸板
 * 输入设备事件类型常用宏
 ```
         /*
        EV_SYN 0x00     同步事件
        EV_KEY 0x01     按键事件
        EV_REL 0x02     相对坐标
        EV_ABS 0x03     绝对坐标
        EV_MSC 0x04     其它
        EV_LED 0x11     LED
        EV_SND 0x12     声音
        EV_REP 0x14     连击
        EV_FF  0x15     力反馈 
        EV_PWR 0x16     电源
        EV_FF_STATUS    状态
        */
 ```
