#include <stdio.h>

int main(){
    int n;
    printf("Introdusca un numero mayor a 0:  ");
    scanf("%d",&n);
    while(n<=0){
        printf("\nNumero Invalido\nIntrodusca un numero mayor a 0:  ");
        scanf("%d",&n);
    }

    float flotante;
    float suma=0;
    int entero;
    for(int i=0;i<n;i++){
        printf("Introdusca un numero:  ");
        scanf("%f",&flotante);
        entero=flotante;
        flotante-=entero;
        suma+=flotante;
    }

    printf("La suma de la parte decimal de los numeros ingresados es %f",suma);

    return 0;
}