#ifndef EXPRESION_H_INCLUDED
#define EXPRESION_H_INCLUDED
#include "ExpresionABB.h"

typedef struct
{
    ExpresionABB terminos;
    int indiceLista;
} Expresion;

// Setea el indice de una expresion
// PRECONDICIÓN: id debe ser un entero positivo.
void setIndiceExpresion(Expresion &exp, int id);

// Devuelve el indice de una expresion dada
int getIndiceExpresion(Expresion exp);

// Muestra por pantalla la expresion
// PRECONDICIÓN: exp debe ser una Expresion válida con terminos inicializado.
void MostrarExpresion(Expresion exp);

// Destruye la expresion y libera toda la memoria
void DestruirExpresion(Expresion &exp);

// Guarda una expresion en archivo
// PRECONDICIÓN: f debe ser un archivo abierto para escritura.
void BajarExpresion(Expresion exp, FILE *f);

// Recupera una expresion desde un archivo
// PRECONDICIÓN: f debe ser un archivo abierto para lectura, posicionado al inicio de una expresión serializada.
void LevantarExpresion(Expresion &exp, FILE *f);

// Crea una expresion simple
Expresion CrearExpresionSimple(Boolean esX, int num);

// Crea una expresion compuesta
// PRECONDICIÓN: exp1 y exp2 deben ser Expresiones válidas previamente creadas. op debe ser un valor válido del enum Operacion.
Expresion CrearExpresionCompuesta(Operacion op, Expresion exp1, Expresion exp2);

// Calcula el resultado de una expresion
// PRECONDICIÓN: errDiv debe estar inicializado en FALSE.
void CalcularExpresion(Expresion exp, int num, Boolean &errDiv, int &resultado);

// Compara dos expresiones y determina si son iguales
void CompararExpresiones(Expresion exp1, Expresion exp2);

#endif