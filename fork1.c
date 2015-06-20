#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//fork() exercise no 1

int main(void)
{
	pid_t pid;
	int r1,r2;
        
        

	switch(pid = fork())
	{
          
	  case -1:
		perror("fork");
		exit(1);

	  case 0:
		printf(" CHILD 1: This is child 1 process! \n");
		printf(" CHILD 1: My PID is %d\n", getpid());
		printf(" CHILD 1: My parent's PID is %d\n", getppid());	
		printf(" CHILD 1: Enter my exit status (make it small): ");
		scanf(" %d", &r1);
		printf(" CHILD 1: I'm outta here! \n");
                sleep(1);
		exit(r1);

	  default:
		
		printf(" PARENT: This is the parent process! \n");
		printf(" PARENT: My PID is %d\n", getppid());
		printf(" PARENT: My child 1 PID is %d\n", pid);
		printf(" PARENT: I'm waiting for both child 1 and 2 to exit()....\n");
		wait(&r1);
		

		if(pid=fork())
		  {
			printf(" PARENT: This is the parent process! \n");
			printf(" PARENT: My PID is %d\n", getppid());
			printf(" PARENT: My child 2 PID is %d\n", pid);
			printf(" PARENT: I'm waiting for my child 2 to exit()....\n");
			wait(&r2);
			printf(" PARENT: My child 1 exit status is: %d\n", WEXITSTATUS(r1));
			printf(" PARENT: My child 2 exit status is: %d\n", WEXITSTATUS(r2));
			printf(" PARENT: I'm outta here! \n");

		}else{

			printf(" CHILD 2: This is child 2 process! \n");
			printf(" CHILD 2: My PID is %d\n", getpid());
			printf(" CHILD 2: My parent's PID is %d\n", getppid());	
			printf(" CHILD 2: Enter my exit status (make it small): ");
			scanf(" %d", &r2);
			printf(" CHILD 2: I'm outta here! \n");
                	sleep(1);
			exit(r2);


			


		}

	}
	return 0;
}













