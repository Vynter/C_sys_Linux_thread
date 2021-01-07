#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <pthread.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mtxcond = PTHREAD_COND_INITIALIZER;

void *Lecture(void *arg){
    
    int *fd=(int*) arg;
    char buff[100];
    pthread_mutex_lock(&mtx);
    pthread_cond_wait(&mtxcond,&mtx);
    
    read(*fd,buff,sizeof(buff));
    printf(": %s",buff);
    close(*fd);
    pthread_mutex_unlock(&mtx);
    pthread_exit(NULL);
}

int main(){
    int fd;
    
    pthread_t th2;
    
    mkfifo("/tmp/pipe1",S_IRWXU|S_IRGRP);
    
    fd=open("/tmp/pipe1",O_RDONLY);

    if(pthread_create(&th2,NULL,Lecture,&fd)==-1){
        perror("erreur");
        return EXIT_FAILURE;
    }
    
    pthread_join(th2,NULL);
        
    pthread_mutex_destroy(&mtx);
    
    

    return 0;
}

