#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>

#define BOLD "\e[1m"
#define WHITE "\e[7m"
#define BLUE "\e[44m"
#define NORMAL "\e[0m"

#define CARACTERESMAXIMOS 100000
#define modulo_direccion 8
#define modulo_peso 11
#define tamano_particula 250
#define particulas_maximas 2000
#define volumen_fondo 2     //Maximo dividido por este numero

//Estructura en que se guardaran los recursos necesarios para correr el programa
typedef struct {

    //Valores para el sonido
    Mix_Chunk *sonido_fondo;
    Mix_Chunk *sonido_golpe;
    Mix_Chunk *sonido_pared;

    //Variable para la fuente del texto
    TTF_Font *font;

    //Surfaces para imprimir en pantalla
    SDL_Surface *surface_colisiones;
    SDL_Texture *textura_colisiones;

    SDL_Surface *surface_tiempo;
    SDL_Texture *textura_tiempo;

    SDL_Surface *surface_contador;
    SDL_Texture *textura_contador;

    //Cuadros de texto para imprimir en pantalla
    SDL_Rect cuadro_texto;
    SDL_Rect cuadro_tiempo_transcurrido;
    SDL_Rect cuadro_contador;
    
    //Variables de la ventana donde se imprimira
    SDL_Window *ventana;
    SDL_Renderer *render;

    //Variable de la Dimencion de la Pantalla
    SDL_DisplayMode DM;

    //Variable para registrar los eventos
    SDL_Event evento;

    //Variable para registrar las acciones del mouse
    SDL_Point mouse;

    //Variables extras
    int running;                    //Variable que indica si se sigue o no en la Simulacion
    int contador_colisiones;        //Registra las cantidades de colisiones
    time_t tiempo_inicial;          //Registra el momento en que se inicio el programa
    time_t tiempo_actual;           //Registra el tiempo actual
    time_t tiempo_que_paso;         //Registra el tiempo que paso entre el tiempo inicial y el tiempo actual
    SDL_Color colorTexto;           //Almacena el color de los textos que se muestran en pantalla
    char texto_colisiones[30];      //Almacena el texto que muestra las colisiones en pantalla
    char texto_tiempo[30];          //Almacena el texto que muestra el tiempo transcurrido en pantalla
    char texto_contador[30];        //Almacena el texto que muestra la cantidad de particulas en pantalla

} Recursos;

//Funciones de lectura
void asignacion_direcciones(SDL_Rect *particula,int direccion){
    switch (direccion)
    {
    case 0: //Derecha
        particula->dx = 1;      //X
        particula->dy = 0;      //Y
        break;
    case 1: //Derecha Arriba
        particula->dx = 1;      //X
        particula->dy = -1;     //Y
        break;
    case 2: //Arriba
        particula->dx= 0 ;      //X
        particula->dy = -1;     //Y
        break;
    case 3: //Arriba Izquierda
        particula->dx = -1;     //X
        particula->dy = -1;     //Y
        break;
    case 4: //Izquierda
        particula->dx = -1;     //X
        particula->dy = 0;      //Y
        break;
    case 5: //Izquierda Abajo
        particula->dx= -1;      //X
        particula->dy = 1;      //Y
        break;
    case 6: //Abajo
        particula->dx = 0;      //X
        particula->dy = 1;      //Y
        break;
    case 7: //Abajo Derecha
        particula->dx = 1;      //X
        particula->dy = 1;      //Y
        break;
    }
}

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
        asignacion_direcciones(&particulas[*contador],numero3 % modulo_direccion); //Asignacion de la Direccion de forma definitiva                    
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
                    asignacion_direcciones(&particulas[*contador],dato);    //Se asigna el dato de direccion al array
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
                asignacion_direcciones(&particulas[*contador],rand()%modulo_direccion);    //Como no hay direccion lo asigno de forma random
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
        exit(0);
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
    /*for(int i=0;i<(*cantidad_particulas);i++){
        printf("%s%s%u\t%u\t%u\t%u%s\n",BOLD,BLUE,particulas[i].x,particulas[i].y,particulas[i].d,particulas[i].p,NORMAL);
    }*/

    for(int i=0;i<(*cantidad_particulas);i++){ //Le doy dimencion a las particulas
        particulas[i].h=tamano_particula;
        particulas[i].w=tamano_particula;
    }

    return particulas;
}

//Funciones de inicializado y cierre
int inicializado_SDL2(){
    //Inicializacion de SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
        SDL_Log("Incapaz de inicializar SDL: %s", SDL_GetError());
        return 1;
    }

    //Configuracion Audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        printf("Error al inicializar SDL_mixer: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }

    //Inicializo SDL_TTF
    if (TTF_Init() != 0) {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }
    return 0;
}

