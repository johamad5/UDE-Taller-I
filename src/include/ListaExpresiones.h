#ifndef LISTAEXPRESIONES_H_INCLUDED
#define LISTAEXPRESIONES_H_INCLUDED
#include "String.h"
#include "Expresion.h"

typedef struct nodoL
{
    Expresion exp;
    nodoL *sig;
} NodoL;

typedef NodoL *ListaExpresiones;

// Reserva memoria para un nodo de lista e inicializa su enlace.
void ReservarNodoL(ListaExpresiones &n);

// Inserta una nueva expresión al final de la lista.
// PRECONDICIÓN: exp debe ser una Expresion válida previamente creada.
void InsertarExpresionAlFinalL(ListaExpresiones &lp, Expresion &exp);

// Busca una expresión por índice dentro de la lista.
// PRECONDICIÓN: indiceLista debe existir en la lista (verificado previamente con EsIndiceValido).
Expresion BuscarExpresionPorIndice(ListaExpresiones l, int indiceLista);

// Indica si un índice es válido según las expresiones almacenadas.
// PRECONDICIÓN: índice debe ser un valor entero positivo
Boolean EsIndiceValido(ListaExpresiones l, int indiceLista);

// Muestra por pantalla todas las expresiones de la lista.
void MostrarExpresiones(ListaExpresiones l);

// Destruye la lista y libera la memoria de sus nodos
void DestruirListaExpresiones(ListaExpresiones &l);

// Devuelve el ultimo indice disponible para ser usado
int UltimoIndiceDisponible(ListaExpresiones l);

// Crea una expresion simple la agrega al final de la lista
void CrearInsertarExpresionSimple(ListaExpresiones &lp, Boolean esX, int num);

// Crea una expresion compuesta la agrega al final de la lista
// PRECONDICIÓN: idx1 e idx2 deben ser índices válidos en lp. op debe ser un valor válido del enum Operacion.
void CrearInsertarExpresionCompuesta(ListaExpresiones &lp, Operacion op, int idx1, int idx2);

// Calcula el valor de la expresion con el indice dado
// PRECONDICIÓN: idx1 debe ser un índice válido en lp
void CalcularExpresionPorIndice(ListaExpresiones lp, int idx1, int num, Boolean &errDiv, int &resultado);

// Busca una expresion por indice y la guarda en un archivo
// PRECONDICIÓN: idx1 debe ser un índice válido en lp. arch debe ser un archivo abierto para escritura.
void BajarExpresionEnLista(ListaExpresiones lp, int idx1, FILE *arch);

// Recupera una expresion de un archivo y la agrega al final de la lista
// PRECONDICIÓN: arch debe ser un archivo abierto para lectura, posicionado al inicio de una expresión serializada.
void LevantarInsertarExpresion(ListaExpresiones &lp, FILE *arch);

// Busca dos expresiones de la lista y compara si son iguales
// PRECONDICIÓN: idx1 e idx2 deben ser índices válidos en lp.
void CompararExpresionesPorIndice(ListaExpresiones lp, int idx1, int idx2);

#endif