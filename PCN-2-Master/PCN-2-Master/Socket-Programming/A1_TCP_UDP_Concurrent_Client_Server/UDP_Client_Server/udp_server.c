#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 5001
int main(void){int s=socket(AF_INET,SOCK_DGRAM,0);struct sockaddr_in a={0},client;socklen_t len=sizeof(client);char b[4096];a.sin_family=AF_INET;a.sin_addr.s_addr=htonl(INADDR_LOOPBACK);a.sin_port=htons(PORT);if(bind(s,(struct sockaddr*)&a,sizeof(a))<0){perror("bind");return 1;}printf("UDP echo server listening on 127.0.0.1:%d\n",PORT);while(1){int n=recvfrom(s,b,sizeof(b),0,(struct sockaddr*)&client,&len);if(n<0)continue;if(n==4&&!memcmp(b,"STOP",4))break;sendto(s,b,n,0,(struct sockaddr*)&client,len);}close(s);return 0;}
