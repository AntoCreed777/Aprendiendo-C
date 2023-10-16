/*Escriba un programa que pida dos números enteros n y m, para que luego pida ingresar suficientes valores
enteros hasta llenar un arreglo A de largo n. Su programa deberá generar dos arreglos B y C, donde B contendrá
todos los valores del arreglo A que sean menores a m, mientras que C contendrá todos los valores del arreglo A
que sean mayores o iguales a m.*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    
    int N;                                                                  //Declaracion de N que representa el largo de un arreglo y la cantidad de valores que ingresan
    printf("Ingrese la cantidad de numeros que ingresara:   ");             //Mensaje guia para el usuario
    while(scanf("%d",&N)!=1 || N<=0){                                       //Ingreso y validacion del valor N
        printf("Error de entrada\n\nIngrese la cantidad de numeros que ingresara:   "); //Mensaje guia para el usuario
        int c;                                                              //Declaracion de caracter auxiliar
        while ((c = getchar()) != '\n' && c != EOF) {}                      // Limpio la entrada para eliminar caracteres no válidos
    }

    
    int M;                                                                  //Declaracion de M que representa el valor por el cual se ordenaran los demas numeros
    printf("Ingrese el numero delimitador:   ");                            //Mensaje guia para el usuario
    while(scanf("%d",&M)!=1 || M<=0){                                       //Ingreso y validacion del valor M
        printf("Error de entrada\n\nIngrese el numero delimitador:   ");    //Mensaje guia para el usuario
        int c;                                                              //Declaracion de caracter auxiliar
        while ((c = getchar()) != '\n' && c != EOF) {}                      // Limpio la entrada para eliminar caracteres no válidos
    }

    int *A=(int*)malloc(sizeof(int)*N);                                     //Creacion y llenado de la matriz A que guardara los numeros que ingrese el usuario
    int aux;                                                                //Declaracion de una variable auxiliar que guardara de forma momentania los numeros ingresados
    for(int i=0;i<N;i++){
        printf("Ingrese el numero de la posicion %d:   ",i+1);              //Mensaje guia para el usuario
        while(scanf("%d",&aux)!=1 || aux<=0){                               //Ingreso y validacion de los numeros a ordenar
            printf("Error de entrada\n\nIngrese el numero de la posicion %d:   ",i+1);  //Mensaje guia para el usuario
            int c;                                                          //Declaracion de caracter auxiliar
            while ((c = getchar()) != '\n' && c != EOF) {}                  // Limpio la entrada para eliminar caracteres no válidos
        }
        A[i]=aux;                                                           //Asignacion del numero en el arreglo oficial
    }
    
    //Creacion de las matrices B y C

    int *B=(int*)malloc(sizeof(int)*N);
    int *C=(int*)malloc(sizeof(int)*N);

    
    //Declaracion de variables auxiliares que guardaran la longitud de sus respectivos arreglos
    int cantidadB=0;
    int cantidadC=0;

    //Comparo los elementos de A con el numero M para repartirlos entre B o C
    for(int i=0;i<N;i++){
        if(A[i]<M){                     //Si el elemento de A es menos a M entonces se guarda en B
            B[cantidadB]=A[i];
            cantidadB++;                //Se aumenta el contador de elementos de B
        }
        else{                           //Si es Mayor o Menor a M entonces se guarda en C
            C[cantidadC]=A[i];
            cantidadC++;                //Se aumenta el contador de elementos de C
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

    //Liberacion de la memoria asignada con malloc y realloc
    free(A);
    free(B);
    free(C);
    return 0;
}