#include "Expresion.h"

void setTermino(Expresion &exp, ExpresionABB expABB)
{
    exp.terminos = expABB;
}

ExpresionABB getTermino(Expresion exp)
{
    return exp.terminos;
}

void setIndiceExpresion(Expresion &exp, int id)
{
    exp.indiceLista = id;
}

int getIndiceExpresion(Expresion exp)
{
    return exp.indiceLista;
}

void MostrarExpresion(Expresion exp)
{
    printf("%d) ", exp.indiceLista);
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
    exp.indiceLista = 0;
    LevantarExpresionABB(exp.terminos, f);
}