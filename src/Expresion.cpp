#include "Expresion.h"

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

Expresion CrearExpresionSimple(Boolean esX, int num)
{
    Expresion exp;
    exp.indiceLista = 0;

    if (esX)
        exp.terminos = CrearAbbSimpleChar();
    else
        exp.terminos = CrearAbbSimpleInt(num);

    return exp;
}

Expresion CrearExpresionCompuesta(Operacion op, Expresion exp1, Expresion exp2)
{
    Expresion exp;
    exp.indiceLista = 0;
    exp.terminos = CrearAbbCompuesta(op, exp1.terminos, exp2.terminos);

    return exp;
}

void CalcularExpresion(Expresion exp, int num, Boolean &errDiv, int &resultado)
{
    CalcularABB(exp.terminos, num, errDiv, resultado);
}

void CompararExpresiones(Expresion exp1, Expresion exp2)
{
    if (ArbolesIdenticos(exp1.terminos, exp2.terminos))
        printf("Las expresiones son identicas.\n");
    else
        printf("Las expresiones NO son identicas.\n");
}