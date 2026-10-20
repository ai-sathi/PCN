#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 5000
int main(void){int s=socket(AF_INET,SOCK_STREAM,0);struct sockaddr_in a={0};char buf[4096]={0};struct timespec t1,t2;
 a.sin_family=AF_INET;a.sin_port=htons(PORT);inet_pton(AF_INET,"127.0.0.1",&a.sin_addr);
 if(connect(s,(struct sockaddr*)&a,sizeof(a))<0){perror("connect");return 1;}const char*m="Hello from TCP client";clock_gettime(CLOCK_MONOTONIC,&t1);send(s,m,strlen(m),0);int n=recv(s,buf,sizeof(buf)-1,0);clock_gettime(CLOCK_MONOTONIC,&t2);if(n>0)buf[n]='\0';
 double sec=(t2.tv_sec-t1.tv_sec)+(t2.tv_nsec-t1.tv_nsec)/1e9;printf("Server: %s\nRTT (send to reply): %.2f ms\n",buf,sec*1000);if(sec>0)printf("Application throughput: %.2f KiB/s\n",n/sec/1024);close(s);return 0;}
