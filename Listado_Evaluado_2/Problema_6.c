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
    int n;
    ingreso("Introdusca un numero de este rango[0,255]:  ",&n);
    while(n<0 || n>255){
        ingreso("\nNumero Invalido\nIntrodusca un numero de este rango[0,255]:  ",&n);
    }

    printf("Para %d: caracter '%c', entero sin signo %u, octal %o y hexadecimal %x",n,n,n,n,n);
    return 0;
}