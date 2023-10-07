#include <stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    unsigned int b1=n<<28;
    b1=b1>>28;
    unsigned int b2=n<<24;
    b2=b2>>28;
    unsigned int b3=n<<20;
    b3=b3>>28;
    unsigned int b4=n<<16;
    b4=b4>>28;
    unsigned int b5=n<<12;
    b5=b5>>28;
    unsigned int b6=n<<8;
    b6=b6>>28;
    unsigned int b7=n<<4;
    b7=b7>>28;
    unsigned int b8=n<<0;
    b8 = b8 >> 28; 
    
    printf("%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t",b1,b2,b3,b4,b5,b6,b7,b8);
    return 0;
}