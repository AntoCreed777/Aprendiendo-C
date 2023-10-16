/*Escriba un programa que, dado un número entero entre 0 y 255, imprima su representación como:

Caracter
Entero sin signo
Octal
Hexadecimal*/

#include <stdio.h>

int main(){
    int n;                                                                              //Se declara la variable que alamcenara el numero
    printf("Introdusca un numero de este rango[0,255]:  ");                             //Mensaje gia para el usuario
    while(scanf("%d",&n)!=1 || n<0 || n>255){                                           //Ingreso del numero n y se valida que cumpla con las restricciones
        printf("Error de entrada\n\nIntrodusca un numero de este rango[0,255]:  : ");   //Mensaje gia para el usuario
        int c;                                                                          //Declaracion de caracter auxiliar
        while ((c = getchar()) != '\n' && c != EOF) {}                                  // Limpio la  entrada para eliminar caracteres no válidos
    }

    //Se imprime el numero en las distintas formas en que solicita el ejercicio
    printf("Para %d: caracter '%c', entero sin signo %u, octal %o y hexadecimal %x",n,n,n,n,n);
    return 0;
}