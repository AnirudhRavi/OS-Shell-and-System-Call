**Program**: These programs involve 2 parts: (i) Developing a Shell and (ii) Adding a System Call to the Linux Kernel

**Author**: Anirudh Ravi

**About**:

*Developing a Shell*:

The shell or command line interpreter is the fundamental User interface to an Operating System. Wrote a simple shell in C named as osshell that has the following properties. It supports the following internal commands:
	- cd DirectoryName - Change the current working directory to DirectoryName. If the DirectoryName argument is not present, reports the current directory. If the directory does not exist an appropriate error message is reported
	- mkdir DirectoryName - Create a directory in the current working directory
	- quit - Quit the shell

All other command line input is interpreted as program invocation, which should be done by shell forking and
executing the programs as its own child process.

*Adding a System Call to the Linux Kernel*:

A system call is the standard way an OS service is exported to a user program. For example, a system call may be used to give users access to internal information of a file system such as superblock or inodes. The procedure to create a system call varies in different versions of Linux. When you add a system call you will have to recompile the Linux kernel, so you must have the Linux source tree installed on your system.

1. Creating the System Call Source: Created a simple hellow world system call called os_syscall.c with the following code:

```
#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage long sys_os_syscall(int i)
{
	printk("\nAssignment 1 Problem 2! The number was %d.\nTeam Members are:\n\nName\t\tID\nAnirudh Ravi\t2011C6PS575H\nShreerang Pande\t2011A7PS164H\nSrikar Varanasi\t2011A7PS223H\n\n", i);
	return 1;
}
```
2. Implementing system call kernel source 3.5.0 resulted in a faulty return value (System call was not implemented correctly. Returned -1)

3. Implemented kernel source 3.2.17 after this. System call successfully returned 1 and 'dmesg' confirmed that the correct message was printed to the kernel space

4. For adding system call to 64-bit system on kernel 3.2.17 used the following source: http://arvindsraj.wordpress.com/2012/10/05/adding-hello-world-system-call-to-linux/

5. Compiled the kernel using this approach: http://www.howtoforge.com/kernel_compilation_ubuntu

6. Patch file (.diff - for files modified in linux kernel code) was created using the command from the following source: http://kailaspatil.blogspot.in/2010/08/how-to-create-patch-on-liunx.html
