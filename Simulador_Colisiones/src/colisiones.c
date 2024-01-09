#include <code/entrada.h>
#include <code/coliciones.h>

#ifndef VARIABLES_H
#define VARIABLES_H
#include <code/variables.h>
#endif

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
    if(interseccion.y == particula1->y){                                        // La intersección esta en la parte superior de la particula
        arriba=1;
    }
    if(interseccion.y + interseccion.h == particula1->y + particula1->h){       //La interseccion esta en la parte inferior de la particula
        abajo=1;
    }
    if(interseccion.x == particula1->x){                                        //La interseccion esta en la parte izquierda de la particula
        izquierda=1;
    }
    if(interseccion.x + interseccion.w == particula1->x + particula1->w){       //La interseccion esta en la parte derecha de la particula
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
                if(pared != 0){         //Si choca con una pared y particula a la vez, esto es independiente del peso que posean
                    //Les invierto la direccion para que se vallan de ahi
                    if(pared == 1)particulas[i].dx*=-1;                         //Invierto la direccion en X
                    if(pared == 1)particulas[j].dx*=-1;                         //Invierto la direccion en X

                    if(pared == 2)particulas[i].dy*=-1;                         //Invierto la direccion en Y
                    if(pared == 2)particulas[j].dy*=-1;                         //Invierto la direccion en Y

                    //La muevo otra ves para que no este pegada a la pared, para que no vuelva a cambiar su direccion
                    movimiento_particula(&particulas[i]);
                    //La que no toca la pared la muevo un ves mas para que no sigan intersectadas
                    movimiento_particula(&particulas[j]);
                    movimiento_particula(&particulas[j]);
                }
                
                else if(particulas[i].p <= particulas[j].p){             //Si no choca con una pared y si es de peso menor
                    colision_particulas(&particulas[i],&particulas[j],recursos);
                    movimiento_particula(&particulas[i]);   //Para que se salga de la interseccion
                }
                recursos->contador_colisiones++;
                choca_particula=1;

                //Comienzo la reproduccion del sonido de fondo
                if(cantidad_particulas <100)Mix_PlayChannel(1, recursos->sonido_golpe, 0);
            }
        }

        //Si la particula solamente choco con la pared
        if((pared != 0) && (choca_particula == 0)){
            if(pared == 1)particulas[i].dx*=-1;                         //Invierto la direccion en X
            if(pared == 2)particulas[i].dy*=-1;                         //Invierto la direccion en Y
            if(pared == 3){particulas[i].dx*=-1;particulas[i].dy*=-1;}  //Invierto la direccion en X e Y
            if(cantidad_particulas <100)Mix_PlayChannel(2,recursos->sonido_pared, 0);               //Reprodusco el sonido de choque con la pared
        }

    }

    for(int i=0;i<cantidad_particulas;i++){
        movimiento_particula(&particulas[i]);
    }
}
