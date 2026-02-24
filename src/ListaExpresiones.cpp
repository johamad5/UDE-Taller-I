#include "ListaExpresiones.h"

void ReservarNodoL(NodoL *&n)
{
    n = new NodoL;
    n->sig = NULL;
}

void InsertarExpresionAlFinalL(ListaExpresiones &l, Expresion exp)
{
    NodoL *nuevo = NULL;
    ReservarNodoL(nuevo);

    nuevo->exp = exp;
    nuevo->sig = NULL;

    if (l == NULL)
    {
        l = nuevo;
    }
    else
    {
        NodoL *aux = l;

        while (aux->sig != NULL)
        {
            aux = aux->sig;
        }

        aux->sig = nuevo;
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