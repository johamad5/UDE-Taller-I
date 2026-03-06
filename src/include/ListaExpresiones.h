#ifndef LISTAEXPRESIONES_H_INCLUDED
#define LISTAEXPRESIONES_H_INCLUDED
#include "Boolean.h"
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
void InsertarExpresionAlFinalL(ListaExpresiones &lp, Expresion &exp);

// Busca una expresión por índice dentro de la lista.
// PRECONDICIÓN: índice es un valor válido y existente
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

#endif