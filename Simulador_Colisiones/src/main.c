#ifndef ENTRADA_H
#define ENTRADA_H
#include "entrada.h"
#endif // ENTRADA_H

#ifndef VISUALIZACION_H
#define VISUALIZACION_H
#include "visualizacion.h"
#endif // VISUALIZACION_H

#ifndef COLICIONES_H
#define COLICIONES_H
#include "coliciones.h"
#endif // COLICIONES_H

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

    //Muestro los videos iniciales
    if(videos_iniciales(&recursos) == 1){
        finalizacion_de_recursos_y_librerias(particulas,&recursos);
        return 0;
    }

    recursos.running = 1;   //Le reasigno 1 para que se ejecute el siguiente bucle

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