#include <stdio.h>
#include <string.h>

void ingreso(char rut[]){
    printf("Ingrese su rut: ");
    scanf("%12s",rut);
}
void limpiador(char rut[]) {
    int aux = 0;
    char aux2[10];
    for (int i = 0; i < strlen(rut); i++) {
        if (rut[i+aux] == '.') {
            aux = aux+1;
        }
        aux2[i] = rut[i+aux];
        if (i+aux>=strlen(rut)){
            break;
        }
    }
    aux2[strlen(rut) - aux] = '\0'; // Agregar el carácter nulo al final de aux2
    strcpy(rut,aux2);
}
void invertir(char rut[], char inversorut[13]){
    for (int i=0;i<strlen(rut); i++){
        inversorut[i] = rut[strlen(rut)-i-1];
    } 
    inversorut[strlen(rut)]='\0';
}
int suma(char rut[], char inversorut[13]){
    int resultado=0;
    int aux[]={2,3,4,5,6,7};
    for (int i=0;i<strlen(rut); i++){
        int aux1=inversorut[i]-'0';
        resultado+=aux1*aux[i%6];
    }
    return resultado;
}


int main(){
    char rut[13];
    ingreso(rut);
    limpiador(rut);
    char inversorut[13];
    invertir(rut,inversorut);
    int resultadosuma = suma(rut,inversorut);
    int resultado =resultadosuma/11;
    resultado =resultado*11;
    resultado= resultadosuma-resultado;
    resultado=11-resultado;
    printf("%d",resultado);
    return 0;
}