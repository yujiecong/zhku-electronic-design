#include <stdio.h>
#include <sys/types.h>//open
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd = open("./my.txt",O_RDONLY);
	printf("fd=%d\n",fd);
	return 0;
}