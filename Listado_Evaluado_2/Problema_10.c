#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int precipitaciones[12][16][15];    //[meses][regiones][anos]

    char meses[12][11]={"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
    
    char regiones[16][30]={
        "Region de Arica y Parinacota","Region de Tarapaca          ","Region de Antofagasta       ","Region de Atacama           ","Region de Coquimbo          ",
        "Region de Valparaiso        ","Region Metropolitana        ","Region de OHiggins          ","Region del Maule            ","Region del Nuble            ",
        "Region del Biobio           ","Region de La Araucania      ","Region de Los Rios          ","Region de Los Lagos         ","Region de Aysen             ",
        "Region de Magallanes        "
    };
    
    srand (time(NULL));

    for(int i=0;i<15;i++){
        printf("ANO %d\n",2009+i);
        for(int j=0;j<12;j++){
            printf("\t   En el mes de %s\n",meses[j]);
            for(int k=0;k<16;k++){
                precipitaciones[j][k][i]=rand()%1500;    //En la lluvia es poco probable que sobrepace este valor ya que en meses muy lluviosos caen  como 1200 mm
                printf("\t\t\t\t   En la %s calleron %4d mm de presipitaciones en promedio\n",regiones[k],precipitaciones[j][k][i]);
            }
        }
    }

    return 0;
}