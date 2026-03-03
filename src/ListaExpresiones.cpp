#include "ListaExpresiones.h"

void ReservarNodoL(ListaExpresiones &n)
{
    n = new NodoL;
    n->sig = NULL;
}

void InsertarExpresionAlFinalL(ListaExpresiones &lp, Expresion exp)
{
    if (lp == NULL)
    {
        ReservarNodoL(lp);
        lp->exp = exp;
        lp->sig = NULL;
    }
    else
    {
        ListaExpresiones aux = lp;
        while (aux->sig != NULL)
        {
            aux = aux->sig;
        }

        ReservarNodoL(aux->sig);
        aux->sig->exp = exp;
        aux->sig->sig = NULL;
    }
}

Expresion BuscarExpresionPorIndice(ListaExpresiones l, int indiceLista)
{
    NodoL *aux = l;

    while (ObtenerIndiceExpresion(aux->exp) != indiceLista)
    {
        aux = aux->sig;
    }

    return aux->exp;
}

Boolean EsIndiceValido(ListaExpresiones l, int indiceLista)
{
    NodoL *aux = l;
    Boolean existe = FALSE;

    while (aux != NULL && !existe)
    {
        if (ObtenerIndiceExpresion(aux->exp) == indiceLista)
        {
            existe = TRUE;
        }
        else
        {
            aux = aux->sig;
        }
    }

    return existe;
}

void MostrarExpresiones(ListaExpresiones l)
{
    NodoL *aux = l;

    while (aux != NULL)
    {
        printf("Indice en lista: %d \n", ObtenerIndiceExpresion(aux->exp));
        printf("--------------------------------\n");
        MostrarExpresion(aux->exp);
        printf("\n\n");

        aux = aux->sig;
    }
}

void DestruirListaExpresiones(ListaExpresiones &l)
{
    NodoL *aux;

    while (l != NULL)
    {
        aux = l;
        l = l->sig;

        DestruirExpresion(aux->exp);

        delete aux;
    }
}