#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>
//X significa que se mato
//B es bandera
//* es simbolo interno de que hay una mina

int main(){
    //Ingreso de las medidas del tablero
    int largo,ancho;
    printf("Ingrese el tamano del tablero(Largo Ancho): ");
    scanf("%d %d",&largo,&ancho);
    while(isdigit(largo)!=0 ||isdigit(ancho)!=0){
        printf("\n\nTamano invalido\nIngrese el tamano del tablero(Largo Ancho): ");
        scanf("%d %d",&largo,&ancho);
    }
    
    //Ingreso de la cantidad de minas en el tablero
    int minas;
    printf("Ingrese la cantidad de minas: ");
    scanf("%d",&minas);
    while(isdigit(minas)!=0){
        printf("\n\nCantidad invalida\nIngrese la cantidad de minas: ");
        scanf("%d",&minas);
    }
    
    //declaracion del tablero
    char tablero[largo][ancho];
    for(int i=0;i<largo;i++){
        for(int j=0;j<ancho;j++){
            tablero[i][j]='-';
        }
    }

    srand(time(NULL));  //Inicializo random

    for(int i=0;i<minas;i++){   //Generacion de las minas
        int v=rand()%largo;
        int h=rand()%ancho;
        tablero[v][h]='*';
    }

    for(int i=0;i<largo;i++){   //Llenado con numeros segun las minas en el perimetro
        for(int j=0;j<ancho;j++){
            int contador=0;
            if(tablero[i+1][j]=='*' && i+1<largo){
                contador++;
            }
            if(tablero[i-1][j]=='*'&& i-1>=0){
                contador++;
            }
            if(tablero[i+1][j+1]=='*'&& i+1<largo &&j+1<ancho){
                contador++;
            }
            if(tablero[i+1][j-1]=='*'&& i+1<largo &&j-1>=0){
                contador++;
            }
            if(tablero[i-1][j+1]=='*'&& i-1>=0 &&j+1<ancho){
                contador++;
            }
            if(tablero[i-1][j-1]=='*'&& i-1>=0 && j-1>=0){
                contador++;
            }
            if(tablero[i][j+1]=='*' && j+1<ancho){
                contador++;
            }
            if(tablero[i][j-1]=='*' && j-1>=0){
                contador++;
            }
            if(tablero[i][j]=='*' || contador==0){
                continue;
            }
            char aux[2];
            sprintf(aux,"%d",contador);
            tablero[i][j]=aux[0];
        }
    }
    
    char tablero2[largo][ancho]; //Tablero que se le mostrara al usuario
    for(int i=0;i<largo;i++){
        for(int j=0;j<ancho;j++){
            tablero2[i][j]='#';
        }
    }
    
    int falta=largo*ancho-minas;




    while(falta!=0){
        ///*
        for(int i=0;i<largo;i++){
            for(int j=0;j<ancho;j++){
                printf("%c\t",tablero[i][j]);
            }
            printf("\n");
        }
        
        printf("\n\n\n");
        //*/
        for(int i=0;i<largo;i++){
            for(int j=0;j<ancho;j++){
                printf("%c\t",tablero2[i][j]);
            }
            printf("\n");
        }
        
        int x,y;
        printf("Ingrese las coordenadas: ");
        scanf("%d %d",&x,&y);

        if(tablero[largo-y][x-1]=='*'){
            printf("\n\nHAS PERDIDO, MEJOR SUERTE PARA LA PROXIMA");
            return 0;
        }
        
        tablero2[largo-y][x-1]=tablero[largo-y][x-1];
        if(tablero2[largo-y][x-1]!='#'){
            falta--;
        }

        if(tablero[largo-y][x-1]=='-'){
            if(tablero[largo-y+1][x-1]!='*' && largo-y+1<largo && tablero2[largo-y+1][x-1]=='#'){
                tablero2[largo-y+1][x-1]=tablero[largo-y+1][x-1];
                falta--;
            }
            if(tablero[largo-y-1][x-1]!='*' && largo-y-1>=0 && tablero2[largo-y-1][x-1]=='#'){
                tablero2[largo-y-1][x-1]=tablero[largo-y-1][x-1];
                falta--;
            }
            if(tablero[largo-y+1][x]!='*' && largo-y+1<largo && x<ancho && tablero2[largo-y+1][x]=='#'){
                tablero2[largo-y+1][x]=tablero[largo-y+1][x];
                falta--;
            }
            if(tablero[largo-y+1][x-2]!='*' && largo-y+1<largo && x-2>=0 && tablero2[largo-y+1][x-2]=='#'){
                tablero2[largo-y+1][x-2]=tablero[largo-y][x-2];
                falta--;
            }
            if(tablero[largo-y-1][x]!='*' && largo-y-1>=0 && x<ancho && tablero2[largo-y-1][x]=='#'){
                tablero2[largo-y-1][x]=tablero[largo-y-1][x];
                falta--;
            }
            if(tablero[largo-y-1][x-2]!='*' && largo-y-1>=0 && x-2>=0 && tablero2[largo-y-1][x-2]=='#'){
                tablero2[largo-y-1][x-2]=tablero[largo-y-1][x-2];
                falta--;
            }
            if(tablero[largo-y][x]!='*' && x<ancho && tablero2[largo-y][x]=='#'){
                tablero2[largo-y][x]=tablero[largo-y][x];
                falta--;
            }
            if(tablero[largo-y][x-2]!='*' && x-2>=0 && tablero2[largo-y][x-2]=='#'){
                tablero2[largo-y][x-2]=tablero[largo-y][x-2];
                falta--;
            }
        }
        
        system("cls");  //Limpia terminal
    }
    printf("FELISICADES, HAS GANADO");
    return 0;
}