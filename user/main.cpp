#include <iostream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <string>

typedef struct 
{
	/* data */
	int data[2]; //被加数与加数
}msg;


using namespace std;

int main()
{
	int fd = 0;
	int ret;
	msg my_msg;

	string toSend = "hello driver";

	//打开自字符型设备
	if((fd = open("/dev/msg_printer", O_RDWR)) < 0)
	{
		cerr << strerror(errno) << endl;	
		return -1;
	}

	memset(&my_msg, 0, sizeof(my_msg));

	//加法器赋值
	my_msg.data[0] = 1;
	my_msg.data[1] = -9;

	//系统调用
    ret = ioctl(fd, 1, &my_msg);

	if(ret < 0)
	{
		cerr << strerror(errno) << endl;
		close(fd);
		return -1;	
	}
	
	//返回结果
	cout << "After ioctl sum = " << my_msg.data[0] << endl;

	close(fd);

	return 0;
}
