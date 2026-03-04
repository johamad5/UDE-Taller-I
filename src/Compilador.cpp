#include "Compilador.h"

Boolean ValidarComandoMostrar(ListaParsing tokens, ListaExpresiones expresiones, CodigoError &err)
{
    Boolean cmdValido = TRUE;

    if (CantidadTokens(tokens) != 1)
    {
        err = ERR_CANT_PARAMETROS;
        cmdValido = FALSE;
    }

    if (expresiones == NULL)
    {
        err = ERR_LISTA_VACIA;
        cmdValido = FALSE;
    }

    return cmdValido;
}

Boolean ValidarComandoRecuperar(ListaParsing tokens, String &nombreArchivo, CodigoError &err)
{
    Boolean cmdValido = TRUE;

    if (CantidadTokens(tokens) != 2)
    {
        err = ERR_CANT_PARAMETROS;
        cmdValido = FALSE;
    }

    if (!EsAlfabetico(nombreArchivo))
    {
        err = ERR_ARCHIVO_INVALIDO;
        cmdValido = FALSE;
    }
    else if (!ExisteArchivo(nombreArchivo))
    {
        err = ERR_ARCHIVO_NO_EXISTE;
        cmdValido = FALSE;
    }

    return cmdValido;
}

Boolean ValidarComandoSalir(ListaParsing tokens, CodigoError &err)
{
    Boolean cmdValido = TRUE;

    if (CantidadTokens(tokens) != 1)
    {
        err = ERR_CANT_PARAMETROS;
        cmdValido = FALSE;
    }

    return cmdValido;
}
