#include <stdio.h>
#include <stdlib.h>

int main(){
    int q;
    scanf("%d",&q);
    if(q<1 || q>100){return 0;}
    unsigned *array = (unsigned*)malloc(sizeof(unsigned)*q);
    unsigned int n;
    for(int i=0;i<q;i++){
        scanf("%u",&n);
        array[i]=~n;
    }
    for(int i=0;i<q;i++){
        printf("%u\n",array[i]);
    }
    free(array);
    return 0;
}