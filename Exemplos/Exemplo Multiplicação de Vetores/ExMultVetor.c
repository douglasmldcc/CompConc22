#include<stdio.h>
#include<stdlib.h>

float *mat;
float *vet;
float *saida;

int main(int argc,char*argv[]){
    int dim;
    //leitura e av par
    if(argc<2){
        printf("Digite: %s <dimensao da matriz>\n", argv[0]);
        return 1;
    }
    dim = atoi(argv[1]);
    //malloc
    mat = (float*) malloc(sizeof(float)*dim*dim);
    if(mat==NULL) {printf("ERRO -- malloc\n"); return 2;}
    vet = (float*) malloc(sizeof(float)*dim*dim);
    if(vet==NULL) {printf("ERRO -- malloc\n"); return 2;}
    saida = (float*) malloc(sizeof(float)*dim*dim);
    if(saida==NULL) {printf("ERRO -- malloc\n"); return 2;}
    //init estrut dados
    for(int i=0 ; i<dim; i++){
        for(int j=0 ; j<dim; j++)
            mat[i*dim+j]=1;
        vet[i]=1;
        saida[1]=0;
    }
    //mult matriz por vetor
    for(int i=0 ; i<dim; i++){
        for(int j=0 ; j<dim; j++)
            saida[i]+=mat[i*dim+j]*vet[j];
    }
    //exibe
    
    puts("Matriz de entrada");
    for(int i=0 ; i<dim; i++){
        for(int j=0 ; j<dim; j++)
            printf("%.lf",mat[i*dim+j]);
        puts("");
    }
    puts("Vetor de entrada");
    for(int i=0 ; i<dim; i++){
        printf("%.lf",vet[i]);
    puts("");
    }
    
    puts("Vetor de saida");
    for(int i=0 ; i<dim; i++){
        printf("%.lf",saida[i]);
    puts("");
    }
    
    //libera memoria
    free(mat);
    free(vet);
    free(saida);

    return 0;
}