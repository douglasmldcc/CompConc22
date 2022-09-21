#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

float *mat;
float *vet;
float *saida;
int nthreads;

typedef struct{
    int id;     // indentificador do elemento que a trhread ira processar
    int dim;    //dimensao das estruturas de entrada
} tArgs;

void* tarefa(void *arg){
    tArgs *args = (tArgs*) arg;
    printf("Thread %d \n", args->id);
    for(int i=args->id;i<args->dim; i+=nthreads)
        for(int j=0 ; j<args->dim; j++)
            saida[i]+=mat[i*(args->dim)+j]*vet[j];
    pthread_exit(NULL);
}

int main(int argc,char*argv[]){
    int dim;
    pthread_t *tid; //intentificadores da threads no sistema 
    tArgs *args;    //intendificadores locais de dimensao

    //leitura e av par
    if(argc<3){
        printf("Digite: %s <dimensao da matriz> <numero de threads>\n", argv[0]);
        return 1;
    }
    dim = atoi(argv[1]);
    nthreads = atoi(argv[2]);

    if (nthreads>dim) nthreads=dim;
    //malloc
    mat = (float*) malloc(sizeof(float)*dim*dim);
    if(mat==NULL) {printf("ERRO -- malloc\n"); return 2;}
    vet = (float*) malloc(sizeof(float)*dim*dim);
    if(vet==NULL) {printf("ERRO -- malloc\n"); return 2;}
    saida = (float*) malloc(sizeof(float)*dim*dim);
    if(saida==NULL) {printf("ERRO -- malloc\n"); return 2;}

    //init estrut dados
    for(int i=0 ; i<dim; i++){
        for(int j=0 ; j<dim; j++)
            mat[i*dim+j]=1;
        vet[i]=1;
        saida[1]=0;
    }
    //Multiplicacao da matriz pelas estruturas 
    //alocacao das estruturas 

    tid = (pthread_t*)malloc(sizeof(pthread_t)*nthreads);
    if(tid==NULL) {printf("ERRO -- malloc\n"); return 2;}
    args = (tArgs*)malloc(sizeof(tArgs)*nthreads);
    if(args==NULL) {printf("ERRO -- malloc\n"); return 2;}

    //criacao das threads
    for(int i=0; i<nthreads; i++){
        (args+i)->id = i;
        (args+i)->dim = dim;
        if(pthread_create(tid+i, NULL, tarefa, (void*) (args+i))){
            puts("ERRO -- pthread_create"); return 3;
        }
    }
    //Espera o termino das threads

    for(int i=0; i<nthreads; i++){
        pthread_join(*(tid+i),NULL);
    }
    //Exibe os resultados 

    puts("Matriz de entrada");
    for(int i=0 ; i<dim; i++){
        for(int j=0 ; j<dim; j++)
            printf("%.lf ",mat[i*dim+j]);
        puts("");
    }
    puts("Vetor de entrada");
    for(int i=0 ; i<dim; i++){
        printf("%.lf ",vet[i]);
    puts("");
    }
    
    puts("Vetor de saida");
    for(int i=0 ; i<dim; i++){
        printf("%.lf ",saida[i]);
    puts("");
    }
    
    //libera memoria
    free(mat);
    free(vet);
    free(saida);
    free(args);
    free(tid);

    return 0;
}