#include "Operacion.h"

char DevolverOperacionChar(Operacion o)
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

Operacion DevolverOperacion(char c)
{
    Operacion o;
    switch (c)
    {
    case '+':
        o = SUMA;
        break;
    case '-':
        o = RESTA;
        break;
    case '*':
        o = MULTIPLICACION;
        break;
    case '/':
        o = DIVISION;
        break;
    }

    return o;
}