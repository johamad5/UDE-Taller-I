#ifndef EXPRESIONABB_H_INCLUDED
#define EXPRESIONABB_H_INCLUDED
#include "TipoDato.h"
#include "Operacion.h"
#include "Boolean.h"

typedef struct nodoA
{
    TipoDato tipo;
    int indiceNodo;
    union
    {
        int num;
        char simbolo;
    } dato;
    nodoA *hizq;
    nodoA *hder;
} NodoABB;
typedef NodoABB *ExpresionABB;

// Reserva memoria para un nodo ABB e inicializa sus enlaces.
ExpresionABB CrearExpresionSimpleChar(char c);

// Reserva memoria para un nodo ABB e inicializa sus enlaces.
ExpresionABB CrearExpresionSimpleInt(int num);

// Reserva memoria para un nodo ABB e inicializa sus enlaces.
ExpresionABB CrearExpresionCompuesta(Operacion o, ExpresionABB a, ExpresionABB b);

// Indica si dos árboles son idénticos en estructura y contenido.
Boolean ArbolesIdenticos(ExpresionABB a, ExpresionABB b);

// Calcula el resultado del ABB evaluando la variable x.
int CalcularABB(ExpresionABB nodo, int valorX, Boolean &errorDivision);

// Llibera toda la memoria del ABB.
void DestruirABB(ExpresionABB &abb);

// Ajusta los índices del árbol
void reindexarInorden(ExpresionABB abb, int &contador);

// Copia un árbol completo.
ExpresionABB copiarArbol(ExpresionABB original);

// Ingresa un paréntesis izquierdo como último hizq.
void insertarParentesisIzquierdo(ExpresionABB &abb);

// Ingresa un paréntesis derecho como último hder.
void insertarParentesisDerecho(ExpresionABB &abb);

// Muestra por pantalla la expresion
void MostrarABB(ExpresionABB abb);

//
// PRECONDICION:
void BajarExpresionABB(ExpresionABB abb, FILE *f);

//
// PRECONIDCION:
void BajarNodoABB(ExpresionABB nodo, FILE *f);

//
// PRECONIDICON:
void LevantarExpresionABB(ExpresionABB &abb, FILE *f);

//
void InsertarEnABB(ExpresionABB &abb, ExpresionABB nuevo);

#endif