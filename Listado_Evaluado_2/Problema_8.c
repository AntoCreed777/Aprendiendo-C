#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char** argv){

    if(argc != 3) { //Sino se ingresan los argumentos necesarios para funcionar, imprime un mensaje y cierra el programa
        printf("\nUso: %s <archivo1> <archivo2>\n\n", argv[0]);
        exit(0);
    }

    FILE *fp = fopen(argv[1], "r");     //Abrimos el Stream del archivo que leeremos
    FILE *fp2 = fopen(argv[2], "w");    //Abrimos el Stream del archivo en que escribiremos
    if (fp == NULL || fp2 == NULL) {    //Si no se logran abrir imprimimos un mensaje de error y cerramos el programa
        if(fp == NULL){
            printf("\nNO SE PUEDE ABRIR %s\n",argv[1]);
        }
        if(fp2 == NULL){
            printf("\nNO SE PUEDE ABRIR %s\n",argv[2]);
        }
        exit(1);
    }

    char c;             //Variable que almacena los caracteres del archivo que leemos
    int cantidadt=0;    //Cantidad total de caracteres
    int cantidadd=0;    //Cantidad total de digitos
    int cantidadl=0;    //Cantidad total de letras
    int cantidads=0;    //Cantidad total de simbolos
    int cantidadp=0;    //Cantidad total de palabras

    int hay_letra_antes=0;  //Indica 1 si habia una letra antes, sino 0
    int hay_letra_ahora;    //Indica 1 si hay una letra ahora, sino 0

    //Aqui vemos cuantos caracteres en total hay en el Archivo
    fseek(fp, 0L, SEEK_END);
    long int num_bytes = ftell(fp);
    long int num_caracteres = num_bytes / sizeof(char);

    fseek(fp, 0L, SEEK_SET);    //Movemos al Stream al inicio del archivo

    while ((c = fgetc(fp)) != EOF){     //Mientras queden cosas seguira recibiendo los caracteres del archivo
        cantidadt++;    //Contador de caracteres vistos

        if(c>='0' && c<='9'){   //Si es un numero se aumneta el contador de Digitos
            cantidadd++;
            hay_letra_ahora=0;  //No es una letra por lo que se asigna 0
        }

        else if((c>='a' && c<='z') || (c>='A' && c<='Z')){  //Si es una letra se aumneta el contador de Letras
            cantidadl++;
            hay_letra_ahora=1;  //Si es una letra por lo que se asigna 1
        }

        else{   //Sino  es nada de lo anterior se aumenta el contador de Simbolos
            cantidads++;
            hay_letra_ahora=0;  //No es una letra por lo que se asigna 0
        }

        if((c==' ' || c=='\t' || c=='\n' || c==',' || c==';' || c=='.') && hay_letra_antes==1){   //Si antes habia una letra y hay un simbolo de puntuacion se aumenta el contador de Palabras
            cantidadp++;
        }
        
        if(hay_letra_ahora && (cantidadt==num_caracteres)){     //Si estamos en el final del archivo y hay una letra se aumneta la cantidad de palabras
            cantidadp++;
        }
        
        hay_letra_antes=hay_letra_ahora;    //Lo que hay ahora se guarda en antes
    }

    char estadisticas[100];     //String en que se guardara el mensaje a escribir en el archivo saliente

    sprintf(estadisticas,"Hay %d caracteres en total, %d digitos, %d letras, %d simbolos y %d palabras",cantidadt,cantidadd,cantidadl,cantidads,cantidadp); //Concatenacion de los resultados

    int len=strlen(estadisticas);   //Se registra el tamano del mensaje

    for(int i=0;i<len;i++){ //Se escribe el mensaje en el archivo saliente
        c=estadisticas[i];
        fputc(c,fp2);
    }

    printf("Resultados guardados en %s\n",argv[2]); //Se le indica al usuario donde se guardo la respuesta

    fclose(fp);     //Cerramos el stream
    fclose(fp2);    //Cerramos el stream

    return 0;   //Finalizamos el programa
}