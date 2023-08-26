/*Son las 18:25 y sólo le quedan 9 minutos a su permiso sanitario para regresar a su residencia, la cual
está a 3.7 km de distancia desde su posición actual. Escriba un programa en C que decida si logrará llegar
a tiempo a su residencia si se desplaza a metros por minuto. El valor de 
 debe ser ingresado al momento de ejecutar su código. (Nota: Asuma que su residencia está en línea recta)*/

 #include<stdio.h>

 #define distancia 3700
 #define tiempo 9 //minutos

 int main(){
    int velocidad;
    printf("Ingrese la velocidad a la que se desplaza: ");
    scanf("%d",&velocidad);
    if((velocidad*tiempo)<distancia){
        printf("No alcanzara a llegar a tiempo");
    }
    else{
        printf("Si alcanzara a llegar a tiempo");
    }
    return 0;
 }