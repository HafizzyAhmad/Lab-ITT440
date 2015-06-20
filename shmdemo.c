#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

//sharedmemory exercise 4 no 1

char* receiveInput(){

	char *s;
	scanf("%s",s);

	return s;

}


int main(int argc, char *argv[])
{
	pid_t pid;
	int r1,r2;
	int pfds[2],pfds2[2];
	char buf[30];
	
	pipe(pfds);
	pipe(pfds2);
	key_t key;
	int shmid;
	char *data;
	int mode;



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

			if (argc > 2){
				fprintf(stderr, "usage: shmdemo [data_to_write]\n");
			}

			if((key = ftok("shmdemo.c", 'R')) == -1){
				perror("ftok");
				exit(1);
			}

			if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1){
				perror("shmget");
				exit(1);
			}

			data = shmat(shmid, (void *)0, 0);
			if (data == (char *) (-1)){
				perror("shmat");
				exit(1);
			}


		default:
		  //printf("PARENT: reading from pipe\n");
                  read(pfds[0], buf, 30);
		  printf("PARENT: read \"%s\"\n", buf);
		  wait(&r1);

		if (argc == 2){
			printf("writing to segment: \"%s\"\n", argv[1]);
			strncpy(data, argv[1], SHM_SIZE);
		}else
			printf("segment contains: \"%s\"\n", data);

	
		if(shmdt(data) == -1){
			perror("shmdt");
			exit(1);
		}
	}
	return 0;
}























