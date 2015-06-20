#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#define MAX_BUF 100

main()
{
	int s1, s2;
	struct sockaddr_in saddr;
	int ret, on=1;
	char outbuf[10];
	char inbuf[MAX_BUF+1];

	/*create two stream sockets*/
	s1 = socket( AF_INET, SOCK_DGRAM, 0 );
	s2 = socket( AF_INET, SOCK_DGRAM, 0 );

	/*Make s1 (the server) reusable from 
	* address perspective
	*/

	ret = setsockopt( s1, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

	/*Create the address for tyhe server socket*/
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons( 8192 );
	saddr.sin_addr.s_addr = htonl( INADDR_ANY );

	/*bind the address to s1*/
	ret = bind( s1, (struct sockaddr *)&saddr, sizeof(saddr) );

	/*connect the two sockets together (connected 
	* datagram socket)
	*/
	ret = connect( s2, (struct sockaddr *)&saddr, sizeof(saddr) );

	/*generate some output data*/
	outbuf[0] = 'a';
	outbuf[1] = 0;

	/*make three distinct calls with the data*/
	ret = write( s2, outbuf, 1);
	ret = write( s2, outbuf, 1);
	ret = write( s2, outbuf, 1);

	/*sleep for one second*/
	sleep( 1 );

	/*read the data from client*/
	ret = read( s1, inbuf, MAX_BUF );

	/*should have read 1 byte*/
	printf("read %d bytes\n", ret );

	/*Close the sockets*/
	close(s1);
	close(s2);
}
