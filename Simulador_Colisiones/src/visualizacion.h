#ifndef ENTRADA_H
#define ENTRADA_H
#include "entrada.h"
#endif // ENTRADA_H

#ifndef VARIABLES_H
#define VARIABLES_H
#include "variables.h"
#endif // VARIABLES_H

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
    recursos->sonido_fondo = Mix_LoadWAV("assets/sonido_Fondo.mp3");
    recursos->sonido_inicio = Mix_LoadWAV("assets/sonido_inicio.mp3");
    recursos->sonido_golpe = Mix_LoadWAV("assets/right-cross-cross.mp3");
    recursos->sonido_pared = Mix_LoadWAV("assets/sonido_colision_pared.mp3");

    //Verifico que se hayan iniciado bien
    if (!recursos->sonido_golpe || !recursos->sonido_fondo || !recursos->sonido_pared) {
        printf("Error al cargar los archivos de audio: %s\n", Mix_GetError());
        return 1;
    }

    Mix_PlayChannel(0, recursos->sonido_inicio, -1);
    Mix_VolumeChunk(recursos->sonido_inicio, MIX_MAX_VOLUME);

    //Inicio la fuente en su respectiva variable
    recursos->font = TTF_OpenFont("assets/PottaOne-Regular.ttf", 50);

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
        TTF_CloseFont(recursos->font);
        SDL_DestroyWindow(recursos->ventana);
        return 1;
    }

    // Maximizo la ventana
    SDL_MaximizeWindow(recursos->ventana);

    //Cargo los videos en sus respectivas variables
    recursos->video_historia = IMG_LoadAnimation("assets/historia.gif");
    if (!recursos->video_historia) {
        SDL_Log("No se pudo cargar el video de historia");
        TTF_CloseFont(recursos->font);
        SDL_DestroyWindow(recursos->ventana);
        SDL_DestroyRenderer(recursos->render);
        return 1;
    }

    recursos->video_inicio = IMG_LoadAnimation("assets/inicio.gif");
    if (!recursos->video_inicio) {
        SDL_Log("No se pudo cargar el video de inicio");
        TTF_CloseFont(recursos->font);
        IMG_FreeAnimation(recursos->video_historia);
        SDL_DestroyWindow(recursos->ventana);
        SDL_DestroyRenderer(recursos->render);
        return 1;
    }

    //Creo la textura para los videos
    recursos->textura_video_historia = (SDL_Texture **)SDL_calloc(recursos->video_historia->count, sizeof(*recursos->textura_video_historia));
    if (!recursos->textura_video_historia) {
        SDL_Log("No se pudo crear la textura del video de historia");
        TTF_CloseFont(recursos->font);
        IMG_FreeAnimation(recursos->video_historia);
        IMG_FreeAnimation(recursos->video_inicio);
        SDL_DestroyWindow(recursos->ventana);
        SDL_DestroyRenderer(recursos->render);
        return 1;
    }

    recursos->textura_video_inicio = (SDL_Texture **)SDL_calloc(recursos->video_inicio->count, sizeof(*recursos->textura_video_inicio));
    if (!recursos->textura_video_inicio) {
        SDL_Log("No se pudo crear la textura del video de inicio");
        TTF_CloseFont(recursos->font);
        SDL_free(recursos->textura_video_historia);
        IMG_FreeAnimation(recursos->video_historia);
        IMG_FreeAnimation(recursos->video_inicio);
        SDL_DestroyWindow(recursos->ventana);
        SDL_DestroyRenderer(recursos->render);
        return 1;
    }

    //Cargo los frames en las texturas de video
    for (int j = 0; j < recursos->video_historia->count; ++j) {
        recursos->textura_video_historia[j] = SDL_CreateTextureFromSurface(recursos->render, recursos->video_historia->frames[j]);
    }

    for (int j = 0; j < recursos->video_inicio->count; ++j) {
        recursos->textura_video_inicio[j] = SDL_CreateTextureFromSurface(recursos->render, recursos->video_inicio->frames[j]);
    }

    //Le asigno los valores RGB del texto que se muestra en pantalla
    recursos->colorTexto.r = 250;
    recursos->colorTexto.g = 130;
    recursos->colorTexto.b = 50;
    recursos->colorTexto.a = 255;

    //Asigna las posiciones de los cuadros de texto
    recursos->cuadro_texto_trasero.x = 0;
    recursos->cuadro_texto_trasero.y = (recursos->DM.h) - 3*70 - 10;
    recursos->cuadro_texto_trasero.w = 870;
    recursos->cuadro_texto_trasero.h = 3*70 + 10;

    recursos->cuadro_texto.x = 0;
    recursos->cuadro_texto.y = (recursos->DM.h) - 70;

    recursos->cuadro_tiempo_transcurrido.x = 0;
    recursos->cuadro_tiempo_transcurrido.y = (recursos->DM.h) - 3*70;

    recursos->cuadro_contador.x = 0;
    recursos->cuadro_contador.y = (recursos->DM.h) - 2*70;

    //ASignacion de valores para el cuadro del video
    recursos->cuadro_video.x = 0;
    recursos->cuadro_video.y = 0;
    recursos->cuadro_video.w = recursos->DM.w;
    recursos->cuadro_video.h = recursos->DM.h;

    //Inicializo otras variables
    recursos->running = 1;
    recursos->contador_colisiones = 0;
    recursos->tiempo_inicial = time(NULL);
    recursos->frame_actual = 0;

    //Inicializar imagenes
    recursos->textura_gato = IMG_LoadTexture(recursos->render, "assets/gato_2.png");
    if (recursos->textura_gato == NULL) {
        SDL_Log("No se pudo crear la textura de la imagen del gato");
        TTF_CloseFont(recursos->font);
        SDL_free(recursos->textura_video_inicio);
        SDL_free(recursos->textura_video_historia);
        IMG_FreeAnimation(recursos->video_historia);
        IMG_FreeAnimation(recursos->video_inicio);
        SDL_DestroyWindow(recursos->ventana);
        SDL_DestroyRenderer(recursos->render);
        return 1;
    }

    recursos->textura_perro = IMG_LoadTexture(recursos->render, "assets/perro_2.png");
    if (recursos->textura_perro == NULL) {
        SDL_Log("No se pudo crear la textura de la imagen del perro");
        TTF_CloseFont(recursos->font);
        SDL_DestroyTexture(recursos->textura_gato);
        SDL_free(recursos->textura_video_inicio);
        SDL_free(recursos->textura_video_historia);
        IMG_FreeAnimation(recursos->video_historia);
        IMG_FreeAnimation(recursos->video_inicio);
        SDL_DestroyWindow(recursos->ventana);
        SDL_DestroyRenderer(recursos->render);
        return 1;
    }

    recursos->textura_fondo = IMG_LoadTexture(recursos->render, "assets/fondo.png");
    if (recursos->textura_fondo == NULL) {
        SDL_Log("No se pudo crear la textura del fondo");
        TTF_CloseFont(recursos->font);
        SDL_DestroyTexture(recursos->textura_gato);
        SDL_DestroyTexture(recursos->textura_perro);
        SDL_free(recursos->textura_video_inicio);
        SDL_free(recursos->textura_video_historia);
        IMG_FreeAnimation(recursos->video_historia);
        IMG_FreeAnimation(recursos->video_inicio);
        SDL_DestroyWindow(recursos->ventana);
        SDL_DestroyRenderer(recursos->render);
        return 1;
    }

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
    Mix_FreeChunk(recursos->sonido_pared);

    // Libera las texturas
    SDL_DestroyTexture(recursos->textura_colisiones);
    SDL_DestroyTexture(recursos->textura_tiempo);
    SDL_DestroyTexture(recursos->textura_contador);
    SDL_DestroyTexture(recursos->textura_peso);
    SDL_DestroyTexture(recursos->textura_gato);
    SDL_DestroyTexture(recursos->textura_perro);

    //Destruccion de la ventana
    SDL_DestroyRenderer(recursos->render);
    SDL_DestroyWindow(recursos->ventana);

    //Cierre de las librerias de SDL2
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

