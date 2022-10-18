#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void BBP(int k){
    float bbpk = (4/(8*k+1))-(2/(8*k+4))-(1/(8*k+5))-(1/(8*k+6));
    float bbp = bbpk*(1/(powf(16,k)));
    
    return bbp;
}

int main(int argc,char argv[]){
    float sum=0;
    int n;

    if(argc < 2) {
        fprintf(stderr, "Digite: %s <linhas>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);


}