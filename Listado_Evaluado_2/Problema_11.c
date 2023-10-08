#include <stdio.h>

void diagonal(int n,int matriz[][n],int posicionx,int posiciony,int *contador){
    int x=posicionx;
    int y=posiciony;
    while(x<n && y<n){
        matriz[y][x]=(*contador);
        (*contador)++;
        x++;
        y++;
    }
}

int main(){
    //Declaracion e ingreso de n, que almacena el tamano del lado del cuadrado
    int n;
    printf("Ingrese el tamano del tablero de NxN:   ");
    scanf("%d",&n);
    while(n<1 || n>100){    //Validacion de n
        printf("\nValor fuera de rango\nIngrese el tamano del tablero de NxN:   ");
        scanf("%d",&n);
    }

    int matriz[n][n];

    int contador=1;

    int j=0;
    for(int i=n-1;i>=0;i--){
        if(i==0){
            for(int j=0;j<n;j++){
                diagonal(n,matriz,i,j,&contador);
            }
        }else{
            diagonal(n,matriz,i,j,&contador);
        }
    }


    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d\t",matriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}