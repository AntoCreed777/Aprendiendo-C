#include <stdio.h>
#include <stdlib.h>

int main(){
    //Ingreso y validacion del valor N
    int N;
    printf("Ingrese la cantidad de numeros que ingresara:   "); 
    while(scanf("%d",&N)!=1 || N<=0){
        printf("Error de entrada\n\nIngrese la cantidad de numeros que ingresara:   ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la  entrada para eliminar caracteres no válidos
    }

    //Ingreso y validacion del valor M
    int M;
    printf("Ingrese el numero delimitador:   ");
    while(scanf("%d",&M)!=1 || M<=0){
        printf("Error de entrada\n\nIngrese el numero delimitador:   ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la  entrada para eliminar caracteres no válidos
    }

    //Creacion y llenado de la matriz A que guardara los numeros que ingrese el usuario

    int *A=(int*)malloc(sizeof(int)*N);
    int aux;
    for(int i=0;i<N;i++){
        printf("Ingrese el numero de la posicion %d:   ",i+1);
        while(scanf("%d",&aux)!=1 || aux<=0){
            printf("Error de entrada\n\nIngrese el numero de la posicion %d:   ",i+1);
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la  entrada para eliminar caracteres no válidos
        }
        A[i]=aux;
    }
    
    //Creacion de las matrices B yC

    int *B=(int*)malloc(sizeof(int)*N);
    int *C=(int*)malloc(sizeof(int)*N);

    //Comparo los elementos de A con el numero M para repartirlos entre B o C
    
    int cantidadB=0;
    int cantidadC=0;
    for(int i=0;i<N;i++){
        if(A[i]<M){
            B[cantidadB]=A[i];
            cantidadB++;
        }
        else{
            C[cantidadC]=A[i];
            cantidadC++;
        }
    }

    //Reduccion de los arreglos B y C segun la cantidad de elementos que poseen

    B=(int*)realloc(B,sizeof(int)*cantidadB);
    C=(int*)realloc(C,sizeof(int)*cantidadC);

    //Impresion de las matrices resultantes
    printf("Matriz A\n");
    for(int i=0;i<N;i++){
        printf("%d\t",A[i]);
    }

    printf("\n\nMatriz B\n");
    for(int i=0;i<cantidadB;i++){
        printf("%d\t",B[i]);
    }    

    printf("\n\nMatriz C\n");
    for(int i=0;i<cantidadC;i++){
        printf("%d\t",C[i]);
    }

    free(A);
    free(B);
    free(C);
    return 0;
}