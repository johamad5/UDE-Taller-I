#include "ListaExpresiones.h"

void ReservarNodoL(ListaExpresiones &n)
{
    n = new NodoL;
    n->sig = NULL;
}

void InsertarExpresionAlFinalL(ListaExpresiones &lp, Expresion &exp)
{
    setIndiceExpresion(exp, UltimoIndiceDisponible(lp));

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
    }
}

Expresion BuscarExpresionPorIndice(ListaExpresiones l, int indiceLista)
{
    NodoL *aux = l;

    while (aux != NULL && getIndiceExpresion(aux->exp) != indiceLista)
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
        if (getIndiceExpresion(aux->exp) == indiceLista)
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

    printf("EXPRESIONES EN MEMORIA\n");
    printf("-----------------------\n");
    while (l != NULL)
    {
        MostrarExpresion(l->exp);
        printf("\n");

        l = l->sig;
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

int UltimoIndiceDisponible(ListaExpresiones l)
{
    int i = 1;

    while (l != NULL)
    {
        l = l->sig;
        i++;
    }

    return i;
}

void CrearInsertarExpresionSimple(ListaExpresiones &lp, Boolean esX, int num)
{
    Expresion exp = CrearExpresionSimple(esX, num);
    InsertarExpresionAlFinalL(lp, exp);
    MostrarExpresion(exp);
}

void CrearInsertarExpresionCompuesta(ListaExpresiones &lp, Operacion op, int idx1, int idx2)
{
    Expresion exp = CrearExpresionCompuesta(op, BuscarExpresionPorIndice(lp, idx1), BuscarExpresionPorIndice(lp, idx2));
    InsertarExpresionAlFinalL(lp, exp);
    MostrarExpresion(exp);
}

void CalcularExpresionPorIndice(ListaExpresiones lp, int idx1, int num, Boolean &errDiv, int &resultado)
{
    resultado = 0;
    errDiv = FALSE;
    CalcularExpresion(BuscarExpresionPorIndice(lp, idx1), num, errDiv, resultado);
}

void BajarExpresionEnLista(ListaExpresiones lp, int idx1, FILE *arch)
{
    BajarExpresion(BuscarExpresionPorIndice(lp, idx1), arch);
}

void LevantarInsertarExpresion(ListaExpresiones &lp, FILE *arch)
{
    Expresion exp;
    LevantarExpresion(exp, arch);
    InsertarExpresionAlFinalL(lp, exp);
    MostrarExpresion(exp);
}

void CompararExpresionesPorIndice(ListaExpresiones lp, int idx1, int idx2)
{
    CompararExpresiones(BuscarExpresionPorIndice(lp, idx1), BuscarExpresionPorIndice(lp, idx2));
}