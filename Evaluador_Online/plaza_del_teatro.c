#include <stdio.h>

int main(){
    long long int n,m,a;
    scanf("%lld %lld %lld",&n,&m,&a);
    if(n<1 || m<1 || a<1 || n>1000000000 || m>1000000000 || a>1000000000){return 0;}

    long long int aux1 = (n/a);
    if(n%a != 0)aux1++;

    long long int aux2 = (m/a);
    if(m%a != 0)aux2++;

    printf("%lld",aux1*aux2);
    return 0;
}