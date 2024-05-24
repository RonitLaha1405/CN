#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<math.h>
int main() {
    int sd,cd,cadl; 
    struct sockaddr_in sad,cad;
    char data[100],d[100],data3[100];
    int data1[100],data2[100];
    int dl,r,i=0,j=0,k=0,z,c,s=0,flag;
    sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd,10);
    cadl=sizeof(cad);
    cd=accept(sd, (struct sockaddr *)&cad, &cadl);
    recv(cd,data,sizeof(data),0);
    printf("Enter the data:");
    scanf("%s",d);
    printf("\nThe codeword received:  %s\n",data);
    dl=strlen(d); //length of the input string
    while(1) //finding number of parity bits
    {
        if(pow(2,i)>=dl+i+1)
            break;
        i++;
    }
    r=i; //storing number of parity bits into r variable
    for(i=1;i<=dl+r;i++)
    {
        data3[i]=data[dl+r-i];
    }
    printf("\nThe redundant bits: ");
    for(i=0;i<dl;i++) //conversion of string data into integer
    {
        data1[i]=d[i]-48; //data1 array is used to store only integer data
    }
    for(i=0;i<r;i++) //initialising parity bits' positions with some value (say 999) in data2 array
    {
        z=pow(2,i);
        data2[z]=999; //data2 array is used to store data+parity bits
    }
    for(i=dl+r;i>=1;i--) //this loop is used to place the data bits and parity bits at fixed positions
    {
        if(data2[i]!=999)
        {
            data2[i]=data1[j]; //if it's not a parity bit, store the data bit in reverse order
            j++;
        } 
    }
    for(i=r-1;i>=0;i--) //outer loop is used to find the values for each parity bit
    {
        z=pow(2,i); //finding position of each parity bit
        c=0; //initializing counter c
        for(j=z;j<=dl+r;j=z+k) //inner loop is used to add data bits related to each parity bit
        {
            for(k=j;k<z+j;k++) //this loop is for part by part parity calculation
            {
                if(k<=dl+r)
                {
                    if(data2[k]!=999) //if k is not a parity bit
                    {
                        c=c+data2[k]; //add the value of that position with counter c
                    }
                }
            }
        }
        if(c%2!=data3[z]-48)
        {
            s=s+z;
            flag=1;
        }
        else
            flag=0;
        data2[z]=data3[z]-48;
        printf("\nr%d=%d (should be %d) ----> %d\n",z,data2[z],c%2,flag);
    }
    if(s==0)
        printf("\nNo error\n");
    else
    {
        printf("\nError at position %d\n",s);
        if(data2[s]==0)
            data2[s]=1;
        else
            data2[s]=0;
        printf("Corrected codeword:");
        for(i=dl+r;i>=1;i--)
            printf("%d",data2[i]);
        printf("\n");
    }
    close(cd);
    close(sd);
    // *************END CODE FOR hamming RECEIVER ************//
    return(0);
}
