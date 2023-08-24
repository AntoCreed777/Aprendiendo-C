/*Escriba un programa que pida una cadena de caracteres y que reporte la cantidad de caracteres en may ́uscula,
min ́uscula, d ́ıgitos y espacios. Note que la cadena a ingresar debe permitir espacios.*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    char *cadena=NULL;
    int longitud=0;
    int capacidad=0;
    char caracter;

    //Ingreso de datos en una cadena de caracteres dinamico
    while((caracter=getchar())!='\n'){
        if (longitud>=capacidad){
            capacidad+=10;
            cadena=(char*)realloc(cadena,sizeof(char)*capacidad);
        }
        cadena[longitud]=caracter;
        longitud++;
    }
    int mayuscula=0;
    int minuscula=0;
    int digitos=0;
    int espacios=0;
    for(int i=0;i<longitud;i++){
        if(cadena[i]>=48 && cadena[i]<=57){
            digitos+=1;
        }
        if(cadena[i]>=65 && cadena[i]<=90){
            mayuscula+=1;
        }
        if(cadena[i]>=97 && cadena[i]<=122){
            minuscula+=1;
        }
        if(cadena[i]==32){
            espacios+=1;
        }
    }
    printf("Hay %d mayusculas, %d minusculas, %d digitos y %d espacios",mayuscula,minuscula,digitos,espacios);

    /*
    //Impresion de la cadena
    for(int i=0;i<longitud;i++){
        printf("%c",cadena[i]);
    }
    */
    return 0;
}