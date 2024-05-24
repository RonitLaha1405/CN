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
int main()
{
	int sd,cd,cadl;
	struct sockaddr_in sad,cad;
	char str[50];
	
	sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	sad.sin_family=AF_INET;
	sad.sin_port=htons(9995);
	sad.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	bind(sd,(struct sockaddr *)&sad,sizeof(sad));
	listen(sd,10);
	
	cadl=sizeof(cad);
	cd=accept(sd,(struct sockaddr *)&cad,&cadl);
	
	recv(cd,str,sizeof(str),0);
	if(check(str)==1)
		printf("%s is rejected\n",str);
	else
		printf("%s is accepted\n",str);	
	close(cd);
	close(sd);
}
