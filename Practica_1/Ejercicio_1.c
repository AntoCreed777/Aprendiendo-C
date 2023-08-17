#include <stdio.h>

int main(){
    int largo,ancho;
    printf("Ingrese el largo de su figura: ");
    scanf("%d",&largo);
    printf("Ingrese el ancho de su figura: ");
    scanf("%d",&ancho);
    int resultado=largo*ancho;
    printf("El area de su figura es %d",resultado);
    return 0;
}