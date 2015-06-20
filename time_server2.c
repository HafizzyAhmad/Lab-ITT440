#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <time.h>


#define MAX_BUFFER 128

#define PORT 3490

//Lab Exercise 3
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size, connectionFd;
    struct sockaddr_in server , client;
    char server_message[2000], client_message[2000], timebuffer[MAX_BUFFER+1];
    time_t currenTime;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    memset(&server, 0, sizeof server);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons( PORT );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 5);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    while(1){
        //accept connection from an incoming client
        connectionFd = accept(socket_desc, (struct sockaddr *) NULL, NULL);

        
        if (connectionFd < 0)
        {
            perror("accept failed");
            return 1;
        }

        if(connectionFd >= 0){

            currenTime = time(NULL);
            snprintf(timebuffer, MAX_BUFFER, "%s\n", ctime(&currenTime));

            //send @ sendto
            write(connectionFd, timebuffer, strlen(timebuffer));
            close(connectionFd);
        }
     
        if(read_size == 0)
        {
            puts("Client disconnected");
            fflush(stdout);
        }
        else if(read_size == -1)
        {
            perror("recv failed");
        }
     
        return 0;
    }
}