#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 1234
#define BUF_SIZE 1024
#define SA struct sockaddr
int main()
{
 int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
 if (sockfd < 0)
 {
        perror("Error creating socket");
        exit(1);
 }
 struct sockaddr_in server_addr;
 memset(&server_addr, 0, sizeof(server_addr));
 server_addr.sin_family = AF_INET;
 server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 server_addr.sin_port = htons(PORT);
 char buff[BUF_SIZE];
 while(1){
   printf("Enter TIME to get current sys time or EXIT :");
   fgets(buff,BUF_SIZE,stdin);
  if(strcmp("QUIT\n",buff)==0){
      break;
  }
  sendto(sockfd,buff,BUF_SIZE,0,(SA*)&server_addr,sizeof(server_addr));
  bzero(buff,BUF_SIZE);
  recvfrom(sockfd,buff,BUF_SIZE,0,NULL,NULL);
  printf("Server time :%s\n",buff);
}
 close(sockfd);
 return 0;
}
