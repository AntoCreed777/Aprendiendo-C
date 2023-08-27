
#include <stdio.h>

int main(){
    //Ingreso
    int n;
    printf("Ingrese un numero: ");
    scanf("%d",&n);

    //Calculo de los resultados de la funcion
    float resultado;
    for(float i=1;i<=n;i++){
        if(i<=5 && i>0){
            resultado=2*i;
        }
        else if(i>5 && i<=13){
            resultado= (i*i)-(3*i)+2;
        }
        else{   //i>13
            resultado=(100/i)+3;
        }
        printf("Pa x=%.0f la funcion entrega el resultado f(x)= %.2f\n",i,resultado);
    }
    return 0;
}