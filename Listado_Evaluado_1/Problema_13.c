/*INPUT
La primera línea contiene un número de candidatos N (1 ≤ N ≤ 10000) y un número de electores M (1 ≤ M ≤ 10000).
Luego siguen M líneas, cada una contiene un número de candidatos por los que votó el elector.
Los candidatos están numerados con números enteros del 1 al N.

OUTPUT
Salida N líneas. La línea i-ésima debe contener el porcentaje de electores que votaron por el candidato i-ésimo
(con una precisión de 2 decimales)*/

#include <stdio.h>
#include<stdlib.h>

int main(){
    //Ingreso de Datos Iniciales
    float n;
    float m;
    printf("Ingrese la cantidad de candidatos: ");
    scanf("%f",&n);
    while(n>10000 || n<1){
        printf("EL numero debe estar entre 1 y 10000\nIngrese la cantidad de candidatos: ");
        scanf("%f",&n);
    }
    printf("Ingrese la cantidad de electores: ");
    scanf("%f",&m);
    while(m>10000 || m<1){
        printf("EL numero debe estar entre 1 y 10000\nIngrese la cantidad de electores: ");
        scanf("%f",&m);
    }

    //Creaccion ded lista que almacena los votos
    int *votos;
    votos=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        votos[i]=0;
    }
    //Votacion a nivel nacional XD

    int aux;
    for(int i=0;i<m;i++){
        printf("Ingrese el voto numero %d: ",i+1);
        scanf("%d",&aux);
        while(aux<1 || aux>n){
            printf("Los numeros de los candidatos van desde 1 hasta %.0f\nIngrese el voto numero %d: ",n,i+1);
            scanf("%d",&aux);
        }
        votos[aux-1]+=1;
    }


    //Entregas de los resultados de las votaciones
    float porcentaje;
    printf("\n");
    for(int i=0;i<n;i++){
        porcentaje=(votos[i]/m)*100;
        printf("El candicato cuyo numero es %d obtuvo un %.2f %% de aprobacion\n",i+1,porcentaje);
    }
    return 0;
}