#include "lib_dbg.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int listenfd = 0;
struct sockaddr_in serv_addr; 

int dbg_open()
{
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);
    
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    listen(listenfd, 10);
    
    printf("Connected!");
}


void dbg_write(const char* msg)
{
	int connfd = 0;
	
	while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

        write(connfd, msg, strlen(msg));

        close(connfd);
        sleep(1);
     }
}

void dbg_read(char* msg)
{
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    while ( (n = read(sockfd, msg, sizeof(msg)-1)) > 0)
    {
        msg[n] = 0;
    } 

    if(n < 0)
    {
        printf("\n Read error \n");
    } 
}

void dbg_close()
{
	close(listenfd);
}
