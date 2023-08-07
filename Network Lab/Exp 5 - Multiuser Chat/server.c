#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<pthread.h>
#include<stdlib.h>

#define SA struct sockaddr
#define PORT 1234
#define MAX 1024

pthread_mutex_t mutex;
int clients[20];
int n=0;

void sendtoall(char *msg,int curr){
        pthread_mutex_lock(&mutex);
        for(int i=0;i<n;i++){
                if(clients[i]!=curr){           //send msg to all sockfds' except the current one
                        send(clients[i],msg,strlen(msg),0);
                }
        }
        pthread_mutex_unlock(&mutex);
}

void *recvmg(void *sock){
        char msg[500];
        int len;
        int sockfd=*((int *)sock);
        while((len=recv(sockfd,msg,500,0))>0){
                msg[len]='\n';
                sendtoall(msg,sockfd);
        }
        return NULL;
}

int main(){
int port = 8080;
pthread_t recvt;
int e;
int sockfd, connfd;
struct sockaddr_in server_addr, new_addr;
socklen_t addr_size;
char buffer[MAX];
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd < 0) {
perror("[-]Error in socket");
exit(1);
}
printf("[+]Server socket created successfully.\n");
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(port);
server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
if(e < 0) {
perror("[-]Error in bind");
exit(1);
}
printf("[+]Binding successfull.\n");
if(listen(sockfd, 10) == 0){
printf("[+]Listening....\n");
}else{
perror("[-]Error in listening");
exit(1);
}
addr_size = sizeof(new_addr);
while(1){
        connfd=accept(sockfd,(SA*)NULL,NULL);
        if(connfd<0){
                printf("[-]Accept failed  \n");
                exit(0);
        }

        printf("[+]Connection successfull\n");

        //acquire lock
        pthread_mutex_lock(&mutex);

        //store connfd to clients array
        clients[n]=connfd;
        n++;

        //create thread for each client
        pthread_create(&recvt,NULL,(void *)recvmg,&connfd);

        //release lock
        pthread_mutex_unlock(&mutex);
}
return 0;
}
