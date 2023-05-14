#include "headers.h"

/* Modify this file as needed*/
int remainingtime;
int gotosleep=0;

void handler(int signum)
{ gotosleep++;
 printf("\nprocess with id %d has continue working\n",getpid());
}
int main(int agrc, char * argv[])
{
    initClk();
    int x; 
    signal(SIGCONT,handler);
    printf(" \nactive process\n");
    sscanf(argv[1], "%d", &x);
    remainingtime=x;
    printf("remmaining time is %d",x);
    printf("\n----------------------i am the process----------------------------------\n");
    printf("%d",getpid());
    kill(getppid(),SIGCONT);
    perror("wake el scheduler");

    if(!gotosleep)
    {
        perror("\nSTOP EL PROCESS\n");
        kill(getpid(),SIGSTOP);

    }
    else
       gotosleep--;
    perror(" \nstopped process continued \n");
    while ((clock()/CLOCKS_PER_SEC)< remainingtime)
    {

    }
    int p_clock=getClk();
    destroyClk(false);
    perror("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    printf("\nprocess with runtime %d finished at time %d\n",x,p_clock);
    //up(sem1);
    exit(0);
    
    return 0;
}