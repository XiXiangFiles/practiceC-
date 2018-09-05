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
#include"socketlib/HostInfo.h"

class udp:public infoHost{
	private:
		int send;
		uint8_t maxudp[1472];
		char ip4[4];
		socklen_t addrlen;
		struct sockaddr_in sin;
		struct sockaddr_in cin;

	public :
		udp(char *interface, char *dstip , int port, char* type ,char *data):infoHost(interface){
			int fd;
			char str[16];

			if((send=socket(AF_INET,SOCK_DGRAM,0))<0){
				perror("create socket error.");
			}
			

			sin.sin_family=AF_INET;	
			if((fd=inet_pton(AF_INET,dstip,&sin.sin_addr))<0)
				perror("error to convert ip");

			sin.sin_port=htons(port);
			addrlen=sizeof(sin);
			
			//--------------------------------------------------------   set up the port & ip on sockaddr_in
			cin.sin_family=AF_INET;
			cin.sin_port=htons(port);
			memcpy(&cin.sin_addr,getIP(), 4);
			// -------------------------------------------------------   bind port & ip for sender
			bind(send,(struct sockaddr *) &cin ,(socklen_t)sizeof(cin));

			memset(maxudp,0,sizeof(maxudp));

			inet_ntop(AF_INET,getIP(),str,16);
			printf("%s\n",str);
			//-------------------------------------------------------- Assign the packet data
			maxudp[0]=0x01;
			maxudp[1]=0x00;
			maxudp[2]=0x08;
			maxudp[3]=0x0c;
			memcpy(maxudp+4,data,strlen(data));

		}

		~udp(){
			close(send);
		}

		void sendout(){	
			if((sendto(send,maxudp,sizeof(maxudp),0,(struct sockaddr *)&sin , sizeof(sin))<0)){
				perror("failed to send udp packet");
			}
		}
};

int main(void){
	
	udp d("eth0","140.119.143.79",10001,"PUBLISH","test");
	for(int i=0; i<100 ; i++){
		d.sendout();
	}
	return 0;
}
