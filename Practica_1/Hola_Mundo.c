#include <stdio.h>

int main(){
    char a[]="Hola Mundo";
    for(int i=0;i<=9;i++){
        if(i==4){
            printf("%s\n",a);
        }
        else{
        printf("    %c\n",a[i]);
        }
    }
    return 0;
}