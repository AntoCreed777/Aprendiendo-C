#include <stdio.h>

int main(){
    float a=20.3;
    float *b=&a;
    printf("%f\n",*b * *b);
    
    return 0;
}