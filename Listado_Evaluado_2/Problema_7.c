#include <stdio.h>
#include <stdlib.h>

void ingreso(char mensaje[],int *numero){    //Funcion como el getline que valida que solo ingresen numeros
    int tamal=1;
    char *string=NULL;
    while (tamal==1){ 
        int longitud=0;
        int capacidad=0;
        char caracter;
        printf("%s",mensaje);
        while((caracter=getchar())!='\n'){
            if (longitud>=capacidad){
                capacidad+=2;
                string=(char*)realloc(string,sizeof(char)*capacidad);
            }
            (string)[longitud]=caracter;
            (longitud)++;
        }
        if(string==NULL){
            continue;
        }
        tamal=0;
        for(int i=0;i<longitud;i++){
            if((string)[i]<48 || (string)[i]>57){
                tamal=1;
                printf("Solo se aceptan numeros\n");
                string=NULL;
                break;
            }
        }
    }
    *numero=atoi(string);
    free(string);
}

int main(){
    //Declaracion e ingreso de n, que guarda la cantidad de numeros que van a ingresar
    int n;
    ingreso("Introdusca la cantidad de numeros que va a ingresar (debe ser mayor a 0):  ",&n);
    while(n<=0){    //Validacion de que n sea una entrada valida
        ingreso("\nNumero Invalido\nIntrodusca un numero mayor a 0:  ",&n);
    }

    float flotante;     //Variable que almacenara las entradas
    float suma=0;   //Variable que almacenara la suma de las entradas;
    int entero;     //Variable que almacenara la parte entera de los numeros ingresados
    
    for(int i=0;i<n;i++){   //Ciclo en que se ingresa y se suma las entradas
        printf("Introdusca un numero real:  ");
        scanf("%f",&flotante);
        entero=flotante;    //Se extrae la parte entera dedl numero
        flotante-=entero;   //Se le resta la parte entera para solo tener la parte decimal
        suma+=flotante; //Se suma ls parte decimal de los ingresos
    }

    printf("La suma de la parte decimal de los numeros ingresados es %f",suma); //Se imprime el resultado

    return 0;
}