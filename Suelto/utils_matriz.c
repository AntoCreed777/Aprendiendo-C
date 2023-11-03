#include "utils_matriz.h"

#include <stdio.h>

void imprime_matriz(int **matriz,int filas,int columnas){
    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            printf("%d\t",matriz[i*columnas+j]);
        }
        printf("\n");
    }
}