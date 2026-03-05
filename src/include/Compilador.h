#ifndef COMPILADOR_H_INCLUDED
#define COMPILADOR_H_INCLUDED
#include "ListaParsing.h"
#include "Operacion.h"
#include "CodigoError.h"
#include "ListaExpresiones.h"

const int TOKENS_COMPUESTA = 3;
const int TOKENS_CALCULAR = 2;
const int TOKENS_IGUALES = 2;

const int POSICION_TOKEN_PRIMER_INDICE_COMPUESTA = 1;
const int POSICION_TOKEN_OPERADOR_COMPUESTA = 2;
const int POSICION_TOKEN_SEGUNDO_INDICE_COMPUESTA = 3;
const int POSICION_TOKEN_INDICE_CALCULO = 2;
const int POSICION_TOKEN_INDICE_VARIABLE = 1;
const int POSICION_TOKEN_PRIMER_INDICE_IGUALES = 1;
const int POSICION_TOKEN_SEGUNDO_INDICE_IGUALES = 2;

void ValidarComandoCompuesta(ListaParsing tokens, ListaExpresiones expresiones, int &indiceUno, int &indiceDos, Operacion &operacion, CodigoError &codigoError);
void ValidarComandoCalcular(ListaParsing tokens, ListaExpresiones expresiones, int &valor, int &indice, CodigoError &codigoError);
void ValidarComandoIguales(ListaParsing tokens, ListaExpresiones expresiones, int &indiceUno, int &indiceDos, CodigoError &codigoError);

#endif