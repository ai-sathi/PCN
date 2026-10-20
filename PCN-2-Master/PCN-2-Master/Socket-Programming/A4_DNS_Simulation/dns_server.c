#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 53535
int main(void){int s=socket(AF_INET,SOCK_DGRAM,0);struct sockaddr_in a={0},cl;socklen_t l=sizeof(cl);char b[1024];a.sin_family=AF_INET;a.sin_addr.s_addr=htonl(INADDR_LOOPBACK);a.sin_port=htons(PORT);if(bind(s,(struct sockaddr*)&a,sizeof(a))<0){perror("bind");return 1;}puts("Toy DNS server listening on 127.0.0.1:53535");while(1){int n=recvfrom(s,b,sizeof(b)-1,0,(struct sockaddr*)&cl,&l);if(n<=0)continue;b[n]=0;while(n>0&&isspace((unsigned char)b[n-1]))b[--n]=0;for(int i=0;b[i];i++)b[i]=(char)tolower((unsigned char)b[i]);const char*ip=NULL;if(!strcmp(b,"example.com"))ip="93.184.216.34";else if(!strcmp(b,"localhost"))ip="127.0.0.1";else if(!strcmp(b,"college.local"))ip="192.168.1.10";const char*r=ip?ip:"ERROR: domain not found";printf("%s -> %s\n",b,r);sendto(s,r,strlen(r),0,(struct sockaddr*)&cl,l);}close(s);return 0;}
