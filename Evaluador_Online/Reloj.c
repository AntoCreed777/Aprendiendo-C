#include <stdio.h>
#include <string.h>

char* timeConversion(char *hora){
    static char s[11];
    strcpy(s,hora);
    if(s[8] == 'P'){
        if(!(s[0] == '1' && s[1] == '2')){
            if(s[1] < '8'){
                s[1]+=2;
                s[0]++;
            }
            else{
                s[1]=((s[1]-'0')%8)+'0';
                s[0]+=2;
            }
        }
    }
    else if(s[0] == '1' && s[1] == '2'){
        s[0]='0';s[1]='0';
    }
    s[8] = '\0';
    return s;
}

int main(){
    char hora_entrada[11];
    scanf("%s",&hora_entrada);
    printf("%s",timeConversion(hora_entrada));
    return 0;
}