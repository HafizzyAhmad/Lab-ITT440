#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <stdlib.h>
#include <publib.h>

#define PORT 3490

//Lab Exercise 3
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size, n, num1, num2, result;
    struct sockaddr_in server , client;
    char server_message[2000], client_message[2000];
    

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
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
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    while(1){

        //accept connection from an incoming client
        client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        if (client_sock < 0)
        {
            perror("accept failed");
            return 1;
        }

        if (client_sock >= 0){
            puts("Connection accepted");
     
            //Receive a message from client
            read_size = recv(client_sock , client_message , 2000 , 0);
            n= strsplit(client_message, " ");

                  num1 = atoi(n[1]);
                  num2 = atoi(n[2]);
                    
                  if(strcmp(fields[0], "ADD" ) == 0)
                  {
                        result=num1 + num2;
                        //Send the message back to client
                        write(client_sock , result , sizeof(result));
                  }

                  if(strcmp(fields[0], "SUB" ) == 0)
                  {
                        result=num1 - num2;
                        //Send the message back to client
                        write(client_sock , result , sizeof(result));
                  }
        

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