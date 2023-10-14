#include <stdio.h>

void impresion_matriz(char matriz[8][8]){   //Impresion del tablero
    printf("  ----------------\n");     //Marco Superior
    for(int i=0;i<8;i++){
        for(int j=0;j<11;j++){
            if(j==0){
                printf("%d",8-i);   //Coordenadas del eje y
            }
            else if(j==1 || j==10){
                printf("|");    //Marcos laterales
            }
            else{
                printf("%c ",matriz[i][j-2]);   //Elementos del tablero
            }
        }
        printf("\n");
    }
    printf("  ----------------\n"); //Marco Inferior
    printf("  a b c d e f g h");    //Coordenadas del eje x
}

void diagonales(char matriz[8][8],int x,int y){ //Asignacion de las Diagonales del alfil
    for(int i=y+1,j=x+1;i<8 && j<8;i++,j++){    //Diagonal Inferior Derecha
        matriz[i][j]='x';
    }
    for(int i=y-1,j=x-1;i>=0 && j>=0;i--,j--){  //Diagonal Superior Izquierda
        matriz[i][j]='x';
    }
    for(int i=y+1,j=x-1;i<8 && j>=0;i++,j--){   //Diagonal Inferior Izquierda
        matriz[i][j]='x';
    }
    for(int i=y-1,j=x+1;i>=0 && j<8;i--,j++){   //Diagonal Superior Derecha
        matriz[i][j]='x';
    }
}

int main(){
    char x1;    //Coordenada en el eje X en formato de letra
    int y;      //Coordenada en el eje y en forma numerica
    printf("Ingrese la coordenada (Ej: d4): ");
    scanf(" %c%d",&x1,&y);  //Ingreso de la coordenada en notacion de ajedrez
    while(y<=0 || y>8 || x1<'a' || x1>'h'){ //Validacion de que sea un coordenada valida
        printf("\nValor fuea de rango[a,h][1,8]:  ");
        scanf(" %c%d",&x1,&y);
    }
    int x=x1-'a';   //Transformacion de coordenada de letra a numerico

    char tablero[8][8]={    //Declaracion del tablero
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '}
    };

    tablero[8-y][x]='A';    //Se coloca la posicion del Alfil en el tablero

    diagonales(tablero,x,8-y);  //Se colocan los movimiiento que puede hacer el alfil

    impresion_matriz(tablero);  //Se imprime el tablero

    return 0;
}