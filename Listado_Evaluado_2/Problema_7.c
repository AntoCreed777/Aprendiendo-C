#include <stdio.h>

int main(){
    //Declaracion e ingreso de n, que guarda la cantidad de numeros que van a ingresar
    int n;
    printf("Introdusca la cantidad de numeros que va a ingresar (debe ser mayor a 0):  ");
    while(scanf("%d",&n)!=1 || n<=0){   //Ingreso del numero
        printf("Error de entrada\n\nIntrodusca la cantidad de numeros que va a ingresar (debe ser mayor a 0):  ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la  entrada para eliminar caracteres no válidos
    }

    float flotante;     //Variable que almacenara las entradas
    float suma=0;   //Variable que almacenara la suma de las entradas;
    int entero;     //Variable que almacenara la parte entera de los numeros ingresados
    
    for(int i=0;i<n;i++){   //Ciclo en que se ingresa y se suma las entradas
        printf("Introdusca un numero real:  ");
        while(scanf("%f",&flotante)!=1){   //Ingreso del numero
            printf("Error de entrada\n\nIntrodusca un numero real:  ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la  entrada para eliminar caracteres no válidos
        }

        entero=flotante;    //Se extrae la parte entera dedl numero
        flotante-=entero;   //Se le resta la parte entera para solo tener la parte decimal
        suma+=flotante; //Se suma ls parte decimal de los ingresos
    }

    printf("La suma de la parte decimal de los numeros ingresados es %f",suma); //Se imprime el resultado

    return 0;
}