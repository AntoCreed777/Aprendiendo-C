/*Escriba un programa que pida ingresar una matriz de 9x9 y verifique si es una solución válida para el juego Sudoku*/

#include <stdio.h>

int filas(int matriz[9][9],int fila){       //Funcion que valida que no se repitan numeros en la fila i-nesima
    int visto[9];                           //Array que almacena los numeros vistos
    for(int i=0;i<9;i++){                   //Ciclo que recorre las filas de la matriz
        for(int j=0;j<i;j++){               //Ciclo que recorre los elementos del array vistos
            if(visto[j]==matriz[fila][i]){  //Si ya se vio el numero se retorna un 1 de error
                return 1;
            }
        }
        visto[i]=matriz[fila][i];           //Se agrega el numero visto al array de numeros visitados
    }
    return 0;                               //Se regresa 0 porque si llego hasta aqui esta todo bien
}

int columnas(int matriz[9][9],int columna){     //Funcion que valida que no se repitan numeros en la columna i-nesima
    int visto[9];                               //Array que almacena los numeros vistos
    for(int i=0;i<9;i++){                       //Ciclo que recorre las columnas de la matriz
        for(int j=0;j<i;j++){                   //Ciclo que recorre los elementos del array vistos
            if(visto[j]==matriz[i][columna]){   //Si ya se vio el numero se retorna un 1 de error
                return 1;
            }
        }
        visto[i]=matriz[i][columna];            //Se agrega el numero visto al array de numeros visitados
    }
    return 0;                                   //Se regresa 0 porque si llego hasta aqui esta todo bien
}

int submatris(int matriz[9][9],int fila,int columna){   //Funcion que valida que no se repitan numeros en la submatriz de vertice superior izquierdo [fila,columnma]
    int visto[9];                                       //Array que almacena los numeros vistos
    int cantidad=0;                                     //Variable que almacena la cantidad de elementos vistos
    for(int i=0;i<3;i++){                               //Ciclo que recorre las filas de la matriz
        for(int j=0;j<3;j++){                           //Ciclo que recorre las columnas de la matriz
            for(int k=0;k<cantidad;k++){                //Ciclo que recorre los elementos del array vistos
                if(visto[k]==matriz[fila+i][columna+j]){    //Si ya se vio el numero se retorna un 1 de error
                    return 1;
                }
            }
            visto[cantidad]=matriz[fila+i][columna+j];  //Se agrega el numero visto al array de numeros visitados
            cantidad++;                                 //Se aumenta el contador de numeros vistos
        }
    }
    return 0;                                           //Se regresa 0 porque si llego hasta aqui esta todo bien
}

int main(){
    int matriz[9][9];   //Declaracion e Ingreso de la matriz del Sudoku de 9x9

    for(int i=0;i<9;i++){   //Ciclo que recorre las filas de la matriz
        for(int j=0;j<9;j++){   //Ciclo que recorre las columnas de la matriz
            printf("Ingrese el numero de la fila %d y la columna %d:    ",i+1,j+1);    //Mensage guia para el usuario
            while(scanf("%d",&matriz[i][j])!=1 || matriz[i][j]<1 || matriz[i][j]>9){   //Ingreso del numero
                printf("Error de entrada, debe ser un numero de este rango[1,9]\n\nIngrese el numero de la fila %d y la columna %d:    ",i+1,j+1);  //Mensage guia para el usuario
                int c;                                          //Declaracion de caracter auxiliar
                while ((c = getchar()) != '\n' && c != EOF) {}  // Limpio la entrada para eliminar caracteres no válidos
            }
        }
        printf("\n");   //Salto de linea para diferenciar los numerosa de una fila con los de la otra
    }

    for(int i=0;i<9;i++){   //Recorro las filas y columnas para validar que estan bien
        if(filas(matriz,i) || columnas(matriz,i)){      //Se valida que no se repitan elementos enla fila i y en la columna i
            if(filas(matriz,i)){
                printf("No es una solucion valida para el Sudoku\nProblemas en la fila %d",i+1);
            }
            else{
                printf("No es una solucion valida para el Sudoku\nProblemas en la columna %d",i+1);
            }
            return 0;   //Se termina el programa porque ya no se cumple una de las reglas del Sudoku
        }
    }

    //Recorro cada submatriz de 3x3 con la casilla superior izquierda como guia
    for(int i=0;i<9;i+=3){  //Recorro las filas de 3 en 3
        for(int j=0;j<9;j+=3){  //Recorro las columnas de 3 en 3
            if(submatris(matriz,i,j)){  //Valido que no haya ningun elemento repetido en la submatriz
                printf("No es una solucion valida para el Sudoku\nProblemas en la submatriz de esquina superior derecha (%d,%d)",i+1,j+1);
                return 0;       //Se termina el programa porque ya no se cumple una de las reglas del Sudoku
            }
        }
    }

    printf("Es una matriz valida como solucion del Sudoku");    //Si se logra llegar hsta esta parte del programa significa que se superaron todas las validaciones por lo que si es una solucion

    return 0;
}