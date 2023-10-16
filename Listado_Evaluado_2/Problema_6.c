#include <stdio.h>

int main(){
    int n;
    printf("Introdusca un numero de este rango[0,255]:  ");
    while(scanf("%d",&n)!=1 || n<0 || n>255){   //Ingreso del numero
        printf("Error de entrada\n\nIntrodusca un numero de este rango[0,255]:  : ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la  entrada para eliminar caracteres no válidos
    }

    printf("Para %d: caracter '%c', entero sin signo %u, octal %o y hexadecimal %x",n,n,n,n,n);
    return 0;
}