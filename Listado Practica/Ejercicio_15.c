/*Escriba la funci ́on int ortogonal(int n, int m, int M[n][m]) que reciba la matriz M de n filas y m
columnas, y retorne 1 si la matriz M es ortogonal y 0 en caso contrario. Para responder esta pregunta debe utilizar
las funciones resultantes de las preguntas 12, 13 y 14.
Nota: Una matriz cuadrada A es ortogonal si se cumple A × AT = I, donde AT es la matriz traspuesta de A e I es
la matriz identidad*/

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


void mult(int n, int m, int M[n][m], int R[n][m]){
    for(int i=0;i<n;i++){   //Recorro las filas de M
        for(int k=0;k<m;k++){   //Recorro las filas de transpuesta
            int aux=0;
            for(int j=0;j<m;j++){   //Recorro las columnas de M y transpuesta
                aux+=M[i][j]*M[k][j];
            }
            R[i][k]=aux;
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
    if (n!=m){
        printf("Solo las matrices cuadradas pueden ser una matriz identidad");
        return 0;
    }
    int M[n][m];
    int R[n][m];
    //Asignacion de valores a la matriz M
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("Ingrese el valor de la fila %d y columna %d de la Primera Matriz: ",i+1,j+1);
            int aux;
            scanf("%d",&aux);
            M[i][j]=aux;
        }
    }
    mult(n, m,M, R);

    if(identidad(n, m, R)==1){
        printf("Es ortogonal");
    }
    else{
        printf("No es ortogonal");
    }
    
    return 0;
}