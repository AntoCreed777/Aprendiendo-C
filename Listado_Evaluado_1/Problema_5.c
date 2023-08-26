/*Observe el siguiente patrón de impresión de 8 niveles.
Escriba un programa que pida un número entero n e imprima el mismo patrón con n niveles.

########
   +++++++
    ######
     +++++
      ####
       +++
        ##
         +
*/


#include<stdio.h>

void ingreso(int *a){
    printf("Ingrese el numero de niveles: ");
    scanf("%d",a);
}

int main(){
    int numero;
    ingreso(&numero);

    int aux=1;
    for (int i=0;i<=numero;i++){
        for (int k = 0; k < aux; k++)
        {
            printf(" ");
        }
        
        if (i%2!=1){
            for (int j=1;j<=numero-i;j++){
                printf("#");
            }
            printf("\n");
        }
        else{
            for (int j=1;j<=numero-i;j++){
                printf("+");
            }
            printf("\n");
        }
        aux+=1;
    }
    return 0;
}