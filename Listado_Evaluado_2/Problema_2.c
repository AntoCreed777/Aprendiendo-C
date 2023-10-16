/*Como vimos en clases, toda permutación de números puede ser vista como un conjunto de ciclos.
Escriba un programa que pida un número entero n, para que luego lea n números que forman una
permutación en el rango [1..n]. Su programa debe reportar el largo del ciclo más largo.
Por ejemplo, si tenemos la permutación [0, 6, 3, 10, 5, 11, 2, 9, 7, 4, 1, 8], la respuesta es 6,
debido a que el ciclo más largo está dado por 4, 5, 11, 8, 7, 9.*/

#include <stdio.h>
#include <stdlib.h>

int permutacion(int arreglo[],int tamano,int posicioni){    //Funcion que busca la permutacion mas larga
    int contador=0;                                         //Cuenta cuantos "pasos" se han realizados en la permutacion
    int *visitados=(int*)malloc(sizeof(int)*tamano);        //Reguistra los valores por los cuales ya se a pasado
    visitados[0]=posicioni;                                 //Se guarda la posicioni en visitados porque es donde parte la permutacion
    int posicion=posicioni;                                 //Guarda la posicion a la que debe ir

    while(1){                                       //Ciclo infinito hasta que encuentre un valor repetido
        posicion=arreglo[posicion];                 //Se actualiza la posicion a la que debe ir
        for(int i=0;i<=contador;i++){               //Recorre los elementos de "visitados"
            if(posicion==visitados[i]){             //Pregunta si ya se paso por ahi
                free(visitados);                    //Se libera la memoria usada por el arreglo visitados
                return contador+1;                  //Se devuelve la cantidad de ciclos realizados mas 1, ese 1 es por el valor inicial que al principio no se agrega
            }
        }
        contador++;                                 //Se aumenta la cantidad de "pasos" que lleva la permutacion
        visitados[contador]=posicion;               //Se agrega la posicion al arreglo de posiciones ya visitadas
    }
}

int validacion(int cantidad,int aux,int arreglo[]){     //Funcion que valida que no se repitan numeros a la hora del ingreso de estos
    for(int j=0;j<cantidad;j++){    //Ciclo que recorre un arreglo que almacena los numeros ingresados hasta el momento
        if(aux==arreglo[j]){        //Si el numero ingresado coincide con uno anteriormente ingresado entonces entra al if
            return 1;               //Retorna un 1 como error
        }
    }
    return 0;       //Si el codigo llega hasta aqui significa que no existio ningun valor repetido reornando 0 de todo "OK"
}

int main(){
    
    int N;                                                          //Declaracion de N que guarda la cantidad de numeros que ingresaran
    printf("Ingrese la cantidad de numeros que ingresara:   ");     //Mensaje guia para el usuario
    while(scanf("%d",&N)!=1 || N<=0){                               //Ingreso y validacion del valor N
        printf("Error de entrada\n\nIngrese la cantidad de numeros que ingresara:   "); //Mensaje guia para el usuario
        int c;                                                      //Declaracion de caracter auxiliar
        while ((c = getchar()) != '\n' && c != EOF) {}              // Limpio la entrada para eliminar caracteres no válidos
    }

    int *arreglo=(int*)malloc(sizeof(int)*N);   //Creacion y llenado del arreglo que guardara los numeros
    int aux;                                    //Declaracion de una variable auxiliar que guardara los numeros ingresados de forma momentanea y al final del codigo el largo de las permutaciones
    int cantidad=0;                             //Declaracion de una variable que representa la cantidad de numeros ingresados hasta el momento
    for(int i=0;i<N;i++){
        printf("Ingrese el numero de la posicion %d:   ",i+1);  //Mensaje guia para el usuario
        while(scanf("%d",&aux)!=1 || aux<0){                    //Ingreso y validacion de la variable aux
            printf("Error de entrada\n\nIngrese el numero de la posicion %d:   ",i+1);  //Mensaje guia para el usuario
            int c;                                          //Declaracion de caracter auxiliar
            while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la  entrada para eliminar caracteres no válidos
        }
        while(aux>=N || validacion(cantidad,aux,arreglo)){  //Se valida que no sea un valor repetido y que este dentro del rango
            if(validacion(cantidad,aux,arreglo)){           //Si es un valor repetido entra para mostrar un mensaje distintivo
                printf("\nNo se pueden repetir los numeros\n\n");   //Mensaje guia para el usuario
            }
            else{
                printf("Valor fuera de rango\n");   //Mensaje guia para el usuario si es que es un valor fuera de rango
            }
            printf("Ingrese el numero de la posicion %d:   ",i+1);  //Mensaje guia para el usuario
            while(scanf("%d",&aux)!=1 || aux<0){                    //Ingreso y validacion de la variable aux
                printf("Error de entrada\n\nIngrese el numero de la posicion %d:   ",i+1);  //Mensaje guia para el usuario
                int c;                                              //Declaracion de caracter auxiliar
                while ((c = getchar()) != '\n' && c != EOF) {}      // Limpio la  entrada para eliminar caracteres no válidos
            }
        }
        arreglo[i]=aux;     //Se asigna el valor ingresado al arreglo que oficialmente lo guardara
        cantidad++;         //Se aumenta el contador de numeros ingresados
    }

    //Busqueda de la permutacion mas larga
    float permularga=-1;        //Se asigna un valor  negativo para que si o si sea menor a cualquier numero de tamaño del arreglo
    for(int i=0;i<N;i++){       //Se recorre el arreglo que guarda los numeros ingresados
        aux=permutacion(arreglo,N,i);   //Se llama a la funcion que encuentra el tamaño de la permutacion que inicia desde la posicion i
        if(aux>permularga){     //Comparacion entre la permutacion anterior y la actual, la 1ra vez si o si entra por el -INFINITY
            permularga=aux;     //Si la permutacion actual es la mas larga, se asigana ese valor a la variable que guarda la anterior
        }
    }
    
    printf("\nLa permutacion mas larga es de %.0f",permularga);     //Se imprime el resultado

    free(arreglo);      //Se libera la memoria ocupada por el array arreglo

    return 0;
}