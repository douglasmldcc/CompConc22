/* Disciplina: Computacao Concorrente */
/* Nome.: Douglas de Morais Lima  */
/* Laboratório: 6 */
/* Codigo: Implementacao de uma aplicacao que usa o padrao leitores/escritores.*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  3

/* Variaveis globais */
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;
