#include <stdio.h>

int main(){
    int n,m,a;
    scanf("%d %d %d",&n,&m,&a);
    if(n<1 || m<1 || a<1 || n>1000000000 || m>1000000000 || a>1000000000){return 0;}
    int contador1=0,contador2=0,aux1=0,aux2=0;
    while(contador1<n){
        contador1+=a;
        aux1++;
    }
    while(contador2<m){
        contador2+=a;
        aux2++;
    }
    printf("%d",aux1*aux2);
    return 0;
}