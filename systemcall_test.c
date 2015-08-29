#include <stdio.h>
#include <sys/syscall.h>
#include <linux/unistd.h>

#define __NR_os_syscall_32 349	//For 32 bit systems
#define __NR_os_syscall_64 312	//For 64 bit systems

int main(int argc, char *argv())
{
	long int a = syscall(__NR_os_syscall_64, 2013);	//syscall calls the function os_syscall() and passes 2013 as it's argument
	printf("OS System call returned: %ld\n", a);	//System call will return 1 as os_syscall returns 1
	return 0;					//dmesg on Terminal will display Assignment Group Members 
}

