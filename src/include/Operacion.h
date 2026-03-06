#ifndef OPERACION_H_INCLUDED
#define OPERACION_H_INCLUDED

typedef enum
{
    SUMA,
    RESTA,
    MULTIPLICACION,
    DIVISION
} Operacion;

// Devuelve el ENUM de la operacion
Operacion DevolverOperacion(char c);

// Devuelve el simbolo de la operacion
char DevolverOperacionChar(Operacion o);

#endif