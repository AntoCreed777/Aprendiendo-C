#include <stdio.h>
#include <stdlib.h>

int main(){
    int cantidad_elementos;
    scanf("%d",&cantidad_elementos);
    int *array = (int*)malloc(sizeof(int)*cantidad_elementos);
    for(int i=0;i<cantidad_elementos;i++){
        scanf("%d",&array[i]);             //Asignacion
    }

    for(int i=0;i<cantidad_elementos;i++){  //busca no repetido
        int repetido=0;
        for(int j=0;j<cantidad_elementos;j++){
            if(i!=j && array[i] == array[j]){
                repetido=1;
            }
        }
        if(repetido==0){
            printf("%d",array[i]);
            free(array);
            return 0;
        }
    }
    free(array);
    return 0;
}