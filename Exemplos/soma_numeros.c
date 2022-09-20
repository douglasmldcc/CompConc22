//Soma todos os elementos de um vetor de inteiro
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

long int dim; //dimensao do vetor de entrada
int nthreads; //numero de threads
int *vetor; //vetor de entrada com dimensao dim 

//fluxo das threads
void * tarefa(void * arg) {
   long int id = (long int) arg; //identificador da thread
   long int somaLocal = 0; //variavel local da soma de elementos
   long int tamBloco = dim/nthreads;  //tamanho do bloco de cada thread 
   long int ini = id * tamBloco; //elemento inicial do bloco da thread
   long int fim; //elemento final(nao processado) do bloco da thread
   if(id == nthreads-1) fim = dim;
   else fim = ini + tamBloco; //trata o resto se houver
   //soma os elementos do bloco da thread
   for(long int i=ini; i<fim; i++)
      somaLocal += vetor[i];
   //retorna o resultado da soma local
   pthread_exit((void *) somaLocal); 
}

//fluxo principal
int main(int argc, char *argv[]) {
   long int somaSeq= 0; //soma sequencial
   long int somaConc= 0; //soma concorrente
   double ini, fim; //tomada de tempo
   pthread_t *tid; //identificadores das threads no sistema
   long int retorno; //valor de retorno das threads

   //recebe e valida os parametros de entrada (dimensao do vetor, numero de threads)
   if(argc < 3) {
       fprintf(stderr, "Digite: %s <dimensao do vetor> <numero threads>\n", argv[0]);
       return 1; 
   }
   dim = atoi(argv[1]);
   nthreads = atoi(argv[2]);
   //aloca o vetor de entrada
   vetor = (int*) malloc(sizeof(int)*dim);
   if(vetor == NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }
   //preenche o vetor de entrada
   for(long int i=0; i<dim; i++)
      vetor[i] = i%1000;
  
   //soma sequencial dos elementos
   GET_TIME(ini);
   for(long int i=0; i<dim; i++)
      somaSeq += vetor[i];   
   GET_TIME(fim);
   printf("Tempo sequencial:  %lf\n", fim-ini);

   //soma concorrente dos elementos
   GET_TIME(ini);
   tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
   if(tid==NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }
   //criar as threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
   }
   //aguardar o termino das threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_join(*(tid+i), (void**) &retorno)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
      //soma global
      somaConc += retorno;
   }
   GET_TIME(fim);
   printf("Tempo concorrente:  %lf\n", fim-ini);

   //exibir os resultados
   printf("Soma seq:  %ld\n", somaSeq);
   printf("Soma conc: %ld\n", somaConc);

   //libera as areas de memoria alocadas
   free(vetor);
   free(tid);

   return 0;
}