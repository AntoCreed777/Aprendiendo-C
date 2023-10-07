#include <stdio.h>

int main(){
    int n;
    printf("Introdusca un numero de este rango[0,255]:  ");
    scanf("%d",&n);
    while(n<0 || n>255){
        printf("\nNumero Invalido\nIntrodusca un numero de este rango[0,255]:  ");
        scanf("%d",&n);
    }

    printf("Para %d: caracter '%c', entero sin signo %u, octal %o y hexadecimal %x",n,n,n,n,n);
    return 0;
}