#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 5001
#define TOTAL 10
int main(void){int s=socket(AF_INET,SOCK_DGRAM,0);struct sockaddr_in a={0};struct timeval tv={1,0};setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));a.sin_family=AF_INET;a.sin_port=htons(PORT);inet_pton(AF_INET,"127.0.0.1",&a.sin_addr);int got=0,bytes=0;double sum=0;struct timespec all1,all2;clock_gettime(CLOCK_MONOTONIC,&all1);
 for(int i=1;i<=TOTAL;i++){char msg[64],b[4096];snprintf(msg,sizeof(msg),"packet-%d",i);struct timespec t1,t2;clock_gettime(CLOCK_MONOTONIC,&t1);sendto(s,msg,strlen(msg),0,(struct sockaddr*)&a,sizeof(a));int n=recvfrom(s,b,sizeof(b),0,NULL,NULL);clock_gettime(CLOCK_MONOTONIC,&t2);if(n==(int)strlen(msg)&&!memcmp(msg,b,n)){double r=(t2.tv_sec-t1.tv_sec)+(t2.tv_nsec-t1.tv_nsec)/1e9;got++;bytes+=n;sum+=r;printf("Packet %d: ACK/echo received, RTT=%.2f ms\n",i,r*1000);}else printf("Packet %d: lost/invalid (timeout)\n",i);}
 clock_gettime(CLOCK_MONOTONIC,&all2);double elapsed=(all2.tv_sec-all1.tv_sec)+(all2.tv_nsec-all1.tv_nsec)/1e9;printf("Sent=%d, Received=%d, Lost=%d\nPDR: %.2f%%\nPacket loss: %.2f%%\n",TOTAL,got,TOTAL-got,got*100.0/TOTAL,(TOTAL-got)*100.0/TOTAL);if(got)printf("Average RTT: %.2f ms\n",sum/got*1000);if(elapsed>0)printf("Application throughput: %.2f KiB/s\n",bytes/elapsed/1024);close(s);return 0;}
