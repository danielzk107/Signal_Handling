#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static int condition = 1;

void sig_handler5(int sig){
    write(STDOUT_FILENO, "Child proccess stopped(5)   \n", 30);
    exit(1);
}

void sig_handler4(int sig){
    write(STDOUT_FILENO, "You divided 0 by 0(4)   \n", 26);
    fflush(stdout);
    struct sigaction siga = {0};
    siga.sa_handler = sig_handler5;
    sigaction(SIGCHLD, &siga, NULL);
    int pid = fork();
    if(pid == 0){
        usleep(500);
        kill(getpid(), SIGTERM);
    }
    wait(0);
}

void sig_handler3(int sig){
    condition = 0;
    write(STDOUT_FILENO, "Seg fault avoided(3)   \n", 25);
    struct sigaction siga = {0};
    siga.sa_handler = sig_handler4;
    sigaction(SIGFPE, &siga, NULL);
    fflush(stdout);
    int num = 0;
    int num2 = 6/num;
}

void sig_handler1(int sig){
    write(STDOUT_FILENO, "alarm(2)   \n", 13);
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
    write(STDOUT_FILENO, "Tried to interrupt(1) \n", 24);
    struct sigaction siga = {0};
    siga.sa_handler = sig_handler1;
    sigaction(SIGALRM, &siga, NULL);
    alarm(1);
}


int main(){
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