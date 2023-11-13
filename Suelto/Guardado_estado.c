#include <stdio.h>
#include <sys/stat.h>
#include <time.h>


int main(){
    char nombre_carpeta[40]= "Guardado Colisionador Particulas";
    if(access(nombre_carpeta,0) != 0){
        mkdir(nombre_carpeta);
    }

    char nombre_archivo[40];
    time_t tiempo;
    tiempo=time(NULL);

    sprintf(nombre_archivo,"%s/Save_%ld.txt",nombre_carpeta,tiempo);
    FILE *salida = fopen(nombre_archivo,"w");
    feof(salida);
    return 0;
}