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
#define tamano_particula 20
#define DELAY 100


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
    int **valores_particulas = NULL;                                                               //Se crea el arreglo en donde se guardaran los datos
    int numero1,numero2,numero3,numero4;                                                            //Numeros Auxiliares

    while(feof(p)!=true && fscanf(p,"%d;%d;%d;%d;",&numero1,&numero2,&numero3,&numero4)==4){            //Mientras no se acabe, extraere los datos de 3 en 3 separados por ;
        valores_particulas=realloc(valores_particulas,sizeof(int*)*((*contador)+1));        //Le agrego otra fila al arreglo
        valores_particulas[*contador]=(int*)malloc(sizeof(int)*4);                          //A la fila agregada le agrego 3 columnas

        valores_particulas[*contador][0]=numero1;                                           //Asignacion de la coordenada X de forma definitiva
        valores_particulas[*contador][1]=numero2;                                           //Asignacion de la coordenada Y de forma definitiva
        valores_particulas[*contador][2]=numero3 % modulo_direccion;                                           //Asignacion de la Direccion de forma definitiva
        valores_particulas[*contador][3]=numero4 % modulo_peso;                                           //Asignacion de la Direccion de forma definitiva
        (*contador)++;                                                                      //Aumento el contador de particulas en uno
    }
    return  valores_particulas;                                                             //Retorno el arreglo con los datos de cada particula
}

int** BINARIO(FILE *p,int *contador){                       //Funcion que recive un archivo en binario y devuelve un array con los datos que almacena el archivo
    int **valores_particulas = NULL;                        //Se crea el arreglo en donde se guardaran los datos
    char string_particula[128];                              //String que guarda los 96 bits de los 3 datos de una particula
    int dato=0;                                             //Donde se guardara el dato

    while(fread(string_particula, 1, 128, p) == 128){         //Mientras existan los bits necesarios para completar los datos de una particula se sigue leyendo
        valores_particulas = realloc(valores_particulas,sizeof(int*)*((*contador)+1));       //Se agrega otra fila
        valores_particulas[*contador] = (int*)malloc(sizeof(int)*4);                         //A esa fila se le agregan 3 columnas
        for(int i=0;i<128;i++){              //Recorro los 3 datos extraidos
            int aux=(int)string_particula[i%32]-'0';            //Conversion a entero
            dato+=(aux<<(31-(i%32)));                           //Desplazamiento a la ubicacion en el entero final y se agrega al entero final
            if((i%32)==31){                                     //Si se vieron 32, que es la cantidad de bits de un entero se ingresa
                if((i+1)/32 == 3){                              //Al dato de la direccion le aplico el modulo para levarlo a valores dentro del rango
                    dato = dato % modulo_direccion;
                }
                if((i+1)/32 == 4){                              //Al dato del peso le aplico el modulo para levarlo a valores dentro del rango
                    dato = dato % modulo_peso;
                }
                valores_particulas[*contador][i/32]=dato;               //Se asigna el dato al array
                dato=0;                                                 //Se reinicia la variable que almacena el dato
            }
        }
        (*contador)++;                                          //Se aumenta el contador de particulas
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
                    valores_particulas=realloc(valores_particulas,sizeof(int*)*((*contador)+1));     //Le agrego otra fila al arreglo
                }
                valores_particulas[*contador]=(int*)malloc(sizeof(int)*4);                         //A la fila agregada le agrego 3 columnas

                valores_particulas[*contador][0]=x;                                                 //Asignacion de la coordenada X de forma definitiva
                valores_particulas[*contador][1]=y;                                                 //Asignacion de la coordenada Y de forma definitiva
                valores_particulas[*contador][2]=rand()%modulo_direccion;                           //Como no hay direccion lo asigno de forma random
                valores_particulas[*contador][3]=rand()%modulo_peso;                                //Como no hay peso lo asigno de forma random
                
                (*contador)++;                                                                      //Aumento el contador de particulas en uno

            }
            ptr++;
        }
    }
    return  valores_particulas;
}

int ** cuerpo_lectura(int *cantidad_particulas){
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
    int **valores_particulas = NULL;                                    //Array en donde se guardaran los datos
    switch (tipo_entrada){                                              //Llamo la funcion para extraer los datos segun que tipo de archivo entrante es
        case 'c': //CSV
            valores_particulas=CSV(entrada,cantidad_particulas);
            break;
        case 'b': //BINARIO
            valores_particulas=BINARIO(entrada,cantidad_particulas);
            break;
        case 't': //TEXTO
            valores_particulas=TEXTO(entrada,cantidad_particulas);
            break;
        default:
            printf("%s%sTipo de entrada no reconocido.%s\n",BOLD,WHITE,NORMAL);
            free(valores_particulas);
            exit(0);
    }

    fclose(entrada);    //Cierro el arcivo porque ya no se va a usar mas

    //For que imprime en terminal el array con los datos ingresados
    /*for(int i=0;i<(*cantidad_particulas);i++){
        for(int j=0;j<4;j++){
            printf("%s%s%u%s\t",BOLD,BLUE,(unsigned int)valores_particulas[i][j],NORMAL);
        }
        printf("\n");
    }*/
    return valores_particulas;
}

