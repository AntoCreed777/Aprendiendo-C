#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOLD "\e[1m"
#define WHITE "\e[7m"
#define BLUE "\e[44m"
#define NORMAL "\e[0m"


char* ingreso_string(){                                     //Getline casero
    int capacidad=10;                                       //Capacidad del string
    int longitud=0;                                         //Longitud actual del string
    char *string=(char*)malloc(sizeof(char)*capacidad);     //Dimencionamiento del String inicial

    char c;                                                 //Receptor de los caracteres entrantes

    while((c=getchar())!='\n'){
        while(longitud>=capacidad-1){                       //Capacidad-1 para recervar espacio para '\0'
            capacidad+=4;
            string=realloc(string,sizeof(char)*capacidad);     //Se redimenciona el string
        }
        string[longitud]=c;                                     //Se asigna el caracter al string
        longitud++;                                             //Se aumenta la longitud
    }

    string[longitud]='\0';
    string=realloc(string,sizeof(char)*(longitud+1));     //Se redimenciona el string al tamano real
    
    return string;
}

FILE* ingreso_archivo(){
    while(1){
        FILE *p=NULL;
        char *nombre_entrada = ingreso_string();

        if (nombre_entrada != NULL) {           //Se corrobora que se haya ingresado un nombre
            if(strcmp(nombre_entrada,"exit")==0){
                free(nombre_entrada);           //Se libera la memoria usada por el string luego de usarlo
                exit(0);
            }
            p = fopen(nombre_entrada, "r");     //Se abre el archivo
            free(nombre_entrada);               //Se libera la memoria usada por el string luego de usarlo

            if (p != NULL) {                    //Se valida que se haya podido habrir el archivo
                return p;
            }
            else{
                printf("%s%sError al abrir el archivo.%s\n\n",BOLD,WHITE,NORMAL);
            }
        }
        else {
            printf("%s%sError: no se ingresó el nombre del archivo.%s\n\n",BOLD,WHITE,NORMAL);
        }
    }
    
}

int main(){
    FILE *entrada=ingreso_archivo();



    fclose(entrada);
    return 0;
}