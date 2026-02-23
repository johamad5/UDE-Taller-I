#ifndef EXPRESION_H_INCLUDED
#define EXPRESION_H_INCLUDED
#include "TipoDato.h"
#include "Boolean.h"

typedef struct nodoA
{
TipoDato tipo;
int indiceNodo;
union {
int num;
char simbolo;
} dato;
nodoA *hizq;
nodoA *hder;
} NodoABB;
typedef NodoABB* ExpresionABB;

 typedef struct
{
ExpresionABB terminos;
int indiceLista;
} Expresion;


// Reserva memoria para un nodo ABB e inicializa sus enlaces.
void ReservarNodoABB(ExpresionABB &n);

// Inserta un nodo ABB dentro del árbol, ordenando por indiceNodo.
void InsertarABBPorIndice(ExpresionABB &raiz, ExpresionABB nodo);

// Devuelve el índice máximo presente en el ABB.
int IndiceMaximoABB(ExpresionABB abb);

// Indica si dos árboles son idénticos en estructura y contenido.
Boolean ArbolesIdenticos(ExpresionABB a, ExpresionABB b);

// Calcula el resultado del ABB evaluando la variable x.
void CalcularABB(ExpresionABB nodo, int &valorX, Boolean &errorDivision);

// Llibera toda la memoria del ABB.
void DestruirABB(ExpresionABB &abb);

// Ajusta los índices del árbol
void AjustarIndicesABB(ExpresionABB &abb, int delta);

// Copia un árbol completo.
void CopiarArbol(ExpresionABB original, ExpresionABB &copia);

// Ingresa un paréntesis izquierdo como último hizq.
void InsertarParentesisIzquierdo(ExpresionABB &abb);

// Ingresa un paréntesis derecho como último hder.
void InsertarParentesisDerecho(ExpresionABB &abb);


#endif