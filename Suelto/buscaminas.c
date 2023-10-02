#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//X significa que se mato
//B es bandera
//* es simbolo interno de que hay una mina
int ingreso(){
    int a=1;
    int resultado;
    while(a){
        char array[100];
        fgets(array,sizeof(array),stdin);
        size_t len=strlen(array);
        if(len>0 && array[len]=='\n'){
            array[len-1]='\0';
        }
        for(size_t i=0;i<len-1;i++){
            if(isdigit(array[i])==0){
                printf("No es un numero\nVuelva a ingresar: ");
                break;
            }else{
                a=0;
                resultado=atoi(array);
                break;
            }
        }
    }
    return resultado;
}

void imprimir_tableros(int largo, int ancho,char tablero[largo][ancho],char tablero2[largo][ancho]){
        for(int i=0;i<largo;i++){   //tablero del sistema
            for(int j=0;j<ancho;j++){
                printf("%c\t",tablero[i][j]);
            }
            printf("\n");
        }
        
        printf("\n\n\n");

        for(int i=0;i<largo;i++){   //Tablero que ve el jugador
            for(int j=0;j<ancho;j++){
                printf("%c\t",tablero2[i][j]);
            }
            printf("\n");
        }
}

int main(){
    //Ingreso de las medidas del tablero
    int largo,ancho;
    printf("Ingrese el largo del tablero: ");
    largo=ingreso();
    while(largo<=0 || largo>20){
        system("cls");
        printf("Tamano invalido\nIngrese el largo del tablero: ");
        largo=ingreso();
    }
    system("cls");
    printf("Ingrese el ancho del tablero: ");
    ancho=ingreso();
    while(ancho<=0 || ancho>20){
        system("cls");
        printf("Tamano invalido\nIngrese el ancho del tablero: ");
        ancho=ingreso();
    }
    system("cls");
    //Ingreso de la cantidad de minas en el tablero
    int minas;
    printf("Ingrese la cantidad de minas: ");
    minas=ingreso();
    while(minas<=0 || minas>(largo*ancho/2)){
        system("cls");
        printf("Cantidad invalida(Maximo de %d minas)\nIngrese la cantidad de minas: ",largo*ancho/2);
        minas=ingreso();
    }
    system("cls");
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
        imprimir_tableros(largo,ancho,tablero,tablero2);
        char accion;
        printf("Que desea hacer(B o M): ");
        scanf("%c",&accion);
        if(isupper(accion)){
            accion=tolower(accion);
        }
        while(accion!='m' && accion!='b'){
            printf("Ingreso invalido\nQue desea hacer(B o M): ");
            scanf("%c",&accion);
            if(isupper(accion)){
                accion=tolower(accion);
            }
        }
        ///*
        system("cls");

        if(accion=='m'){
            imprimir_tableros(largo,ancho,tablero,tablero2);
            int x,y;
            printf("Faltan %d casillas\n",falta);
            
            printf("Ingrese la coordenada X: ");
            x=ingreso();
            while(x<=0 || x>ancho){
                printf("Coordenada fuera de rango(debe estar entre 1 y %d)\nVuelva a ingresar: ",ancho);
                x=ingreso();
            }
            
            printf("Ingrese la coordenada Y: ");
            y=ingreso();
            while(y<=0 || y>largo){ 
                printf("Coordenada fuera de rango(debe estar entre 1 y %d)\nVuelva a ingresar: ",largo);
                y=ingreso();
            }
            if(tablero[largo-y][x-1]=='*'){
                printf("\n\nHAS PERDIDO, MEJOR SUERTE PARA LA PROXIMA");
                return 0;
            }
            
            
            if(tablero2[largo-y][x-1]=='#'){
                falta--;
            }

            tablero2[largo-y][x-1]=tablero[largo-y][x-1];
            
            if(tablero[largo-y][x-1]=='-'){     //Si no hay nada alrededor de la casilla, se imprime todo alrededor de la casilla
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
                    tablero2[largo-y+1][x-2]=tablero[largo-y+1][x-2];
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
        }
        else{
            imprimir_tableros(largo,ancho,tablero,tablero2);
            int x,y;
            printf("Ingrese la coordenada X: ");
            x=ingreso();
            while(x<=0 || x>ancho){
                printf("Coordenada fuera de rango(debe estar entre 1 y %d)\nVuelva a ingresar: ",ancho);
                x=ingreso();
            }
            
            printf("Ingrese la coordenada Y: ");
            y=ingreso();
            while(y<=0 || y>largo){ 
                printf("Coordenada fuera de rango(debe estar entre 1 y %d)\nVuelva a ingresar: ",largo);
                y=ingreso();
            }
            if(tablero2[largo-y][x-1]!='#' && tablero2[largo-y][x-1]!='B'){
                printf("Coordenada invalida\n\nPresione para continuar");
                getchar();
                continue;
            }

            if(tablero2[largo-y][x-1]!='#'){
                tablero2[largo-y][x-1]='#';
            }
            else if(tablero2[largo-y][x-1]!='B'){
                tablero2[largo-y][x-1]='B';
            }
        }
        system("cls");
    }
    printf("FELISITADES, HAS GANADO");
    return 0;
}