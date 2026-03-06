#include "ListaParsing.h"

void ReservarNodoP(ListaParsing &n)
{
    n = new nodoP;
    n->sig = NULL;
}

void InsertarAlFinalParsing(ListaParsing &lp, String palabra)
{
    if (lp == NULL)
    {
        ReservarNodoP(lp);
        lp->palabra = NULL;
        strcrear(lp->palabra);
        strcop(lp->palabra, palabra);
        lp->sig = NULL;
    }
    else
    {
        ListaParsing aux = lp;
        while (aux->sig != NULL)
        {
            aux = aux->sig;
        }

        ReservarNodoP(aux->sig);
        aux->sig->palabra = NULL;
        strcrear(aux->sig->palabra);
        strcop(aux->sig->palabra, palabra);
        aux->sig->sig = NULL;
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

    DestruirListaParsing(lp);
    lp = NULL;
    int j, i = 0;

    while (linea[i] != '\0')
    {
        while (linea[i] == ' ')
        {
            i++;
        }

        if (linea[i] != '\0')
        {
            int inicioToken = i;
            while (linea[i] != '\0' && linea[i] != ' ')
                i++;

            int largoToken = i - inicioToken;

            String token = NULL;
            token = new char[largoToken + 1];

            for (j = 0; j < largoToken; j++)
            {
                token[j] = linea[inicioToken + j];
            }
            token[largoToken] = '\0';
            InsertarAlFinalParsing(lp, token);
            strdestruir(token);
        }
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