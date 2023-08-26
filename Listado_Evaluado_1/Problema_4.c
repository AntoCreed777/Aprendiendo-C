/*Observe el siguiente patrón que usa 8 símbolos '*' por cada uno de los 7 niveles.
Escriba un programa que pida un número entero n e imprima el mismo patrón con n
símbolos '*' por cada uno de los n-1 niveles.

* ****** *
** **** **
*** ** ***
****  ****
*** ** ***
** **** **
* ****** *
*/

#include<stdio.h>

int main(){
    int nivel;
    printf("Ingrese la cantidad de simbolos de la figura: ");
    scanf("%d",&nivel);

    int cursor=1;
    for (int i = 0; i < nivel-1; i++){    //Moverme por las filas
        if(i==nivel/2){
            cursor+=1;
        }
        for (int j = 0; j <= nivel+1; j++){  //Moverme por las columnas
            if (j==0+cursor || j==nivel+1-cursor){
                printf(" ");
            }
            else{
                printf("*");
            }
        }
        printf("\n");
        cursor+=1;
    }

    return 0;
}