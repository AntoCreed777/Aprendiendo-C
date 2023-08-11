/*Escriba un programa que pida dos n ́umeros enteros m y n, e imprima el resultado de la combinatoria */

#include<stdio.h>

void ingreso(char mensaje[],int *a){
    printf("%s",mensaje);
    scanf("%d",a);
}
int factorial(unsigned int numero){
    unsigned int resultado=1;
    for (int i=1;i<=numero;i++){
        resultado*=i;
    }
    return resultado;
}

int main(){
    unsigned int n;
    unsigned int k;
    ingreso("Ingrese el n de su Combinatoria: ",&n);
    ingreso("Ingrese el k de su Combinatoria: ",&k);
    unsigned int resultado= factorial(n)/((factorial(k))*factorial(n-k));
    printf("\nEl resultado de la combinatoria con \"n\" = %d y \"k\" = %d es %d",n,k,resultado);
    return 0;
}