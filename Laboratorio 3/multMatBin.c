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
    int lin, col;    //dimensao das estruturas de entrada
} tArgs;

int main(int argc, char*argv[]) {
   int linhas, colunas; //dimensoes da matriz
   long long int tam; //qtde de elementos na matriz

   double inicioi,fimi;
   double inicio,fim;
   double iniciof,fimf;

   FILE * descritorArquivo; //descritor do arquivo de entrada
   size_t ret; //retorno da funcao de leitura no arquivo de entrada
   FILE * descritorArquivoB; //descritor do arquivo de entrada
   size_t retB; //retorno da funcao de leitura no arquivo de entrada
     
   //recebe os argumentos de entrada
   if(argc < 3) {
      fprintf(stderr, "Digite: %s <arquivo entrada A> <arquivo entrada B> <numero de threads>\n", argv[0]);
      return 1;
   }
   GET_TIME(inicioi);   //Recebe o tempo inicial

    nthreads = atoi(argv[3]);
    
   //abre os arquivos para leitura binaria

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

   //le as dimensoes da matriz A

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

   //le as dimensoes da matriz B

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

   //   Aloca memoria para as matrizes
   //   Matriz A
   matriz = (float*) malloc(sizeof(float) * tam);
   if(!matriz) {  fprintf(stderr, "Erro de alocao da memoria da matriz\n");  return 3; }
   //   Matriz B
   matrizB = (float*) malloc(sizeof(float) * tam);
   if(!matrizB) {  fprintf(stderr, "Erro de alocao da memoria da matriz\n");  return 3; }
   //   Matriz de saida
   msaida = (float *)malloc(sizeof(float) * tam);
    if(msaida == NULL){  puts("ERROR === 'malloc'\n");  return 3;}

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
    /*
   //imprime a matriz na saida padrao

   printf("Matriz A \n");
   for(int i=0; i<linhas; i++) { 
      for(int j=0; j<colunas; j++)
        fprintf(stdout, "%.6f ", matriz[i*colunas+j]);
      fprintf(stdout, "\n");
   }

   printf("Matriz B \n");
   for(int i=0; i<linhas; i++) { 
      for(int j=0; j<colunas; j++)
        fprintf(stdout, "%.6f ", matrizB[i*colunas+j]);
      fprintf(stdout, "\n");
   }
    */
   printf("Multiplicacao de matrizes %d x %d \n",linhas , colunas);
   //multiplica as matrizes
   GET_TIME(fimi);
   printf("\nTempo de inicializacao:%lf", fimi - inicioi,"\n");

   GET_TIME(inicio);

   for(int i = 0; i < linhas; i++){
      for( int j = 0; j<linhas; j++){
         for(int k = 0; k<colunas; k++){
               msaida[i*linhas+j] += matriz[i*(linhas)+k] * matrizB[k*(linhas)+j];
         }
      }           
   }
   GET_TIME(iniciof);    //Recebe o tempo inicial de finalizacao
   GET_TIME(fim);        //Recebe o tempo final da multiplicacao

   printf("\nTempo de multiplicacao:%lf",fim - inicio,"\n");
   
   printf("\nMatriz de saida \n");
   for(int i=0; i<linhas; i++) { 
      for(int j=0; j<colunas; j++)
        fprintf(stdout, "%.6f ", msaida[i*colunas+j]);
      fprintf(stdout, "\n");
   }
   
   GET_TIME(fimf);      //Recebe o tempo final da finalizacao

   printf("\nTempo de finalizacao:%lf", fimf - iniciof,"\n");
   puts("\n");

   //   Finaliza o uso das variaveis

   fclose(descritorArquivo);
   free(matriz);
   fclose(descritorArquivoB);
   free(matrizB);
   
   return 0;
}
