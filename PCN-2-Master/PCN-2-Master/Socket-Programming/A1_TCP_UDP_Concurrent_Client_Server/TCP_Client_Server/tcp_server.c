#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 5000
int main(void){
 int s=socket(AF_INET,SOCK_STREAM,0), c; struct sockaddr_in a={0}; char buf[4096]={0};
 if(s<0){perror("socket");return 1;} int opt=1; setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
 a.sin_family=AF_INET; a.sin_addr.s_addr=htonl(INADDR_LOOPBACK); a.sin_port=htons(PORT);
 if(bind(s,(struct sockaddr*)&a,sizeof(a))<0||listen(s,5)<0){perror("bind/listen");return 1;}
 printf("TCP server listening on 127.0.0.1:%d\n",PORT); c=accept(s,NULL,NULL); if(c<0){perror("accept");return 1;}
 int n=recv(c,buf,sizeof(buf)-1,0); if(n>0){buf[n]='\0';printf("Client: %s\n",buf); const char *r="Hello from TCP server"; send(c,r,strlen(r),0); puts("Reply sent.");}
 close(c);close(s);return 0;
}
