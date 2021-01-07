#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <pthread.h>

#define ARRAYSIZE 10

void *Threadfunc(void *arg){
    int *array=(int*)arg;
    
    for(int i=0;i<ARRAYSIZE;i++){
        printf("%d\n",array[i]);
    }
    pthread_exit(NULL);
}

int main(){
    
    int array[ARRAYSIZE]={10,20,30,40,50,60,70,80,90,100};

    pthread_t th;
    if(pthread_create(&th,NULL,Threadfunc,(void*)array)==-1){
        perror("Erreur de la création du thread \n");
        return EXIT_FAILURE;
    }
    pthread_join(th,NULL);
    
return 0;
}
