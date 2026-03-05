#include "Compilador.h"

void ReconocerYValidarComando(ListaParsing tokens, ListaExpresiones expresiones, TipoComando &tipoComando, Boolean &esX, int &num, int &idx1, Operacion &operador, int &idx2, int &valorX, String &nombreArchivo, CodigoError &codigoError)
{
    ReconocerComando(tokens->palabra, tipoComando, codigoError);

    if (codigoError != ERR_NINGUNO)
    {
        switch (tipoComando)
        {
        case SIMPLE:
            // ValidarComandoSimple(tokens->sig, esX, num, codigoError);
            break;
        case COMPUESTA:
            ValidarComandoCompuesta(tokens->sig, expresiones, idx1, idx2, operador, codigoError);
            break;
        case CALCULAR:
            ValidarComandoCalcular(tokens->sig, expresiones, num, idx1, codigoError);
            break;
        case MOSTRAR:
            // codigoError = ValidarComandoMostrar(tokens->sig,expresiones);
            break;
        case IGUALES:
            ValidarComandoIguales(tokens->sig, expresiones, idx1, idx2, codigoError);
            break;
        case GUARDAR:
            // ValidarComandoGuardar(tokens->sig, expresiones, idx1, nombreArchivo, codigoError);
            break;
        case RECUPERAR:
            // ValidarComandoRecuperar(tokens->sig, nombreArchivo, codigoError);
            break;
        case SALIR:
            // codigoError = ValidarComandoSalir(tokens->sig);
            break;
        }
    }
}

void ReconocerComando(String cmd, TipoComando &tipoComando, CodigoError &codigoError)
{
    codigoError = ERR_NINGUNO;

    String Simple, Compuesta, Calcular, Mostrar, Guardar, Recuperar, Iguales, Salir;

    strcrear(Simple);
    strcrear(Compuesta);
    strcrear(Calcular);
    strcrear(Mostrar);
    strcrear(Guardar);
    strcrear(Recuperar);
    strcrear(Iguales);
    strcrear(Salir);

    strcop(Simple, "simple");
    strcop(Compuesta, "compuesta");
    strcop(Calcular, "calcular");
    strcop(Mostrar, "mostrar");
    strcop(Guardar, "guardar");
    strcop(Recuperar, "recuperar");
    strcop(Iguales, "iguales");
    strcop(Salir, "salir");

    if (streq(cmd, Simple))
    {
        tipoComando = SIMPLE;
    }
    else if (streq(cmd, Compuesta))
    {
        tipoComando = COMPUESTA;
    }
    else if (streq(cmd, Calcular))
    {
        tipoComando = CALCULAR;
    }
    else if (streq(cmd, Mostrar))
    {
        tipoComando = MOSTRAR;
    }
    else if (streq(cmd, Guardar))
    {
        tipoComando = GUARDAR;
    }
    else if (streq(cmd, Recuperar))
    {
        tipoComando = RECUPERAR;
    }
    else if (streq(cmd, Iguales))
    {
        tipoComando = IGUALES;
    }
    else if (streq(cmd, Salir))
    {
        tipoComando = SALIR;
    }
    else
    {
        codigoError = ERR_COMANDO_INVALIDO;
    }

    strdestruir(Simple);
    strdestruir(Compuesta);
    strdestruir(Calcular);
    strdestruir(Mostrar);
    strdestruir(Guardar);
    strdestruir(Recuperar);
    strdestruir(Iguales);
    strdestruir(Salir);
}

void ValidarComandoCompuesta(ListaParsing tokens, ListaExpresiones expresiones, int &indiceUno, int &indiceDos, Operacion &operacion, CodigoError &codigoError)
{
    codigoError = ERR_NINGUNO;
    indiceUno = 0;
    indiceDos = 0;

    if (CantidadTokens(tokens) != TOKENS_COMPUESTA)
        codigoError = ERR_CANT_PARAMETROS;
    else
    {
        int i = 1;
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
                    if (!EsIndiceValido(expresiones, indiceUno))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            case POSICION_TOKEN_OPERADOR_COMPUESTA:
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
                    if (!EsIndiceValido(expresiones, indiceDos))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            }

            tokens = tokens->sig;
            i++;
        }
    }
}

void ValidarComandoCalcular(ListaParsing tokens, ListaExpresiones expresiones, int &valor, int &indice, CodigoError &codigoError)
{
    codigoError = ERR_NINGUNO;
    indice = 0;

    if (CantidadTokens(tokens) != TOKENS_CALCULAR)
        codigoError = ERR_CANT_PARAMETROS;
    else
    {
        int i = 1;
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
                    if (!EsIndiceValido(expresiones, indice))
                        codigoError = ERR_INDICE_INVALIDO;
                    else
                        valor = ConvertirAEntero(tokens->palabra);
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
        int i = 1;
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
                    if (!EsIndiceValido(expresiones, indiceUno))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            case POSICION_TOKEN_SEGUNDO_INDICE_IGUALES:
                if (!EsEnteroPositivo(tokens->palabra))
                    codigoError = ERR_INDICE_INVALIDO;
                else
                {
                    indiceDos = ConvertirAEntero(tokens->palabra);
                    if (!EsIndiceValido(expresiones, indiceDos))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            }

            tokens = tokens->sig;
            i++;
        }
    }
}
