#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>

#define SA struct sockaddr
#define MAX 80
#define PORT 8010

void func(int sockfd){
        char buff[MAX];
        int len,n;
        struct sockaddr_in server_addr;
        for(;;){
                len=sizeof(buff);
                bzero(buff,MAX);
                int x = sizeof(server_addr);
                recvfrom(sockfd,buff,len,0,(SA*)&server_addr,&x);
                printf("From client : %s",buff);
                bzero(buff,MAX);
                n=0;
                printf("Enter the string : ");
                while((buff[n++]=getchar())!='\n')
                        ;
                sendto(sockfd,buff,len,0,(SA*)&server_addr,x);
                if((strncmp("exit",buff,4))==0){
                        printf("Server exit...\n");
                        break;
                }
        }

}
int main(){
        int sockfd,connfd,len;
        struct sockaddr_in server_addr,client_addr;

        //1.socket creation
        sockfd = socket(AF_INET,SOCK_DGRAM,0);
        if(sockfd == -1){
                printf("[-]Socket creation failed\n");
                exit(0);
        }
        printf("[+]Socket successfully created...\n");

        //2.fill server_addr with 0s and assign IP,PORT
        bzero(&server_addr,sizeof(server_addr));

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        //3.bind socket to server addr
        if(bind(sockfd,(SA*)&server_addr,sizeof(server_addr))!=0){
                printf("[-]Binding failed\n");
                exit(0);
        }
        printf("[+]Binding successfull...\n");

        func(sockfd);
        close(sockfd);
        return 0;
}
