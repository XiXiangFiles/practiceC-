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
#include"lib/hostInfo.cpp"

class udp:public infoHost{
	private:
		int send;
		char maxupd[1472];
		char ip4[4];
		struct sockaddr_in sin;
		struct sockaddr_in cin;

	public :
		udp(char *interface,char *dst , int port, char *data):infoHost(interface){
			if((send=socket(AF_INET,SOCK_DGRAM,0))<0){
				perror("create socket error.");
			}
			
			sin.sin_family=AF_INET;
//			memcpy(sin.sin_addr.s_addr,getIP(),4);
			sin.sin_port=htons(port);
					
		}
		~udp(){
		
		}

};

int main(void){


	return 0;
}
