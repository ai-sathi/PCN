#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 5002
int main(void){int s=socket(AF_INET,SOCK_STREAM,0);struct sockaddr_in a={0};char msg[2048],reply[4096]={0};a.sin_family=AF_INET;a.sin_port=htons(PORT);inet_pton(AF_INET,"127.0.0.1",&a.sin_addr);printf("Enter message: ");if(!fgets(msg,sizeof(msg),stdin))return 1;msg[strcspn(msg,"\n")]=0;if(connect(s,(struct sockaddr*)&a,sizeof(a))<0){perror("connect");return 1;}struct timespec t1,t2;clock_gettime(CLOCK_MONOTONIC,&t1);send(s,msg,strlen(msg),0);int n=recv(s,reply,sizeof(reply)-1,0);clock_gettime(CLOCK_MONOTONIC,&t2);if(n>0)reply[n]=0;double sec=(t2.tv_sec-t1.tv_sec)+(t2.tv_nsec-t1.tv_nsec)/1e9;printf("Server: %s\nResponse time (send/reply): %.2f ms\n",reply,sec*1000);if(sec>0)printf("Application throughput: %.2f KiB/s\n",n/sec/1024);close(s);return 0;}
