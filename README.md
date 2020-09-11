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
### 0.写在前头的一些心得
```
#include<math.h>//在arm-linux-gcc时要加上-lm参数才能通过
```
### 1.学习使用文件操作写入屏幕(screen.c)
 * /dev/fb0是屏幕文件，可以写入数据操控显示
 * 一个像素是由ARGB格式组成，所以要写入32个字节，在最后write时记得WIDTH×HEIGHT×4
 * 常用头文件以及函数原型
 ```
  #include<fcntl.h>//open
  #include<unistd.h>// write lseek read close
  #include<sys/mman.h>//mmap munmap
  
  //open
  int open(const  char *pathname,int flags);
  int open(const char *pathname,int flags,mode_t mode)
  
  //write
  ssize_t write(int fd,const void *buf,size_t count);
  
  //close
  int close（int fd）;
  
  //lseek
  off_t lseek(int  fd,off_t offset,int whence);
  
  //read
  ssize_t  read(int fd,void  *buffer,size_t count);
  
  //mmap 
  void* mmap(void* start,size_t length,int prot,int flags,int fd,off_t offset);
  
  //munmap
  int munmap(void* start,size_t length);
  
 ```
 * _mmap比较复杂，下面是一些补充_
  start：映射区的开始地址，设置为0时表示由系统决定映射区的起始地址。
  length：映射区的长度。//长度单位是 以字节为单位，不足一内存页按一内存页处理
  mmap的prot(期望的内存保护标志)常用的宏
  ```
  PROT_READ //页内容可以被读取
  PROT_WRITE //页可以被写入
  ```
  mmap flags常用
  ```
  flags：指定映射对象的类型，映射选项和映射页是否可以共享。它的值可以是一个或者多个以下位的组合体
  MAP_SHARED //与其它所有映射这个对象的进程共享映射空间。对共享区的写入，相当于输出到文件。直到msync()或者munmap()被调用，文件实际上不会被更新。
  ```
 
 > _[mmap只是在虚拟内存分配了地址空间，只有在第一次访问虚拟内存的时候才分配物理内存。](https://www.jianshu.com/p/755338d11865)_
 
 > _[总而言之，常规文件操作需要从磁盘到页缓存再到用户主存的两次数据拷贝。而mmap操控文件，只需要从磁盘到用户主存的一次数据拷贝过程。说白了，mmap的关键点是实现了用户空间和内核空间的数据直接交互而省去了空间不同数据不通的繁琐过程。因此mmap效率更高](https://blog.csdn.net/qq_33611327/article/details/81738195)_
 
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
 * 常用头文件
 ```
 #include<linux/input.h>
 ```
