#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

//variaveis para sincronizacao
pthread_mutex_t mutex;
pthread_cond_t cond_leit, cond_escr;

double pi= 0.0;
int nthreads; //numero de threads

typedef struct{
    int id;     // indentificador do elemento que a trhread ira processar
} tArgs;

void * bbp(void * arg) {
    tArgs *args = (tArgs*) arg;

    for(double k =args->id;k<50000;k+=nthreads){
        double result;
        result +=((1/pow(16,k))*(4/(8*k+1)-  2/(8*k+4)-  1/(8*k+5)-  1/(8*k+6)) );
        pthread_mutex_lock(&mutex);
        pi += result;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char*argv[]){
    int n;          //variavel de casas decimais 
    pthread_t *tid; //identificadores das threads no sistema
    tArgs *args;    //intendificadores locais de dimensao
  
    if(argc < 2) {
        fprintf(stderr, "Digite: %s <casas decimais> <N threads>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    nthreads = atoi(argv[2]);

    tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
    if(tid==NULL) {
        fprintf(stderr, "ERRO--malloc\n");
        return 2;
    }
    //criar as threads
    for(long int i=0; i<nthreads; i++) {
        if(pthread_create(tid+i, NULL, bbp, (void*) i)){
            fprintf(stderr, "ERRO--pthread_create\n");
            return 3;
        }
    }

    //Espera o termino das threads

    for(int i=0; i<nthreads; i++){
        pthread_join(*(tid+i),NULL);
    }
    
    printf("%.*lf",n, pi);
    return 0;
}