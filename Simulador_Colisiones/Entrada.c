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

#define CARACTERESMAXIMOS 100
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

int** CSV(FILE *p,int *contador){
    int **valores_particulas=(int**)malloc(sizeof(int*));                       //Se crea el arreglo en donde se guardaran los datos
    valores_particulas[0]=(int*)malloc(sizeof(int)*3);                          //Le agrego 3 columnas a esa fila creada
    char separador[]=";";                                                       //Declaracion del criterio para separa el buffer
    char buffer[CARACTERESMAXIMOS];                                             //Se guarda la linea actual
    int datos_por_particula=0;                                                  //Guarda la cantidad ded datos por linea ingresados

    while (fgets(buffer, CARACTERESMAXIMOS, p)){    // Leemos la linea actual y la dejamos copiada en buffer//Mientras no termine el archivo se seguira en el bucle
        char *token = strtok(buffer, separador);    //Extraigo el string separado por ";"

        //Comparo que el token no sea un salto de linea, evitando su asignacion al array, para que strcmp funcione, antes valido que token no sea NULL
        if(token!=NULL){
            while(strcmp(token,"\n")==0){
                token = strtok(NULL, separador);
                if(token==NULL){break;} //Si por a b c toca que token es NULL, salgo del while, porque no funciona el ctrcmp del while con token=NULL
            }
        }

        while(token != NULL) {                                                  //Mentras token sea distinto de NULL, permanesco en el Ciclo
            if(datos_por_particula==3){                                                         //Si ya se registraron 3 datos para una particula
                datos_por_particula=0;                                                          //Reinicio el contardor
                valores_particulas=realloc(valores_particulas,sizeof(int*)*((*contador)+1));    //Le agrego otra fila al arreglo
                valores_particulas[*contador]=(int*)malloc(sizeof(int*)*3);                     //A la fila agregada le agrego 3 columnas
            }
            valores_particulas[*contador][datos_por_particula]=atoi(token);     //Asigno el token como entero al array
            token = strtok(NULL, separador);                                    //Obtengo el siguiente token
            
            //Comparo que el token no sea un salto de linea, evitando su asignacion al array, para que strcmp funcione, antes valido que token no sea NULL
            if(token!=NULL){
                while(strcmp(token,"\n")==0){
                    token = strtok(NULL, separador);
                    if(token==NULL){break;}
                }
            }

            datos_por_particula++;                                                              //Aumento el contador de datos por particula
            if(datos_por_particula==3){
                (*contador)++;                                                                  //Aumento el contador de particulas
            }
        }
    }
    return  valores_particulas;     //Retorno el arreglo con los datos de cada particula
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

    /*
    unsigned char c;                                        //Se guarda los caracteres ingresados
    int datos_por_particula=0;                              //Guarda la cantidad de datos por linea ingresados
    int cantidad_caracteres=0;                              //Guarda la cantidad de caracteres registrados por particula
    int dato=0;                                             //Donde se guardara el dato

    while (tamano_archivo!=(*contador)*3+cantidad_caracteres){      //Leemos el caracter actual
        c=fgetc(p);
        for(int i=7;i>=0;i--){
            int aux=c;              //Auxiliar para no perder el valor original del caracter "c"
            dato+=((aux >> i) & 1)<<(8*(4-cantidad_caracteres));
        }

        cantidad_caracteres++;
        if(cantidad_caracteres==4){
            valores_particulas[*contador][datos_por_particula]=dato;
            dato=0;
            cantidad_caracteres=0;
            datos_por_particula++;
            if(datos_por_particula==3){
                (*contador)++;
                valores_particulas = (int**)realloc(valores_particulas, sizeof(int*) * (*contador+1)); // Se agrega otra fila
                valores_particulas[*contador] = (int*)malloc(sizeof(int) * 3);
                datos_por_particula=0;
            }
        }
    }
    */
    return  valores_particulas;     //Se retorna el array con los datos de las particulas
}

int** extrae_coordenada_texto(int **valores_particulas,char* token1,int *contador){
    int datos_por_particula=0;                                                                      //Guarda la cantidad ded datos por linea ingresados
    char *token2 = strtok(token1,"(");                                                              //Extraigo el string separado por "(" a la izquierda
    token2 = strtok(NULL, "(");                                                                     //Extraigo el string separado por "(" a la derecha
    char *token3 = strtok(token2, ",");                                                             //Extraigo el string separado por "," a la izquierda, que seria la x
    char *token4 = strtok(NULL, ",");                                                               //Extraigo el string separado por "," a la derecha, que seria la y
    if(token3!=NULL && isdigit(token3[0]) && token4!=NULL && isdigit(token4[0])){
        valores_particulas = (int**)realloc(valores_particulas, sizeof(int*) * (*contador+1));      // Se agrega otra fila
        valores_particulas[*contador] = (int*)malloc(sizeof(int) * 3);                              //A esa fila se le agregan 3 columnas
        valores_particulas[*contador][datos_por_particula]=atoi(token3);                            //Guardo el dato de la x
        datos_por_particula++;
        valores_particulas[*contador][datos_por_particula]=atoi(token4);                            //Guardo el dato de la y
        datos_por_particula++;

        valores_particulas[*contador][datos_por_particula]=rand()%modulo_random;                    //como no hay direccion lo asigno de forma random
        (*contador)++;                                                                              //Aumento el contador de particulas
    }

    return valores_particulas;                                                                                     
}

int** TEXTO(FILE *p,int *contador){
    srand (time(NULL));                                                                         //Se inicializa la semilla del random
    int **valores_particulas=NULL;

    char buffer[CARACTERESMAXIMOS];                                             //Se guarda la linea actual
    
    while (fgets(buffer, CARACTERESMAXIMOS, p)){    // Leemos la linea actual y la dejamos copiada en buffer//Mientras no termine el archivo se seguira en el bucle
        char *token1 = strtok(buffer, ")");                 //Extraigo la parte con el "posible" dato
        char *token_restante = strtok(NULL, "");            //Mantengo guardado el resto del buffer
        while(token1!=NULL && token1 && "\n"){              //Si no esta vacio ni es un salto de linea se extrae las coordenadas
            valores_particulas=extrae_coordenada_texto(valores_particulas,token1,contador);     //Extraigo las particulas generando el array dentro de la funcion
            token1 = strtok(token_restante, ")");           //Extraigo otro "posible" dato de lo que quedaba del anterior token
            char *auxiliar2 = strtok(NULL, "");             //Guardo lo que queda de  forma temporal
            token_restante=auxiliar2;                       //Lo guardo en la variable que guarda lo que falta
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