<h1>Laboratório 2</h1>
Implementação sequencial do problema de multiplicação de matrizes com tomada de tempos e  avaliação da possibilidade de ganho de desempenho com uma versão concorrente.</br></br>
Os códigos e vídeo-aulas disponíveis aqui são para orientar o desenvolvimento da solução sequencial (vídeo-aulas 2 e 3) e  como fazer a tomada de tempo interno (vídeo-aula 6). A versão concorrente da multiplicação de matrizes  será desenvolvida no Laboratório 3.</br></br>
O código <geraMatrizBinario.c> é uma programa para gerar matrizes de entrada, com elementos do tipo float, em formato binário.O arquivo de saida possui dois valores do tipo inteiro indicando as dimensoes (linhas e colunas) da matriz, e em seguida a sequencia de valores (float) da matriz. </br></br>
O código <leMatrizBinario.c> é um programa auxiliar para ler uma matriz binaria gerada pelo codigo <geraMatrizBinario.c> e exibi-la na forma de texto (com 6 casas decimais).
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Digite: C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2\geraMatBin.exe <linhas> <colunas> <arquivo saida A> <arquivo saida B>
PS C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2> & .\"geraMatBin.exe" 500 500 500a 500b
PS C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2> & .\"geraMatBin.exe" 500 500 5a 5b    
PS C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2> & .\"geraMatBin.exe" 1000 1000 1a 1b
PS C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2> & .\"multMatBin.exe" 5a 5b

Tempo de inicializacao:0.001357
Tempo de multiplicacao:0.575501
PS C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2> & .\"multMatBin.exe" 5a 5b

Tempo de inicializacao:0.001560
Tempo de multiplicacao:0.579727
PS C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2> & .\"multMatBin.exe" 5a 5b

Tempo de inicializacao:0.000979
Tempo de multiplicacao:0.586294
PS C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2> & .\"multMatBin.exe" 1a 1b

Tempo de inicializacao:0.003853
Tempo de multiplicacao:4.727837
PS C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2> & .\"multMatBin.exe" 1a 1b

Tempo de inicializacao:0.003425
Tempo de multiplicacao:5.177112
PS C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2> & .\"multMatBin.exe" 1a 1b

Tempo de inicializacao:0.004520
Tempo de multiplicacao:4.949570
PS C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2> & .\"multMatBin.exe" 2a 2b

Tempo de inicializacao:0.015299
Tempo de multiplicacao:41.971925
Tempo de finalizacao:0.000000
PS C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2> & .\"multMatBin.exe" 2a 2b

Tempo de inicializacao:0.016180
Tempo de multiplicacao:43.037936
Tempo de finalizacao:0.000000
PS C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2> & .\"multMatBin.exe" 2a 2b

Tempo de inicializacao:0.013123
Tempo de multiplicacao:42.783140
Tempo de finalizacao:0.000000
PS C:\Users\dougl\Documents\UFRJ\CompConc22\Laboratorio 2> & .\"multMatBin.exe" 2a 2b

Tempo de inicializacao:0.013979
Tempo de multiplicacao:42.562890
Tempo de finalizacao:0.000000
