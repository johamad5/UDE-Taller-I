#include <stdio.h>
#include "ExpresionABB.h"

ExpresionABB CrearExpresionSimpleX(char c)
{
    ExpresionABB e = new nodoA;
    e->indiceNodo = 1;
    e->tipo = VARIABLE;
    e->dato.simbolo = c;
    e->hizq = NULL;
    e->hder = NULL;
    return e;
}

ExpresionABB CrearExpresionSimpleInt(int num)
{
    ExpresionABB e = new nodoA;
    e->indiceNodo = 1;
    e->tipo = ENTERO;
    e->dato.num = num;
    e->hizq = NULL;
    e->hder = NULL;
    return e;
}

ExpresionABB CrearExpresionCompuesta(Operacion o, ExpresionABB a, ExpresionABB b)
{
    ExpresionABB eIzq = new nodoA;
    ExpresionABB eDer = new nodoA;
    ExpresionABB eRaiz = new nodoA;
    eRaiz->tipo = OPERADOR;
    eRaiz->dato.simbolo = DevolverOperacion(o);
    eIzq = copiarArbol(a);
    eDer = copiarArbol(b);
    insertarParentesisIzquierdo(eIzq);
    insertarParentesisDerecho(eDer);
    eRaiz->indiceNodo = indiceMaximoABB(eIzq) + 1;
    ajustarIndicesABB(eDer, eRaiz->indiceNodo);
    eRaiz->hizq = eIzq;
    eRaiz->hder = eDer;
    return eRaiz;
}

int indiceMaximoABB(ExpresionABB abb)
{
    int i = 0;
    if (abb != NULL)
    {
        ExpresionABB actual = abb;
        while (actual->hder != NULL)
        {
            actual = actual->hder;
        }
        i = actual->indiceNodo;
    }

    return i;
}

Boolean ArbolesIdenticos(ExpresionABB a, ExpresionABB b)
{
    if ((a == NULL && b == NULL) || (a == NULL && b != NULL) || (b == NULL && a != NULL) || (a->tipo != b->tipo) || (a->tipo == ENTERO && a->dato.num != b->dato.num) || (a->tipo == VARIABLE && a->dato.simbolo != b->dato.simbolo))
        return FALSE;
    else
    {
        Boolean izq = ArbolesIdenticos(a->hizq, b->hizq);
        Boolean der = ArbolesIdenticos(a->hder, b->hder);
        if (izq == TRUE && der == TRUE)
            return TRUE;
        else
            return FALSE;
    }
}

void CalcularABB(ExpresionABB nodo, int &valorX, Boolean &errorDivision) {}

void DestruirABB(ExpresionABB &abb)
{
    if (abb != NULL)
    {
        DestruirABB(abb->hizq);
        DestruirABB(abb->hder);
        delete abb;
    }
}

void ajustarIndicesABB(ExpresionABB &abb, int delta)
{
    if (abb != NULL)
    {
        abb->indiceNodo += delta;
        ajustarIndicesABB(abb->hizq, delta);
        ajustarIndicesABB(abb->hder, delta);
    }
}

ExpresionABB copiarArbol(ExpresionABB original)
{
    ExpresionABB copia = new NodoABB;
    copia->indiceNodo = original->indiceNodo;
    copia->tipo = original->tipo;

    if (original->tipo == ENTERO)
        copia->dato.num = original->dato.num;
    else
        copia->dato.simbolo = original->dato.simbolo;

    copia->hizq = copiarArbol(original->hizq);
    copia->hder = copiarArbol(original->hder);

    return copia;
}

void insertarParentesisIzquierdo(ExpresionABB &abb)
{
    if (abb != NULL)
    {

        ExpresionABB actual = abb;
        actual->indiceNodo += 1;
        while (actual->hizq != NULL)
        {
            actual = actual->hizq;
            actual->indiceNodo += 1;
        }

        ExpresionABB nuevo = new nodoA;
        nuevo->indiceNodo = 1;
        nuevo->tipo = ABREPARENTESIS;
        nuevo->dato.simbolo = '(';
        nuevo->hizq = NULL;
        nuevo->hder = NULL;

        actual->hizq = nuevo;
    }
}

void insertarParentesisDerecho(ExpresionABB &abb)
{
    if (abb != NULL)
    {

        ExpresionABB actual = abb;
        int i = actual->indiceNodo;
        while (actual->hder != NULL)
        {
            actual = actual->hder;
            i = actual->indiceNodo;
        }

        ExpresionABB nuevo = new nodoA;
        nuevo->indiceNodo = i + 1;
        nuevo->tipo = CIERRAPARENTESIS;
        nuevo->dato.simbolo = ')';
        nuevo->hizq = NULL;
        nuevo->hder = NULL;

        actual->hder = nuevo;
    }
}
