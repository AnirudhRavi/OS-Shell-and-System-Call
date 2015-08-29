#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage long sys_os_syscall(int i)
{
	printk("\nAssignment 1 Problem 2! The number was %d.\nTeam Members are:\n\nName\t\tID\nAnirudh Ravi\t2011C6PS575H\nShreerang Pande\t2011A7PS164H\nSrikar Varanasi\t2011A7PS223H\n\n", i);
	return 1;
}

