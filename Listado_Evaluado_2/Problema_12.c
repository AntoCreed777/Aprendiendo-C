#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    //Declaracion del String que recibira la palabra entrante
    char entrada[101];
    scanf("%s",entrada);
    int len=strlen(entrada);

    //Declaracion del array que almacenara los numeros de las letras
    int *numeros=(int*)malloc(sizeof(int)*len);

    //Obtengo los numeros que representan cada letra
    for(int i=0;i<len;i++){
        numeros[i]=entrada[i]-'a';
    }
    
    for(int i=1;i<len;i++){     //for que desace el modulo por 26 que se aplico a la hora de cifrarlo
        while(numeros[i]<numeros[i-1]){
            numeros[i]+=26;
        }
    }

    for(int i=len-1;i>0;i--){   //for que desace la suma de los numeros
        numeros[i]-=numeros[i-1];
    }

    if(numeros[0]>= 5){     //Si es mayor o igual a 5 significa que no se aplico ningun modulo de 26
        numeros[0]-=5;      //Se le resta 5 para obtener el numero original
    }
    else{                   //Si no significa que si se le aplico un modulo de 26 por lo que cambia lo que hay que hacer
        numeros[0] += 21;   //Forma compacta de 26+(numeros[0]-5) para deshacer la suma del 5 y el modulo que se le aplico al numero inicial
    }

    for(int i=0;i<len;i++){     //Impresion de las letras resultantes
        printf("%c",(char)(numeros[i]+'a'));
    }
    
    free(numeros);  //Liberacion de memoria

    return 0;
}