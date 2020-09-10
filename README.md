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
#include<fcntl.h>
#include<string.h>
#include<linux/input.h>
```
### 1.学习使用文件操作写入屏幕(screen.c)
 * /dev/fb0是屏幕文件，可以写入数据操控显示
 * 一个像素是由ARGB格式组成，所以要写入32个字节，在最后write时记得×4
### 2.学习操控触摸板
 * 待定
