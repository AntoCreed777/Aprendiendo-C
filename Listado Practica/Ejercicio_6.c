/*En algunas oficinas del gobierno pagan horas extra a los bur ́ocratas, adem ́as del salario correspondiente. Escriba un
programa en C que permita calcular la cantidad a pagar a un trabajador por concepto de horas extra trabajadas. Las
horas extra se pagan seg ́un la categor ́ıa a la que pertenece cada trabajador y se calculan en funci ́on de la siguiente
tabla. Cada trabajador puede tener como m ́aximo 30 horas extra, si tienen m ́as, s ́olo se les pagar ́an las primeras 30.
Los trabajadores con categor ́ıa 4 o mayor a 4 no pueden recibir este beneficio

1-->20000
2-->23000
3-->25000

*/

#include <stdio.h>
#include <stdlib.h>


void ingreso(char mensaje[],int *a){
    printf("%s",mensaje);
    scanf("%d",a);
}

int main(){
    int categoria;
    int horas;
    ingreso("Ingrese la categoria a la que pertence el trabajador: ",&categoria);
    if (categoria>3){
        printf("Usted no puede recibir este beneficio");
        exit(0);
    }

    ingreso("Ingrese las horas extras trabajadas: ",&horas);
    if (horas>30){
        printf("Para su informacion, como maximo solo se pagan 30 horas extras\n");
        horas=30;
    }

    int pago;

    if(categoria==1){
        pago=20000*horas;
    }

    if(categoria==2){
        pago=23000*horas;
    }

    if(categoria==3){
        pago=25000*horas;
    }

    printf("Su pago es de %d",pago);
    return 0;
}