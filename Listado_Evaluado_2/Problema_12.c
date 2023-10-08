#include <stdio.h>
#include <string.h>
int main(){
    //Declaracion del String que recibira la palabra entrante
    char entrada[100];
    scanf("%s",entrada);
    int len=strlen(entrada);

    //Declaracion del array que almacenara los numeros de las letras
    int numeros[len];

    //Obtengo los numeros que representan cada letra
    for(int i=0;i<len;i++){
        numeros[i]=entrada[i]-'a';
    }


    int anterior=numeros[0];    //Variable que almacenara el valor anterior al ciclo actual para comparar
    int actual;                 //Variable que almacenara el valor actual al ciclo para comparar
    
    for(int i=1;i<len;i++){     //for que desace el modulo por 26 que se aplico a la hora de cifrarlo
        actual=numeros[i];
        while(actual<anterior){
            numeros[i]+=26;
            actual=numeros[i];
        }
        anterior=actual;
    }

    for(int i=len-1;i>0;i--){   //for que desace la suma de los numeros
        numeros[i]=numeros[i]-numeros[i-1];
    }
    numeros[0]-=5;  //Se le resta 5 para obtener el numero original

    //Obtengo las letras que representan cada numero
    for(int i=0;i<len;i++){
        entrada[i]=numeros[i]+'a';
    }

    for(int i=0;i<len;i++){     //Impresion de las letras finales
        printf("%c",entrada[i]);
    }
    
    return 0;
}