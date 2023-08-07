#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 1234
#define BUF_SIZE 1024
#define SA struct sockaddr


char msg[500];
pthread_mutex_t mutex;
int clients[20];
int n=0;

void *recvmg(void *my_sock){
        int sock = *((int *)my_sock);
        int len;
        // client thread always ready to receive message
        while((len = recv(sock,msg,500,0)) > 0) {
                msg[len] = '\n';
                fputs(msg,stdout);
        }
    return NULL;
}


int main(){
int port = 8080;
int e;
char msg[500];
int sockfd;
pthread_t recvt;
char client_name[10];
struct sockaddr_in server_addr;

//ask client's name
printf("Enter client name :");
scanf("%s",client_name);


sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd < 0) {
perror("[-]Error in socket");
exit(1);
}
printf("[+]Server socket created successfully.\n");
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(port);
server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
if(e == -1) {
perror("[-]Error in socket");
exit(1);
}
printf("[+]Connected to Server.\n");

//create client thread
pthread_create(&recvt,NULL,(void *)recvmg,&sockfd);

//take input
 char send_msg[500];
while(fgets(msg,500,stdin)>0){
        strcpy(send_msg,client_name);
        strcpy(send_msg,":");
        strcpy(send_msg,msg);
        write(sockfd,send_msg,strlen(send_msg));
}

//close thread
pthread_join(recvt,NULL);
close(sockfd);
return 0;
}
