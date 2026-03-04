#ifndef OPERACION_H_INCLUDED
#define OPERACION_H_INCLUDED

typedef enum
{
    SUMA,
    RESTA,
    MULTIPLICACION,
    DIVISION
} Operacion;

char DevolverOperacionChar(Operacion o);

Operacion DevolverOperacion(char c);

#endif