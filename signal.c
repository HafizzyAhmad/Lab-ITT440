#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<errno.h>

//signal exercise 2 no 1

void sig_handler(int signo)
{
  if (signo == SIGINT)
    printf("\nSIGINT : This is special signal handler for SIGINT\n");
}

void term_handler(int myterm)
{
  if (myterm == SIGTERM)
 	printf("\nSIGTERM : This is special signal handler for SIGTERM\n");
}

void kill_handler(int sigkill)
{
  if(sigkill == SIGKILL)
	printf("\nSIGKILL : This is special signal handler for SIGKILL\n");
}

void hup_handler(int sighup)
{
	printf("\nSIGHUP : This is special signal handler for SIGHUP\n");
}

int main(void)
{
  int i = 0;
  if (signal(SIGINT, sig_handler) == SIG_ERR)
  	printf("\nSIGINT : can't catch SIGINT\n");
  if (signal(SIGHUP, term_handler) == SIG_ERR)
	printf("SIGHUP : ");
   if (signal(SIGKILL, kill_handler) == SIG_ERR)
	printf("SIGKILL : can't catch SIGKILL\n");	
  // A long long wait so that we can easily issue a signal to this process
  while(1)
 	{
		printf("i = %d\n", i);
		i++;	
    		sleep(1);
	}
  return 0;
}
