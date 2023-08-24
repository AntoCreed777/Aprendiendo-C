/*Escriba la funci ́on void traspuesta(int n, int m, int M[n][m], int T[m][n]) que reciba la matriz M
de n filas y m columnas, y compute su traspuesta, la cual ser ́a almacenada en la matriz T */

#include <stdio.h>

void traspuesta(int n, int m, int M[n][m], int T[m][n]){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            T[j][i]=M[i][j];
        }
     }
}

int main(){
    int n;
    int m;
    //Asignacion de las filas y columnas
    printf("Escriba el numero de filas de su matriz: ");
    scanf("%d",&n);
    printf("Escriba el numero de columnas de su matriz: ");
    scanf("%d",&m);
    //Creacion de las matrices
    int M[n][m];
    int T[m][n];
    //Asignacion de valores a la matriz inicial
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("Ingrese el valor de la fila %d y columna %d: ",i+1,j+1);
            int aux;
            scanf("%d",&aux);
            M[i][j]=aux;
        }
    }

    traspuesta(n,m,M,T);
    //Impresion de la matriz resultante
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%d\t",T[i][j]);
        }
        printf("\n");
    }

    return 0;
}