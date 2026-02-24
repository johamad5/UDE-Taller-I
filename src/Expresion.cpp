#include "Expresion.h"

int ObtenerIndiceExpresion(Expresion exp) {}

void MostrarExpresion(Expresion exp) {}

void DestruirExpresion(Expresion &exp)
{
    DestruirABB(exp->terminos);
}