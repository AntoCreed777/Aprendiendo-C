/*Escriba la funci ́on void mult(int n, int m, int l, int M[n][m], int T[m][l], int R[n][l]), la
cual computar ́a la multiplicaci ́on de las matrices M y T . La matriz resultante quedar ́a almacenada en la matriz R*/

#include <stdio.h>

void mult(int n, int m, int l, int M[n][m], int T[m][l], int R[n][l]){
    int transpuesta[l][m];
    for(int i=0;i<m;i++){
        for(int j=0;j<l;j++){
            transpuesta[j][i]=T[i][j];
        }
    }

    for(int i=0;i<n;i++){   //Recorro las filas de M
        for(int k=0;k<l;k++){   //Recorro las filas de transpuesta
            int aux=0;
            for(int j=0;j<m;j++){   //Recorro las columnas de M y transpuesta
                aux+=M[i][j]*transpuesta[k][j];
            }
            R[i][k]=aux;
        }
    }

}

int main(){
    int n;
    int m;
    int l;
    //Asignacion de las filas y columnas
    printf("Escriba el numero de filas de su Primera matriz: ");
    scanf("%d",&n);
    printf("Escriba el numero de columnas de su Primera matriz y filas de la Segunda: ");
    scanf("%d",&m);
    printf("Escriba el numero de columnas Segunda Matriz: ");
    scanf("%d",&l);
    //Creacion de las matrices
    int M[n][m];
    int T[m][l];
    int R[n][l];
    //Asignacion de valores a la matriz M
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("Ingrese el valor de la fila %d y columna %d de la Primera Matriz: ",i+1,j+1);
            int aux;
            scanf("%d",&aux);
            M[i][j]=aux;
        }
    }
    //Asignacion de valores a la matriz T
    for(int i=0;i<m;i++){
        for(int j=0;j<l;j++){
            printf("Ingrese el valor de la fila %d y columna %d de la Segunda Matriz: ",i+1,j+1);
            int aux;
            scanf("%d",&aux);
            T[i][j]=aux;
        }
    }

    mult(n, m, l, M, T, R);

    //Impresion de la matriz resultante
    printf("Esta es la matriz resultante: \n");
    for(int i=0;i<n;i++){
        for(int j=0;j<l;j++){
            printf("%d\t",R[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}