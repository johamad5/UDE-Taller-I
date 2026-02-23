#ifndef CODIGOERROR_H_INCLUDED
#define CODIGOERROR_H_INCLUDED

typedef enum {
    ERR_NINGUNO,
    ERR_COMANDO_VACIO,
    ERR_COMANDO_INVALIDO,
    ERR_CANT_PARAMETROS,
    ERR_PARAMETRO_INVALIDO,
    ERR_INDICE_INVALIDO,
    ERR_INDICE_INEXISTENTE,
    ERR_OPERADOR_INVALIDO,
    ERR_DIVISION_POR_CERO,
    ERR_NOMBRE_ARCHIVO_INVALIDO,
    ERR_ARCHIVO_EXISTE,
    ERR_ARCHIVO_NO_EXISTE,
    ERR_LISTA_VACIA,
    ERR_ARCHIVO_INVALIDO,
    ERR_ARCHIVO_NO_SE_PUEDE_ABRIR
    } CodigoError;

// Muestra por pantalla un mensaje asociado al código de error pasado por parámetro.
void MostrarError(CodigoError e);

#endif