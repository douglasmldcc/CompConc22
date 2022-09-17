#include<stdio.h>
#include<stdlib.h>
#include "timer.h"

int main(int argc, char*argv[]) {
   float *matriz; //matriz que será carregada do arquivo
   float *matrizB; //matriz que será carregada do arquivo
   float *msaida; //matriz que será carregada do arquivo

   int linhas, colunas; //dimensoes da matriz
   long long int tam; //qtde de elementos na matriz

   double inicioi,fimi,deltai;
   double inicio,fim,delta;
   double iniciof,fimf,deltaf;

   FILE * descritorArquivo; //descritor do arquivo de entrada
   size_t ret; //retorno da funcao de leitura no arquivo de entrada
   FILE * descritorArquivoB; //descritor do arquivo de entrada
   size_t retB; //retorno da funcao de leitura no arquivo de entrada
     
   //recebe os argumentos de entrada
   if(argc < 3) {
      fprintf(stderr, "Digite: %s <arquivo entrada A> <arquivo entrada B>\n", argv[0]);
      return 1;
   }
    GET_TIME(inicioi);
   //abre o arquivo para leitura binaria
   descritorArquivo = fopen(argv[1], "rb");
   if(!descritorArquivo) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }
   //abre o arquivo para leitura binaria Matriz B
   descritorArquivoB = fopen(argv[2], "rb");
   if(!descritorArquivoB) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }

   //le as dimensoes da matriz
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

    msaida = (float *)malloc(sizeof(float) * linhas * colunas);
    if(msaida == NULL){
        puts("ERROR === 'malloc'\n");
        return 2;
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

   //aloca memoria para a matriz
   matriz = (float*) malloc(sizeof(float) * tam);
   if(!matriz) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }
   // Matriz B
   matrizB = (float*) malloc(sizeof(float) * tam);
   if(!matrizB) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }

   //carrega a matriz de elementos do tipo float do arquivo
   ret = fread(matriz, sizeof(float), tam, descritorArquivo);
   if(ret < tam) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }
   // Matriz B
   retB = fread(matrizB, sizeof(float), tam, descritorArquivoB);
   if(retB < tam) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }
    /*
   //imprime a matriz na saida padrao
   
   for(int i=0; i<linhas; i++) { 
      for(int j=0; j<colunas; j++)
        fprintf(stdout, "%.6f ", matriz[i*colunas+j]);
      fprintf(stdout, "\n");
   }
   //imprime a matriz na saida padrao
   printf("Matriz B \n");
   for(int i=0; i<linhas; i++) { 
      for(int j=0; j<colunas; j++)
        fprintf(stdout, "%.6f ", matrizB[i*colunas+j]);
      fprintf(stdout, "\n");
   }
    */

    //multiplica as matrizes
    GET_TIME(fimi);
    deltai = fimi - inicioi;
    printf("\nTempo de inicializacao:%lf",deltai,"\n");

    GET_TIME(inicio);

    for(int i = 0; i < linhas; i++){
        for( int j = 0; j<linhas; j++){
            for(int k = 0; k<colunas; k++){
                msaida[i*linhas+j] += matriz[i*(linhas)+k] * matrizB[k*(linhas)+j];
            }
        }           
    }
    GET_TIME(iniciof);
    GET_TIME(fim);
    delta = fim - inicio;
    printf("\nTempo de multiplicacao:%lf",delta,"\n");
        
    /*
   //imprime a matriz na saida padrao
   printf("\nMatriz de saida \n");
   for(int i=0; i<linhas; i++) { 
      for(int j=0; j<colunas; j++)
        fprintf(stdout, "%.6f ", msaida[i*colunas+j]);
      fprintf(stdout, "\n");
   }
    */
   //finaliza o uso das variaveis
   fclose(descritorArquivo);
   free(matriz);
   fclose(descritorArquivoB);
   free(matrizB);
   
    GET_TIME(fimf);
    deltai = fimf - iniciof;
    printf("\nTempo de finalizacao:%lf",deltaf,"\n");
   return 0;
}
