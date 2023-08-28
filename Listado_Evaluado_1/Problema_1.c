/*Son las 18:25 y sólo le quedan 9 minutos a su permiso sanitario para regresar a su residencia, la cual
está a 3.7 km de distancia desde su posición actual. Escriba un programa en C que decida si logrará llegar
a tiempo a su residencia si se desplaza a metros por minuto. El valor de 
 debe ser ingresado al momento de ejecutar su código. (Nota: Asuma que su residencia está en línea recta)*/

 #include<stdio.h>
 #include<stdlib.h>

 #define distancia 3700
 #define tiempo 9 //minutos

void ingreso(char mensaje[],char **velocidad,int *longitud){    //Funcion que valida que solo ingresen numeros
    int tamal=1;
    while (tamal==1){ 
        *longitud=0;
        int capacidad=0;
        char caracter;
        printf("%s",mensaje);
        while((caracter=getchar())!='\n'){
            if (*longitud>=capacidad){
                capacidad+=2;
                *velocidad=(char*)realloc(*velocidad,sizeof(char)*capacidad);
            }
            (*velocidad)[*longitud]=caracter;
            (*longitud)++;
        }
        tamal=0;
        for(int i=0;i<*longitud;i++){
            if((*velocidad)[i]<48 || (*velocidad)[i]>57){
                tamal=1;
                printf("Solo se aceptan numeros\n");
                break;
            }
        }
    }
}

 int main(){
    char *velocidad=NULL;
    int longitud;
    ingreso("Ingrese la velocidad a la que se desplaza: ",&velocidad,&longitud);
    int velocidadint=atoi(velocidad);
    
    if((velocidadint*tiempo)<distancia){
        printf("No alcanzara a llegar a tiempo");
    }
    else{
        printf("Si alcanzara a llegar a tiempo");
    }
    
    return 0;
 }