int main(int argc,char *argv[]){
    int cantidad_particulas=0;                                          //Guarda la cantidad de particulas ingresados
    int **valores_particulas=cuerpo_lectura(&cantidad_particulas);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////// FIN LECTURA ///////////INICIO VISUALIZACION/////////// Y-O MOVIMIENTO ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Inicializacion de SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
        SDL_Log("Incapaz de inicializar SDL: %s", SDL_GetError());
        return 1;
    }

    // Obtengo la maxima resolucion de la pantalla
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode(0, &DM);

    //Creacion de la ventana
    SDL_Window *ventana = SDL_CreateWindow("Desplegable",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,DM.w,DM.h,SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_FULLSCREEN);
    if(ventana == NULL){
        SDL_Log("Incapaz de crear la ventana: %s", SDL_GetError());
        return 1;
    }

    SDL_Surface *screen_surface = SDL_GetWindowSurface(ventana);
    int running = 1;
    SDL_Event evento;

    SDL_Rect rect[cantidad_particulas];     //Declaracion de rectangulos
    for(int i=0;i<cantidad_particulas;i++){
        rect[i].x=valores_particulas[i][0];
        rect[i].y=valores_particulas[i][1];
        rect[i].h=tamano_particula;
        rect[i].w=tamano_particula;
    }
    SDL_Point mouse;

    int cambio_color = 0;

    while(running == 1){
        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_QUIT){
                running = 0;
            }
            if(evento.type == SDL_KEYDOWN){
                SDL_Keycode key = evento.key.keysym.sym;
                if(key == SDLK_ESCAPE){
                    running =0;
                }
            }
            if(evento.type == SDL_MOUSEBUTTONDOWN){
                mouse.x = evento.button.x;
                mouse.y = evento.button.y;
                SDL_Log("Hice CLICK en (%d,%d)",mouse.x,mouse.y);
            }
        }

        //Impresion en la ventana
        SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 255 + cambio_color, 120 + cambio_color, 25 + cambio_color));
        for(int i=0;i<cantidad_particulas;i++){
            SDL_FillRect(screen_surface, &rect[i], SDL_MapRGB(screen_surface->format, 0 + cambio_color, 255 + cambio_color, 0 + cambio_color));
        }
        SDL_UpdateWindowSurface(ventana);

        cambio_color++;
        //Calculo de la siguiente posicion y actualizacion de valores particulas
        for(int i=0;i<cantidad_particulas;i++){
            //Colicion con algun borde de la ventana
            if(rect[i].x == 0){
                if(valores_particulas[i][2] == 3){
                    valores_particulas[i][2]= 1;
                }
                else if(valores_particulas[i][2] == 4){
                    valores_particulas[i][2]= 0;
                }
                else if(valores_particulas[i][2] == 5){
                    valores_particulas[i][2]= 7;
                }
            }
            if(rect[i].x == DM.w){
                if(valores_particulas[i][2] == 7){
                    valores_particulas[i][2]= 5;
                }
                else if(valores_particulas[i][2] == 0){
                    valores_particulas[i][2]= 4;
                }
                else if(valores_particulas[i][2] == 1){
                    valores_particulas[i][2]= 3;
                }
            }
            if(rect[i].y == 0){
                if(valores_particulas[i][2] == 1){
                    valores_particulas[i][2]= 7;
                }
                else if(valores_particulas[i][2] == 2){
                    valores_particulas[i][2]= 6;
                }
                else if(valores_particulas[i][2] == 3){
                    valores_particulas[i][2]= 5;
                }
            }
            if(rect[i].y == DM.h){
                if(valores_particulas[i][2] == 7){
                    valores_particulas[i][2]= 1;
                }
                else if(valores_particulas[i][2] == 6){
                    valores_particulas[i][2]= 2;
                }
                else if(valores_particulas[i][2] == 5){
                    valores_particulas[i][2]= 3;
                }
            }
            
            switch (valores_particulas[i][2])
            {
            case 0: //Derecha
                rect[i].x++ ;    //X
                break;
            case 1: //Derecha Arriba
                rect[i].x++ ;    //X
                rect[i].y-- ;    //Y
                break;
            case 2: //Arriba
                rect[i].y-- ;    //Y
                break;
            case 3: //Arriba Izquierda
                rect[i].x-- ;    //X
                rect[i].y-- ;    //Y
                break;
            case 4: //Izquierda
                rect[i].x-- ;    //X
                break;
            case 5: //Izquierda Abajo
                rect[i].x-- ;    //X
                rect[i].y++ ;    //Y
                break;
            case 6: //Abajo
                rect[i].y++ ;    //Y
                break;
            case 7: //Abajo Derevha
                rect[i].x++ ;    //X
                rect[i].y++ ;    //Y
                break;
            }
            //Colicion con otra particula
            for(int j=0;j<cantidad_particulas;j++){ //Recorro las particulas
                for(int k=0;k<cantidad_particulas;k++){ //Recorro las particulas menos la de la J
                    if(SDL_HasIntersection(&rect[j],&rect[k]) && j!=k){ //Si se intersectan
                        if(valores_particulas[j][3]<=valores_particulas[k][3]){
                            valores_particulas[j][2]=rand()%modulo_direccion;
                        }
                    }
                }
            }
        }
    
        //SDL_Delay(DELAY);
    }

    //Liberacion de la memoria usada en el programa
    for(int i=0;i<cantidad_particulas;i++){
        free(valores_particulas[i]);
    }
    free(valores_particulas);
    //Destruccion de la ventana y cierre de SDL
    SDL_FreeSurface(screen_surface);
    SDL_DestroyWindow(ventana);
    SDL_Quit();

    return 0;
}