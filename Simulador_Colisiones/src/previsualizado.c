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
#define tamano_particula 30


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
    /*for(int i=0;i<(*cantidad_particulas);i++){
        printf("%s%s%u\t%u\t%u\t%u%s\n",BOLD,BLUE,particulas[i].x,particulas[i].y,particulas[i].d,particulas[i].p,NORMAL);
    }*/
    return particulas;
}

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
        fprintf(salida,"%d;%d;%d;%d;\n",particulas[i].x,particulas[i].y,particulas[i].d,particulas[i].p);
    }

    fclose(salida);
}

SDL_Rect* crear_particula(SDL_Rect *particulas, int *cantidad_particulas,SDL_DisplayMode Dimencion){
    (*cantidad_particulas)++;
    particulas=(SDL_Rect*)realloc(particulas,sizeof(SDL_Rect)*(*cantidad_particulas));
    int x,y,colision=0;
    while(1){
        x=rand()%(Dimencion.w-tamano_particula);    //Obtengo la posicion en X
        y=rand()%(Dimencion.h-tamano_particula);    //Obtengo la posicion en Y
        for(int i=0;i<(*cantidad_particulas);i++){      //Recorro cada particula
            if(x <= particulas[i].x+tamano_particula && x >= particulas[i].x && y <= particulas[i].y+tamano_particula && y >= particulas[i].y){
                colision=1; //Si hay una particula
                break;      //Sale del for
            }
        }
        if(!colision){
            particulas[(*cantidad_particulas)-1].x=x;
            particulas[(*cantidad_particulas)-1].y=y;
            break;
        }
    }

    int d=rand()%modulo_direccion;
    particulas[(*cantidad_particulas)-1].d=d;

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

int main(int argc,char *argv[]){
    int cantidad_particulas=0;                                          //Guarda la cantidad de particulas ingresados
    SDL_Rect *particulas=cuerpo_lectura(&cantidad_particulas);          //Array en donde se guardaran los datos
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////// FIN LECTURA ///////////INICIO VISUALIZACION/////////// Y-O MOVIMIENTO ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Inicializacion de SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
        SDL_Log("Incapaz de inicializar SDL: %s", SDL_GetError());
        return 1;
    }
    //Configuracion Audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        printf("Error al inicializar SDL_mixer: %s\n", Mix_GetError());
        return -1;
    }
    Mix_Chunk *sonido_fondo = Mix_LoadWAV("assets/Sonido_Fondo.mp3");
    Mix_Chunk *sonido_golpe = Mix_LoadWAV("assets/right-cross-cross.mp3");
    if (!sonido_golpe || !sonido_fondo) {
        printf("Error al cargar el archivo de audio: %s\n", Mix_GetError());
        return -1;
    }
    Mix_PlayChannel(0,sonido_fondo, -1);
    //Inicializo SDL_TTF
    if (TTF_Init() != 0) {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    //Creacion del Texto
    TTF_Font *font;
    font = TTF_OpenFont("assets/Handlee-Regular.ttf",24);
    if(!font){
        printf("TTF_OpenFont:   %s\n",TTF_GetError());
    }
    SDL_Surface *surface_colisiones;
    SDL_Surface *tiempo_transcurrido;
    SDL_Surface *delay;
    SDL_Surface *contador;

    // Obtengo la maxima resolucion de la pantalla
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode(0, &DM);
    //Creacion de la ventana
    SDL_Window *ventana = SDL_CreateWindow("Desplegable",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,DM.w,DM.h,SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);
    if(ventana == NULL){
        SDL_Log("Incapaz de crear la ventana: %s", SDL_GetError());
        return 1;
    }

    SDL_Surface *screen_surface = SDL_GetWindowSurface(ventana);
    int running = 1;
    SDL_Event evento;

    for(int i=0;i<cantidad_particulas;i++){ //Le doy dimencion a las particulas
        particulas[i].h=tamano_particula;
        particulas[i].w=tamano_particula;
    }

    SDL_Point mouse;

    int cambio_color = 0;
    int contador_colisiones=0;
    time_t tiempo_inicial = time(NULL);
    int DELAY=0;        //Controla el Delay de la pantalla
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
                else if(key == SDLK_g){
                    guardado(particulas,cantidad_particulas);
                }
                else if(key == SDLK_m){
                    if(cantidad_particulas < 20){   //El limite de pariculas en pantalla es de 20
                        particulas = crear_particula(particulas,&cantidad_particulas,DM);
                    }
                }
                else if(key == SDLK_k){
                    if(cantidad_particulas >0){ //Si existen particulas se eliminan
                        particulas=destruir_particula(particulas,&cantidad_particulas);
                    }
                }
                else if(key == SDLK_t){
                    if(DELAY < 100){    //Solo se puede colocar un DELAY maximo de 100
                        DELAY++;
                    }
                }
                else if(key == SDLK_y){
                    if(DELAY > 0){     //No puede ser negativo el DELAY
                        DELAY--;
                    }
                }
                else if(key == SDLK_r){ //Se reinicia el contador de coliciones
                    contador_colisiones=0;
                }
            }
            if(evento.type == SDL_MOUSEBUTTONDOWN){
                mouse.x = evento.button.x;
                mouse.y = evento.button.y;
                SDL_Log("Hice CLICK en (%d,%d)",mouse.x,mouse.y);
            }
        }
        SDL_Color colorTexto = {255 + cambio_color, 255 + cambio_color, 255 + cambio_color, 255};

        //Se actualiza la surface del texto
        char texto_colisiones[30];
        sprintf(texto_colisiones,"Colisiones: %d",contador_colisiones);
        surface_colisiones = TTF_RenderText_Solid(font,texto_colisiones,colorTexto);

        //Se actualiza la surface del tiempo transcurrido
        char texto_tiempo[30];
        time_t tiempo_actual = time(NULL);
        time_t tiempo_que_paso = tiempo_actual - tiempo_inicial;
        sprintf(texto_tiempo,"Tiempo transcurrido: %ld",(long int)tiempo_que_paso);
        tiempo_transcurrido = TTF_RenderText_Solid(font,texto_tiempo,colorTexto);
        
        // Se actualiza la superficie del Delay
        char texto_delay[30];
        sprintf(texto_delay,"DELAY: %d",DELAY);
        delay = TTF_RenderText_Solid(font,texto_delay,colorTexto);

        // Se actualiza la superficie del contador de particulas
        char texto_contador[30];
        sprintf(texto_contador,"Cantidad de Particulas: %d",cantidad_particulas);
        contador = TTF_RenderText_Solid(font,texto_contador,colorTexto);

        //Limpia la ventana
        SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 255 + cambio_color, 120 + cambio_color, 25 + cambio_color));
        
        //Se agregan las particulas a la pantalla
        for(int i=0;i<cantidad_particulas;i++){
            SDL_FillRect(screen_surface, &particulas[i], SDL_MapRGB(screen_surface->format, 0 + cambio_color, 255 + cambio_color, 0 + cambio_color));
        }

        //Se agrega el Texto a la pantalla
        SDL_Rect cuadro_texto={0,90};
        SDL_Rect cuadro_tiempo_transcurrido={0,0};
        SDL_Rect cuadro_delay={0,30};
        SDL_Rect cuadro_contador={0,60};
        SDL_BlitSurface(surface_colisiones, NULL, screen_surface, &cuadro_texto);
        SDL_BlitSurface(tiempo_transcurrido, NULL, screen_surface, &cuadro_tiempo_transcurrido);
        SDL_BlitSurface(delay, NULL, screen_surface, &cuadro_delay);
        SDL_BlitSurface(contador, NULL, screen_surface, &cuadro_contador);
        
        //Se imprime la pantalla
        SDL_UpdateWindowSurface(ventana);

        //Calculo de la siguiente posicion y actualizacion de valores particulas
        for(int i=0;i<cantidad_particulas;i++){
            //Colicion con algun borde de la ventana
            if(particulas[i].x <= 0){                       //Borde Izquierdo
                if(particulas[i].d == 3){
                    particulas[i].d= 1;
                }
                else if(particulas[i].d == 4){
                    particulas[i].d= 0;
                }
                else if(particulas[i].d == 5){
                    particulas[i].d= 7;
                }
            }
            if(particulas[i].x >= DM.w-tamano_particula){   //Borde Derecho
                if(particulas[i].d == 7){
                    particulas[i].d= 5;
                }
                else if(particulas[i].d == 0){
                    particulas[i].d= 4;
                }
                else if(particulas[i].d == 1){
                    particulas[i].d= 3;
                }
            }
            if(particulas[i].y <= 0){                       //Borde Superior
                if(particulas[i].d == 1){
                    particulas[i].d= 7;
                }
                else if(particulas[i].d == 2){
                    particulas[i].d= 6;
                }
                else if(particulas[i].d == 3){
                    particulas[i].d= 5;
                }
            }
            if(particulas[i].y >= DM.h-tamano_particula){   //Borde Inferior
                if(particulas[i].d == 7){
                    particulas[i].d= 1;
                }
                else if(particulas[i].d == 6){
                    particulas[i].d= 2;
                }
                else if(particulas[i].d == 5){
                    particulas[i].d= 3;
                }
            }
            
            //Colicion con otra particula
            for(int j=0;j<cantidad_particulas;j++){ //Recorro las particulas
                for(int k=0;k<cantidad_particulas;k++){ //Recorro las particulas menos la de la J
                    if(SDL_HasIntersection(&particulas[j],&particulas[k]) && j!=k && particulas[j].p<=particulas[k].p){ //Si se intersectan 
                        SDL_Rect interseccion;
                        int aux_direccion, arriba=0,abajo=0,izquierda=0,derecha=0;
                        SDL_IntersectRect(&particulas[j], &particulas[k], &interseccion);              //Extraigo la interseccion

                        //Detecto donde se transpazo el limite de la particula
                        if(interseccion.y == particulas[j].y){                                         // La intersección esta en la parte superior de la particula
                            arriba=1;
                        }
                        if(interseccion.y + interseccion.h == particulas[j].y + particulas[j].h){      //La interseccion esta en la parte inferior de la particula
                            abajo=1;
                        }
                        if(interseccion.x == particulas[j].x){                                         //La interseccion esta en la parte izquierda de la particula
                            izquierda=1;
                        }
                        if(interseccion.x + interseccion.w == particulas[j].x + particulas[j].w){      //La interseccion esta en la parte derecha de la particula
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
                        particulas[j].d=aux_direccion;

                        // Reproducir sonido de golpe
                        Mix_PlayChannel(1,sonido_golpe, 0);
                        cambio_color+= 4;
                        contador_colisiones++;
                        switch (particulas[j].d)    //Los desplazo un espacio extra
                        {
                        case 0: //Derecha
                            particulas[j].x++ ;    //X
                            break;
                        case 1: //Derecha Arriba
                            particulas[j].x++ ;    //X
                            particulas[j].y-- ;    //Y
                            break;
                        case 2: //Arriba
                            particulas[j].y-- ;    //Y
                            break;
                        case 3: //Arriba Izquierda
                            particulas[j].x-- ;    //X
                            particulas[j].y-- ;    //Y
                            break;
                        case 4: //Izquierda
                            particulas[j].x-- ;    //X
                            break;
                        case 5: //Izquierda Abajo
                            particulas[j].x-- ;    //X
                            particulas[j].y++ ;    //Y
                            break;
                        case 6: //Abajo
                            particulas[j].y++ ;    //Y
                            break;
                        case 7: //Abajo Derevha
                            particulas[j].x++ ;    //X
                            particulas[j].y++ ;    //Y
                            break;
                        }
                    }
                }
            }
        
            //Movimiento +1
            switch (particulas[i].d)
            {
            case 0: //Derecha
                particulas[i].x++ ;    //X
                break;
            case 1: //Derecha Arriba
                particulas[i].x++ ;    //X
                particulas[i].y-- ;    //Y
                break;
            case 2: //Arriba
                particulas[i].y-- ;    //Y
                break;
            case 3: //Arriba Izquierda
                particulas[i].x-- ;    //X
                particulas[i].y-- ;    //Y
                break;
            case 4: //Izquierda
                particulas[i].x-- ;    //X
                break;
            case 5: //Izquierda Abajo
                particulas[i].x-- ;    //X
                particulas[i].y++ ;    //Y
                break;
            case 6: //Abajo
                particulas[i].y++ ;    //Y
                break;
            case 7: //Abajo Derevha
                particulas[i].x++ ;    //X
                particulas[i].y++ ;    //Y
                break;
            }
        }
    
        SDL_Delay(DELAY);
    }

    //Liberacion de la memoria usada en el programa
    free(particulas);
    //Destruccion de la ventana y cierre de SDL
    TTF_CloseFont(font);
    SDL_FreeSurface(surface_colisiones);
    SDL_FreeSurface(screen_surface);
    SDL_DestroyWindow(ventana);
    Mix_FreeChunk(sonido_fondo);
    Mix_FreeChunk(sonido_golpe);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    return 0;
}