#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SUBNET "192.168.1.%d"
#define MAX_HOSTS 254

int main()
{
	int i, count, ret;
	struct sockaddr_in servaddr;
	int socks[MAX_HOSTS], maxfd = 0;
	char buf[30+1];
	fd_set fds;
	struct timeval timeout;

	/* Set up a timeout */
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;

	/* partially setup address structure */
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8888);

	FD_ZERO( &fds );

	/* attempt to connect to all nodes on the subnet */
	for (i = 1 ; i <= MAX_HOSTS ; i++){

		/*complete address structure*/
		sprintf(buf, SUBNET, i);
		servaddr.sin_addr.s_addr = inet_addr(buf);

		/*create a new socket for this node*/
		socks[i] = socket(AF_INET, SOCK_STREAM, 0);

		/*add it to the socket descriptor list*/
		FD_SET( socks[i], &fds);

		/*make the socket non blocking*/
		fcntl(socks[i], F_SETFL, O_NONBLOCK);

		/*attempt a connect (nonblocking)*/
		connect( socks[i], (struct sockaddr *)&servaddr, sizeof(servaddr));

		if(socks[i] > maxfd) maxfd = socks[i];

	}

	count = MAX_HOSTS;

	while (1){

		/*await connect responses (writable sockets)*/
		ret = select(maxfd, NULL, &fds, NULL, &timeout);

		if (ret > 0){

			count -= ret;

			/*walk through the socket descriptor list*/
			for(i = 1 ; i <= MAX_HOSTS ; i++){
				if ( FD_ISSET( socks[i], &fds) ){
					printf("Port open at 192.168.1.%d\n", i);
					FD_CLR( socks[i], &fds );
				}
			}

			/*if we've found everything, exit*/
			if (count == 0) break;

		}else {

			/*Timeout, exit*/
			break;

		}
	}

	/*Cleanup, close all of the sockets*/
	for( i = 1 ; i < MAX_HOSTS ; i++){
		close(socks[i]);
	}

	return(0);

}
