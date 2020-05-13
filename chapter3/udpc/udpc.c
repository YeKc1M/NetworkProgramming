#include "unp.h"

#define MAXLINE 4096

void dg_cli(FILE *fp, int sockfd, const SA * pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE+1];
    while(fgets(sendline, MAXLINE, fp)!=NULL)
    {
        sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        n=recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        recvline[n]=0;
        fputs(recvline, stdout);
    }
}

int main(int argc, char ** argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    if(argc!=2)
        err_quit("usage: udpcli<Ipaddress>");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_port=htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);
    dg_cli(stdin, sockfd, (SA*)&servaddr, sizeof(servaddr));
    exit(0);
}