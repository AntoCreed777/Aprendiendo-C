/*Escriba un programa que pida dos n ́umeros enteros n e y, e imprima el resultado de las funciones f (1), f (2), f (3),
. . ., f (n), donde f (x) se define de la siguiente forma:
f (x) =
y2 + 15 si 0 < x ≤ 15
y3 − y2 + 12 si 15 < x ≤ 30
4y3/y2 + 8 si 30 < x ≤ 60
0 si en otro caso*/

#include <stdio.h>
#include <math.h>

void ingreso(char mensaje[],int *a){
    printf("%s",mensaje);
    scanf("%d",a);
}

void funcion(int n,int y){
    int caso1= pow(y,2) + 15;
    int caso2= (pow(y,3)-pow(y,2)+12);
    int caso3= (4*pow(y,3)/pow(y,2))+8;

    for (int i=1;i<=n;i++){
        if (i<=15){
            printf ("%d\n",caso1);
        }
        else if (i>15 && i<=30){
            printf ("%d\n",caso2);
        }
        else if (i>30 && i<=60){
            printf ("%d\n",caso3);
        }
        else{
            printf("0\n");
        }
    }
}

int main(){
    int n,y;
    ingreso("Ingrese el numero que modifica la funcion: ",&y);
    ingreso("Ingrese el numero a evaluar en la funcion: ",&n);
    funcion(n,y);

    return 0;
}