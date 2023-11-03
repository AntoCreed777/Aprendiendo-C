#include "utils_matriz.h"

#include <stdio.h>
#include <stdlib.h>

#define fila 3
#define columna 4


int main(){
    int **m=(int**)malloc(sizeof(int*)*fila);
    for(int i=0;i<fila;i++){
        m[i]=(int*)malloc(sizeof(int)*columna);
    }
    for(int i=0;i<fila;i++){
        for(int j=0;j<columna;j++){
            m[i][j]=i+j;
        }
    }
    imprime_matriz(m,fila,columna);
    return 0;
}