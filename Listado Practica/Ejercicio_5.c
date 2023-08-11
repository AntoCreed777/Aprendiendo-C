/*Escriba un programa que pida 3 coordenadas (x, y) e imprima “contenido” si la tercera coordenada est ́a contenida en
el rect ́angulo delimitado por las primeras dos coordenadas. En caso contrario, imprima “no contenido”   */

#include <stdio.h>

void ingreso(char mensaje[],int *a){
    printf("%s",mensaje);
    scanf("%d",a);
}

int main(){
    int x;
    int y;
    ingreso("Ingrese la Coordenada x delimitadora: ",&x);
    ingreso("Ingrese la Coordenada y delimitadora: ",&y);

    int a;
    int b;
    ingreso("Ingrese la Coordenada x de su consulta: ",&a);
    ingreso("Ingrese la Coordenada y de su consulta: ",&b);

    (a>x || b>y || a<0 || b<0)?printf("No esta contenida"):printf("Esta contenida");

    return 0;
}