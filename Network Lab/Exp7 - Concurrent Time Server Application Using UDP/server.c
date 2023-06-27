#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<time.h>

#define SA struct sockaddr
#define PORT 1234
#define MAX 1024

int main(){
        struct sockaddr_in server_addr,client_addr;
        int sockfd = socket(AF_INET,SOCK_DGRAM,0);
        if(sockfd==-1){
                printf("[-]Socket creation fail..\n");
                exit(0);
        }
        printf("[+]Socket creation success..\n");
        bzero(&server_addr,sizeof(server_addr));
        server_addr.sin_family=AF_INET;
        server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
        server_addr.sin_port=htons(PORT);

        if(bind(sockfd,(SA*)&server_addr,sizeof(server_addr))!=0){
                printf("[-]Server bind fail..\n");
                exit(0);
        }
        printf("[+]Server bind success..\n");
        char buff[MAX];
        while(1){
                bzero(buff,MAX);
                socklen_t client_len =sizeof(client_addr);
                recvfrom(sockfd,buff,MAX,0,(SA*)&client_addr,&client_len);
                if(strcmp(buff,"TIME\n")==0){
                        char client[40];
                        strcpy(client,inet_ntoa(client_addr.sin_addr));
                        printf("Received time request from client %s :%d\n",client,ntohs(client_addr.sin_port));
                        bzero(buff,MAX);
                        time_t t=time(NULL);
                        snprintf(buff,MAX,"%s\n",ctime(&t));
                        sendto(sockfd,buff,MAX,0,(SA*)&client_addr,client_len);
                        printf("Sent time %s to client %s\n",buff,client);
                }

        }
        close(sockfd);
        return 0;
}
