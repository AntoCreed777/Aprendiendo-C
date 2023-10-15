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

int filas(int matriz[9][9],int fila){
    int visto[9];
    for(int i=0;i<9;i++){
        for(int j=0;j<i;j++){
            if(visto[j]==matriz[fila][i]){
                return 1;
            }
        }
        visto[i]=matriz[fila][i];
    }
    return 0;
}

int columnas(int matriz[9][9],int columna){
    int visto[9];
    for(int i=0;i<9;i++){
        for(int j=0;j<i;j++){
            if(visto[j]==matriz[i][columna]){
                return 1;
            }
        }
        visto[i]=matriz[i][columna];
    }
    return 0;
}

int submatris(int matriz[9][9],int fila,int columna){
    int visto[9];
    int cantidad=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<cantidad;k++){
                if(visto[k]==matriz[fila+i][columna+j]){
                    return 1;
                }
            }
            visto[cantidad]=matriz[fila+i][columna+j];
            cantidad++;
        }
    }
    return 0;
}

int main(){
    //Declaracion e Ingreso de la matriz del Sudoku de 9x9
    int matriz[9][9];

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            char mensaje[100];
            sprintf(mensaje,"Ingrese el numero de la fila %d y la columna %d:    ",i+1,j+1);
            ingreso(mensaje,&matriz[i][j]);
        }
        printf("\n");
    }

    for(int i=0;i<9;i++){   //Recorro las filas y columnas para validar que estan bien
        if(filas(matriz,i) || columnas(matriz,i)){
            if(filas(matriz,i)){
                printf("No es una solucion valida para el Sudoku\nProblemas en la fila %d",i+1);
            }
            else{
                printf("No es una solucion valida para el Sudoku\nProblemas en la columna %d",i+1);
            }
            return 0;
        }
    }

    for(int i=0;i<9;i+=3){  //Recorro cada submatriz de 3x3 con la casilla superior izquierda como guia
        for(int j=0;j<9;j+=3){
            if(submatris(matriz,i,j)){
                printf("No es una solucion valida para el Sudoku\nProblemas en la submatriz de esquina superior derecha (%d,%d)",i+1,j+1);
                return 0;
            }
        }
    }

    printf("Es una matriz valida como solucion del Sudoku");

    return 0;
}