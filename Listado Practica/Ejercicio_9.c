/*Escriba un programa que pida un n ́umero entero positivo n y que luego pida suficientes n ́umeros que ser ́an almacenados
en una matriz triangular superior de n × n.*/

#include <stdio.h>
#include<stdlib.h>

int main(){

    //Ingreso de el largo de la matriz cuadrada
    int largo;
    printf("Ingrese el ladode su matriz cuadrada: ");
    scanf("%d",&largo);
    //Genero la matriz cuadrada
    int *matrizfinal;
    matrizfinal=(int*)malloc(sizeof(int)*(largo*largo));

    //Asignacion de datos a la matriz
    for (int i=0;i<largo*largo;i++){
        if ((i+1)/largo!=0){
            if (i%largo<(i/largo)){
                matrizfinal[i]=0;
                continue;
            }
        }
        printf("Ingrese el numero en la fila %d y columna %d: ",(i/largo)+1,(i%largo)+1);
        int aux;
        scanf("%d",&aux);
        matrizfinal[i]=aux;
    }

    //Impresion de la matriz
    for (int i=0;i<largo*largo;i++){
        printf("%d\t",matrizfinal[i]);
        if ((i+1)%largo==0){
            printf("\n");
        }
    }
    return 0;
}