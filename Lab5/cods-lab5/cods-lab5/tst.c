#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#define nThreads 4

pthread_mutex_t mutex;
pthread_cond_t xcond, ycond;
int x = 0;

void* A (void* t){
    sleep(2);
    printf(" Seja bem-vindo!\n");

    pthread_mutex_lock(&mutex);
    x++;
    
    pthread_cond_broadcast(&ycond);
    
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);

}

void* B (void* t){
    sleep(2);
    
    
    pthread_mutex_lock(&mutex);
    while(x < 1){
        pthread_cond_wait(&ycond, &mutex);
    }
    x++;
    printf(" Fique a vontade!\n");
    pthread_cond_signal(&xcond);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void* C (void* t){
    sleep(2);
    
    
    pthread_mutex_lock(&mutex);
    while(x < 1){
        pthread_cond_wait(&ycond, &mutex);
    }
    x++;
    printf(" Sente-se por favor.\n");
    pthread_cond_signal(&xcond);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void* D (void* t){
    sleep(2);
    pthread_mutex_lock(&mutex);
    while(x<3){
        pthread_cond_wait(&xcond, &mutex);
    }
    printf("\n Volte sempre!\n");
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(){
    int i;
    pthread_t threads[nThreads];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&xcond, NULL);
    pthread_cond_init(&ycond, NULL);

    pthread_create(&threads[1], NULL, A, NULL);
    pthread_create(&threads[0], NULL, B, NULL);
    pthread_create(&threads[3], NULL, C, NULL);
    pthread_create(&threads[2], NULL, D, NULL);

    for(i = 0; i<nThreads; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&xcond);
    pthread_cond_destroy(&ycond);

    printf("\n END \n");
}
