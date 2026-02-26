#include "Operacion.h"

char DevolverOperacion(Operacion o)
{
    char c;
    switch (o)
    {
    case SUMA:
        c = '+';
        break;
    case RESTA:
        c = '-';
        break;
    case MULTIPLICACION:
        c = '*';
        break;
    case DIVISION:
        c = '/';
        break;
    default:
        break;
    }

    return c;
}