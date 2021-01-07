#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <pthread.h>

struct TypeArray{
    int a_Size;
    int *array;
};

void *Threadfunc(void *arg){
    
    struct TypeArray *t_array =(struct TypeArray*)arg;

    for(int i=0;i<t_array->a_Size;i++){
        printf("Veuillez saisir la valeur N %d\n",i+1);
        scanf("%d",&t_array->array[i]);
    }
    printf("==================Affichage================\n");
    for(int i=0;i<t_array->a_Size;i++){
        printf("La valeur N %d : %d\n",i+1,t_array->array[i]);
    }
    printf("===========================================\n");
    pthread_exit(NULL);
}

int main(){
    
    struct TypeArray t_array;
    printf("Veuillez saisir la taille du tableau : ");
    scanf("%d",&t_array.a_Size);
    t_array.array=malloc(t_array.a_Size*sizeof(int));

    pthread_t th;

    if(pthread_create(&th,NULL,Threadfunc,(void*)(&t_array))==-1){
        perror("Erreur de la création du thread \n");
        return EXIT_FAILURE;
    }
    pthread_join(th,NULL);
    
    
    free(t_array.array);
return 0;
}