int inicializado_de_recursos(Recursos *recursos) {

    //Inicio los sonidos en sus respectivas variables
    recursos->sonido_fondo = Mix_LoadWAV("assets/Sonido_Fondo.mp3");
    recursos->sonido_golpe = Mix_LoadWAV("assets/right-cross-cross.mp3");
    recursos->sonido_pared = Mix_LoadWAV("assets/sonido_colision_pared.mp3");

    //Verifico que se hayan iniciado bien
    if (!recursos->sonido_golpe || !recursos->sonido_fondo || !recursos->sonido_pared) {
        printf("Error al cargar los archivos de audio: %s\n", Mix_GetError());
        return 1;
    }

    //Comienzo la reproduccion del sonido de fondo
    Mix_PlayChannel(0, recursos->sonido_fondo, -1);
    Mix_VolumeChunk(recursos->sonido_fondo, MIX_MAX_VOLUME / volumen_fondo);

    //Inicio la fuente en su respectiva variable
    recursos->font = TTF_OpenFont("assets/Handlee-Regular.ttf", 24);

    //Verifico que se haya inicido bien
    if (!recursos->font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return 1;
    }

    //Obtengo la dimension de la pantalla y la guardo en su respectiva variable
    SDL_GetCurrentDisplayMode(0, &recursos->DM);


    //Inicio la ventana en su respectiva variable
    recursos->ventana = SDL_CreateWindow("Desplegable", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        recursos->DM.w, recursos->DM.h, SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);

    //Si no se inicio la ventana retorno error 
    if (!recursos->ventana) {
        SDL_Log("Incapaz de crear la ventana: %s", SDL_GetError());
        TTF_CloseFont(recursos->font);
        return 1;
    }

    // Crea un renderer asociado a la ventana
    recursos->render = SDL_CreateRenderer(recursos->ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!recursos->render) {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(recursos->ventana);
        SDL_Quit();
        return 1;
    }

    // Maximizo la ventana
    SDL_MaximizeWindow(recursos->ventana);

    //Le asigno los valores RGB del texto que se muestra en pantalla
    recursos->colorTexto.r = 250;
    recursos->colorTexto.g = 170;
    recursos->colorTexto.b = 50;
    recursos->colorTexto.a = 255;

    //Asigna las posiciones de los cuadros de texto
    recursos->cuadro_texto.x = 0;
    recursos->cuadro_texto.y = 60;
    recursos->cuadro_tiempo_transcurrido.x = 0;
    recursos->cuadro_tiempo_transcurrido.y = 0;
    recursos->cuadro_contador.x = 0;
    recursos->cuadro_contador.y = 30;

    //Inicializo otras variables
    recursos->running = 1;
    recursos->contador_colisiones = 0;
    recursos->tiempo_inicial = time(NULL);

    return 0; // Exito al inicializar los recursos 
}

