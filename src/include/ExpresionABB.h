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
ExpresionABB CrearAbbSimpleChar();

// Reserva memoria para un nodo ABB e inicializa sus enlaces.
ExpresionABB CrearAbbSimpleInt(int num);

// Reserva memoria para un nodo ABB e inicializa sus enlaces.
// PRECONDICIÓN: a y b deben ser ExpresionABB válidos (no NULL). o debe ser un valor válido del enum Operacion.
ExpresionABB CrearAbbCompuesta(Operacion o, ExpresionABB a, ExpresionABB b);

// Indica si dos árboles son idénticos en estructura y contenido.
Boolean ArbolesIdenticos(ExpresionABB a, ExpresionABB b);

// Calcula el resultado del ABB evaluando la variable x.
void CalcularABB(ExpresionABB nodo, int valorX, Boolean &errorDivision, int &resultado);

// Llibera toda la memoria del ABB.
void DestruirABB(ExpresionABB &abb);

// Ajusta los índices del árbol
// PRECONDICIÓN: contador debe estar inicializado en 0 antes de la primera llamada.
void reindexarInorden(ExpresionABB abb, int &contador);

// Copia un árbol completo.
ExpresionABB copiarArbol(ExpresionABB original);

// Ingresa un paréntesis izquierdo como último hizq.
// PRECONDICIÓN: abb no debe ser NULL.
void insertarParentesisIzquierdo(ExpresionABB &abb);

// Ingresa un paréntesis derecho como último hder.
// PRECONDICIÓN: abb no debe ser NULL.
void insertarParentesisDerecho(ExpresionABB &abb);

// Muestra por pantalla la expresion en recorrido inorden.
void MostrarABB(ExpresionABB abb);

// Serializa el ABB en un archivo en preorden.
// PRECONDICIÓN: f debe ser un archivo abierto para escritura.
void BajarExpresionABB(ExpresionABB abb, FILE *f);

// Serializa un único nodo en un archivo.
// PRECONDICIÓN: nodo no debe ser NULL. f debe ser un archivo abierto para escritura.
void BajarNodoABB(ExpresionABB nodo, FILE *f);

// Deserializa un ABB desde un archivo e inserta los nodos.
// PRECONDICIÓN: f debe ser un archivo abierto para lectura, posicionado al inicio de una expresión serializada.
void LevantarExpresionABB(ExpresionABB &abb, FILE *f);

// Inserta un nuevo nodo en el ABB según su índice.
// PRECONDICIÓN: nuevo no debe ser NULL. Su indiceNodo debe ser único dentro del árbol.
void InsertarEnABB(ExpresionABB &abb, ExpresionABB nuevo);

#endif