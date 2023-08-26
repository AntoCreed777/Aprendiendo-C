/*Escriba un programa que pida un número entero n e imprima su representación en notación binaria.
En el caso de ingresar un número negativo, use notación complemento dos.*/

#include <stdio.h>
#include<stdlib.h>

int main(){
    //Declaracion
    int numero,binario[8]={0,0,0,0,0,0,0,0};
    //Asignacion
    printf("Ingrese su numero: ");
    scanf("%d",&numero);
    if(numero>127 || numero <-128){
        printf("Numero fuera de rango(1 byte)");
        exit(0);
    }
    //Conversion
    if(numero>=0){
        int numero2=numero;
        int cursor=7;
        while (numero2!=0){
            binario[cursor]=numero2%2;
            numero2=numero2/2;
            cursor-=1;
        }
    }
    else{
        int numero2=-numero;
        int cursor=7;

        //Conversion normal
        while (numero2!=0){
            binario[cursor]=numero2%2;
            numero2=numero2/2;
            cursor-=1;
        }

        //Intercambio de 1 por 0 y 0 por 1
        for(int i=0;i<8;i++){
            if(binario[i]==1){
                binario[i]=0;
            }
            else{
                binario[i]=1;
            }
        }

        //Suma 1
        for(int i=7;i>=0;i--){
            if(binario[i]==1){
                binario[i]=0;
            }
            else{
                binario[i]=1;
                break;
            }
        }
    }

    //Entrega de resultado
    printf("El numero %d en binario es ",numero);
    for (int i=0;i<8;i++){
        printf("%d",binario[i]);
    }
    return 0;
}