void liberar_video(Recursos *recursos){
    //Destruyo las texturas de los frames del video
    for (int j = 0; j < recursos->video_historia->count; ++j) {
        SDL_DestroyTexture(recursos->textura_video_historia[j]);
    }

    for (int j = 0; j < recursos->video_inicio->count; ++j) {
        SDL_DestroyTexture(recursos->textura_video_inicio[j]);
    }

    SDL_free(recursos->textura_video_historia);
    SDL_free(recursos->textura_video_inicio);
    IMG_FreeAnimation(recursos->video_historia);
    IMG_FreeAnimation(recursos->video_inicio);
}

//Funciones de eventos
void guardado(SDL_Rect *particulas,int cantidad_particulas){
    char nombre_carpeta[33]= "Guardado Colisionador Particulas";
    if(access(nombre_carpeta,0) != 0){
        mkdir(nombre_carpeta);
    }

    char nombre_destino[55];
    char nombre_archivo[20];
    time_t tiempo;
    tiempo=time(NULL);

    sprintf(nombre_archivo, "Save_%ld.txt", (long int) tiempo);
    sprintf(nombre_destino, "%s/%s", nombre_carpeta,nombre_archivo);

    FILE *salida = fopen(nombre_destino,"w");

    fputc('c',salida);
    fputc('\n',salida);
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
    printf("\nInformacion de las particulas guardado en:\n%s%sCarpeta:%s\t%s%s%s%s\n%s%sArchivo:%s\t%s%s%s%s",
    BOLD,BLUE,NORMAL,BOLD,WHITE,nombre_carpeta,NORMAL,BOLD,BLUE,NORMAL,BOLD,WHITE,nombre_archivo,NORMAL);

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
                for(int i=0; i<genera_particulas;i++){
                    if((*cantidad_particulas) < particulas_maximas){   //El limite de pariculas en pantalla
                        particulas = crear_particula(particulas,cantidad_particulas,recursos->DM);
                    }
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
            else if(key == SDLK_c){     //limpia la pantalla de particulas
                particulas = NULL;
                (*cantidad_particulas) = 0;
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
int videos_iniciales(Recursos *recursos){
    int video = 0; //Si es 0 se ejecuta video de historia, si es 1 video de inicio
    
    while(recursos->running){
        if(SDL_PollEvent(&(recursos->evento))){
            if(recursos->evento.type == SDL_QUIT){    //Si se aprieta la X de la ventana para salir
                recursos->running = 0;
            }
            if(recursos->evento.type == SDL_KEYDOWN){     //Si se aprieta una tecla
                recursos->running = 0;
            }
        }
        if(video == 0){     //Video Historia
            SDL_RenderCopy(recursos->render, recursos->textura_video_historia[recursos->frame_actual], NULL, &recursos->cuadro_video);
            SDL_RenderPresent(recursos->render);

            if (recursos->video_historia->delays[recursos->frame_actual]) {
                recursos->delay_video = recursos->video_historia->delays[recursos->frame_actual];
            } else {
                recursos->delay_video = 100;
            }
            SDL_Delay(recursos->delay_video);

            recursos->frame_actual++;
            if(recursos->video_historia->count == recursos->frame_actual){
                recursos->frame_actual = 0;
                video = 1;
            }

        }
        else{               //Video Inicio
            SDL_RenderCopy(recursos->render, recursos->textura_video_inicio[recursos->frame_actual], NULL, &recursos->cuadro_video);
            SDL_RenderPresent(recursos->render);

            if (recursos->video_inicio->delays[recursos->frame_actual]) {
                recursos->delay_video = recursos->video_inicio->delays[recursos->frame_actual];
            } else {
                recursos->delay_video = 100;
            }
            SDL_Delay(recursos->delay_video);

            recursos->frame_actual = (recursos->frame_actual + 1) % recursos->video_inicio->count;  //Permanece en bucle
        }

    }

    liberar_video(recursos);

    return 0;
}

void visualizacion(SDL_Rect *particulas, Recursos *recursos, int cantidad_particulas) {
    //Limpia la ventana
    SDL_SetRenderDrawColor(recursos->render, 0, 0, 0, 255);
    SDL_RenderClear(recursos->render);
    
    //Textura del fondo
    SDL_RenderCopy(recursos->render, recursos->textura_fondo, NULL, NULL);


    SDL_RenderFillRect(recursos->render, &recursos->cuadro_texto_trasero);

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
    sprintf(recursos->texto_tiempo, "Tiempo transcurrido: %d min %d s", (int)recursos->tiempo_que_paso/60,(int)recursos->tiempo_que_paso%60);

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

    //Se agregan las particulas a la pantalla
    for (int i = 0; i < cantidad_particulas; i++) {
        if (particulas[i].p%2==0){
            SDL_RenderCopy(recursos->render, recursos->textura_gato, NULL, &particulas[i]);
        }
        else{
            SDL_RenderCopy(recursos->render, recursos->textura_perro, NULL, &particulas[i]);
        }
        //SDL_SetRenderDrawColor(recursos->render, 240, 50, 250, 255);
        //SDL_RenderFillRect(recursos->render, &particulas[i]);

        sprintf(recursos->texto_peso, "%d", particulas[i].p);
        recursos->surface_peso = TTF_RenderText_Solid(recursos->font, recursos->texto_peso, recursos->colorTexto);
        recursos->textura_peso = SDL_CreateTextureFromSurface(recursos->render, recursos->surface_peso);
        SDL_FreeSurface(recursos->surface_peso);
        SDL_RenderCopy(recursos->render, recursos->textura_peso, NULL, &(particulas[i]));
    }

    //Se agrega el Texto a la pantalla
    SDL_RenderCopy(recursos->render, recursos->textura_colisiones, NULL, &(recursos->cuadro_texto));
    SDL_RenderCopy(recursos->render, recursos->textura_tiempo, NULL, &(recursos->cuadro_tiempo_transcurrido));
    SDL_RenderCopy(recursos->render, recursos->textura_contador, NULL, &(recursos->cuadro_contador));

    // Se imprime la pantalla
    SDL_RenderPresent(recursos->render);
}
