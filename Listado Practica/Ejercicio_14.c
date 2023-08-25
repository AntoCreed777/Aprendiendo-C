/*Escriba la funci ́on int identidad(int n, int m, int M[n][m]) que reciba la matriz M de n filas y m
columnas, y retorne 1 si la matriz M es la matriz identidad y 0 en caso contrario*/


#include <stdio.h>

int identidad(int n, int m, int M[n][m]){
    for(int i=0;i<n;i++){
        if (M[i][i]!=1){
            return 0;
        }
        for(int j=0;j<m;j++){
            if (M[i][j]!=0 && i!=j){
                return 0;
            }
        }
    }
    return 1;
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
    if (n!=m){
        printf("Solo las matrices cuadradas pueden ser una matriz identidad");
        return 0;
    }
    int M[n][m];

    //Asignacion de valores a la matriz M
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("Ingrese el valor de la fila %d y columna %d de la Primera Matriz: ",i+1,j+1);
            int aux;
            scanf("%d",&aux);
            M[i][j]=aux;
        }
    }
    if(identidad(n, m, M)==1){
        printf("Es la matriz identidad");
    }
    else{
        printf("No es la matriz identidad");
    }
    
    return 0;
}