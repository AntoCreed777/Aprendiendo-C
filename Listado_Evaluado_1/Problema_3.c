/*Escriba un programa que pida dos números enteros m y n, a continuación pida ingresar n números enteros
para luego imprimir los números ingresados que sean mayores a m.*/

#include<stdio.h>
#include <stdlib.h>

int main(){
    int m,n;
    printf("Ingrese la cantidad de numeros que entregara: ");
    scanf("%d",&n);
    int *guardado=NULL;
    guardado=(int*)malloc(sizeof(int)*n);
    printf("Ingrese el numero minimo: ");
    scanf("%d",&m);
    for(int i=0;i<n;i++){
        int aux;
        printf("Ingrese el numero en la posicion %d: ",i+1);
        scanf("%d",&aux);
        guardado[i]=aux;
    }

    printf("Estos son los numeros mayores a %d:\n\n",m);
    for(int i=0;i<n;i++){
        if(guardado[i]>m){
            printf("%d\t",guardado[i]);
        }
    }

    return 0;
}