#include <stdio.h>
#include <string.h>
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
    //Declaracion de variables
    int n,m;

    //Ingreso de n que guardara la cantidad de strings que ingresaran
    ingreso("Ingrese la cantidad de Cadenas de Caracteres:   ",&n);
    while(n<=0){
        ingreso("Debe ser un numero mayor a 0\nIngrese la cantidad de Cadenas de Caracteres: ",&n);
    }

    //Ingreso de m que guardara la cantidad de letras que se guardaran de cada String
    ingreso("Ingrese la cantidad de Letras a copiar:   ",&m);
    while(m<=0){
        ingreso("Debe ser un numero mayor a 0\nIngrese la cantidad de Letras a copiar: ",&m);
    }

    char ingreso[20];   //Declaracion de la variable que guardara a las palabras que ingresen
    
    //Declaracion de la variable que guardara la concatenacion de las primeras m letras de las n palabras
    char *resultado=(char*)malloc(sizeof(char)*n*m);

    //Relleno con 0 para que no tenga valores aleatorios almacenados
    for(int i=0;i<m*n;i++){
        resultado[i]=0;
    }

    //Ingresan las palabras y las concateno de inmediato
    for(int i=0;i<n;i++){
        printf("Ingrese la palabra numero %d:   ",i+1);
        scanf("%s",ingreso);
        strncat(resultado,ingreso,m);
    }

    //Imprimo el resultado de inmediato
    printf("%s",resultado);

    free(resultado);

    return 0;
}