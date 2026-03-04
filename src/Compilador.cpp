#include "Compilador.h"

void ValidarComandoCompuesta(ListaParsing tokens, ListaExpresiones expresiones, int &indiceUno, int &indiceDos, Operacion &operacion, CodigoError &codigoError)
{
    codigoError = ERR_NINGUNO;
    indiceUno = 0;
    indiceDos = 0;

    if (CantidadTokens(tokens) != TOKENS_COMPUESTA)
        codigoError = ERR_CANT_PARAMETROS;
    else
    {
        int i = 0;
        while (tokens != NULL && codigoError == ERR_NINGUNO)
        {
            switch (i)
            {
            case POSICION_TOKEN_PRIMER_INDICE_COMPUESTA:
                if (!EsEnteroPositivo(tokens->palabra))
                    codigoError = ERR_INDICE_INVALIDO;
                else
                {
                    indiceUno = ConvertirAEntero(tokens->palabra);
                    if (EsIndiceValido(expresiones, indiceUno))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            case POSICION_TOKEN_OPERADOR:
                if (!EsOperadorValido(tokens->palabra))
                    codigoError = ERR_OPERADOR_INVALIDO;
                else
                    operacion = DevolverOperacion(PrimerCaracter(tokens->palabra));
                break;

            case POSICION_TOKEN_SEGUNDO_INDICE_COMPUESTA:
                if (!EsEnteroPositivo(tokens->palabra))
                    codigoError = ERR_INDICE_INVALIDO;
                else
                {
                    indiceDos = ConvertirAEntero(tokens->palabra);
                    if (EsIndiceValido(expresiones, indiceDos))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            }

            tokens = tokens->sig;
            i++;
        }
    }
}

void ValidarComandoCalcular(ListaParsing tokens, ListaExpresiones expresiones, int &indice, CodigoError &codigoError)
{
    codigoError = ERR_NINGUNO;
    indice = 0;

    if (CantidadTokens(tokens) != TOKENS_CALCULAR)
        codigoError = ERR_CANT_PARAMETROS;
    else
    {
        int i = 0;
        while (tokens != NULL && codigoError == ERR_NINGUNO)
        {
            switch (i)
            {
            case POSICION_TOKEN_INDICE_VARIABLE:
                if (!EsEntero(tokens->palabra))
                    codigoError = ERR_PARAMETRO_INVALIDO;
                break;
            case POSICION_TOKEN_INDICE_CALCULO:
                if (!EsEnteroPositivo(tokens->palabra))
                    codigoError = ERR_INDICE_INVALIDO;
                else
                {
                    indice = ConvertirAEntero(tokens->palabra);
                    if (EsIndiceValido(expresiones, indice))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            }

            tokens = tokens->sig;
            i++;
        }
    }
}

void ValidarComandoIguales(ListaParsing tokens, ListaExpresiones expresiones, int &indiceUno, int &indiceDos, CodigoError &codigoError)
{
    codigoError = ERR_NINGUNO;
    indiceUno = 0;
    indiceDos = 0;

    if (CantidadTokens(tokens) != TOKENS_IGUALES)
        codigoError = ERR_CANT_PARAMETROS;
    else
    {
        int i = 0;
        while (tokens != NULL && codigoError == ERR_NINGUNO)
        {
            switch (i)
            {
            case POSICION_TOKEN_PRIMER_INDICE_IGUALES:
                if (!EsEnteroPositivo(tokens->palabra))
                    codigoError = ERR_INDICE_INVALIDO;
                else
                {
                    indiceUno = ConvertirAEntero(tokens->palabra);
                    if (EsIndiceValido(expresiones, indiceUno))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            case POSICION_TOKEN_SEGUNDO_INDICE_IGUALES:
                if (!EsEnteroPositivo(tokens->palabra))
                    codigoError = ERR_INDICE_INVALIDO;
                else
                {
                    indiceDos = ConvertirAEntero(tokens->palabra);
                    if (EsIndiceValido(expresiones, indiceDos))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            }

            tokens = tokens->sig;
            i++;
        }
    }
}
