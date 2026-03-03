#ifndef EXPRESION_H_INCLUDED
#define EXPRESION_H_INCLUDED
#include "ExpresionABB.h"

typedef struct
{
    ExpresionABB terminos;
    int indiceLista;
} Expresion;

// Devuelve el indice de una expresion dada
int ObtenerIndiceExpresion(Expresion exp);

// Muestra por pantalla la expresion
void MostrarExpresion(Expresion exp);

// Destruye la expresion y libera toda la memoria
void DestruirExpresion(Expresion &exp);

void BajarExpresion(Expresion exp, FILE * f);

void LevantarExpresion(Expresion &exp, FILE * f);


#endif