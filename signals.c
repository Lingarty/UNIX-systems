/* 
    Задача: пример общения двух процессов: отца и сына
    с помощью kill() и signal(). 
    Создаётся процесс, распараллеливается, отец и сын обмениваются сообщениями,
    пока отец, наконец, не убивает сына и не прекращает работу.
 */

#include <stdio.h>
#include <signal.h>

void sighup() /* routines child will call upon sigtrap */
{  
    signal(SIGHUP,sighup); /* reset signal */
    printf("Сын: я получил SIGHUP\n");
}

void sigint()
{  
    signal(SIGINT,sigint); /* reset signal */
    printf("Сын: я получил SIGINT\n");
}

void sigquit()
{ 
    printf("Папа, не убивай меня!\n");
    exit(0);
}

int main()
{ 
    int pid;

    if ((pid = fork()) < 0) 
    {
        printf("Не могу создать дочерний процесс. Одному скучно :С\n");;
        exit(1);
    }
    
    if (pid == 0)
    {
        signal(SIGHUP,sighup); /* set function calls */
        signal(SIGINT,sigint);
        signal(SIGQUIT, sigquit);
        for(;;); /* циклимся навсегда */
    }
    else
    {  /* pid хранит id сына*/
        printf("\nОтец:  отправляю SIGHUP\n\n");
        kill(pid,SIGHUP);
        sleep(3); /* pause for 3 secs */
        printf("\nОтец:  отправляю SIGINT\n\n");
        kill(pid,SIGINT);
        sleep(3); /* pause for 3 secs */
        printf("\nОтец:  отправляю SIGQUIT\n\n");
        kill(pid,SIGQUIT);
        sleep(3);
    }

    return 0;
}
