#ifndef LISTAPARSING_H_INCLUDED
#define LISTAPARSING_H_INCLUDED
#include "String.h"

typedef struct nodoP
{
    String palabra;
    nodoP *sig;
} NodoP;

typedef NodoP *ListaParsing;

// Reserva memoria para un nodo de parsing e inicializa su enlace.
void ReservarNodoP(ListaParsing &n);

// Inserta una palabra al final de la lista de tokens.
// PRECONDICIÓN: palabra debe ser un String válido (no NULL, terminado en '\0').
void InsertarAlFinalParsing(ListaParsing &lp, String palabra);

// Destruye la lista de tokens y libera memoria.
void DestruirListaParsing(ListaParsing &lp);

// Tokeniza una línea y genera la lista de tokens.
// PRECONDICIÓN: linea debe ser un String válido no NULL, terminado en '\0'.
void TokenizarEntrada(ListaParsing &lp, String linea);

// Devuelve el token en la posición indicada.
// PRECONDICIÓN: lp no debe ser NULL. pos debe ser un valor válido: estar dentro del rango.
void TokenEnPosicion(ListaParsing lp, int pos, String &token);

// Devuelve la cantidad total de tokens almacenados en la lista.
int CantidadTokens(ListaParsing lp);

#endif