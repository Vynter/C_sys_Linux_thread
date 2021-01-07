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

void *Ecriture(void *arg){
    
    int *fd=(int*) arg;
    char buff[100];
    pthread_mutex_lock(&mtx);
    //pthread_cond_wait(&mtxcond,&mtx);
    printf("Veuillez saisir une phrase \n");
    fgets(buff,sizeof(buff),stdin);
    write(*fd,buff,sizeof(buff));
    close(*fd);
    pthread_cond_signal(&mtxcond);
    pthread_mutex_unlock(&mtx);
    sleep(1);
    pthread_exit(NULL);
}

int main(){
    int fd;
    char buff[100];
    
    pthread_t th;
    
    mkfifo("/tmp/pipe1",S_IRWXU|S_IRGRP);
    
    fd=open("/tmp/pipe1",O_WRONLY);

        if(pthread_create(&th,NULL,Ecriture,&fd)==-1){
        perror("erreur");
        return EXIT_FAILURE;
    }
    
    
    pthread_join(th,NULL);
        
    pthread_mutex_destroy(&mtx);
    

    return 0;
}

