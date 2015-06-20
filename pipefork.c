#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

//pipe and fork exercise 3 no 1

char* receiveInput(){

	char *s;
	scanf("%s",s);

	return s;

}


int main(void)
{
	pid_t pid;
	int r1,r2;
	int pfds[2],pfds2[2];
	char buf[30];
	
	pipe(pfds);
	pipe(pfds2);

	switch(pid = fork())
	{
		case -1:
		  perror("fork");
		  exit(1);
		case 0:
		  printf("CHILD 1: Writing to the pipe :\n");
		  char *str = receiveInput();
		  write(pfds[1],("CHILD 1 write %s", str),30);
		  sleep(1);
		  printf("CHILD 1: exiting\n");
		  sleep(1);
		  exit(r1);
		default:
		  //printf("PARENT: reading from pipe\n");
                  read(pfds[0], buf, 30);
		  printf("PARENT: read \"%s\"\n", buf);
		  wait(&r1);
		  if(pid=fork())
		  {
			//printf("PARENT: reading from pipe\n");
                        read(pfds[0], buf, 30);
		        printf("PARENT: read \"%s\"\n", buf);
			wait(&r2);
		  }else{
			printf("CHILD 2: Writing to the pipe :\n");
			char *str2 = receiveInput(); 
		        write(pfds[1],("CHILD 2 write %s", str2),30);
		        sleep(1);
			printf("CHILD 2: exiting\n");
			sleep(1);
			exit(r2);
		  }
		  

	}
return 0;
}
