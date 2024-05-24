#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
int check(char st[])
{
	int c=0;
	for(int i=0;i<strlen(st);i++)
	{
		if(st[i]=='1')
			c++;
	}
	if(c%2==0)
		return 0;
	else
		return 1;
}
void addParity(char st[])
{
	int c=check(st);
	st[strlen(st)]=(c==0)?'0':'1';
	st[strlen(st)+1]=='\0';
}
int main()
{
	int sd,cadl;
	struct sockaddr_in sad,cad;
	char str[50];
	
	sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	sad.sin_family=AF_INET;
	sad.sin_port=htons(9995);
	sad.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	connect(sd,(struct sockaddr *)&sad,sizeof(sad));
	
	printf("Enter the dataword:");
	scanf("%[^\n]s",str);
	addParity(str);
	printf("Codeword with parity bit sent: %s\n",str);
	send(sd,str,sizeof(str),0);
	
	close(sd);
}
