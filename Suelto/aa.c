#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main(){
    int a=1;
    while(a){
        char array[100];
        fgets(array,sizeof(array),stdin);
        size_t len=strlen(array);
        if(len>0 && array[len]=='\n'){
            array[len-1]='\0';
        }
        for(size_t i=0;i<len-1;i++){
            if(isdigit(array[i])==0){
                printf("No es un numero");
                break;
            }else{
                a=0;
            }
        }
    }
    return 0;
}