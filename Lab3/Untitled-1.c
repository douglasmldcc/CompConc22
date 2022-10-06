#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#include "timer.h"

float *matriz; //matriz que será carregada do arquivo
float *matrizB; //matriz que será carregada do arquivo
float *msaida; //matriz que será carregada do arquivo

int nthreads;

typedef struct{
    int id;     // indentificador do elemento que a trhread ira processar
    int lin,col;
} tArgs;

void* tarefa(void *arg){
    tArgs *args = (tArgs*) arg;
    printf("Thread %d \n", args->id);
    for(int i = 0; i < args->lin; i++)
        for( int j = 0; j<args->lin; j++)
            for(int k = 0; k<args->col; k++)
                msaida[i*args->lin+j] += matriz[i*(args->lin)+k] * matrizB[k*(args->lin)+j];
    pthread_exit(NULL);
}

int main(int argc,char*argv[]){
    int linhas, colunas; //dimensoes da matriz
    long long int tam; //qtde de elementos na matriz


    double inicioi,fimi;
    double inicio,fim;
    double iniciof,fimf;
   
    pthread_t *tid; //intentificadores da threads no sistema 
    tArgs *args;    //intendificadores locais de dimensao

    FILE * descritorArquivo; //descritor do arquivo de entrada
    size_t ret; //retorno da funcao de leitura no arquivo de entrada
    FILE * descritorArquivoB; //descritor do arquivo de entrada
    size_t retB; //retorno da funcao de leitura no arquivo de entrada

    //leitura e av par
    if(argc<4){
        printf("Digite: %s <arquivo entrada A> <arquivo entrada B> <numero de threads>\n", argv[0]);
        return 1;
    }

    GET_TIME(inicioi);   //Recebe o tempo inicial

    nthreads = atoi(argv[3]);   //Numero de Threads

    //abre os arquivos para leitura binaria
    descritorArquivo = fopen(argv[1], "rb");
    if(!descritorArquivo) {
        fprintf(stderr, "Erro de abertura do arquivo\n"); return 2; }
    descritorArquivoB = fopen(argv[2], "rb");
    if(!descritorArquivoB) { fprintf(stderr, "Erro de abertura do arquivo\n"); return 2; }



    //le as dimensoes das matrizes A
    //matriz A
    ret = fread(&linhas, sizeof(int), 1, descritorArquivo);
    if(!ret) { fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n"); return 3; }
    ret = fread(&colunas, sizeof(int), 1, descritorArquivo);
    if(!ret) { fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n"); return 3; }
    //matriz B
    retB = fread(&linhas, sizeof(int), 1, descritorArquivoB);
    if(!retB) { fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n"); return 3; }
    retB = fread(&colunas, sizeof(int), 1, descritorArquivoB);
    if(!retB) { fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n"); return 3;}

    tam = linhas * colunas; //calcula a qtde de elementos da matriz
    if (nthreads>tam) nthreads=tam;

    //malloc --  Aloca memoria para as matrizes
    //   Matriz A
    matriz = (float*) malloc(sizeof(float) * tam);
    if(!matriz) { fprintf(stderr, "Erro de alocao da memoria da matriz\n");return 4;}
    //   Matriz B
    matrizB = (float*) malloc(sizeof(float) * tam);
    if(!matrizB) {fprintf(stderr, "Erro de alocao da memoria da matriz\n");return 4; }
    //   Matriz de saida
    msaida = (float *)malloc(sizeof(float) * tam);
    if(msaida == NULL){ puts("ERROR === 'malloc'\n"); return 4; }
    //
    printf("Multiplicacao de matrizes %d x %d \n",linhas , colunas);

    //init estrut dados

    GET_TIME(fimi);
    GET_TIME(inicio);

    //Multiplicacao da matriz pelas estruturas 
    //alocacao das estruturas 

    tid = (pthread_t*)malloc(sizeof(pthread_t)*nthreads);
    if(tid==NULL) {printf("ERRO -- malloc\n"); return 4;}
    args = (tArgs*)malloc(sizeof(tArgs)*nthreads);
    if(args==NULL) {printf("ERRO -- malloc\n"); return 4;}

    //criacao das threads
    for(int i=0; i<nthreads; i++){
        (args+i)->id = i;
        (args+i)->lin = linhas;
        (args+i)->col = colunas;
        if(pthread_create(tid+i, NULL, tarefa, (void*) (args+i))){
            puts("ERRO -- pthread_create"); return 3;
        }
    }
    //Espera o termino das threads
    

    for(int i=0; i<nthreads; i++){
        pthread_join(*(tid+i),NULL);
    }


    GET_TIME(iniciof);    //Recebe o tempo inicial de finalizacao
    GET_TIME(fim);        //Recebe o tempo final da multiplicacao

    printf("\nTempo de inicializacao:%lf", (fimi - inicioi),"\n");
    printf("\nTempo de multiplicacao:%lf",(fim - inicio),"\n");
    

    // Exibe os resultados da matriz de saida 
    /*
    printf("\nMatriz A \n");
    for(int i=0; i<linhas; i++) { 
        for(int j=0; j<colunas; j++)
        fprintf(stdout, "%.6f ", matriz[i*colunas+j]);
        fprintf(stdout, "\n");
    }
    printf("\nMatriz B \n");
    for(int i=0; i<linhas; i++) { 
        for(int j=0; j<colunas; j++)
        fprintf(stdout, "%.6f ", matrizB[i*colunas+j]);
        fprintf(stdout, "\n");
    }
    printf("\nMatriz de saida \n");
    for(int i=0; i<linhas; i++) { 
        for(int j=0; j<colunas; j++)
        fprintf(stdout, "%.6f ", msaida[i*colunas+j]);
        fprintf(stdout, "\n");
    }
    */
    //libera memoria

    free(args);
    free(tid);



    fclose(descritorArquivo);
    free(matriz);
    fclose(descritorArquivoB);
    free(matrizB);
    GET_TIME(fimf);
    printf("\nTempo de finalizacao:%lf", (fimf - iniciof),"\n");
    puts("\n");

    return 0;
}