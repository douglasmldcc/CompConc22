/*
Programa: pc.c
Descricao: implementa  o problema dos produtores/consumidores usando variaveis de condicao da biblioteca Pthread
Autor: Silvana Rossetto
*/

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <time.h>
#include <semaphore.h>


#define N 5 //tamanho do buffer
#define P 4//qtde de threads produtoras
#define C 3//qtde de threads consumidoras

//variaveis do problema
int Buffer[N]; //espaco de dados compartilhados

//variaveis para sincronizacao
pthread_mutex_t mutex;
pthread_cond_t cond_cons, cond_prod;

sem_t slotCheio, slotVazio;     //semaforos para sincronizar a ordem de execucao das threads
sem_t mutexProd, mutexCons;     //exclusão mutua

//inicializa o buffer
void IniciaBuffer(int n) {
  int i;
  for(i=0; i<n; i++)
    Buffer[i] = 0;
}

//imprime o buffer
void ImprimeBuffer(int n) {
  int i;
  for(i=0; i<n; i++)
    printf("%d ", Buffer[i]);
  printf("\n");
}

//insere um elemento no Buffer ou bloqueia a thread caso o Buffer esteja cheio
void Insere (int item, int id) {
    static int in = 0;
    sem_wait(&slotVazio);
    //aguarda slot vazio
    sem_wait(&mutexProd);
    if((in+1)== N){
        printf("P[%d] quer inserir\n", id);
        Buffer[in] = item;
        in = (in + 1)%N;
        printf("%d \n",in);
        printf("P[%d] inseriu\n", id);
        ImprimeBuffer(N);

        printf("--------------- Buffer cheio--------------- \n");

        sem_post(&slotCheio);
        sem_post(&slotCheio);
        sem_post(&slotCheio);
        sem_post(&slotCheio);
        sem_post(&slotCheio);
    }else{
        //exclusao mutua entre produtores
        printf("P[%d] quer inserir\n", id);
        Buffer[in] = item;
        in = (in + 1)%N;
        printf("%d \n",in);
        printf("P[%d] inseriu\n", id);
        ImprimeBuffer(N);
    }
    sem_post(&mutexProd);

}

//retira um elemento no Buffer ou bloqueia a thread caso o Buffer esteja vazio
int Retira (int id) {
   int item;
   static int out = 0;
    //aguarda slot cheio
    sem_wait(&slotCheio);
    //exclusão mutua entre consumidores
    sem_wait(&mutexCons);
    if(out+1 == N){
        printf("C[%d] quer consumir\n", id);

        item = Buffer[out];
        out = (out + 1)%N;
        printf("%d \n",out);
        printf("C[%d] consumiu %d\n", id, item);
        ImprimeBuffer(N);
        printf("--------------- Buffer vazio--------------- \n");
        sem_post(&slotVazio);
        sem_post(&slotVazio);
        sem_post(&slotVazio);
        sem_post(&slotVazio);
        sem_post(&slotVazio);

        out = (out + 1)%N;
        printf("%d \n",out);
    }else{
        printf("C[%d] quer consumir\n", id);

        item = Buffer[out];
        out = (out + 1)%N;
        printf("%d \n",out);
        printf("C[%d] consumiu %d\n", id, item);
        ImprimeBuffer(N);
    }
    sem_post(&mutexCons);
    //sinaliza um slot vazio

    return item;
}

//thread produtora
void * produtor(void * arg) {
  int *id = (int *) arg;
  printf("Sou a thread produtora %d\n", *id);
  while(1) {
    //produzindo o item
    Insere(*id, *id);
    sleep(1);
  } 
  free(arg);
  pthread_exit(NULL);
}

//thread consumidora
void * consumidor(void * arg) {
  int *id = (int *) arg;
  int item;
  printf("Sou a thread consumidora %d\n", *id);
  while(1) {
    item = Retira(*id);
    sleep(1); //faz o processamento do item 
  } 
  free(arg);
  pthread_exit(NULL);
}


//funcao principal
int main(void) {
    srand(time(NULL));
  //variaveis auxiliares
  int i;
 
  //identificadores das threads
  pthread_t tid[P+C];
  int *id[P+C];

  //aloca espaco para os IDs das threads
  for(i=0; i<P+C;i++) {
    id[i] = malloc(sizeof(int));
    if(id[i] == NULL) exit(-1);
    *id[i] = i+1;
  }

    //inicializa o Buffer
    IniciaBuffer(N);  
    //inicia os semaforos
    sem_init(&slotCheio, 0, 0);
    sem_init(&slotVazio, 0, N);
    sem_init(&mutexCons, 0, 1);
    sem_init(&mutexProd, 0, 1);

  //cria as threads produtoras
  for(i=0; i<P; i++) {
    if(pthread_create(&tid[i], NULL, produtor, (void *) id[i])) exit(-1);
  } 
  
  //cria as threads consumidoras
  for(i=0; i<C; i++) {
    if(pthread_create(&tid[i+P], NULL, consumidor, (void *) id[i+P])) exit(-1);
  } 

  pthread_exit(NULL);
  return 1;
}