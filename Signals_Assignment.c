#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static int condition = 1;

void sig_handler5(int sig){
    write(STDOUT_FILENO, "Child proccess stopped   ", 25);
    exit(1);
}

void sig_handler4(int sig){
    write(STDOUT_FILENO, "You divided 0 by 0   \n", 23);
    fflush(stdout);
    int pid = fork();
    if(pid == 0){
        usleep(500);
        kill(pid, SIGKILL);
    }
    else{
        struct sigaction siga = {0};
        siga.sa_handler = sig_handler5;
        sigaction(SIGCHLD, &siga, NULL);
    }
    wait(NULL);
}

void sig_handler3(int sig){
    condition = 0;
    write(STDOUT_FILENO, "Seg fault avoided   \n", 22);
    struct sigaction siga = {0};
    siga.sa_handler = sig_handler4;
    sigaction(SIGFPE, &siga, NULL);
    fflush(stdout);
    int num = 0;
    int num2 = 6/num;
}

void sig_handler1(int sig){
    write(STDOUT_FILENO, "alarm   \n", 10);
    struct sigaction siga = {0};
    siga.sa_handler = sig_handler3;
    sigaction(SIGSEGV, &siga, NULL);
    // sleep(2);
    fflush(stdout);
    if(condition == 1){
        int arr[2];
        arr[10000] = 90;
        // sleep(1);
    }
}

void sig_handler2(int sig){
    write(STDOUT_FILENO, "Tried to interrupt \n", 21);
    struct sigaction siga = {0};
    siga.sa_handler = sig_handler1;
    sigaction(SIGALRM, &siga, NULL);
    alarm(1);
}


int main(){
    // int pid = fork();
    // if(pid == 0){
    //     // struct sigaction siga;
    //     // siga.sa_handler = &sig_handler2;
    //     // sigaction(SIGUSR1, &siga, NULL);
    //     while(condition == 1){
    //         sleep(2);
    //         // printf("\nThis is the child proccess\n");
    //         kill(getppid(), SIGUSR1);
    //     }
    // }
    // else{
    //     struct sigaction siga;
    //     siga.sa_handler = &sig_handler1;
    //     sigaction(SIGUSR1, &siga, NULL);
    //     printf("Pick a number between 0 and 100\n");
    //     int num = 0;
    //     scanf("%d", &num);
    //     printf("You picked the number %d\n", num);
    //     // condition = 0;
    //     kill(0, SIGUSR1);
    // }
    printf("Start\n");
    struct sigaction siga = {0};
    siga.sa_handler = sig_handler2;
    siga.sa_flags = 0;
    sigemptyset(&siga.sa_mask);
    sigaction(SIGINT, &siga, NULL);
    kill(getpid(), SIGINT);
    while (1)
    {
        /* code */
    }
    
}