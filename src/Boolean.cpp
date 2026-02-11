#include "Boolean.h"

void Cargar(Boolean &b){
    int valor;
    do{
        printf ("ingrese 0 si es falso y 1 si es verdadero: ");
        scanf ("%d",& valor);

        switch(valor){
            case 0:
                    b = FALSE;
                break;
            case 1:
                    b = TRUE;
                break;
            default:
            break;
        }

    } while (valor != 0 && valor != 1);
}

void Despliegue(Boolean b){
     if (b)
        printf ("verdadero");
     else
        printf ("falso");
}