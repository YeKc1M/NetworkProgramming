//test thread

#include <stdio.h>
#include <unistd.h>


int main()
{
    __pid_t fpid;
    //int count=0;
    fpid=fork();
    printf("in main\n");
    if(fpid<0)
    {
        printf("error in fork\n");
    }else if(fpid==0)
    {
        printf("child process, process id is %d\n",getpid());
    }else
    {
        printf("parent process, process id is %d\n", getpid());
    }
    forkThread();
    return 0;
}

void forkThread()
{
    printf("int function\n");
    __pid_t fpid;
    fpid=fork();
    if(fpid<0)
    {
        printf("error in fork\n");
    }else if(fpid==0)
    {
        printf("child function, process id is %d\n",getpid());
    }else
    {
        printf("parent function, process id is %d\n", getpid());
    }
}