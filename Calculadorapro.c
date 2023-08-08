#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

bool comprobador(char operacion[]){
    char aux[]="0123456789+-/*";
    for(int i=0;i<strlen(operacion);i++){
        bool esOperador = false;
        for(int j=0;j<strlen(aux);j++){
            if(operacion[i]==aux[j]){
                esOperador = true;
                break;
            }
        }
        if(!esOperador){
            return false;
        }
    }
    return true;

}

void ingreso(char operacion[]){
    printf("Ingrese la operacion a realizar: ");
    scanf("%s",operacion);
    while (comprobador(operacion)==false){
        printf("\nLa operacion es invalida\nVuelava a ingresar la operacion a realizar: ");
        scanf("%s",operacion);
    }
}

void selector1(char operacion[],char *signo,int *posinicial1,int *posfinal1,int *posinicial2,int *posfinal2){
    for(int i=0;i<strlen(operacion);i++){
        *signo=operacion[i];
        if(*signo=='/' || *signo=='*'){
            for(int j=i-1;j>=0;j--){
                if (j==0){
                    *posinicial1=0;
                    break;
                }
                if(operacion[j]=='+' || operacion[j]=='-' || operacion[j]=='/' || operacion[j]=='*'){
                    *posinicial1=j+1;
                    break;
                }
            }
            *posfinal1=i-1;
            for(int j=i+1;j<=strlen(operacion);j++){
                if (j==strlen(operacion)){
                    *posfinal2=strlen(operacion)-1;
                    break;
                }
                if(operacion[j]=='+' || operacion[j]=='-' || operacion[j]=='/' || operacion[j]=='*'){
                    *posfinal2=j-1;
                    break;
                }
            }
            *posinicial2=i+1;
            break;
        }
    }
}

void numerosf(char operacion[],int posinicial1,int posfinal1,int posinicial2,int posfinal2,int *numero1,int *numero2){
    for(int i=posinicial1;i<=posfinal1;i++){
        *numero1=(*numero1)*10+(operacion[i]-'0');
    }
    for(int i=posinicial2;i<=posfinal2;i++){
        *numero2=(*numero2)*10+(operacion[i]-'0');
    }
}

int operacionf(char signo,int numero1,int numero2){
    int resultado;
    if (signo=='+'){
        resultado = numero1 + numero2;
    }

    if (signo=='-'){
        resultado = numero1 - numero2;
    }

    if (signo=='*'){
        resultado = numero1 * numero2;
    }

    if (signo=='/'){
        if(numero2 == 0){
            printf("No se puede hacer una division por 0");
            exit(0);
        }
        resultado = numero1 / numero2;
    }

    return resultado;
}

int main(){
    char operacion[20];
    ingreso(operacion);
    char signo;
    int posinicial1;
    int posfinal1;
    int posinicial2;
    int posfinal2;
    int contador=0;

    for(int i=0;i<strlen(operacion);i++){
        if(operacion[i]=='+' || operacion[i]=='-' || operacion[i]=='/' || operacion[i]=='*'){
            contador+=1;
        }
    }
    
    for (int q=0;q<contador;q++){
        selector1(operacion,&signo,&posinicial1,&posfinal1,&posinicial2,&posfinal2);

        int numero1=0;
        int numero2=0;

        numerosf(operacion,posinicial1,posfinal1,posinicial2,posfinal2,&numero1,&numero2);

        int resultado = operacionf(signo,numero1,numero2);
        char aux[20];
        snprintf(aux, sizeof(aux), "%d", resultado);
            
        for(q=0;q<strlen(aux);q++){
            operacion[posinicial1+q]=aux[q];
        }
        int salto=posfinal2-posinicial1-strlen(aux)+1;
        for(q=posfinal2+1;q<strlen(operacion);q++){
            operacion[q-salto]=operacion[q];
        }
        operacion[strlen(operacion)-posfinal2-posinicial1]='\0';
        numero1=0;
        numero2=0;
    }

    printf("El resultado de la operacion ingresada es %s",operacion);

    return 0;
}