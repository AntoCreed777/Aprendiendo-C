/*Tu tarea es encontrar la suma de todos los números enteros que se encuentran entre 1 y N inclusive.
INPUT
La entrada consta de un único número entero N que no es mayor que 10000 en su valor absoluto.
OUTPUT
Escribe un único número entero que sea la suma de todos los números enteros que se encuentran entre 1 y N inclusive.*/

#include<stdio.h>

int main(){
    //Ingreso
    int n;
    printf("Ingrese un numero: ");
    scanf("%d",&n);
    while(n>10000 || n<-10000){
        printf("El numero debe estar entre 10.000 y -10.000Ingrese un numero: ");
        scanf("%d",&n);
    }

    //Calculo del resultado
    int resultado=0;
    if(n>1){
        for(int i=1;i<=n;i++){
            resultado+=i;
        }
    }
    else{
        for(int i=n;i<=1;i++){
            resultado+=i;
        }
    }

    //Impresion del resultado
    printf("El resultado es %d",resultado);

    return 0;
}