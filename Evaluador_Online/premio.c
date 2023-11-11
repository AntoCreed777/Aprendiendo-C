#include <stdio.h>
#include <stdlib.h>

int main(){
    int t,x,y;
    scanf("%d",&t);
    if(t<1 || t>1000){return 0;}
    int *premios = (int*)malloc(sizeof(int)*t);
    for(int i=0;i<t;i++){
        scanf("%d %d",&x,&y);
        if(x<1 || x>1000 || y<1 || y>1000){return 0;}
        premios[i]=x*10+y*90;
    }
    for(int i=0;i<t;i++){
        printf("%d\n",premios[i]);
    }
    free(premios);
    return 0;
}