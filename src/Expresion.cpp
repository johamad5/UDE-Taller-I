#include "Expresion.h"

int ObtenerIndiceExpresion(Expresion exp)
{
    return exp.indiceLista;
}

void MostrarExpresion(Expresion exp)
{
    MostrarABB(exp.terminos);
}

void DestruirExpresion(Expresion &exp)
{
    DestruirABB(exp.terminos);
    exp.terminos = NULL;
}