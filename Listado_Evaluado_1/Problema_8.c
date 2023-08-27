/*Escriba un programa que pida dos números enteros m y n, e imprima el rango [1..n] módulo m.
Ejemplo:
Para m=7 y n=9, la respuesta es 1 2 3 4 5 6 0 1 2
Para m=2 y n=15, la respuesta es 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1*/

#include <stdio.h>

int main(){
    //Declaracion e ingreso de datos
    int m,n;
    printf("Ingrese el numero que indicara el modulo: ");
    scanf("%d",&m);
    printf("Ingrese el numero que indicara el rango: ");
    scanf("%d",&n);

    //Impresion de los resultados
    for(int i=1;i<=n;i++){
        printf("%d\t",i%m);
    }
    return 0;
}