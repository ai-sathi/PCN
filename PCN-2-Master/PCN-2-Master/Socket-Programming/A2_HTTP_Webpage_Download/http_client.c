#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 8000
int main(void){int s=socket(AF_INET,SOCK_STREAM,0);struct sockaddr_in a={0};a.sin_family=AF_INET;a.sin_port=htons(PORT);inet_pton(AF_INET,"127.0.0.1",&a.sin_addr);if(connect(s,(struct sockaddr*)&a,sizeof(a))<0){perror("connect (start local HTTP server on port 8000)");return 1;}char req[]="GET /index.html HTTP/1.1\r\nHost: 127.0.0.1:8000\r\nConnection: close\r\n\r\n";struct timespec t1,t2;clock_gettime(CLOCK_MONOTONIC,&t1);send(s,req,strlen(req),0);FILE*f=fopen("http_response.tmp","wb");char b[4096];int n;while((n=recv(s,b,sizeof(b),0))>0)fwrite(b,1,n,f);fclose(f);close(s);clock_gettime(CLOCK_MONOTONIC,&t2);double sec=(t2.tv_sec-t1.tv_sec)+(t2.tv_nsec-t1.tv_nsec)/1e9;
 FILE*in=fopen("http_response.tmp","rb");if(!in){perror("open response");return 1;}char all[200000];size_t len=fread(all,1,sizeof(all)-1,in);fclose(in);all[len]=0;char*body=strstr(all,"\r\n\r\n");if(!body){fprintf(stderr,"Invalid HTTP response\n");return 1;}*body=0;body+=4;printf("%s\n",all);FILE*out=fopen("downloaded.html","wb");fwrite(body,1,len-(size_t)(body-all),out);fclose(out);size_t blen=len-(size_t)(body-all);printf("Saved %zu body bytes to downloaded.html\nDownload time: %.2f ms\n",blen,sec*1000);if(sec>0)printf("Application throughput: %.2f KiB/s\n",blen/sec/1024);remove("http_response.tmp");return 0;}
