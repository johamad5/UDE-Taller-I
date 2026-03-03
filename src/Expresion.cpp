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

void BajarExpresion(Expresion exp, FILE *f)
{
    BajarExpresionABB(exp.terminos, f);
}

void LevantarExpresion(Expresion &exp, FILE *f)
{
    exp.terminos = NULL;
    LevantarExpresionABB(exp.terminos, f);
}