//Teste gerando numeros randomicos 

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#define N 5 
#define P rand() % N+1 
#define C rand() % N+1 

int main(void){
    srand(time(NULL));
    printf("%d \n",N);
    printf("%d \n",P);
    printf("%d \n",C);
  
}