#ifndef VARIABLES_H
#define VARIABLES_H
#include <code/variables.h>
#endif

//Funciones de lectura
void asignacion_direcciones(SDL_Rect*,int);

char* ingreso_string();

FILE* ingreso_archivo();

SDL_Rect* CSV(FILE*,int*);

SDL_Rect* BINARIO(FILE*,int*);

SDL_Rect* TEXTO(FILE*,int*);

SDL_Rect* cuerpo_lectura(int*);