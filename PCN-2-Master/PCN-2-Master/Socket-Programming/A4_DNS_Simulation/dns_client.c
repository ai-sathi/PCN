#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 53535
int main(void){int s=socket(AF_INET,SOCK_DGRAM,0);struct timeval tv={3,0};setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));struct sockaddr_in a={0};a.sin_family=AF_INET;a.sin_port=htons(PORT);inet_pton(AF_INET,"127.0.0.1",&a.sin_addr);char domain[512],reply[1024];printf("Enter domain (example.com / localhost / college.local): ");if(!fgets(domain,sizeof(domain),stdin))return 1;domain[strcspn(domain,"\r\n")]=0;struct timespec t1,t2;clock_gettime(CLOCK_MONOTONIC,&t1);sendto(s,domain,strlen(domain),0,(struct sockaddr*)&a,sizeof(a));int n=recvfrom(s,reply,sizeof(reply)-1,0,NULL,NULL);clock_gettime(CLOCK_MONOTONIC,&t2);double sec=(t2.tv_sec-t1.tv_sec)+(t2.tv_nsec-t1.tv_nsec)/1e9;if(n>0){reply[n]=0;printf("DNS response: %s\nLookup response time: %.2f ms\nLookup success rate for this query: %d%%\n",reply,sec*1000,strncmp(reply,"ERROR:",6)?100:0);}else{puts("DNS server timed out.");printf("Lookup response time until timeout: %.2f ms\nLookup success rate for this query: 0%%\n",sec*1000);}close(s);return 0;}
