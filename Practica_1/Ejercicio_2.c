#include <stdio.h>

int main(){
    while(1){
        int caracter;
        printf("Ingrese su caracter en numero: ");
        scanf("%d",&caracter);
        if (caracter==0){
            break;
        }
        char letra=caracter+96;
        printf("%c\n",letra);
    }
    return 0;
}