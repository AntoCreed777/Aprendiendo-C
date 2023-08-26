/*El último teorema de Fermat dice que no existen enteros positivos 
, 
 y 
, tal que 
 para valores de 
 mayores que 2. Escriba un programa que pida ingresar por teclado los valores de  
, 
, 
 y 
, y compruebe si el teorema se cumple para los valores ingresados. De cumplirse, debe imprimir el mensaje "Eureka!". En caso contrario, debe imprimir el mensaje "Oh no! Fermat se equivocó". Además, su programa deberá verificar que  
, 
 y 
 sean valores positivos y que 
 sea mayor que 2. Si no se cumple esa condición, entonces deberá imprimir el mensaje "No se puede calcular".

 */

#include <stdio.h>
#include <math.h>
#include<stdlib.h>
int main(){
    //Declaracion y asignacion de valores
    int a,b,c,n;
    printf("Ingrese el valor de \"a\": ");
    scanf("%d",&a);
    printf("Ingrese el valor de \"b\": ");
    scanf("%d",&b);
    printf("Ingrese el valor de \"c\": ");
    scanf("%d",&c);
    printf("Ingrese el valor de \"n\": ");
    scanf("%d",&n);

    //Corroboracion de los datos
    if(a<0 || b<0 || c<0){
        printf("No se puede calcular");
        exit(0);
    }

    if(n<=2){
        printf("Fermat se aplica a n > 2, no se puede calcular");
        exit(0);
    }
    
    //Calculo de Fermat
    if((pow(a,n)+pow(b,n))!=pow(c,n)){
        printf("Eureka!!!!");
    }
    else{
        printf("Oh no! Fermat se equivocó");
    }




    return 0;
}