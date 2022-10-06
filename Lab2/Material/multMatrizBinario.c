/* Programa que le um arquivo binario com dois valores inteiros (indicando as dimensoes de uma matriz) 
 * e uma sequencia com os valores da matriz (em float)
 * Entrada: nome do arquivo de entrada
 * Saida: valores da matriz escritos no formato texto (com 6 casas decimais) na saida padrao 
 * */

#include<stdio.h>
#include<stdlib.h>

#include "timer.h"

int main(int argc, char*argv[]) {
   float *matriz; //matriz que será carregada do arquivo
   float* saida;
   double inicio, fim, delta;
   int linhas, colunas; //dimensoes da matriz
   long long int tam; //qtde de elementos na matriz
   FILE * descritorArquivo; //descritor do arquivo de entrada
   size_t ret; //retorno da funcao de leitura no arquivo de entrada
   
   GET_TIME(inicio);
   //recebe os argumentos de entrada
   if(argc < 2) {
      fprintf(stderr, "Digite: %s <arquivo entrada>\n", argv[0]);
      return 1;
   }
   
   //abre o arquivo para leitura binaria
   descritorArquivo = fopen(argv[1], "rb");
   if(!descritorArquivo) {
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
   tam = linhas * colunas; //calcula a qtde de elementos da matriz

   //aloca memoria para a matriz
   matriz = (float*) malloc(sizeof(float) * tam);
   if(!matriz) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }

   //carrega a matriz de elementos do tipo float do arquivo
   ret = fread(matriz, sizeof(float), tam, descritorArquivo);
   if(ret < tam) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }


   saida = (float *)malloc(sizeof(float) * tam);
    if(saida == NULL){
        puts("ERROR === 'malloc'\n");
        return 2;
    }

   for(int i=0; i<linhas; i++) { 
      for(int j=0; j<colunas; j++)
        
      fprintf(stdout, "\n");
   }
   for(int i=0; i<linhas; i++) { 
      for(int j=0; j<linhas; j++)
         for(int k=0; k<colunas; j++)
            saida[i*colunas+j] += matriz[i*(colunas)+k] * matriz[k*(colunas)+j];
   }
   //imprime a matriz na saida padrao
   for(int i=0; i<linhas; i++) { 
      for(int j=0; j<colunas; j++)
        fprintf(stdout, "%.1f ", matriz[i*colunas+j]);
      fprintf(stdout, "\n");
   }
   
    GET_TIME(fim);
    delta = fim - inicio;
    printf("\nTempo de multiplicacao:%lf",delta);

   //finaliza o uso das variaveis
   fclose(descritorArquivo);
   free(matriz);
   return 0;
}
/* Programa que le um arquivo binario com dois valores inteiros (indicando as dimensoes de uma matriz) 
 * e uma sequencia com os valores da matriz (em float)
 * Entrada: nome do arquivo de entrada
 * Saida: valores da matriz escritos no formato texto (com 6 casas decimais) na saida padrao 
 * */

#include<stdio.h>
#include<stdlib.h>

#include "timer.h"

int main(int argc, char*argv[]) {
   float *matriz; //matriz que será carregada do arquivo
   float* saida;
   double inicio, fim, delta;
   int linhas, colunas; //dimensoes da matriz
   long long int tam; //qtde de elementos na matriz
   FILE * descritorArquivo; //descritor do arquivo de entrada
   size_t ret; //retorno da funcao de leitura no arquivo de entrada
   
   GET_TIME(inicio);
   //recebe os argumentos de entrada
   if(argc < 2) {
      fprintf(stderr, "Digite: %s <arquivo entrada>\n", argv[0]);
      return 1;
   }
   
   //abre o arquivo para leitura binaria
   descritorArquivo = fopen(argv[1], "rb");
   if(!descritorArquivo) {
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
   tam = linhas * colunas; //calcula a qtde de elementos da matriz

   //aloca memoria para a matriz
   matriz = (float*) malloc(sizeof(float) * tam);
   if(!matriz) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }

   //carrega a matriz de elementos do tipo float do arquivo
   ret = fread(matriz, sizeof(float), tam, descritorArquivo);
   if(ret < tam) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }


   saida = (float *)malloc(sizeof(float) * tam);
    if(saida == NULL){
        puts("ERROR === 'malloc'\n");
        return 2;
    }

   for(int i=0; i<linhas; i++) { 
      for(int j=0; j<colunas; j++)
        
      fprintf(stdout, "\n");
   }
   for(int i=0; i<linhas; i++) { 
      for(int j=0; j<linhas; j++)
         for(int k=0; k<colunas; j++)
            saida[i*colunas+j] += matriz[i*(colunas)+k] * matriz[k*(colunas)+j];
   }
   //imprime a matriz na saida padrao
   for(int i=0; i<linhas; i++) { 
      for(int j=0; j<colunas; j++)
        fprintf(stdout, "%.1f ", matriz[i*colunas+j]);
      fprintf(stdout, "\n");
   }
   
    GET_TIME(fim);
    delta = fim - inicio;
    printf("\nTempo de multiplicacao:%lf",delta);

   //finaliza o uso das variaveis
   fclose(descritorArquivo);
   free(matriz);
   return 0;
}
