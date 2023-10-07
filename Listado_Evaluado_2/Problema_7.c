#include <stdio.h>

int main(){
    //Declaracion e ingreso de n, que guarda la cantidad de numeros que van a ingresar
    int n;
    printf("Introdusca un numero mayor a 0:  ");
    scanf("%d",&n);
    while(n<=0){    //Validacion de que n sea una entrada valida
        printf("\nNumero Invalido\nIntrodusca un numero mayor a 0:  ");
        scanf("%d",&n);
    }

    float flotante;     //Variable que almacenara las entradas
    float suma=0;   //Variable que almacenara la suma de las entradas;
    int entero;     //Variable que almacenara la parte entera de los numeros ingresados
    
    for(int i=0;i<n;i++){   //Ciclo en que se ingresa y se suma las entradas
        printf("Introdusca un numero:  ");
        scanf("%f",&flotante);
        entero=flotante;    //Se extrae la parte entera dedl numero
        flotante-=entero;   //Se le resta la parte entera para solo tener la parte decimal
        suma+=flotante; //Se suma ls parte decimal de los ingresos
    }

    printf("La suma de la parte decimal de los numeros ingresados es %f",suma); //Se imprime el resultado

    return 0;
}