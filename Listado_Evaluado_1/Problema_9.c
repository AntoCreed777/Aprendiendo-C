/*Escriba un programa que pida un número entero n e imprima el resultado de la serie:*/

#include <stdio.h>
#include <math.h>

int main(){
    //Ingreso
    int n;
    printf("Ingrese el numero del  ultimo denominador de su serie: ");
    scanf("%d",&n);

    //Sumatoria
    float resultado=0;

    /*
    for(int i=1;i<=n;i++){
        resultado+=pow(i,-1);
    }*/

    for(float i=1;i<=n;i++){
        resultado+=1/i;
    }

    //Impresion del resultado
    printf("%f",resultado);
    return 0;
}