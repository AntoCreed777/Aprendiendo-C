/*Escriba un programa que pida un n ́umero entero n, que luego genere dos arreglos ordenados de largo n, A y B, con
valores al azar, y finalmente genere un arreglo ordenado C que sea el resultante de la uni ́on de A y B.
Por ejemplo, si los arreglos generados son A = [1, 5, 9, 15] y B = [0, 6, 7, 8], el programa debe generar el arreglo
C = [0, 1, 5, 6, 7, 8, 9, 15]*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void ingreso(char mensaje[],int *a){
    printf("%s",mensaje);
    scanf("%d",a);
}

int main(){
    //Ingreso del tamaño de los arreglos
    int largo;
    ingreso("Ingrese el largo de sus areglos: ",&largo);

    //Creacion de los arreglos
    int *arregloA;
    int *arregloB;
    arregloA=(int*)malloc(sizeof(int)*largo);
    arregloB=(int*)malloc(sizeof(int)*largo);

    //Inicializo el Randomizador
    srand(time(NULL));

    //Asignacion de los valores random a los Arreglos
    printf("El arreglo A es: ");
    for (int i=0;i<=largo-1;i++){
        arregloA[i]=rand();
        printf("%d\t",arregloA[i]);
    }

    printf("\n\nEl arreglo B es: ");
    for (int i=0;i<=largo-1;i++){
        arregloB[i]=rand();
        printf("%d\t",arregloB[i]);
    }

    //Creacion del arreglo final
    int *arregloC;
    arregloC=(int*)malloc(sizeof(int)*largo*2);

    //Asignacion de los valores al arreglo C
    int posicion;
    int largoA=largo;
    int largoB=largo;
    for (int j=0;j<=largo*2-1;j++){
        char arreglo='A';
        int aux=INFINITY;
        for (int i=0;i<(largoA);i++){
            if (aux>arregloA[i]){
                aux=arregloA[i];
                posicion=i;
            }
        }
        for (int i=0;i<(largoB);i++){
            if (aux>arregloB[i]){
                aux=arregloB[i];
                posicion=i;
                arreglo='B';
            }
        }
        if(arreglo=='A'){
            for (int i=posicion;i<=largoA-1;i++){
                arregloA[i]=arregloA[i+1];
            }
            largoA--;
        }
        if(arreglo=='B'){
            for (int i=posicion;i<=largoB-1;i++){
                arregloB[i]=arregloB[i+1];
            }
            largoB--;
        }
        arregloC[j]=aux;
    }

    //Mostramos el arreglo resultante
    printf("\n\nEl arreglo resultante es: ");
    for(int i=0;i<=largo*2-1;i++){
        printf("%d\t",arregloC[i]);
    }

    return 0;
}