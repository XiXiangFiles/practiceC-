#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<unistd.h>

int main(void){
	int pid=-1;
	int value=2;
	printf("~~~~~father id= %d child id= %d\n",getpid(),pid);
	do{
		pid=fork();	
		printf("@@@@father id= %d child id= %d\n",getpid(),pid);
		if(pid ==0){
			value--;
			printf("child id = %d \n", getpid());
			printf("value= %d\n",value);
		}else{
			printf("****father id= %d child id= %d\n",getpid(),pid);
			fork();
			printf("2 child id = %d pid= %d \n", getpid(),pid);
			execlp("ls", "ls", "-al", "/etc/passwd", (char *)0);}
	}while(value>1);
	
	printf("value = %d end\n",value);
	return 0;
}
