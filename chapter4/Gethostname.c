#include <stdio.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <netdb.h>
#include <setjmp.h>
#include <errno.h>

int main(int argc, char ** argv)
{
    if(argc<2)
    {
        printf("usage:%s hostname/IP address\n",argv[0]);
        exit(1);
    }
    struct hostent *host;
    unsigned long inaddr=01;
    struct sockaddr_in dest_addr;
    bzero(&dest_addr, sizeof(dest_addr));
    dest_addr.sin_family=AF_INET;
    if((inaddr=inet_addr(argv[1]))==INADDR_NONE)
    {
        if((host=gethostbyname(argv[1]))==NULL)
        {
            perror("gethostbyname error");
            exit(1);
        }
        memcpy((char *)&dest_addr.sin_addr, host->h_addr, host->h_length);
        printf("hostname: %s\n", argv[1]);
        printf("IP address: %s\n", inet_ntoa(dest_addr.sin_addr));
    }
    else 
    {
        struct in_addr *hipaddr=(struct inaddr *)malloc(sizeof(struct in_addr));
        if(!inet_aton(argv[1], hipaddr))
        {
            perror("inet_aton error");
            exit(1);
        }
        if((host=gethostbyaddr(hipaddr, INET_ADDRSTRLEN, AF_INET))==NULL)
        {
            perror("gethostbyaddr error");
            exit(1);
        }
        printf("IP address: %s\n", argv[1]);
        printf("hostname: %s\n", host->h_name);
    }
}