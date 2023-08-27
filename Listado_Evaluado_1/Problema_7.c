/*La codificación zig-zag permite representar números con signo como números sin signo.
Sea n un número positivo, su codificación zig-zag es, mientras que si n es un número negativo, su codificación zig-zag es 
. Por ejemplo, la codificación zig-zag de la secuencia de números -1, 1, -2, 2, -3, 3 es
1, 2, 3, 4, 5, 6. Escriba un programa que pida un número positivo e imprima el número para el cual 
 es su codificación zig-zag. Verifique que la entrada sea un número positivo.*/

 #include <stdio.h>

void ingreso(int *numero,char mensaje[]){
    printf("%s",mensaje);
    scanf("%d",numero);
}

 int main(){
    int numero;
    ingreso(&numero,"Ingrese el numero codificado en Zig-Zag: ");
    while(numero<0){
        ingreso(&numero,"\nDeve ser un numero estrictamente positivo\nIngrese el numero codificado en Zig-Zag: ");
    }

    int conversion;
    if(numero%2==0){
        conversion=numero/2;
    }
    else{
        conversion=(numero+1)/-2;
    }
    printf("El numero decodificado es %d",conversion);
    return 0;
 }