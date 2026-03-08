#ifndef EXPRESION_H_INCLUDED
#define EXPRESION_H_INCLUDED
#include "ExpresionABB.h"

typedef struct
{
    ExpresionABB terminos;
    int indiceLista;
} Expresion;

// Setea el indice de una expresion
void setIndiceExpresion(Expresion &exp, int id);

// Devuelve el indice de una expresion dada
int getIndiceExpresion(Expresion exp);

// Muestra por pantalla la expresion
void MostrarExpresion(Expresion exp);

// Destruye la expresion y libera toda la memoria
void DestruirExpresion(Expresion &exp);

// Guarda una expresion en archivo
void BajarExpresion(Expresion exp, FILE *f);

// Recupera una expresion desde un archivo
void LevantarExpresion(Expresion &exp, FILE *f);

// Crea una expresion simple
Expresion CrearExpresionSimple(Boolean esX, int num);

// Crea una expresion compuesta
Expresion CrearExpresionCompuesta(Operacion op, Expresion exp1, Expresion exp2);

// Calcula el resultado de una expresion
void CalcularExpresion(Expresion exp, int num, Boolean &errDiv, int &resultado);

// Compara dos expresiones y determina si son iguales
void CompararExpresiones(Expresion exp1, Expresion exp2);

#endif