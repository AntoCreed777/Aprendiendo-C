#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
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
#define particulas_maximas 6000
#define volumen_fondo 2     //Maximo dividido por este numero
#define genera_particulas 1

//Estructura en que se guardaran los recursos necesarios para correr el programa
typedef struct {

    //Valores para el sonido
    Mix_Chunk *sonido_fondo;
    Mix_Chunk *sonido_inicio;
    Mix_Chunk *sonido_golpe;
    Mix_Chunk *sonido_pared;

    //Variable para la fuente del texto
    TTF_Font *font;

    //Variables que guardan los GIF (Videos)
    IMG_Animation *video_historia;
    IMG_Animation *video_inicio;

    //Surfaces para imprimir en pantalla
    SDL_Surface *surface_colisiones;
    SDL_Texture *textura_colisiones;

    SDL_Surface *surface_tiempo;
    SDL_Texture *textura_tiempo;

    SDL_Surface *surface_contador;
    SDL_Texture *textura_contador;

    SDL_Surface *surface_peso;
    SDL_Texture *textura_peso;

    SDL_Texture **textura_video_historia;
    SDL_Texture **textura_video_inicio;
    
    //Cuadros de texto para imprimir en pantalla
    SDL_Rect cuadro_texto;
    SDL_Rect cuadro_tiempo_transcurrido;
    SDL_Rect cuadro_contador;
    SDL_Rect cuadro_video;
    
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
    char texto_peso[20];            //Almacena el texto que muestra el peso de las particulas
    int frame_actual;               //Almacena el frame que actualmente se muestra en pnatalla
    int delay_video;                //Almacena el delay de los videos
    
} Recursos;