#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 5003
int main(void){int s=socket(AF_INET,SOCK_DGRAM,0);struct sockaddr_in a={0},cl;socklen_t l=sizeof(cl);char b[4096];a.sin_family=AF_INET;a.sin_addr.s_addr=htonl(INADDR_LOOPBACK);a.sin_port=htons(PORT);if(bind(s,(struct sockaddr*)&a,sizeof(a))<0){perror("bind");return 1;}printf("Reliable-UDP receiver listening on 127.0.0.1:%d\n",PORT);while(1){int n=recvfrom(s,b,sizeof(b)-1,0,(struct sockaddr*)&cl,&l);if(n<=0)continue;b[n]=0;char*sep=strchr(b,'|');if(!sep){sendto(s,"BAD",3,0,(struct sockaddr*)&cl,l);continue;}*sep=0;int seq=atoi(b);printf("Received sequence=%d, payload=%s\n",seq,sep+1);char ack[64];snprintf(ack,sizeof(ack),"ACK|%d",seq);sendto(s,ack,strlen(ack),0,(struct sockaddr*)&cl,l);if(!strcmp(sep+1,"QUIT")){puts("Receiver stopping.");break;}}close(s);return 0;}
