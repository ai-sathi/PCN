#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 5002
static int clients=0; static pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
void *handle(void *arg){int c=*(int*)arg;free(arg);char b[4096]={0};int n=recv(c,b,sizeof(b)-1,0);if(n>0){b[n]='\0';printf("Client message: %s\n",b);char out[4200];snprintf(out,sizeof(out),"Echo: %s",b);send(c,out,strlen(out),0);pthread_mutex_lock(&lock);printf("Clients handled so far: %d\n",++clients);pthread_mutex_unlock(&lock);}close(c);return NULL;}
int main(void){int s=socket(AF_INET,SOCK_STREAM,0),opt=1;struct sockaddr_in a={0};setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));a.sin_family=AF_INET;a.sin_addr.s_addr=htonl(INADDR_LOOPBACK);a.sin_port=htons(PORT);if(bind(s,(struct sockaddr*)&a,sizeof(a))<0||listen(s,20)<0){perror("bind/listen");return 1;}printf("Concurrent TCP server listening on 127.0.0.1:%d\nRun multiple clients in separate terminals.\n",PORT);while(1){int c=accept(s,NULL,NULL);if(c<0)continue;int*p=malloc(sizeof(int));*p=c;pthread_t t;if(pthread_create(&t,NULL,handle,p)==0)pthread_detach(t);else{close(c);free(p);}}close(s);return 0;}
