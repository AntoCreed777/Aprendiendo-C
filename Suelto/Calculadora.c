#include <stdio.h>
#include <string.h>
#include <math.h>

int ingreso(int posicion){
    printf("\nIngrese un numero %d: ",posicion);
    int numero;
    scanf("%d", &numero);

    return numero;
}

int operacion(){
    int resultado = 0; // Inicializar la variable resultado
    char operacion[20]; // Usar un arreglo de caracteres para almacenar la operación
    printf("Que operacion desea realizar?: ");
    scanf("%19s", operacion); // Usar %9s para evitar desbordamientos de búfer

    while (strcmp(operacion, "suma") != 0 && strcmp(operacion, "resta") != 0 && strcmp(operacion, "multiplicacion") != 0 && strcmp(operacion, "division") != 0){
        printf("\nDato mal ingresado\nQue operacion desea realizar?: ");
        scanf("%9s", operacion);
    }

    if (strcmp(operacion, "suma") == 0){
        int num1 = ingreso(1);
        int num2 = ingreso(2);
        resultado = num1 + num2;
    }

    if (strcmp(operacion, "resta") == 0){
        int num1 = ingreso(1);
        int num2 = ingreso(2);
        resultado = num1 - num2;
    }

    if (strcmp(operacion, "multiplicacion") == 0){
        int num1 = ingreso(1);
        int num2 = ingreso(2);
        resultado = num1 * num2;
    }

    if (strcmp(operacion, "division") == 0){
        float aux;
        int num1 = ingreso(1);
        int num2 = ingreso(2);
        while(num2 == 0){
            int num2 = ingreso(2);
        }
        aux = num1 / num2;
        resultado = floor(aux);
    }

    return resultado;
}

int main(){
    char continuar[3]="si";
    while (strcmp(continuar,"si")==0){
    printf("\nEl resultado es %d", operacion());

    printf("\n\nDesea continuar???\n\n");
    scanf("%2s",continuar);
    while (strcmp(continuar,"si")!=0 && strcmp(continuar,"no")!=0){
        printf("\n\nDato mal ingresado\nDesea continuar???\n\n");
        scanf("%2s",continuar);
        }
    }
}