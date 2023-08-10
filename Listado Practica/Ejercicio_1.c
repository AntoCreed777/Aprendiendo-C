/*Escriba un programa que pida un n ́umero entero n e imprima “primo” si el numero es primo o “compuesto” en caso
contrario. (Nota: Basta con verificar los n ́umeros hasta √n.)*/

#include <stdio.h>
#include<math.h>

void ingreso(int *a){
    printf("Ingrese un numero: ");
    scanf("%d",a);
}

int comprobador(int n){
    int raiz= sqrt(n);
    for(int i=2;i<=raiz;i++){
        if (n%i==0){
            return 0;
        }

    }
    return 1;
}

int main(){
    int numero;
    ingreso(&numero);
    comprobador(numero)==1?printf("Es primo"):printf("No es primo");
    return 0;
}