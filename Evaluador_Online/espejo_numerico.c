#include <stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    if(n<0 || n>100000){return 0;}
    int salida=0;
    for(int i=0;i<32;i++){
        salida+=((1<<(31-i))&n);
    }
    printf("%d",salida);
    return 0;
}