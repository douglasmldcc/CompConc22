#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int main(int argc, char*argv[]){
    int n;

    if(argc < 2) {
        fprintf(stderr, "Digite: %s <casas decimais>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    double pi;


    for(double k =0;k<500000;k++){
        pi +=((1/pow(16,k))*(4/(8*k+1)-  2/(8*k+4)-  1/(8*k+5)-  1/(8*k+6)) );
    }

    printf("%.*f\n", n, pi);
    return 0;
}
    