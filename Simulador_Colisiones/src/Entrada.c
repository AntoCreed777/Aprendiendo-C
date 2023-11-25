#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define BOLD "\e[1m"
#define WHITE "\e[7m"
#define BLUE "\e[44m"
#define NORMAL "\e[0m"

#define CARACTERESMAXIMOS 100000
#define modulo_direccion 8
#define modulo_peso 11

char* ingreso_string(){                                     //Getline casero
    printf("%sIngrese la direccion de su archivo: %s\n",BOLD,NORMAL);
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

FILE* ingreso_archivo(){    //Se valida que se haya abierto bien el archivo y devuelbe el puntero hacia el si es que esta bien
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
            else{                               //Si no se pudo abrir se imprime un mensaje para el usuario
                printf("%s%sError al abrir el archivo.%s\n\n",BOLD,WHITE,NORMAL);
            }
        }
        else {                                  //Si esta vacio la entrada del nombre imprime un mensaje para el usuario
            printf("%s%sError: no se ingresó el nombre del archivo.%s\n\n",BOLD,WHITE,NORMAL);
        }
    }
    
}

SDL_Rect* CSV(FILE *p,int *contador){       //Funcion que recibe los datos separados por ; y los guarda en un array
    SDL_Rect *particulas = NULL;                                                               //Se crea el arreglo en donde se guardaran los datos
    int numero1,numero2,numero3,numero4;                                                            //Numeros Auxiliares

    while(feof(p)!=true && fscanf(p,"%d;%d;%d;%d;",&numero1,&numero2,&numero3,&numero4)==4){            //Mientras no se acabe, extraere los datos de 3 en 3 separados por ;
        particulas=(SDL_Rect*)realloc(particulas,sizeof(SDL_Rect)*((*contador)+1));        //Le agrego otra fila al arreglo

        particulas[*contador].x=numero1;                                           //Asignacion de la coordenada X de forma definitiva
        particulas[*contador].y=numero2;                                           //Asignacion de la coordenada Y de forma definitiva
        particulas[*contador].d=numero3 % modulo_direccion;                        //Asignacion de la Direccion de forma definitiva
        particulas[*contador].p=numero4 % modulo_peso;                             //Asignacion de la Direccion de forma definitiva
        (*contador)++;                                                             //Aumento el contador de particulas en uno
    }
    return  particulas;                                                            //Retorno el arreglo con los datos de cada particula
}

SDL_Rect* BINARIO(FILE *p,int *contador){                       //Funcion que recive un archivo en binario y devuelve un array con los datos que almacena el archivo
    SDL_Rect *particulas = NULL;                        //Se crea el arreglo en donde se guardaran los datos
    char string_particula[128];                              //String que guarda los 96 bits de los 3 datos de una particula
    int dato=0;                                             //Donde se guardara el dato

    while(fread(string_particula, 1, 128, p) == 128){         //Mientras existan los bits necesarios para completar los datos de una particula se sigue leyendo
        particulas = (SDL_Rect*)realloc(particulas,sizeof(SDL_Rect)*((*contador)+1));       //Se agrega otra fila
        for(int i=0;i<128;i++){              //Recorro los 3 datos extraidos
            int aux=(int)string_particula[i%32]-'0';            //Conversion a entero
            dato+=(aux<<(31-(i%32)));                           //Desplazamiento a la ubicacion en el entero final y se agrega al entero final
            if((i%32)==31){                                     //Si se vieron 32, que es la cantidad de bits de un entero se ingresa
                if((i+1)/32 == 1){                              //Al dato de la direccion le aplico el modulo para levarlo a valores dentro del rango
                    particulas[*contador].x=dato;               //Se asigna el dato de direccion al array
                }
                else if((i+1)/32 == 2){                         //Al dato de la direccion le aplico el modulo para levarlo a valores dentro del rango
                    particulas[*contador].y=dato;               //Se asigna el dato de direccion al array
                }
                else if((i+1)/32 == 3){                         //Al dato de la direccion le aplico el modulo para levarlo a valores dentro del rango
                    dato = dato % modulo_direccion;
                    particulas[*contador].d=dato;               //Se asigna el dato de direccion al array
                }
                else if((i+1)/32 == 4){                         //Al dato del peso le aplico el modulo para levarlo a valores dentro del rango
                    dato = dato % modulo_peso;
                    particulas[*contador].p=dato;               //Se asigna el dato dee peso al array
                }
                dato=0;                                                 //Se reinicia la variable que almacena el dato
            }
        }
        (*contador)++;                                          //Se aumenta el contador de particulas
    }
    return  particulas;     //Se retorna el array con los datos de las particulas
}

