#include <stdio.h>
#include "ExpresionABB.h"

ExpresionABB CrearExpresionSimpleX(char c)
{
    ExpresionABB e = new NodoABB;
    e->indiceNodo = 1;
    e->tipo = VARIABLE;
    e->dato.simbolo = c;
    e->hizq = NULL;
    e->hder = NULL;
    return e;
}

ExpresionABB CrearExpresionSimpleInt(int num)
{
    ExpresionABB e = new NodoABB;
    e->indiceNodo = 1;
    e->tipo = ENTERO;
    e->dato.num = num;
    e->hizq = NULL;
    e->hder = NULL;
    return e;
}

ExpresionABB CrearExpresionCompuesta(Operacion o, ExpresionABB a, ExpresionABB b)
{
    int contador = 0;

    ExpresionABB eIzq = copiarArbol(a);
    ExpresionABB eDer = copiarArbol(b);

    insertarParentesisIzquierdo(eIzq);
    insertarParentesisDerecho(eDer);

    ExpresionABB eRaiz = new NodoABB;
    eRaiz->tipo = OPERADOR;
    eRaiz->dato.simbolo = DevolverOperacion(o);
    eRaiz->hizq = eIzq;
    eRaiz->hder = eDer;

    reindexarInorden(eRaiz, contador);
    return eRaiz;
}

Boolean ArbolesIdenticos(ExpresionABB a, ExpresionABB b)
{
    Boolean resultado = FALSE;

    if (a == NULL && b == NULL)
    {
        resultado = TRUE;
    }
    else if (a != NULL && b != NULL)
    {
        Boolean mismoTipo = (a->tipo == b->tipo) ? TRUE : FALSE;
        Boolean mismoDato = FALSE;

        if (mismoTipo)
        {
            if (a->tipo == ENTERO)
                mismoDato = (a->dato.num == b->dato.num) ? TRUE : FALSE;
            else
                mismoDato = (a->dato.simbolo == b->dato.simbolo) ? TRUE : FALSE;
        }

        if (mismoTipo && mismoDato)
        {
            Boolean izq = ArbolesIdenticos(a->hizq, b->hizq);
            Boolean der = ArbolesIdenticos(a->hder, b->hder);

            resultado = (izq == TRUE && der == TRUE) ? TRUE : FALSE;
        }
    }

    return resultado;
}

int CalcularABB(ExpresionABB nodo, int valorX, Boolean &errorDivision)
{
    int resultado = 0;

    if (nodo != NULL && errorDivision == FALSE)
    {
        if (nodo->tipo == ENTERO)
        {
            resultado = nodo->dato.num;
        }
        else if (nodo->tipo == VARIABLE)
        {
            resultado = valorX;
        }
        else if (nodo->tipo == OPERADOR)
        {
            int izq = CalcularABB(nodo->hizq, valorX, errorDivision);
            int der = CalcularABB(nodo->hder, valorX, errorDivision);

            if (errorDivision == FALSE)
            {
                if (nodo->dato.simbolo == '+')
                    resultado = izq + der;

                else if (nodo->dato.simbolo == '-')
                    resultado = izq - der;

                else if (nodo->dato.simbolo == '*')
                    resultado = izq * der;

                else if (nodo->dato.simbolo == '/')
                {
                    if (der == 0)
                    {
                        errorDivision = TRUE;
                        resultado = 0;
                    }
                    else
                    {
                        resultado = izq / der;
                    }
                }
            }
        }
    }

    return resultado;
}

void DestruirABB(ExpresionABB &abb)
{
    if (abb != NULL)
    {
        DestruirABB(abb->hizq);
        DestruirABB(abb->hder);
        delete abb;
        abb = NULL;
    }
}

void reindexarInorden(ExpresionABB abb, int &contador)
{
    if (abb != NULL)
    {
        reindexarInorden(abb->hizq, contador);
        abb->indiceNodo = ++contador;
        reindexarInorden(abb->hder, contador);
    }
}

ExpresionABB copiarArbol(ExpresionABB original)
{
    ExpresionABB copia = NULL;

    if (original != NULL)
    {
        copia = new NodoABB;

        copia->indiceNodo = original->indiceNodo;
        copia->tipo = original->tipo;
        copia->dato = original->dato;

        copia->hizq = copiarArbol(original->hizq);
        copia->hder = copiarArbol(original->hder);
    }
    return copia;
}

void insertarParentesisIzquierdo(ExpresionABB &abb)
{
    if (abb != NULL)
    {

        ExpresionABB actual = abb;

        while (actual->hizq != NULL)
        {
            actual = actual->hizq;
        }

        ExpresionABB nuevo = new NodoABB;
        nuevo->indiceNodo = 0;
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

        while (actual->hder != NULL)
        {
            actual = actual->hder;
        }

        ExpresionABB nuevo = new NodoABB;
        nuevo->indiceNodo = 0;
        nuevo->tipo = CIERRAPARENTESIS;
        nuevo->dato.simbolo = ')';
        nuevo->hizq = NULL;
        nuevo->hder = NULL;

        actual->hder = nuevo;
    }
}

void MostrarABB(ExpresionABB abb)
{
    if (abb != NULL)
    {
        MostrarABB(abb->hizq);

        if (abb->tipo == ENTERO)
            printf("%d", abb->dato.num);

        else if (abb->tipo == VARIABLE)
            printf("%c", abb->dato.simbolo);

        else if (abb->tipo == OPERADOR)
            printf("%c", abb->dato.simbolo);

        else if (abb->tipo == ABREPARENTESIS)
            printf("(");

        else if (abb->tipo == CIERRAPARENTESIS)
            printf(")");

        MostrarABB(abb->hder);
    }
}


void BajarExpresionABB(ExpresionABB abb, FILE * f)
{
    if (abb != NULL)
    {
        BajarNodoABB(abb, f);
        BajarExpresionABB(abb->hizq, f);
        BajarExpresionABB(abb->hder, f);
    }
}

void BajarNodoABB(ExpresionABB nodo, FILE * f)
{
    fwrite(&nodo->tipo, sizeof(TipoDato), 1, f);
    if(nodo->tipo == ENTERO ){
        fwrite(&nodo->dato.num, sizeof(int), 1, f);
    }else{
        fwrite(&nodo->dato.simbolo, sizeof(char), 1, f);
    }
    fwrite(&nodo->indiceNodo, sizeof(int), 1, f);
}

void LevantarNodoABB(ExpresionABB &nodo, FILE * f)
{
    nodo = new NodoABB;
    fread(&nodo->tipo, sizeof(TipoDato), 1, f);
    if(nodo->tipo == ENTERO ){
        fread(&nodo->dato.num, sizeof(int), 1, f);
    }else{
        fread(&nodo->dato.simbolo, sizeof(char), 1, f);
    }
    fread(&nodo->indiceNodo, sizeof(int), 1, f);
}





void LevantarExpresionABB(ExpresionABB &abb, FILE * f)
{
    if (abb != NULL) 
    {
        LevantarNodoABB(abb, f);
        LevantarExpresionABB(abb->hizq, f);
        LevantarExpresionABB(abb->hder, f);
    }
} 