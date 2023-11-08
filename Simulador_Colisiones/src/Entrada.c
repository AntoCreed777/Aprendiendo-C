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
#define modulo_random 2000

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

int** CSV(FILE *p,int *contador){       //Funcion que recibe los datos separados por ; y los guarda en un array
    int **valores_particulas;                                                               //Se crea el arreglo en donde se guardaran los datos
    int numero1,numero2,numero3;                                                            //Numeros Auxiliares

    while(feof(p)!=true && fscanf(p,"%d;%d;%d;",&numero1,&numero2,&numero3)==3){            //Mientras no se acabe, extraere los datos de 3 en 3 separados por ;
        if((*contador)==0){
            valores_particulas=(int**)malloc(sizeof(int*));                                 //Le agrego la primera fila
        }
        else{
            valores_particulas=realloc(valores_particulas,sizeof(int)*((*contador)+1));    //Le agrego otra fila al arreglo
        }
        valores_particulas[*contador]=(int*)malloc(sizeof(int*)*3);                         //A la fila agregada le agrego 3 columnas

        valores_particulas[*contador][0]=numero1;                                           //Asignacion de la coordenada X de forma definitiva
        valores_particulas[*contador][1]=numero2;                                           //Asignacion de la coordenada Y de forma definitiva
        valores_particulas[*contador][2]=numero3;                                           //Asignacion de la Direccion de forma definitiva
        
        (*contador)++;                                                                      //Aumento el contador de particulas en uno
    }
    return  valores_particulas;                                                             //Retorno el arreglo con los datos de cada particula
}

int** BINARIO(FILE *p,int *contador){                       //Funcion que recive un archivo en binario y devuelve un array con los datos que almacena el archivo
    int **valores_particulas=(int**)malloc(sizeof(int*));   //Se crea el arreglo en donde se guardaran los datos
    valores_particulas[0]=(int*)malloc(sizeof(int)*3);      //Le agrego 3 columnas a esa fila creada

    int datos_por_particula=0;                              //Guarda la cantidad de datos por linea ingresados
    int cantidad_caracteres=0;                              //Guarda la cantidad de caracteres registrados por particula
    char c;
    int dato=0;                                             //Donde se guardara el dato

    while((c=fgetc(p))!=EOF){                               //Mientras no se acabe se sigen registrando los caracteres
        if(datos_por_particula==3){                                 //Si se completa la cantidad de datos por particulas(3) se ingresa
            valores_particulas = (int**)realloc(valores_particulas, sizeof(int*) * (*contador+1));  // Se agrega otra fila
            valores_particulas[*contador] = (int*)malloc(sizeof(int) * 3);                          //A esa fila se le agregan 3 columnas
            datos_por_particula=0;                                                                  //Se reinicia el contador de datos por paricula
        }
        int aux=(int)c-'0';                                 //Conversion a entero
        aux=aux<<(31-cantidad_caracteres);                  //Desplazamiento a la ubicacion en el entero final
        dato+=aux;                                          //Se agrega al entero final
        cantidad_caracteres++;                              //Se aumenta el contador de caracteres vistos en este dato
        if(cantidad_caracteres==32){                        //Si se vieron 32, que es la cantidad de bits de un entero se ingresa
            cantidad_caracteres=0;                          //Se reinicia el contador
            valores_particulas[*contador][datos_por_particula]=dato;    //Se asigna el dato al array
            datos_por_particula++;                                      //Se aumenta el contador de datos vistos por particula
            dato=0;                                                     //Se reinicia la variable que almacena el dato
            if(datos_por_particula==3){                                 //Si se completa la cantidad de datos por particulas(3) se ingresa
                (*contador)++;                                          //Se aumenta el contador de particulas
            }
        }
    }
    return  valores_particulas;     //Se retorna el array con los datos de las particulas
}

int** TEXTO(FILE *p,int *contador){
    srand (time(NULL));                                                                         //Se inicializa la semilla del random
    int **valores_particulas=NULL;

    char buffer[CARACTERESMAXIMOS];                                             //Se guarda la linea actual
    int x,y;
    while (fgets(buffer, CARACTERESMAXIMOS, p)){    // Leemos la linea actual y la dejamos copiada en buffer//Mientras no termine el archivo se seguira en el bucle
        char *ptr = buffer;
        while ((ptr = strstr(ptr, "(")) != NULL) {
            if (sscanf(ptr, "(%d,%d)", &x, &y) == 2) {
                if((*contador)==0){
                    valores_particulas=(int**)malloc(sizeof(int*));                                 //Le agrego la primera fila
                }
                else{
                    valores_particulas=realloc(valores_particulas,sizeof(int)*((*contador)+1));     //Le agrego otra fila al arreglo
                }
                valores_particulas[*contador]=(int*)malloc(sizeof(int*)*3);                         //A la fila agregada le agrego 3 columnas

                valores_particulas[*contador][0]=x;                                                 //Asignacion de la coordenada X de forma definitiva
                valores_particulas[*contador][1]=y;                                                 //Asignacion de la coordenada Y de forma definitiva
                valores_particulas[*contador][2]=rand()%modulo_random;                              //Como no hay direccion lo asigno de forma random
                
                (*contador)++;                                                                      //Aumento el contador de particulas en uno

            }
            ptr++;
        }
    }
    return  valores_particulas;
}

int main(){
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
    int **valores_particulas=NULL;                                      //Array en donde se guardaran los datos
    int cantidad_particulas=0;                                          //Guarda la cantidad de particulas ingresados
    switch (tipo_entrada){                                              //Llamo la funcion para extraer los datos segun que tipo de archivo entrante es
        case 'c': //CSV
            valores_particulas=CSV(entrada,&cantidad_particulas);
            break;
        case 'b': //BINARIO
            valores_particulas=BINARIO(entrada,&cantidad_particulas);
            break;
        case 't': //TEXTO
            valores_particulas=TEXTO(entrada,&cantidad_particulas);
            break;
        default:
            printf("%s%sTipo de entrada no reconocido.%s\n",BOLD,WHITE,NORMAL);
            return 1;
    }

    //For que imprime en terminal el array con los datos ingresados
    for(int i=0;i<cantidad_particulas;i++){
        for(int j=0;j<3;j++){
            printf("%s%s%u%s\t",BOLD,BLUE,(unsigned int)valores_particulas[i][j],NORMAL);
        }
        printf("\n");
    }


    //Liberacion de la memoria usada en el programa
    for(int i=0;i<cantidad_particulas;i++){
        free(valores_particulas[i]);
    }
    free(valores_particulas);
    fclose(entrada);
    return 0;
}