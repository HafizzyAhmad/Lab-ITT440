#include <sys/types.h>
#include <sys/socket.h>    //socket
#include <stdio.h> //printf
#include <netinet/in.h> 
#include <arpa/inet.h> //inet_addr
#include <string.h>    //strlen
#include <unistd.h>
#include <time.h>


#define MAX_BUFFER 128

#define PORT 3490

//Lab Exercise 3
 
int main(int argc , char *argv[])
{
    int sock, in;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000], timebuffer[MAX_BUFFER+1];
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
    
    //Prepare the sockaddr_in structure
    memset(&server, 0, sizeof server); 
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( PORT );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");
     
    //keep communicating with server
    while((in = read(sock, timebuffer, MAX_BUFFER)) > 0)
    {
       

        timebuffer[in] = 0;
        printf("\nThe Current time is: %s", timebuffer);

    }
     
    close(sock);
    return 0;
}