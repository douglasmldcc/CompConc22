/* Disciplina: Computacao Concorrente */
/* Nome.: Douglas de Morais Lima  */
/* Laboratório: 6 */
/* Codigo: Implementacao de uma aplicacao que usa o padrao leitores/escritores.*/

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define L 1 //numero de threads leitoras
#define E 2 //numero de threads escritoras
#define LE 3 //numero de threads leitoras e escritoras



//variaveis do problema
int leit=0; //contador de threads lendo
int escr=0; //contador de threads escrevendo

int x = 0;
//variaveis para sincronizacao
pthread_mutex_t mutex;
pthread_cond_t cond_leit, cond_escr;

//entrada leitura
void InicLeit (int id) {
   pthread_mutex_lock(&mutex);
   printf("L[%d] quer ler\n", id);
   while(escr > 0) {
     pthread_cond_wait(&cond_leit, &mutex);
   }
    printf("E[%d] X = %d \n", id,x);

   leit++;
   pthread_mutex_unlock(&mutex);
}

//saida leitura
void FimLeit (int id) {
   pthread_mutex_lock(&mutex);
   printf("L[%d] terminou de ler\n", id);
   leit--;
   if(leit==0) pthread_cond_signal(&cond_escr);
   pthread_mutex_unlock(&mutex);
}

//entrada escrita
void InicEscr (int id) {
   pthread_mutex_lock(&mutex);
   printf("E[%d] quer escrever\n", id);
   while((leit>0) || (escr>0)) {
     pthread_cond_wait(&cond_escr, &mutex);
   }
   pthread_mutex_unlock(&mutex);
}

//saida escrita
void FimEscr (int id) {
   pthread_mutex_lock(&mutex);
   printf("E[%d] terminou de escrever\n", id);
   escr--;
   pthread_cond_signal(&cond_escr);
   pthread_cond_broadcast(&cond_leit);
   pthread_mutex_unlock(&mutex);
}

//thread leitora
void * leitor (void * arg) {
  int *id = (int *) arg;
  while(1) {
    InicLeit(*id);
    // Lê a variavel X e imprime se é par ou impar
    printf("Leitora %d esta lendo\n", *id);
    if((x%2)==0){printf("Leitora %d, encontrou X = %d, X e par \n",*id,x); }else if((x%2)!=0){printf("Leitora %d, encontrou X = %d, X e impar\n",*id,x);} 
    FimLeit(*id);
    sleep(1);
  } 
  free(arg);
  pthread_exit(NULL);
}

//thread escritora
void * escritor (void * arg) {
  int *id = (int *) arg;
  while(1) {
    InicEscr(*id);
    // Incrementando valor 1 em X
    printf("Escritora %d esta escrevendo\n", *id);
    x++;
    printf("Escritora %d incrementou 1 em X\n", *id);
    FimEscr(*id);
    sleep(1);
  } 
  free(arg);
  pthread_exit(NULL);
}

//thread leitora escritora
void * leitorescritor (void * arg) {
  int *id = (int *) arg;
  while(1) {
    int boba1, boba2;

    // Lê a variavel X e imprime na tela
    InicLeit(*id);
    printf("Leitora Escritora %d esta lendo\n", *id);
    printf("Leitora Escritora %d, encontrou X = %d \n", *id,x);
    FimLeit(*id);

    /* faz alguma coisa inutil pra gastar tempo... */

    boba1=10000; boba2=-10000; while (boba2 < boba1) boba2++;

    // Incrementando valor do indentificador em X
    InicEscr(*id);
    printf("Leitora Escritora %d esta escrevendo\n", *id);
    x+=*id;
    printf("Leitora Escritora %d incrementou %d em X\n", *id,*id);
    FimEscr(*id);
    sleep(1);
  } 
  free(arg);
  pthread_exit(NULL);
}

//funcao principal
int main(void) {
  //identificadores das threads
  pthread_t tid[L+E+LE];
  int id[L+E+LE];

  //inicializa as variaveis de sincronizacao
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond_leit, NULL);
  pthread_cond_init(&cond_escr, NULL);

    //cria as threads leitoras
  for(int i=0; i<L; i++) {
    id[i] = i+1;
    if(pthread_create(&tid[i], NULL, leitor, (void *) &id[i])) exit(-1);
  } 

  //cria as threads escritoras
  for(int i=0; i<E; i++) {
    id[i+L] = i+1;
    if(pthread_create(&tid[i+L], NULL, escritor, (void *) &id[i+L])) exit(-1);
  } 
  //cria as threads leitorasescritoras
  for(int i=0; i<LE; i++) {
    id[i+L+LE] = i+1;
    if(pthread_create(&tid[i+L], NULL, leitorescritor, (void *) &id[i+L])) exit(-1);
  } 
  pthread_exit(NULL);
  return 0;
}