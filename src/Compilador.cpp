#include "Compilador.h"

CodigoError ValidarComandoMostrar(ListaParsing tokens, ListaExpresiones expresiones)
{
    CodigoError err = ERR_NINGUNO;

    if (CantidadTokens(tokens) != MOSTRAR_CANT_TOKENS)
    {
        err = ERR_CANT_PARAMETROS;
    }

    if (expresiones == NULL)
    {
        err = ERR_LISTA_VACIA;
    }

    return err;
}

void ValidarComandoRecuperar(ListaParsing tokens, String &nombreArchivo, CodigoError &err)
{
    err = ERR_NINGUNO;

    if (CantidadTokens(tokens) != RECUPERAR_CANT_TOKENS)
    {
        err = ERR_CANT_PARAMETROS;
    }
    else
    {
        if (!EsAlfabetico(tokens->palabra))
        {
            err = ERR_ARCHIVO_INVALIDO;
        }
        else if (!ExisteArchivo(tokens->palabra))
        {
            err = ERR_ARCHIVO_NO_EXISTE;
        }
        else
        {
            strcop(nombreArchivo, tokens->palabra)
        }
    }
}

CodigoError ValidarComandoSalir(ListaParsing tokens)
{
    CodigoError err = ERR_NINGUNO;

    if (CantidadTokens(tokens) != 1)
        err = ERR_CANT_PARAMETROS;

    return err;
}
