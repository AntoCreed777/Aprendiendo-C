#ifndef VARIABLES_H
#define VARIABLES_H
#include <code/variables.h>
#endif

//Funciones de inicializado y cierre
int inicializado_SDL2();

int inicializado_de_recursos(Recursos*);

void finalizacion_de_recursos_y_librerias(SDL_Rect*,Recursos*);

void liberar_video(Recursos*);

//Funciones de eventos
void guardado(SDL_Rect*,int );

SDL_Rect* crear_particula(SDL_Rect*, int*,SDL_DisplayMode Dimencion);

SDL_Rect* destruir_particula(SDL_Rect*, int*);

SDL_Rect* control_de_eventos(Recursos*,int*,SDL_Rect*);

// Funcion de visualizado
int videos_iniciales(Recursos*);

void visualizacion(SDL_Rect*, Recursos*, int );