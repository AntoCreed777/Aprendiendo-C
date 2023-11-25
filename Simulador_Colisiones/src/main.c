#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define DELAY 5

int main(int argc,char *argv[]){
    //Inicializacion de SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
        SDL_Log("Incapaz de inicializar SDL: %s", SDL_GetError());
        return 1;
    }

    // Obtengo la maxima resolucion de la pantalla
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode(0, &DM);

    //Creacion de la ventana
    SDL_Window *ventana = SDL_CreateWindow("Desplegable",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,DM.w,DM.h,SDL_WINDOW_FULLSCREEN);
    if(ventana == NULL){
        SDL_Log("Incapaz de crear la ventana: %s", SDL_GetError());
        return 1;
    }

    SDL_Surface *screen_surface = SDL_GetWindowSurface(ventana);
    int running = 1;
    SDL_Event evento;

    SDL_Rect rect;
    rect.x= 100;
    rect.y = 100;
    rect.w = 50;
    rect.h = 50;

    SDL_Point mouse;

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

        SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 255, 120, 25));

        rect.x ++;
        rect.y ++;

        SDL_FillRect(screen_surface, &rect, SDL_MapRGB(screen_surface->format, 120, 25, 255));

        SDL_UpdateWindowSurface(ventana);

        SDL_Delay(DELAY);
    }

    //Destruccion de la ventana y cierre de SDL
    SDL_FreeSurface(screen_surface);
    SDL_DestroyWindow(ventana);
    SDL_Quit();

    return 0;
}