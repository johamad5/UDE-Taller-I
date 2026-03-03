#include "Compilador.h"

Boolean ValidarComandoMostrar(ListaParsing tokens, ListaExpresiones expresiones, CodigoError &err)
{
    Boolean cmdValido = TRUE;

    int cantTokens = CantidadTokens(tokens);
    if (cantTokens != 1)
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
    return TRUE;
}

Boolean ValidarComandoSalir(ListaParsing tokens, CodigoError &err)
{
    return TRUE;
}
