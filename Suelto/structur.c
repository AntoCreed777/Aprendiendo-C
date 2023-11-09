#include <stdio.h>
#include <stdlib.h>

struct datos
{
    int a;
    int b;
};


int main(){
    struct datos *c = NULL;
    
    int x,y,contador;
    while(scanf("%d %d",&x,&y)==2 && x!=0 && y!=0){
        c=realloc(c,sizeof(c)*(contador+1));
        c[contador].a=x;
        c[contador].b=y;
        contador++;
    }
    for(int i=0; i<contador; i++){
        printf("%d %d\n",c[i].a,c[i].b);
    }

    return 0;
}