#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    //Declaracion de variables
    int n,m;

    //Ingreso de n que guardara la cantidad de strings que ingresaran
    printf("Ingrese la cantidad de Cadenas de Caracteres:   ");
    scanf("%d",&n);
    while(n<=0){
        printf("Debe ser un numero mayor a 0\nIngrese la cantidad de Cadenas de Caracteres: ");
        scanf("%d",&n);
    }

    //Ingreso de m que guardara la cantidad de letras que se guardaran de cada String
    printf("Ingrese la cantidad de Letras a copiar:   ");
    scanf("%d",&m);
    while(m<=0){
        printf("Debe ser un numero mayor a 0\nIngrese la cantidad de Letras a copiar: ");
        scanf("%d",&m);
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