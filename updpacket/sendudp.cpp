#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<ctype.h>
#include<netinet/in.h>
#include<errno.h>
#include<sys/types.h>
#include"lib/hostInfo.cpp"

class udp:public infoHost{
	private:
		int send;
		char maxudp[1472];
		char ip4[4];
		socklen_t addrlen;
		struct sockaddr_in sin;
		struct sockaddr_in cin;

	public :
		udp(char *interface,char *dstip , int port, char *data):infoHost(interface){
			int fd;
			if((send=socket(AF_INET,SOCK_DGRAM,0))<0){
				perror("create socket error.");
			}
			
			sin.sin_family=AF_INET;	
			if((fd=inet_pton(AF_INET,dstip,&sin.sin_addr))<0)
				perror("error to convert ip");
		
			sin.sin_port=htons(port);
			addrlen=sizeof(sin);
			strcpy(maxudp,data);			
		}
		~udp(){
			close(send);
		}
		void sendout(){	
			if((sendto(send,maxudp,strlen(maxudp),0,(struct sockaddr *)&sin , sizeof(sin))<0)){}
			//	perror("failed to send udp packet");
		}

};

int main(void){
	
	udp d("wlan0","127.0.0.1",10000,"test");
	d.sendout();

	return 0;
}
