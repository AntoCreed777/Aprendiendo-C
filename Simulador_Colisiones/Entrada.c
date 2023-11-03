#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BOLD "\e[1m"
#define WHITE "\e[7m"
#define BLUE "\e[44m"
#define NORMAL "\e[0m"

#define CARACTERESMAXIMOS 100

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
            else{
                printf("%s%sError al abrir el archivo.%s\n\n",BOLD,WHITE,NORMAL);
            }
        }
        else {
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
            if(datos_por_particula==3){                                                         //Si ya se registraron 3 datos para una particula
                datos_por_particula=0;                                                          //Reinicio el contardor
                (*contador)++;                                                                  //Aumento el contador de particulas
                valores_particulas=realloc(valores_particulas,sizeof(int*)*((*contador)+1));    //Le agrego otra fila al arreglo
                valores_particulas[*contador]=(int*)malloc(sizeof(int*)*3);                     //A la fila agregada le agrego 3 columnas
            }
        }
    }
    return  valores_particulas;     //Retorno el arreglo con los datos de cada particula
}

int** BINARIO(FILE *p,int *contador){
    int **valores_particulas=(int**)malloc(sizeof(int*));
    valores_particulas[0]=(int*)malloc(sizeof(int)*3);

    return  valores_particulas;
}

int** TEXTO(FILE *p,int *contador){

    return  NULL;
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
    int **valores_particulas=NULL;
    int cantidad_particulas=0;                                         //Guarda la cantidad de particulas ingresados
    switch (tipo_entrada){
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

    for(int i=0;i<cantidad_particulas;i++){
        for(int j=0;j<3;j++){
            printf("%s%s%d%s\t",BOLD,BLUE,valores_particulas[i][j],NORMAL);
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