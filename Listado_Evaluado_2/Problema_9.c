#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    //Declaracion de variables
    int n,m;

    //Ingreso de n que guardara la cantidad de strings que ingresaran
    printf("Ingrese la cantidad de Cadenas de Caracteres:   ");
    while(scanf("%d",&n)!=1 || n<=0){   //Ingreso del numero
        printf("Error de entrada\n\nIngrese la cantidad de Cadenas de Caracteres:   ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la  entrada para eliminar caracteres no válidos
    }

    //Ingreso de m que guardara la cantidad de letras que se guardaran de cada String
    printf("Ingrese la cantidad de Letras a copiar:   ");
    while(scanf("%d",&m)!=1 || m<=0){   //Ingreso del numero
        printf("Error de entrada\n\nIngrese la cantidad de Letras a copiar:   ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la  entrada para eliminar caracteres no válidos
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