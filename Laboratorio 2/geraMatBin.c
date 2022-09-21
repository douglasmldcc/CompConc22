#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//descomentar o define abaixo caso deseje imprimir uma versao truncada da matriz gerada no formato texto
//#define TEXTO 1

int main(int argc, char*argv[]) {
   float *matriz; //matriz que será gerada
   float *matrizB; //matriz que será gerada
   
   int linhas, colunas; //dimensoes da matriz

   long long int tam; //qtde de elementos na matriz

   FILE * descritorArquivo; //descritor do arquivo de saida
   size_t ret; //retorno da funcao de escrita no arquivo de saida
   FILE * descritorArquivoB; //descritor do arquivo de saida
   size_t retB; //retorno da funcao de escrita no arquivo de saida

   //recebe os argumentos de entrada
   if(argc < 5) {
      fprintf(stderr, "Digite: %s <linhas> <colunas> <arquivo saida A> <arquivo saida B>\n", argv[0]);
      return 1;
   }
   linhas = atoi(argv[1]); 
   colunas = atoi(argv[2]);
   tam = linhas * colunas;

   // Aloca memoria para a matriz
   matriz = (float*) malloc(sizeof(float) * tam);
   if(!matriz) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 2;
   }
   matrizB = (float*) malloc(sizeof(float) * tam);
   if(!matriz) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 2;
   }
   // Criação de matriz teste preenchida de 1
   /*
   ///////////////////////////////////////////////////////////////
   for(long int i=0; i<tam; i++) {
       *(matriz+i) = 2;
       *(matrizB+i) = 2;
   }
   ///////////////////////////////////////////////////////////////
   */

   //Preenche a matriz com valores float aleatorios
   //randomiza a sequencia de numeros aleatorios
   
   srand(time(NULL));
   for(long int i=0; i<tam; i++) {
       *(matriz+i) = (rand() % 1000) * 0.3;
       *(matrizB+i) = (rand() % 1000) * 0.3;
   }
   
   //imprimir na saida padrao a matriz gerada
   #ifdef TEXTO
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
   #endif

   //escreve a matriz no arquivo
   //abre o arquivo para escrita binaria
   descritorArquivo = fopen(argv[3], "wb");
   if(!descritorArquivo) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 3;
   }
   descritorArquivoB = fopen(argv[4], "wb");
   if(!descritorArquivoB) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 3;
   }
   
   //escreve numero de linhas e de colunas
   ret = fwrite(&linhas, sizeof(int), 1, descritorArquivo);

   retB = fwrite(&linhas, sizeof(int), 1, descritorArquivoB);
   //escreve os elementos da matriz
   ret = fwrite(&colunas, sizeof(int), 1, descritorArquivo);
   ret = fwrite(matriz, sizeof(float), tam, descritorArquivo);

   retB = fwrite(&colunas, sizeof(int), 1, descritorArquivoB);
   retB = fwrite(matrizB, sizeof(float), tam, descritorArquivoB);

   if(ret < tam) {
      fprintf(stderr, "Erro de escrita no  arquivo\n");
      return 4;
   }
   if(retB < tam) {
      fprintf(stderr, "Erro de escrita no  arquivo\n");
      return 4;
   }
   //finaliza o uso das variaveis
   fclose(descritorArquivo);
   free(matriz);
   fclose(descritorArquivoB);
   free(matrizB);
   return 0;
}
