#include "CodigoError.h"

void MostrarError(CodigoError e)
{

    switch (e)
    {

    case ERR_NINGUNO:
        printf("No hay error.\n");
        break;
    case ERR_COMANDO_VACIO:
        printf("ERROR: Comando vacio.\n");
        break;

    case ERR_COMANDO_INVALIDO:
        printf("ERROR: Comando invalido.\n");
        break;

    case ERR_CANT_PARAMETROS:
        printf("ERROR: Cantidad de parametros invalida.\n");
        break;

    case ERR_PARAMETRO_INVALIDO:
        printf("ERROR: Parametro invalido.\n");
        break;

    case ERR_INDICE_INVALIDO:
        printf("ERROR: El indice debe ser un numero entero positivo.\n");
        break;

    case ERR_INDICE_INEXISTENTE:
        printf("ERROR: El indice no existe en memoria.\n");
        break;

    case ERR_OPERADOR_INVALIDO:
        printf("ERROR: Operador invalido. Solo se aceptan +, -, * y /.\n");
        break;

    case ERR_DIVISION_POR_CERO:
        printf("ERROR: No se puede dividir entre cero.\n");
        break;
    case ERR_NOMBRE_ARCHIVO_INVALIDO:
        printf("ERROR: Nombre de archivo invalido. Solo letras permitidas.\n");
        break;

    case ERR_ARCHIVO_EXISTE:
        printf("ERROR: El archivo ya existe.\n");
        break;

    case ERR_ARCHIVO_NO_EXISTE:
        printf("ERROR: El archivo no existe.\n");
        break;
    case ERR_ARCHIVO_INVALIDO:
        printf("ERROR: Archivo invalido.\n");
        break;
    case ERR_LISTA_VACIA:
        printf("ERROR: No hay expresiones guardadas en memoria.\n");
        break;
    default:
        printf("ERROR: Error desconocido.\n");
        break;
    }
}
