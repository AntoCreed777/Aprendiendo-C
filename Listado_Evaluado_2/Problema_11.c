#include <stdio.h>
#include <stdlib.h>

void diagonal(int n,int **matriz,int posicionx,int posiciony,int *contador){    //Funcion que asigna los numeros a la matriz a traves de sus diagonales
    int x=posicionx;                //Se asigna el valor de la posicion inicial en x a la variable x (Columnas)
    int y=posiciony;                //Se asigna el valor de la posicion inicial en y a la variable y (Filas)
    while(x<n && y<n){              //Mientra no se salga de la matriz
        matriz[y][x]=(*contador);   //Se asigna el numero del contador a la matriz
        (*contador)++;              //Se aumnenta el contador
        x++;                        //Se aumenta la coordenada en x (Columnas)
        y++;                        //Se aumenta la coordenada en y (Filas)
    }
}

int main(){
    //Declaracion e ingreso de n, que almacena el tamano del lado del cuadrado
    int n;
    //printf("Ingrese el tamano del tablero de NxN:   ");
    while(scanf("%d",&n)!=1 || n<1 || n>100){   //Ingreso de n y validacion
        //printf("Error de entrada\n\nIntrodusca la cantidad de numeros que va a ingresar (debe ser mayor a 0):  ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la  entrada para eliminar caracteres no válidos
    }

    //Se declara la matriz que guardara los numeros como pide el ejercicio
    int **matriz=(int**)malloc(sizeof(int*)*n); 
    for(int i=0;i<n;i++){
        matriz[i]=(int*)malloc(sizeof(int)*n);
    }

    int contador=1; //Se declara al contador que se usara para asignar valores a la matriz

    int j=0;        //Declaro la variale que recorrera las filas
    for(int i=n-1;i>=0;i--){    //Ciclo que recorre las columnas
        if(i==0){   //Si se llega a la primera columnas se comienza vajar por las filas
            for(int j=0;j<n;j++){   //Se recorren las filas de la primera columna
                diagonal(n,matriz,i,j,&contador);
            }
        }else{
            diagonal(n,matriz,i,j,&contador);
        }
    }

    //printf("\n");
    for(int i=0;i<n;i++){   //Se imprime la matriz resultante
        for(int j=0;j<n;j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }

    //Se libera la memoria usada por la matriz
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }

    free(matriz);

    return 0;
}