#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 5004
unsigned checksum(const unsigned char*d,size_t n){unsigned long sum=0;for(size_t i=0;i<n;i+=2){unsigned w=(unsigned)d[i]<<8;if(i+1<n)w|=d[i+1];sum+=w;sum=(sum&0xffff)+(sum>>16);}return (~sum)&0xffff;}
void crc_remainder_server(const char*bits,const char*poly,char*out){int n=strlen(bits),m=strlen(poly);char w[4096];if(n>=4096||m<2||m>n){strcpy(out,"INVALID");return;}strcpy(w,bits);for(int i=0;i<=n-m;i++)if(w[i]=='1')for(int j=0;j<m;j++)w[i+j]=(w[i+j]==poly[j]?'0':'1');strcpy(out,w+n-(m-1));}
int main(void){int s=socket(AF_INET,SOCK_STREAM,0),opt=1;struct sockaddr_in a={0};setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));a.sin_family=AF_INET;a.sin_addr.s_addr=htonl(INADDR_LOOPBACK);a.sin_port=htons(PORT);if(bind(s,(struct sockaddr*)&a,sizeof(a))<0||listen(s,5)<0){perror("bind/listen");return 1;}printf("Error-detection server listening on 127.0.0.1:%d\n",PORT);int c=accept(s,NULL,NULL);if(c<0){perror("accept");return 1;}char raw[8192]={0},result[4096]={0};int n=recv(c,raw,sizeof(raw)-1,0);if(n<=0)return 1;raw[n]=0;
 if(!strncmp(raw,"CHECKSUM|",9)){char*p=raw+9,*sep=strchr(p,'|');if(!sep)snprintf(result,sizeof(result),"ERROR: malformed checksum request");else{*sep=0;unsigned sent=(unsigned)strtoul(p,NULL,10),got=checksum((unsigned char*)(sep+1),strlen(sep+1));snprintf(result,sizeof(result),"Received checksum=%u; calculated checksum=%u; %s",sent,got,sent==got?"VALID":"ERROR DETECTED");}}
 else if(!strncmp(raw,"CRC|",4)){char*p=raw+4,*sep=strchr(p,'|');if(!sep)strcpy(result,"ERROR: malformed CRC request");else{*sep=0;char rem[256];crc_remainder_server(sep+1,p,rem);int zero=1;for(int i=0;rem[i];i++)if(rem[i]!='0')zero=0;snprintf(result,sizeof(result),"Received codeword=%s; remainder=%s; %s",sep+1,rem,zero?"NO ERROR DETECTED":"ERROR DETECTED");}}
 else if(!strncmp(raw,"HAMMING|",8)){char*code=raw+8;int len=strlen(code),syn=0;for(int p=1;p<=len;p*=2){int parity=0;for(int q=1;q<=len;q++)if(q&p)parity^=code[q-1]-'0';if(parity)syn+=p;}if(syn>0&&syn<=len)code[syn-1]=(code[syn-1]=='0'?'1':'0');char data[2048];int k=0;for(int q=1;q<=len;q++)if(q&(q-1))data[k++]=code[q-1];data[k]=0;snprintf(result,sizeof(result),"Syndrome=%d; corrected codeword=%s; extracted data=%s",syn,code,data);}
 else strcpy(result,"ERROR: unknown mode");send(c,result,strlen(result),0);puts(result);close(c);close(s);return 0;}
