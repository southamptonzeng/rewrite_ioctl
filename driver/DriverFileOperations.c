#include "DriverFileOperations.h"
#include "ToolFunctions.h"

int DriverOpen(struct inode *pslINode, struct file *pslFileStruct)
{
	DEBUG_PRINT(DEVICE_NAME ": open invoked, do nothing\n");
	return 0;
}

int DriverClose(struct inode *pslINode, struct file *pslFileStruct)
{
	DEBUG_PRINT(DEVICE_NAME ": close invoked, do nothing\n");
	return 0;
}

ssize_t DriverRead(struct file *pslFileStruct, char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
	DEBUG_PRINT(DEVICE_NAME ": read invoked, do nothing\n");
	return 0;
}

ssize_t DriverWrite(struct file *pslFileStruct, const char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
	DEBUG_PRINT(DEVICE_NAME ": write invoked, do nothing\n");
	return 0;
}

long DriverIOControl(struct file *pslFileStruct, unsigned int uiCmd, unsigned long ulArg)
{
	struct msg my_msg; //初始化结构体
	int ret;

	DEBUG_PRINT(DEVICE_NAME ": ioctl invoked, do nothing\n");
	
	//操作码为1，进行加法操作
	if(1 == uiCmd)
	{
		DEBUG_PRINT(DEVICE_NAME ": uiCmd = 1\n");
		
		ret = copy_from_user(&my_msg, (struct msg __user *)ulArg, sizeof(my_msg)); //用户态内存拷贝到内核态
		DEBUG_PRINT("ret1: %d", ret);
		if (ret)
		{
			return -1;
		}

		DEBUG_PRINT(DEVICE_NAME ": %d, %d\n", my_msg.data[0], my_msg.data[1]);

		my_msg.data[0] = my_msg.data[0] + my_msg.data[1];

		DEBUG_PRINT(DEVICE_NAME ": %d, %d\n", my_msg.data[0], my_msg.data[1]);

		ret = copy_to_user((struct msg __user *)ulArg, &my_msg, sizeof(my_msg)); //内核态内存拷贝到用户态
		DEBUG_PRINT("ret1: %d", ret);

		if (ret)
		{
			return -1;
		}
	}

	return 0;
}

int DriverMMap(struct file *pslFileStruct, struct vm_area_struct *pslVirtualMemoryArea)
{
	DEBUG_PRINT(DEVICE_NAME ": mmap invoked, do nothing\n");
	return 0;
}