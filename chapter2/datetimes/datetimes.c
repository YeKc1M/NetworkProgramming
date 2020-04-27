#include "datetime.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    pid_t pid;
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;
    listenfd=socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(13);
    bind(listenfd,(struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 1024);
    for(;;)
    {
        connfd=accept(listenfd,(struct sockaddr *)NULL, NULL);
        if((pid=fork())==0)
        {
            printf("in fork()\n");
            close(listenfd);
            ticks=time(NULL);
            snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
            write(connfd, buff, strlen(buff));
            exit(0);
        }
        /*
        ticks=time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n",ctime(&ticks));
        write(connfd, buff, strlen(buff));*/
        close(connfd);
    }
}