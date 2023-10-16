#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int permutacion(int arreglo[],int tamano,int posicioni){    //Funcion que busca la permutacion mas larga
    int contador=0;     //Cuenta cuantos ciclos sque an realizados en la permutacion
    int *visitados=NULL;  //Reguistra los valores por los cuales ya se a pasado
    visitados=(int*)malloc(sizeof(int)*tamano);
    visitados[0]=posicioni;
    int posicion=posicioni; //Guarda la posicion a la que debe ir

    while(1){
        posicion=arreglo[posicion]; //Se actualiza la posicion a la que debe ir
        for(int i=0;i<=contador;i++){   //Recorre los elementos de "visitados"
            if(posicion==visitados[i]){ //Pregunta si ya se paso por ahi
                return contador+1;  //Se devuelve la cantidad de ciclos realizados mas 1, ese 1 es por el valor inicial que al principio no se agrega
            }
        }
        contador++;
        visitados[contador]=posicion;   //Se agrega la posicion al arreglo de posiciones ya visitadas
    }
    free(visitados);
}

int validacion(int cantidad,int aux,int arreglo[]){
    for(int j=0;j<cantidad;j++){
        if(aux==arreglo[j]){
            return 1;
        }
    }
    return 0;
}

int main(){
    //Ingreso y validacion del valor N
    int N;
    printf("Ingrese la cantidad de numeros que ingresara:   ");
    while(scanf("%d",&N)!=1 || N<=0){
        printf("Error de entrada\n\nIngrese la cantidad de numeros que ingresara:   ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la  entrada para eliminar caracteres no válidos
    }

    //Creacion y llenado del arreglo que guardara los numeros

    int *arreglo=(int*)malloc(sizeof(int)*N);
    int aux;
    int cantidad=0;
    for(int i=0;i<N;i++){
        printf("Ingrese el numero de la posicion %d:   ",i+1);
        while(scanf("%d",&aux)!=1 || aux<0){
            printf("Error de entrada\n\nIngrese el numero de la posicion %d:   ",i+1);
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la  entrada para eliminar caracteres no válidos
        }
        while(aux>=N || aux<0 || validacion(cantidad,aux,arreglo)){
            if(validacion(cantidad,aux,arreglo)){
                printf("\nNo se pueden repetir los numeros\n\n");
            }
            else{
                printf("Valor fuera de rango\n");
            }
            printf("Ingrese el numero de la posicion %d:   ",i+1);
            while(scanf("%d",&aux)!=1 || aux<0){
                printf("Error de entrada\n\nIngrese el numero de la posicion %d:   ",i+1);
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la  entrada para eliminar caracteres no válidos
            }
        }
        arreglo[i]=aux;
        cantidad++;
    }

    //Busqueda de la permutacion mas larga
    float permularga=-INFINITY;   //Se asigna un valor lo mas negativo posible para que si o si sea menor a cualquier numero del arreglo
    for(int i=0;i<N;i++){
        aux=permutacion(arreglo,N,i);
        if(aux>permularga){     //Comparacion entre la permutacion anterior y la actual, la 1ra vez si o si entra por el -INFINITY
            permularga=aux;     //Si la permutacion actual es la mas larga, se asigana ese valor a la variable que guarda la anterior
        }
    }
    
    printf("\nLa permutacion mas larga es de %.0f",permularga);     //Se imprime el resultado

    free(arreglo);

    return 0;
}