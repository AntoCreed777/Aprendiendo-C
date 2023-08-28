#include <stdio.h>
#include<stdlib.h>


void ingreso(char mensaje[],char **cadena,int *longitud){    //Funcion que valida que solo ingresen numeros
    int tamal=1;
    char caracter;
    while (tamal==1){ 
        *longitud=0;
        int capacidad=0;
        printf("%s",mensaje);
        while((caracter=getchar())!='\n'){
            if (*longitud>=capacidad){
                capacidad+=2;
                *cadena=(char*)realloc(*cadena,sizeof(char)*capacidad);
            }
            (*cadena)[*longitud]=caracter;
            (*longitud)++;
        }
        tamal=0;
        for(int i=0;i<*longitud;i++){
            if((*cadena)[i]<48 || (*cadena)[i]>57){
                tamal=1;
                printf("Solo se aceptan numeros\n\n");
                break;
            }
        }
    }
}

int main(){
    //Ingreso
    char *cadena=NULL;
    int longitud;
    ingreso("Ingrese la cantidad de notas: ",&cadena,&longitud);
    int n=atoi(cadena);

    while(n<1 || n>10){
        free(cadena);
        cadena=NULL;
        ingreso("Debe estar entre 1 y 10\nIngrese la cantidad de notas: ",&cadena,&longitud);
        n=atoi(cadena);
    }

    //Declaracion de variables
    int *notas;
    notas=(int*)malloc(sizeof(int)*n);
    char *auxchar=NULL;
    int longitudauxchar;

    //Ingreso de las notas
    for(int i=0;i<n;i++){
        char mensaje[30];
        sprintf(mensaje, "Ingrese la nota numero %d: ", i + 1);
        ingreso(mensaje,&auxchar,&longitudauxchar);
        int aux=atoi(auxchar);

        while(aux<3 || aux>5){
            printf("La nota debe estar entre 3 y 5\n\n");
            free(auxchar);
            auxchar=NULL;
            ingreso(mensaje,&auxchar,&longitudauxchar);
            aux=atoi(auxchar);
        }
        notas[i]=aux;
    }

    //Una nota satisfactoria corresponde al valor 3
    //Una buena nota corresponde al valor 4
    //Una nota excelente corresponde al valor 5
    //La nota media de un alumno es el valor medio de todas las notas que obtuvo en sus exámenes.

    //Calculo de la media de las notas
    float media=0;
    for(int i=0;i<n;i++){
        media+=notas[i];
    }
    media=media/n;

    //Si no obtiene ninguna beca, “Ninguno”.
    //Si obtiene un resultado académico común “Común”
    //Si obtiene un resultado académico alto “Alto”
    //Si obtiene un resultado personal “Nombrado”.
    if(media<4){
        printf("None");
    }
    else if(media==5){
        printf("Named");
    }
    else if(media>=4.5){
        printf("High");
    }
    else{
        printf("Common");
    }

    return 0;
}