#include <stdio.h>

void imprime_bits(int x){   //Funcion que imprime los bits del numero ingresado de 

    int mascara=1;  //Variable que se usara para extraer los bits
    int aux[32];    //Variable que se usara para almacenar los bits

    printf("La representacion binaria de %d es :\n\n",x);   //Antes de perder el valor de x imprimo esto para el usuario

    for(int i=0;i<32;i++){  //Ciclo que recorreras los bits de x
        aux[31-i]=mascara&x;    //Extraigo los bits de x y los almaceno en el mismo orden en aux
        x=x>>1;  //Muevo todos los bits un espacio a la derecha
    }

    for(int i=0;i<32;i++){  //Ciclo que se encxarga de imprimir los bots guardados en aux
        printf("%d ",aux[i]);
    }
}

int main(){
    int n;  //Declaracion de variable que registrara el numero que ingrese el usuario
    
    printf("Ingrese un numero negativo perteneciente a este rango [-2147483648,-1]: "); //Mensaje para el usuario
    scanf("%d",&n); //Ingreso del numero
    
    while(n>=0){    //Condicional que valida que el numero cumpla con los requisitos planteados
        printf("\nIngrese un numero negativo perteneciente a este rango [-2147483648,-1]: ");   //Mensaje para el usuario
        scanf("%d",&n);     //Ingreso del numero
    }

    imprime_bits(n);    //Llamada de la funcion que imprimira los bits de n

    return 0;   //Finalizacion del programa
}