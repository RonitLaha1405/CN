#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <math.h>
int main() {
    // *************START CODE FOR CHKSUM RECEIVER ************//
    char data[100];
    int sd,cd,cadl;
    struct sockaddr_in sad,cad;
    int t, c, k, dl, sl, i, j = 0, sum[100],flag=0;
    sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd,10);
    cadl=sizeof(cad);
    cd=accept(sd, (struct sockaddr *)&cad, &cadl);
    printf("\n enter the segment length \n");
    scanf("%d", &sl);
    recv(cd,data,sizeof(data),0);
    printf("Data received= %s\n",data);
    dl=strlen(data);
    for (i = 0; i < sl; i++)
        sum[i] = 0;
    for (i = dl; i > 0; i = i - sl) {
        c = 0;
        k = sl - 1;
        for (j = i - 1; j >= i - sl; j--) {
            t = (sum[k] + (data[j] - 48) + c);
            sum[k] = t % 2;
            c = t / 2;
            k--;
        }
        if (c == 1) {
            for (j = sl - 1; j >= 0; j--) {
                t = sum[j] + c;
                sum[j] = t % 2;
                c = t / 2;
            }
        }
    }
    printf("\n Checksum = ");
    for (i = 0; i < sl; i++) {
        if (sum[i] == 0)
            sum[i] = 1;
        else
            sum[i] = 0;
        printf("%d", sum[i]);
    }
    for (i = 0; i < sl; i++) {
        if (sum[i] == 1)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
        printf("\nGood Codeword\n");
    else
        printf("\nBad Codeword\n");
    close(cd);
    close(sd);
    // *************END CODE FOR CHKSUM SENDER ************//
}
