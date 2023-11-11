#include <stdio.h>
int repite(int y){
    int um=y/1000;
    int c= ((y-(um*1000))/100);
    int d= ((y-(um*1000)-(c*100))/10);
    int u= y-(um*1000)-(c*100)-d*10;
    if(um != c && um!=d && um!= u && c!=d && c!=u && d!=u){
        return 1;
    }
    return 0;
}
int main(){
    int y;
    scanf("%d",&y);
    if(y<1000 || y>9000){return 0;}
    y++;
    while(1){
        if(repite(y)==1){
            printf("%d",y);
            return 0;
        }
        y++;
    }
}