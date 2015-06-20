#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER 128

//define port here to connect
#define DAYTIME_SERVER_PORT 6667

//Lab Exercise 2
//q2...client connect to port 6667
//q4...client will output The current time is: 

int main()
{
   int connectionFd, in;
   struct sockaddr_in servaddr;
   char timebuffer[MAX_BUFFER+1];

   connectionFd = socket(AF_INET, SOCK_STREAM, 0);
   memset(&servaddr, 0, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(DAYTIME_SERVER_PORT);
   servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

   //sockaddr and sockaddr_in are two different structure types
   connect(connectionFd,(const struct sockaddr *)&servaddr,sizeof(servaddr));
   //if != loop: use, if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)

      while((in = read(connectionFd, timebuffer, MAX_BUFFER)) > 0)
      {
         timebuffer[in] = 0;
         printf("\nThe Current time is: %s", timebuffer);
      }

   close(connectionFd);
}