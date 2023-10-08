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

    
    
    numeros[0]+=5;  //Se le resta 5 para obtener el numero original
    for(int i=1;i<len;i++){   //for que hace la suma de los numeros
        numeros[i]=numeros[i]+numeros[i-1];
    }
    
    for(int i=0;i<len;i++){     
        while(numeros[i]>25){
            numeros[i]%=26;
        }
    }

    //Obtengo las letras que representan cada numero
    for(int i=0;i<len;i++){
        entrada[i]=numeros[i]+'a';
    }

    for(int i=0;i<len;i++){     //Impresion de las letras finales
        printf("%c",entrada[i]);
    }
    
    return 0;
}