void finalizacion_de_recursos_y_librerias(SDL_Rect *particulas,Recursos *recursos){
    //Liberacion de la memoria usada en el programa en las particulas
    free(particulas);

    //Destruccion del font (la fuente del texto)
    TTF_CloseFont(recursos->font);

    //Destruccion de las variables con los audios
    Mix_FreeChunk(recursos->sonido_fondo);
    Mix_FreeChunk(recursos->sonido_golpe);

    //Destruccion de las surfaces
    SDL_FreeSurface(recursos->surface_colisiones);
    SDL_FreeSurface(recursos->surface_tiempo);
    SDL_FreeSurface(recursos->surface_contador);

    // Libera las texturas
    SDL_DestroyTexture(recursos->textura_colisiones);
    SDL_DestroyTexture(recursos->textura_tiempo);
    SDL_DestroyTexture(recursos->textura_contador);

    //Destruccion de la ventana
    SDL_DestroyWindow(recursos->ventana);

    //Cierre de las librerias de SDL2
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

//Funciones de eventos
void guardado(SDL_Rect *particulas,int cantidad_particulas){
    char nombre_carpeta[40]= "Guardado Colisionador Particulas";
    if(access(nombre_carpeta,0) != 0){
        mkdir(nombre_carpeta);
    }

    char nombre_archivo[55];
    time_t tiempo;
    tiempo=time(NULL);

    sprintf(nombre_archivo, "%s/Save_%ld.txt", nombre_carpeta, (long int) tiempo);

    FILE *salida = fopen(nombre_archivo,"w");

    fputc('c',salida);
    for(int i=0; i<cantidad_particulas;i++){
        int aux_direccion;
        if(particulas[i].dx == 1 && particulas[i].dy == 0){aux_direccion = 0;}
        if(particulas[i].dx == 1 && particulas[i].dy == -1){aux_direccion = 1;}
        if(particulas[i].dx == 0 && particulas[i].dy == -1){aux_direccion = 2;}
        if(particulas[i].dx == -1 && particulas[i].dy == -1){aux_direccion = 3;}
        if(particulas[i].dx == -1 && particulas[i].dy == 0){aux_direccion = 4;}
        if(particulas[i].dx == -1 && particulas[i].dy == 1){aux_direccion = 5;}
        if(particulas[i].dx == 0 && particulas[i].dy == 1){aux_direccion = 6;}
        if(particulas[i].dx == 1 && particulas[i].dy == 1){aux_direccion = 7;}

        fprintf(salida,"%d;%d;%d;%d;\n",particulas[i].x,particulas[i].y,aux_direccion,particulas[i].p);
    }

    fclose(salida);
}

SDL_Rect* crear_particula(SDL_Rect *particulas, int *cantidad_particulas,SDL_DisplayMode Dimencion){
    int x,y,colision=0,intentos=2000;
    while(intentos>0){
        x=rand()%(Dimencion.w-tamano_particula);    //Obtengo la posicion en X
        y=rand()%(Dimencion.h-tamano_particula);    //Obtengo la posicion en Y
        for(int i=0;i<(*cantidad_particulas);i++){      //Recorro cada particula
            if((x <= particulas[i].x+tamano_particula && x >= particulas[i].x && y <= particulas[i].y+tamano_particula && y >= particulas[i].y) ||      //Vertice superior izquierdo

                (x+tamano_particula <= particulas[i].x+tamano_particula && x+tamano_particula >= particulas[i].x &&                                     //Vertice inferior derecho
                y+tamano_particula <= particulas[i].y+tamano_particula && y+tamano_particula >= particulas[i].y) ||

                (x+tamano_particula <= particulas[i].x+tamano_particula && x+tamano_particula >= particulas[i].x &&                                     //Vertice superior derecho
                y <= particulas[i].y+tamano_particula && y >= particulas[i].y) ||
                
                (x <= particulas[i].x+tamano_particula && x >= particulas[i].x &&                                                                       //Vertice inferior izquierdo
                y+tamano_particula <= particulas[i].y+tamano_particula && y+tamano_particula >= particulas[i].y)){

                colision=1; //Si hay una particula
                break;      //Sale del for
            }
        }
        if(!colision){
            (*cantidad_particulas)++;
            particulas=(SDL_Rect*)realloc(particulas,sizeof(SDL_Rect)*(*cantidad_particulas));
            particulas[(*cantidad_particulas)-1].x=x;
            particulas[(*cantidad_particulas)-1].y=y;
            break;
        }
        intentos--;
    }
    if(intentos == 0){printf("No se pudo encontrar una ubicacion para la particula\n");return particulas;}
    int d=rand()%modulo_direccion;
    asignacion_direcciones(&particulas[(*cantidad_particulas)-1],d);

    int p=rand()%modulo_peso;
    particulas[(*cantidad_particulas)-1].p=p;

    particulas[(*cantidad_particulas)-1].w=tamano_particula;
    particulas[(*cantidad_particulas)-1].h=tamano_particula;

    return particulas;
}

SDL_Rect* destruir_particula(SDL_Rect *particulas, int *cantidad_particulas){
    int marcada=rand()%(*cantidad_particulas);
    for(int i=(marcada+1);i<(*cantidad_particulas);i++){
        particulas[i-1]=particulas[i];
    }
    (*cantidad_particulas)--;
    particulas=(SDL_Rect*)realloc(particulas,sizeof(SDL_Rect)*(*cantidad_particulas));
    return particulas;
}

SDL_Rect* control_de_eventos(Recursos *recursos,int *cantidad_particulas,SDL_Rect *particulas){
    if(SDL_PollEvent(&(recursos->evento))){
        if(recursos->evento.type == SDL_QUIT){    //Si se aprieta la X de la ventana para salir
            recursos->running = 0;
        }
        if(recursos->evento.type == SDL_KEYDOWN){     //Si se aprieta una tecla
            SDL_Keycode key = recursos->evento.key.keysym.sym;
            if(key == SDLK_ESCAPE){
                recursos->running =0;
            }
            else if(key == SDLK_g){
                guardado(particulas,(*cantidad_particulas));
            }
            else if(key == SDLK_m){
                if((*cantidad_particulas) < particulas_maximas){   //El limite de pariculas en pantalla
                    particulas = crear_particula(particulas,cantidad_particulas,recursos->DM);
                }
            }
            else if(key == SDLK_k){
                if((*cantidad_particulas) >0){ //Si existen particulas se eliminan
                    particulas=destruir_particula(particulas,cantidad_particulas);
                }
            }
            else if(key == SDLK_r){ //Se reinicia el contador de coliciones
                recursos->contador_colisiones=0;
            }
        }
        if(recursos->evento.type == SDL_MOUSEBUTTONDOWN){ //Si se clickea con el mause
            recursos->mouse.x = recursos->evento.button.x;
            recursos->mouse.y = recursos->evento.button.y;
            SDL_Log("Hice CLICK en (%d,%d)",recursos->mouse.x,recursos->mouse.y);
        }
    }
    return particulas;
}

// Funcion de visualizado
void visualizacion(SDL_Rect *particulas, Recursos *recursos, int cantidad_particulas) {
    //Se actualiza la textura del texto
    sprintf(recursos->texto_colisiones, "Colisiones: %d", recursos->contador_colisiones);
    recursos->surface_colisiones = TTF_RenderText_Solid(recursos->font, recursos->texto_colisiones, recursos->colorTexto);
    recursos->textura_colisiones = SDL_CreateTextureFromSurface(recursos->render, recursos->surface_colisiones);
    recursos->cuadro_texto.w = recursos->surface_colisiones->w;
    recursos->cuadro_texto.h = recursos->surface_colisiones->h;
    SDL_FreeSurface(recursos->surface_colisiones);

    //Se calcula el tiempo transcurrido
    recursos->tiempo_actual = time(NULL);
    recursos->tiempo_que_paso = recursos->tiempo_actual - recursos->tiempo_inicial;
    sprintf(recursos->texto_tiempo, "Tiempo transcurrido: %d", (int)recursos->tiempo_que_paso);

    //Se actualiza la textura del tiempo transcurrido
    recursos->surface_tiempo = TTF_RenderText_Solid(recursos->font, recursos->texto_tiempo, recursos->colorTexto);
    recursos->textura_tiempo = SDL_CreateTextureFromSurface(recursos->render, recursos->surface_tiempo);
    recursos->cuadro_tiempo_transcurrido.w=recursos->surface_tiempo->w;
    recursos->cuadro_tiempo_transcurrido.h=recursos->surface_tiempo->h;
    SDL_FreeSurface(recursos->surface_tiempo);

    //Se actualiza la textura del contador de particulas
    sprintf(recursos->texto_contador, "Cantidad de Particulas: %d", cantidad_particulas);
    recursos->surface_contador = TTF_RenderText_Solid(recursos->font, recursos->texto_contador, recursos->colorTexto);
    recursos->textura_contador = SDL_CreateTextureFromSurface(recursos->render, recursos->surface_contador);
    recursos->cuadro_contador.w = recursos->surface_contador->w;
    recursos->cuadro_contador.h = recursos->surface_contador->h;
    SDL_FreeSurface(recursos->surface_contador);

    //Limpia la ventana
    SDL_SetRenderDrawColor(recursos->render, 0, 0, 0, 255);
    SDL_RenderClear(recursos->render);

    //Se agregan las particulas a la pantalla
    for (int i = 0; i < cantidad_particulas; i++) {
        SDL_SetRenderDrawColor(recursos->render, 240, 50, 250, 255);
        SDL_RenderFillRect(recursos->render, &particulas[i]);
    }

    //Se agrega el Texto a la pantalla
    SDL_RenderCopy(recursos->render, recursos->textura_colisiones, NULL, &(recursos->cuadro_texto));
    SDL_RenderCopy(recursos->render, recursos->textura_tiempo, NULL, &(recursos->cuadro_tiempo_transcurrido));
    SDL_RenderCopy(recursos->render, recursos->textura_contador, NULL, &(recursos->cuadro_contador));

    // Se imprime la pantalla
    SDL_RenderPresent(recursos->render);
}

void movimiento_particula(SDL_Rect *particula){
    //Movimiento +1
    particula->x+=particula->dx;
    particula->y+=particula->dy;
}

void colision_particulas(SDL_Rect *particula1, SDL_Rect *particula2, Recursos *recursos) {
    SDL_Rect interseccion;
    int aux_direccion, arriba=0,abajo=0,izquierda=0,derecha=0;
    SDL_IntersectRect(particula1, particula2, &interseccion);              //Extraigo la interseccion

    //Detecto donde se transpazo el limite de la particula
    if(interseccion.y == particula1->y){                                         // La intersección esta en la parte superior de la particula
        arriba=1;
    }
    if(interseccion.y + interseccion.h == particula1->y + particula1->h){      //La interseccion esta en la parte inferior de la particula
        abajo=1;
    }
    if(interseccion.x == particula1->x){                                         //La interseccion esta en la parte izquierda de la particula
        izquierda=1;
    }
    if(interseccion.x + interseccion.w == particula1->x + particula1->w){      //La interseccion esta en la parte derecha de la particula
        derecha=1;
    }

    if(arriba == 1 && izquierda == 1){
        do{
            aux_direccion=rand()%modulo_direccion;
        }while(aux_direccion == 2 || aux_direccion == 3 || aux_direccion == 4);
    }
    else if(arriba == 1 && derecha == 1){
        do{
            aux_direccion=rand()%modulo_direccion;
        }while(aux_direccion == 0 ||aux_direccion == 1 || aux_direccion == 2);
    }
    else if(abajo == 1 && derecha == 1){
        do{
            aux_direccion=rand()%modulo_direccion;
        }while(aux_direccion == 0 ||aux_direccion == 7 || aux_direccion == 6);
    }
    else if(abajo == 1 && izquierda == 1){
        do{
            aux_direccion=rand()%modulo_direccion;
        }while(aux_direccion == 4 ||aux_direccion == 5 || aux_direccion == 6);
    }
    asignacion_direcciones(particula1,aux_direccion);
}

void colisiones(Recursos *recursos, SDL_Rect *particulas, int cantidad_particulas) {
    //Recorro las particulas para ver con que chocan
    for(int i=0;i<cantidad_particulas;i++){
        int pared=0,choca_particula=0;     //Variables de control de choque

        //Colision con alguna pared
        if(particulas[i].x < 0 || particulas[i].x > recursos->DM.w-tamano_particula){pared += 1;}   //Paredes Verticales
        if(particulas[i].y < 0 || particulas[i].y > recursos->DM.h-tamano_particula){pared += 2;}   //Paredes Horizontales

        //Colison con una particula
        for (int j = 0; j < cantidad_particulas; j++) {
            if (i != j && SDL_HasIntersection(&particulas[i], &particulas[j])) {    //Si choca con una particula
                //if(particulas[i].p <= particulas[j].p){         //Si es de peso menor
                    if(pared == 0){             //Si no choca con una pared
                        colision_particulas(&particulas[i],&particulas[j],recursos);
                    }
                    else{       //Si choca con una pared y particula a la vez
                        particulas[i].dx=0;
                        particulas[i].dy=0;
                    }
                    recursos->contador_colisiones++;
                    choca_particula=1;
                //}
            }
        }

        //Si la particula solamente choco con la pared
        if((pared != 0) && (choca_particula == 0)){
            if(pared == 1)particulas[i].dx*=-1;                         //Invierto la direccion en X
            if(pared == 2)particulas[i].dy*=-1;                         //Invierto la direccion en Y
            if(pared == 3){particulas[i].dx*=-1;particulas[i].dy*=-1;}  //Invierto la direccion en X e Y
            Mix_PlayChannel(2,recursos->sonido_pared, 0);               //Reprodusco el sonido de choque con la pared
        }

    }

    for(int i=0;i<cantidad_particulas;i++){
        movimiento_particula(&particulas[i]);
    }
}

//Cuerpo principal del Codigo
int main(int argc,char *argv[]){
    int cantidad_particulas=0;                                          //Guarda la cantidad de particulas ingresados
    SDL_Rect *particulas=cuerpo_lectura(&cantidad_particulas);          //Array en donde se guardaran los datos

    //Inicializacion de las librerias
    if(inicializado_SDL2() == 1){free(particulas);return 0;}

    //Creacion de la estructura de recursos
    Recursos recursos;

    //Inicializacion de los recursos
    if(inicializado_de_recursos(&recursos) == 1){
        free(particulas);
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    //Ciclo de la simulacion
    while(recursos.running == 1){
        //Verifico los posibles eventos que esten ocurriendo(Alguna pulsacion de tecla, etc)
        particulas = control_de_eventos(&recursos, &cantidad_particulas, particulas);

        //Actualizo la pantalla
        visualizacion(particulas,&recursos,cantidad_particulas);

        //Calculo de la siguiente posicion y actualizacion de las direcciones de las particulas
        colisiones(&recursos,particulas,cantidad_particulas);
    }
    
    finalizacion_de_recursos_y_librerias(particulas,&recursos);

    return 0;
}