#include <stdio.h>

void ingreso(int *cat1,int *cat2,int *hyp){
    printf("Ingrese el cateto 1: ");
    scanf("%d",cat1);
    printf("\nIngrese el cateto 2: ");
    scanf("%d",cat2);
    printf("\nIngrese la hipotenuza: ");
    scanf("%d",hyp);
}

int main(){
    int cat1,cat2,hyp;
    ingreso(&cat1,&cat2,&hyp);
    printf("%d\n",cat1);
    printf("%d\n",cat2);
    printf("%d\n",hyp);
    ((cat1*cat1+cat2*cat2)==(hyp*hyp))?printf("\nEs un triangulo valido"):printf("\nEs un triangulo invalido");
    return 0;
}