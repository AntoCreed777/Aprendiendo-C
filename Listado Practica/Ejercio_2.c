/*Observe el siguiente patr ́on de impresi ́on de 8 niveles. Escriba un programa que pida un n ́umero entero n e imprima
el mismo patr ́on on n niveles.
#
++
###
++++
#####
++++++
#######
++++++++*/

#include<stdio.h>

void ingreso(int *a){
    printf("Ingrese el numero de niveles: ");
    scanf("%d",a);
}

int main(){
    int numero;
    ingreso(&numero);
    for (int i=1;i<=numero;i++){
        if (i%2!=0){
            for (int j=1;j<=i;j++){
                printf("#");
            }
            printf("\n");
        }
        else{
            for (int j=1;j<=i;j++){
                printf("+");
            }
            printf("\n");
        }
    }
    return 0;
}