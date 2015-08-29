#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAXLINE 100
#define MAXARG 10
#define DELIMITER " "

//Function to print the current working directory
int currentpath() 
{
       char cwd[1024];		//cwd[] stores the current directory - absolute path
       if (getcwd(cwd, sizeof(cwd)) != NULL)
           printf("\nOS Shell Command: \n%s: ", cwd);
       else
           perror("\nOS Shell Command Error");
       return 0;
}

int main(int argc, char *argv[])
{
	char *command;		//Command (e.g. mkdir, cd or quit)
	char cwd[1024];		//Stores the Current Working irectory
	char line[MAXLINE];	//Shell command line (e.g. cd /home/anirudh_ravi/Documents)
	char *arg = NULL;	//Argument - contains the directory to be changed to or to be made (e.g. /home for cd /home command)
	printf("\nAssignment 1 Problem 1! Team Members are:\n\nName\t\tID\nAnirudh Ravi\t2011C6PS575H\nShreerang Pande\t2011A7PS164H\nSrikar Varanasi\t2011A7PS223H\n");

	while(1) 
	{
		//Prints the current working directory		
		currentpath();
		if (fgets(line, MAXLINE, stdin) != NULL) 
		{
	        	//Remove \n from end of line
	        	line[strlen(line)-1] = '\0';
		}
		//Looks for first space (" "), saves as command
    		command = strtok(line, DELIMITER);
		char *path = malloc(strlen("/bin/")+strlen(command)+1);//Appends /bin/ to beginning of the command
		strcpy(path, "/bin/");
		strcat(path, command);
		struct stat sb;
		//Check if command is valid ubuntu command (or quit, cd or mkdir)
		if((stat(path, &sb) != 0)&&(strcmp(command, "cd") != 0)&&(strcmp(command, "quit") != 0)&&(strcmp(command, "mkdir") != 0))
			printf("'%s' command is unfortunately not predefined in ubuntu. Please type another command.\n", command);		
    		//If command is cd then chdir system function is used 
    		else if (strcmp(command, "cd") == 0) 
		{
               		arg = strtok(0, DELIMITER);
			//If argument is not present then move to root directory [This differs from the assignment question] 
        		if (arg == NULL) 
			{
				chdir("/");
				printf("Directory changed to 'root'\n");
            		} 
			else 
			{
				int res = chdir(arg);
				if(res != 0)
					printf("Directory specified does not exist\n");
			} 
		} 
		//If command is mkdir then mkdir system function is used
		else if (strcmp(command, "mkdir") == 0)
		{
			arg = strtok(0, DELIMITER);
			//If argument is missing display the error
			if (arg == NULL) 
				printf("Argument missing for mkdir command\n");
			else 
			{
				int res = mkdir(arg, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
				if(res != 0)
					printf("Error occurred while executing mkdir command\n");
				else 
					printf("'%s' directory created\n", arg);
			} 
    		}
		//If command is quit then exits from shell
		else if (strcmp(command, "quit") == 0) 
		{
			printf("Thank You for using the OS Shell!\n");
			exit(0);
		}			
		//Its neither mkdir, chdir or quit. Execute the command from the /bin/ directory
		else
		{
			pid_t pid;
			char *envp[] = {NULL};
			int res, i; //Stores return value of execve
			char *arg_ptr[10] = {NULL}; //Pointer for the execve(char *path, char *arg_ptr, 0)
			arg_ptr[0] = command;
			//All arguments of command added to arg_ptr[10]
			for(i=1; i<MAXARG; i++) 
			{
				char *arg = strtok(0, DELIMITER);
				if(arg != NULL) 
					arg_ptr[i] = arg; 
				else 
					break;
			}
			//arg_ptr has to end with NULL
			arg_ptr[i] = NULL; 

			//Forking is required for the 'execve' command	       		
			switch(pid = fork()) 
			{
				case -1:
					perror("fork()");
					exit(EXIT_FAILURE);
            			case 0:	//In Child Process
					res = execve(path, arg_ptr, envp);
					exit(res);
				default: //In Parent Process
					if(waitpid(pid, &res, 0) < 0)
					{
						perror("waitpid()");
						exit(EXIT_FAILURE);
					} 
			}
    		}
	}
	return 0;
}
