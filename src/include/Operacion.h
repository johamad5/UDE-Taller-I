#ifndef OPERACION_H_INCLUDED
#define OPERACION_H_INCLUDED

typedef enum
{
    SUMA,
    RESTA,
    MULTIPLICACION,
    DIVISION
} Operacion;

// Devuelve el simbolo de la operacion
Operacion DevolverOperacion(char c);

// Devuelve el primer caracter
char DevolverOperacionChar(Operacion o);

#endif