SDL_Rect* TEXTO(FILE *p,int *contador){
    srand (time(NULL));                                                                         //Se inicializa la semilla del random
    SDL_Rect *particulas = NULL;

    char buffer[CARACTERESMAXIMOS];                                             //Se guarda la linea actual
    int x,y;
    while (fgets(buffer, CARACTERESMAXIMOS, p)){    // Leemos la linea actual y la dejamos copiada en buffer//Mientras no termine el archivo se seguira en el bucle
        char *ptr = buffer;
        while ((ptr = strstr(ptr, "(")) != NULL) {
            if (sscanf(ptr, "(%d,%d)", &x, &y) == 2) {
                particulas=(SDL_Rect*)realloc(particulas,sizeof(SDL_Rect)*((*contador)+1));     //Le agrego otra fila al arreglo

                particulas[*contador].x=x;                                                 //Asignacion de la coordenada X de forma definitiva
                particulas[*contador].y=y;                                                 //Asignacion de la coordenada Y de forma definitiva
                particulas[*contador].d=rand()%modulo_direccion;                           //Como no hay direccion lo asigno de forma random
                particulas[*contador].p=rand()%modulo_peso;                                //Como no hay peso lo asigno de forma random
                
                (*contador)++;                                                                      //Aumento el contador de particulas en uno
            }
            ptr++;
        }
    }
    return  particulas;
}

SDL_Rect* cuerpo_lectura(int *cantidad_particulas){
    //Ingreso de la direccion del archivo
    FILE *entrada=ingreso_archivo();            //Se obtiene el puntero al archivo de ingreso


    //Especificar tipo de entrada
    fseek(entrada, 0, SEEK_END);                // Muevo el puntero al final del archivo
    long tamano_archivo = ftell(entrada);       // Obtengo la posición actual dandome el tamaño del archivo
    fseek(entrada, 0, SEEK_SET);                // Vuelvo el puntero al principio del archivo

    char tipo_entrada;
    if(tamano_archivo==0){                      //Verifico que el archivo no se encuentre vacio
        printf("%s%sError: El archivo se encuentra vacio%s",BOLD,BLUE,NORMAL);
        fclose(entrada);
        return 0;
    }
    else{
        tipo_entrada=fgetc(entrada);       //Obtengo que tipo de entrada es (c=CSV,t=txt,b=binario)
    }
    

    //Recopilacion de datos segun el tipo de entrada
    SDL_Rect *particulas = NULL;                                        //Array en donde se guardaran los datos
    switch (tipo_entrada){                                              //Llamo la funcion para extraer los datos segun que tipo de archivo entrante es
        case 'c': //CSV
            particulas=CSV(entrada,cantidad_particulas);
            break;
        case 'b': //BINARIO
            particulas=BINARIO(entrada,cantidad_particulas);
            break;
        case 't': //TEXTO
            particulas=TEXTO(entrada,cantidad_particulas);
            break;
        default:
            printf("%s%sTipo de entrada no reconocido.%s\n",BOLD,WHITE,NORMAL);
            free(particulas);
            exit(0);
    }

    fclose(entrada);    //Cierro el arcivo porque ya no se va a usar mas

    //For que imprime en terminal el array con los datos ingresados
    for(int i=0;i<(*cantidad_particulas);i++){
        printf("%s%s%u\t%u\t%u\t%u%s\n",BOLD,BLUE,particulas[i].x,particulas[i].y,particulas[i].d,particulas[i].p,NORMAL);
    }
    return particulas;
}

int main(int argc,char *argv[]){
    int cantidad_particulas=0;                                          //Guarda la cantidad de particulas ingresados
    SDL_Rect *particulas=cuerpo_lectura(&cantidad_particulas);          //Array en donde se guardaran los datos

////////////////////////////////////////////////////////////////////////////
////////////////PARTE 2 Y 3/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


    //Liberacion de la memoria usada en el programa
    free(particulas);
    SDL_Quit();
    return 0;
}