#ifndef OPERACION_H_INCLUDED
#define OPERACION_H_INCLUDED

typedef enum
{
    SUMA,
    RESTA,
    MULTIPLICACION,
    DIVISION
} Operacion;

char DevolverOperacion(Operacion o);

#endif