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
    char data[100],data1[100],crc[100],divisor[100];
    int sd,cd,cadl,flag=0;
    struct sockaddr_in sad,cad;
    int dl, dil, i, j;
    sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd,10);
    cadl=sizeof(cad);
    cd=accept(sd, (struct sockaddr *)&cad, &cadl);
    printf("\nEnter the divisor \n");
    scanf("%s", &divisor);
    dil=strlen(divisor);
    recv(cd,data,sizeof(data),0);
    printf("Data received= %s\n",data);
    dl=strlen(data);
    strcpy(data1,data);
    for(i=0;i<dil-1;i++)
    	data1[dl+i]='0';
    for(i=0;i<strlen(data);i++)
    {
    	if(data1[i]=='1')
    	{
    		for(j=0;j<dil;j++)
    			data1[i+j]=xor(data1[i+j],divisor[j]);
    	}
    }
    printf("CRC Checksum: ");
    for(i = strlen(data); i < strlen(data1); i++)
    {
    	printf("%c",data1[i]);
    	if(data1[i]=='1')
    		flag=1;
    }
    if(flag==0)
    	printf("\nGood codeword\n");
    else
    	printf("\nBad codeword\n");
    close(cd);
    close(sd);
}
