#ifndef EXPRESION_H_INCLUDED
#define EXPRESION_H_INCLUDED
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
void CrearExpresionSimpleX(ExpresionABB &n, char c);

// Reserva memoria para un nodo ABB e inicializa sus enlaces.
void CrearExpresionSimpleInt(ExpresionABB &n, int num);

// Devuelve el índice máximo presente en el ABB.
int indiceMaximoABB(ExpresionABB abb);

// Indica si dos árboles son idénticos en estructura y contenido.
Boolean ArbolesIdenticos(ExpresionABB a, ExpresionABB b);

// Calcula el resultado del ABB evaluando la variable x.
void CalcularABB(ExpresionABB nodo, int &valorX, Boolean &errorDivision);

// Llibera toda la memoria del ABB.
void DestruirABB(ExpresionABB &abb);

// Ajusta los índices del árbol
void ajustarIndicesABB(ExpresionABB &abb, int delta);

// Copia un árbol completo.
ExpresionABB copiarArbol(ExpresionABB original);

// Ingresa un paréntesis izquierdo como último hizq.
void insertarParentesisIzquierdo(ExpresionABB &abb);

// Ingresa un paréntesis derecho como último hder.
void insertarParentesisDerecho(ExpresionABB &abb);

#endif