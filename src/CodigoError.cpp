#include "CodigoError.h"


void DesplegarError(Error e) {


    switch (e) {

        case ERR_COMANDO_VACIO:
            printf("ERROR: Comando vacío.\n");
            break;

        case ERR_COMANDO_INVALIDO:
            printf("ERROR: Comando inválido.\n");
            break;

        case ERR_CANT_PARAMETROS:
            printf("ERROR: Cantidad de parámetros inválida.\n");
            break;

        case ERR_PARAMETRO_INVALIDO:
            printf("ERROR: Parámetro inválido.\n");
            break;

        case ERR_INDICE_INVALIDO:
            printf("ERROR: El índice debe ser un número entero positivo.\n");
            break;

        case ERR_INDICE_INEXISTENTE:
            printf("ERROR: El índice no existe en memoria.\n");
            break;

        case ERR_OPERADOR_INVALIDO:
            printf("ERROR: Operador inválido. Solo se aceptan +, -, * y /.\n");
            break;

        case ERR_DIVISION_POR_CERO:
            printf("ERROR: No se puede dividir entre cero.\n");
            break;

        case ERR_LISTA_VACIA:
            printf("ERROR: No hay expresiones guardadas en memoria.\n");
            break;

        case ERR_NOMBRE_ARCHIVO_INVALIDO:
            printf("ERROR: Nombre de archivo inválido. Solo letras permitidas.\n");
            break;

        case ERR_ARCHIVO_EXISTE:
            printf("ERROR: El archivo ya existe.\n");
            break;

        case ERR_ARCHIVO_NO_EXISTE:
            printf("ERROR: El archivo no existe.\n");
            break;

        default:
            printf("ERROR: Error desconocido.\n");
            break;
    }
}

