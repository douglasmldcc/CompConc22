/* Disciplina: Computacao Concorrente */
/* Nome.: Douglas de Morais Lima  */
/* Laboratório: 5 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  3

pthread_mutex_t x_mutex;
pthread_cond_t x_cond, y_cond;
int x = 0;


/* Threads 4 */
void* A (void* t){
    printf(" Seja bem-vindo!\n");

    pthread_mutex_lock(&x_mutex);
    x++;
    pthread_cond_broadcast(&y_cond);
    pthread_mutex_unlock(&x_mutex);
    pthread_exit(NULL);

}
/* Threads 2 */
void* B (void* t){
    pthread_mutex_lock(&x_mutex);
    while(x < 1){
        pthread_cond_wait(&y_cond, &x_mutex);
    }
    x++;
    printf(" Fique a vontade!\n");
    pthread_cond_signal(&x_cond);
    pthread_mutex_unlock(&x_mutex);
    pthread_exit(NULL);
}
/* Threads 3 */
void* C (void* t){
    pthread_mutex_lock(&x_mutex);
    while(x < 1){
        pthread_cond_wait(&y_cond, &x_mutex);
    }
    x++;
    printf(" Sente-se por favor.\n");
    pthread_cond_signal(&x_cond);
    pthread_mutex_unlock(&x_mutex);
    pthread_exit(NULL);
}
/* Threads 1 */
void* D (void* t){
    pthread_mutex_lock(&x_mutex);
    while(x<3){
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf(" Volte sempre!\n");
    pthread_mutex_unlock(&x_mutex);
    pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[NTHREADS];

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);    
  pthread_cond_init(&y_cond, NULL);

  /* Cria as threads */
  pthread_create(&threads[3], NULL, A, NULL);
  pthread_create(&threads[2], NULL, B, NULL);
  pthread_create(&threads[1], NULL, C, NULL);
  pthread_create(&threads[0], NULL, D, NULL);

  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("\nFIM\n");

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);
  pthread_cond_destroy(&y_cond);

}