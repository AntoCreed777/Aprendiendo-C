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
    *numero=(int)(string);
    free(string);
}

int main(){
    //Ingreso y validacion del valor N
    int N;
    ingreso("Ingrese la cantidad de numeros que ingresara:   ",&N);

    //Ingreso y validacion del valor M
    int M;
    ingreso("Ingrese el numero delimitador:   ",&M);

    //Creacion y llenado de la matriz A que guardara los numeros que ingrese el usuario

    int A[N];
    int aux;
    char mensaje[40];
    for(int i=0;i<N;i++){
        sprintf(mensaje,"Ingrese el numero de la posicion %d:   ",i+1);
        ingreso(mensaje,&aux);
        A[i]=aux;
    }
    
    //Creacion de las matrices B yC

    int *B;
    B=(int*)malloc(sizeof(int)*N);
    int *C;
    C=(int*)malloc(sizeof(int)*N);

    //Comparo los elementos de A con el numero M para repartirlos entre B o C
    
    int cantidadB=0;
    int cantidadC=0;
    for(int i=0;i<N;i++){
        if(A[i]<M){
            B[cantidadB]=A[i];
            cantidadB++;
        }
        else{
            C[cantidadC]=A[i];
            cantidadC++;
        }
    }

    //Reduccion de los arreglos B y C segun la cantidad de elementos que poseen

    B=(int*)realloc(B,sizeof(int)*cantidadB);
    C=(int*)realloc(C,sizeof(int)*cantidadC);

    //Impresion de las matrices resultantes
    printf("Matriz A\n");
    for(int i=0;i<N;i++){
        printf("%d\t",A[i]);
    }

    printf("\n\nMatriz B\n");
    for(int i=0;i<cantidadB;i++){
        printf("%d\t",B[i]);
    }    

    printf("\n\nMatriz C\n");
    for(int i=0;i<cantidadC;i++){
        printf("%d\t",C[i]);
    }

    free(B);
    free(C);
    return 0;
}