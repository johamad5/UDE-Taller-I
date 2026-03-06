#ifndef EXPRESION_H_INCLUDED
#define EXPRESION_H_INCLUDED
#include "ExpresionABB.h"

typedef struct
{
    ExpresionABB terminos;
    int indiceLista;
} Expresion;

// Setea la expresionABB de una expresion
void setTermino(Expresion &exp, ExpresionABB expABB);

// Devuelve la expresionABB de una expresion
ExpresionABB getTermino(Expresion exp);

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

#endif