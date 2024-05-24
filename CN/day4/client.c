#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <math.h>
char xor(char a,char b)
{
	if(a=='0' && b=='0')
		return '0';
	else if(a=='0' && b=='1')
		return '1';
	else if(a=='1' && b=='0')
		return '1';
	else
		return '0';
}
int main() {
    char data[100], divisor[100],data1[100];
    int sd,cadl; 
    struct sockaddr_in sad,cad;
    int dl, dil, i, j;
    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(sd, (struct sockaddr *)&sad, sizeof(sad));
    printf("\n Enter the data \n");
    scanf("%s", data);
    dl = strlen(data);
    printf("\n Enter the divisor \n");
    scanf("%s", divisor);
    dil = strlen(divisor);
    for(i=0;i<dil-1;i++)
    	data[dl+i]='0';
    printf("The data with appended zeroes: %s\n",data);
    strcpy(data1,data);
    for(i=0;i<dl;i++)
    {
    	if(data1[i]=='1')
    	{
    		for(j=0;j<dil;j++)
    			data1[i+j]=xor(data1[i+j],divisor[j]);
    	}
    }
    for(i=dl;i<dl+(dil-1);i++)
    	data[i]=data1[i];
    printf("The codeword sent: %s\n",data);
    send(sd, data, sizeof(data),0);
    close(sd);
}
