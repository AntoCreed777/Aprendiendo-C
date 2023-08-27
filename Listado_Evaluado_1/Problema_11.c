#include <stdio.h>
#include<stdlib.h>

int main(){
    //Ingreso
    int n;
    printf("Ingrese la cantidad de notas: ");
    scanf("%d",&n);
    while(n<1 || n>10){
        printf("Debe estar entre 1 y 10\nIngrese la cantidad de notas: ");
        scanf("%d",&n);
    }

    //Declaracion de variables
    int *notas;
    notas=(int*)malloc(sizeof(int)*n);
    int aux=0;

    //Ingreso de las notas
    for(int i=0;i<n;i++){
        printf("Ingrese la nota numero %d: ",i+1);
        scanf("%d",&aux);
        while(aux<3 || aux>5){
            printf("La nota debe estar entre 3 y 5\nIngrese la nota numero %d: ",i+1);
            scanf("%d",&aux);
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
        printf("Ninguno");
    }
    else if(media==5){
        printf("Nombrado");
    }
    else if(media>=4.5){
        printf("Alto");
    }
    else{
        printf("Comun");
    }

    return 0;
}