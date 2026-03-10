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
// PRECONDICIÓN: c debe ser uno de los caracteres: '+', '-', '*', '/'.
Operacion DevolverOperacion(char c);

// Devuelve el simbolo de la operacion
// PRECONDICIÓN: o debe ser un valor válido del enum Operacion.
char DevolverOperacionChar(Operacion o);

#endif