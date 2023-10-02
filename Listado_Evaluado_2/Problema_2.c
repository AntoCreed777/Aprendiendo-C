#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
                break;
            }
        }
    }
    *numero=atoi(string);
}

int permutacion(int arreglo[],int tamano,int posicioni){    //Funcion que busca la permutacion mas larga
    int contador=0;     //Cuenta cuantos ciclos sque an realizados en la permutacion
    int visitados[tamano];  //Reguistra los valores por los cuales ya se a pasado
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

}

int main(){
    //Ingreso y validacion del valor N
    int N;
    ingreso("Ingrese la cantidad de numeros que ingresara:   ",&N);

    //Creacion y llenado del arreglo que guardara los numeros

    int arreglo[N];
    int aux;
    char mensaje[40];
    for(int i=0;i<N;i++){
        sprintf(mensaje,"Ingrese el numero de la posicion %d:   ",i+1);
        ingreso(mensaje,&aux);
        while(aux>=N || aux<0){
            printf("Valor fuera de rango\n");
            ingreso(mensaje,&aux);
        }
        arreglo[i]=aux;
    }

    //Busqueda de la permutacion mas larga
    float permularga=-INFINITY;   //Se asigna un valor lo mas negativo posible para que si o si sea menor a cualquier numero del arreglo
    for(int i=0;i<N;i++){
        aux=permutacion(arreglo,N,i);
        if(aux>permularga){     //Comparacion entre la permutacion anterior y la actual, la 1ra vez si o si entra por el -INFINITY
            permularga=aux;     //Si la permutacion actual es la mas larga, se asigana ese valor a la variable que guarda la anterior
        }
    }
    
    printf("La permutacion mas larga es de %.0f",permularga);     //Se imprime el resultado

    return 0;
}