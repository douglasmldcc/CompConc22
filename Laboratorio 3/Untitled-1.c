#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

float *matriz;   //matriz que será carregada do arquivo
float *matrizB;  //matriz que será carregada do arquivo
float *msaida;   //matriz que será carregada do arquivo

int nthreads;
/*
typedef struct{
    int id;          // indentificador do elemento que a trhread ira processar
    int lin;      // indentificador do elemento de linhas
    int col;     // indentificador do elemento de colunas
} tArgs;

void* tarefa(void *arg){
    tArgs *args = (tArgs*) arg;
    printf("Thread %d \n", args->id);
   for(int i = 0; i < i<args->id; i++){
      for( int j = 0; j<args->lin; j++){
         for(int k = 0; k<args->col; k++){
               msaida[i*args->id+j] += matriz[i*(args->lin)+k] * matrizB[k*(args->lin)+j];
    pthread_exit(NULL);
}
*/

int main(int argc, char*argv[]) {

    int linhas, colunas; //dimensoes da matriz
    long long int tam; //qtde de elementos na matriz

    double inicioi,fimi,deltai;
    double inicio,fim,delta;
    double iniciof,fimf,deltaf;

    FILE * descritorArquivo; //descritor do arquivo de entrada
    size_t ret; //retorno da funcao de leitura no arquivo de entrada
    FILE * descritorArquivoB; //descritor do arquivo de entrada
    size_t retB; //retorno da funcao de leitura no arquivo de entrada

    //  Recebe os argumentos de entrada
    if(argc < 3) {
        fprintf(stderr, "Digite: %s <arquivo entrada A> <arquivo entrada B>\n", argv[0]);
    return 1;
    }

    //   Abre os arquivos para leitura binaria
    descritorArquivo = fopen(argv[1], "rb");
    if(!descritorArquivo) {
        fprintf(stderr, "Erro de abertura do arquivo\n");
        return 2;
    }
    descritorArquivoB = fopen(argv[2], "rb");
    if(!descritorArquivoB) {
        fprintf(stderr, "Erro de abertura do arquivo\n");
        return 2;
    }

    //  Le a dimensao das matrizes
    //   Matriz A
    ret = fread(&linhas, sizeof(int), 1, descritorArquivo);
    if(!ret) {
        fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
        return 3;
    }
    ret = fread(&colunas, sizeof(int), 1, descritorArquivo);
    if(!ret) {
        fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
        return 3;
    }

    //   Matriz B
    retB = fread(&linhas, sizeof(int), 1, descritorArquivoB);
    if(!retB) {
        fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
        return 3;
    }
    retB = fread(&colunas, sizeof(int), 1, descritorArquivoB);
    if(!retB) {
        fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
        return 3;
   }

   tam = linhas * colunas; //calcula a qtde de elementos da matriz

   //   loca memoria para as matrizes
   //   Matriz A
   matriz = (float*) malloc(sizeof(float) * tam);
   if(!matriz) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }
   //    Matriz B
   matrizB = (float*) malloc(sizeof(float) * tam);
   if(!matrizB) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }
   // Matriz de saida
   msaida = (float *)malloc(sizeof(float) * tam);
    if(msaida == NULL){
        puts("ERROR === 'malloc'\n");
        return 3;
   }

   //   Carrega a matriz de elementos do tipo float do arquivo
   //   Matriz A
   ret = fread(matriz, sizeof(float), tam, descritorArquivo);
   if(ret < tam) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }
   //   Matriz B
   retB = fread(matrizB, sizeof(float), tam, descritorArquivoB);
   if(retB < tam) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }
    return 0;
}