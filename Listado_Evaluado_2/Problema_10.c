#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int precipitaciones[12][16];    //[meses][regiones]

    for(int j=0;j<12;j++){
        for(int k=0;k<16;k++){
            precipitaciones[j][k]=0;
        }
    }

    char meses[12][11]={"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
    
    char regiones[16][30]={"I","II","III","IV","V","VI","VII","VIII","IX","X","XI","XII","XIII","XIV","XV","XVI"};
    
    srand (time(NULL));

    for(int i=0;i<15;i++){
        for(int j=0;j<12;j++){
            for(int k=0;k<16;k++){
                if(j>=0 && j<=2){   //Verano
                    precipitaciones[j][k]+=rand()%600;
                }
                else if(j>2 && j<=5){   //Otono
                    precipitaciones[j][k]+=rand()%800;
                }
                else if(j>5 && j<=8){   //Invierno
                    precipitaciones[j][k]+=rand()%1000;
                }
                else if(j>8 && j<=11){  //Primavera
                    precipitaciones[j][k]+=rand()%700;
                }
                
            }
        }
    }

    for(int k=0;k<16;k++){
        if(k==0){
            printf("\t\t");
        }
        printf("%4s\t",regiones[k]);
    }
    printf("\n");

    for(int j=0;j<12;j++){
        for(int k=0;k<16;k++){
            precipitaciones[j][k]/=15;
            if(k==0){
                printf("%11s\t",meses[j]);
            }
            printf("%4d\t",precipitaciones[j][k]);
        }
         printf("\n");
    }

    return 0;
}