#include "ListaParsing.h"

void ReservarNodoP(NodoP *&n)
{
    n = new nodoP;
    n->sig = NULL;
}

void InsertarAlFinalParsing(ListaParsing &lp, NodoP *&ultimo, String palabra)
{
    nodoP *nuevo = NULL;
    ReservarNodoP(nuevo);

    nuevo->palabra = NULL;
    strcop(nuevo->palabra, palabra);
    nuevo->sig = NULL;

    if (lp == NULL)
    {
        lp = nuevo;
        ultimo = nuevo;
    }
    else
    {
        ultimo->sig = nuevo;
        ultimo = nuevo;
    }
}

void DestruirListaParsing(ListaParsing &lp)
{
    while (lp != NULL)
    {
        NodoP *aux = lp;
        lp = lp->sig;
        strdestruir(aux->palabra);
        delete aux;
    }
}

void TokenizarEntrada(ListaParsing &lp, String linea)
{
    lp = NULL;
    NodoP *ultimo = NULL;

    int j, i = 0;

    while (linea[i] != '\0')
    {
        while (linea[i] == ' ')
        {
            i++;
        }

        int inicioToken = i;

        while (linea[i] != '\0' && linea[i] != ' ')
        {
            i++;
        }

        int largoToken = i - inicioToken;

        String token = NULL;
        token = new char[largoToken + 1];

        for (j = 0; j < largoToken; j++)
        {
            token[j] = linea[inicioToken + j];
        }
        token[largoToken] = '\0';

        InsertarAlFinalParsing(lp, ultimo, token);
        strdestruir(token);
    }
}

void TokenEnPosicion(ListaParsing lp, int pos, String &token)
{
    int i = 1;
    NodoP *aux = lp;
    while (i < pos)
    {
        aux = aux->sig;
        i++;
    }

    strcop(token, aux->palabra);
}

int CantidadTokens(ListaParsing lp)
{
    int cant = 0;
    NodoP *aux = lp;
    while (aux != NULL)
    {
        cant++;
        aux = aux->sig;
    }

    return cant;
}