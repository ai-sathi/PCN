#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 5003
#define MAX_RETRIES 5
int main(void){int s=socket(AF_INET,SOCK_DGRAM,0);struct timeval tv={1,0};setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));struct sockaddr_in a={0};a.sin_family=AF_INET;a.sin_port=htons(PORT);inet_pton(AF_INET,"127.0.0.1",&a.sin_addr);const char*msgs[]={"First message","Second message","Third message","QUIT"};int total=0,acked=0,retries=0,bytes=0;double rttsum=0;struct timespec all1,all2;clock_gettime(CLOCK_MONOTONIC,&all1);
 for(int i=0;i<4;i++){int ok=0;char packet[256],reply[256];snprintf(packet,sizeof(packet),"%d|%s",i+1,msgs[i]);for(int attempt=1;attempt<=MAX_RETRIES;attempt++){struct timespec t1,t2;clock_gettime(CLOCK_MONOTONIC,&t1);sendto(s,packet,strlen(packet),0,(struct sockaddr*)&a,sizeof(a));total++;if(attempt>1)retries++;printf("Sent seq=%d, attempt=%d\n",i+1,attempt);int n=recvfrom(s,reply,sizeof(reply)-1,0,NULL,NULL);clock_gettime(CLOCK_MONOTONIC,&t2);if(n>0){reply[n]=0;char expected[64];snprintf(expected,sizeof(expected),"ACK|%d",i+1);if(!strcmp(reply,expected)){double r=(t2.tv_sec-t1.tv_sec)+(t2.tv_nsec-t1.tv_nsec)/1e9;printf("ACK %d received; RTT=%.2f ms\n",i+1,r*1000);rttsum+=r;acked++;bytes+=strlen(packet);ok=1;break;}}else printf("Timeout for seq=%d; retransmitting...\n",i+1);}if(!ok){printf("Failed after %d attempts; stopping.\n",MAX_RETRIES);break;}}
 clock_gettime(CLOCK_MONOTONIC,&all2);double elapsed=(all2.tv_sec-all1.tv_sec)+(all2.tv_nsec-all1.tv_nsec)/1e9;printf("\n--- Performance metrics ---\nMessages acknowledged: %d/4\nPDR: %.2f%%\nTotal transmissions: %d; retransmissions: %d\n",acked,acked*25.0,total,retries);if(acked)printf("Average RTT: %.2f ms\n",rttsum/acked*1000);if(elapsed>0)printf("Application throughput: %.2f KiB/s\n",bytes/elapsed/1024);close(s);return 0;}
