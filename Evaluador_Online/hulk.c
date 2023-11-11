#include <stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    if(n<1 || n>100){
        return 0;
    }
    for(int i=0;i<n;i++){
        if(i==0){
            printf("I hate");
            continue;
        }
        printf(" that ");
        if(i%2!=0){
            printf("I love");
        }
        else{
            printf("I hate");
        }
    }
    printf(" it");
    return 0;
}