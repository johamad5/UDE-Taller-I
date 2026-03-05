#ifndef COMPILADOR_H_INCLUDED
#define COMPILADOR_H_INCLUDED
#include "ListaParsing.h"
#include "Archivo.h"
#include "Comando.h"
#include "Operacion.h"
#include "CodigoError.h"
#include "ListaExpresiones.h"

const int MOSTRAR_CANT_TOKENS = 0;
const int RECUPERAR_CANT_TOKENS = 1;
const int SALIR_CANT_TOKENS = 0;
const int TOKENS_SIMPLE = 1;
const int TOKENS_GUARDAR = 3;
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
const int POSICION_TOKEN_PARAM_SIMPLE = 2;
const int POSICION_TOKEN_NOMBRE_ARCHIVO_GUARDAR = 3;
const int POSICION_TOKEN_INDICE_GUARDAR = 2;

//  LOOP PRINCIPAL
// Ejecuta el ciclo principal del programa. Lee la entrada del usuario, tokeniza, valida y ejecuta comandos.
// PRECONDICIÓN: La lista de expresiones debe estar correctamente inicializada.
void LoopPrincipal(ListaExpresiones &expresiones);

//  RECONOCIMIENTO Y VALIDACIÓN GENERAL
// Reconoce el comando ingresado y valida sus parámetros. Deja cargados todos los valores necesarios para ejecutar el comando.
void ReconocerYValidarComando(ListaParsing tokens, ListaExpresiones expresiones, TipoComando &tipoComando, Boolean &esX, int &num, int &idx1, Operacion &operador, int &idx2, int &valorX, String &nombreArchivo, CodigoError &codigoError);

// Este procedimiento identifica el tipo de comando según el primer token.
void ReconocerComando(String cmd, TipoComando &tipoComando, CodigoError &codigoError);

//  VALIDACIONES ESPECIFICAS POR COMANDO
// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando de creación simple.
void ValidarComandoSimple(
    ListaParsing tokens,
    Boolean &esX,
    int &num,
    CodigoError &err);

// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando de creación compuesta.
void ValidarComandoCompuesta(ListaParsing tokens, ListaExpresiones expresiones, int &indiceUno, int &indiceDos, Operacion &operacion, CodigoError &codigoError);

// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando mostrar.
CodigoError ValidarComandoMostrar(
    ListaParsing tokens,
    ListaExpresiones expresiones);

// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando calcular.
void ValidarComandoCalcular(ListaParsing tokens, ListaExpresiones expresiones, int &valor, int &indice, CodigoError &codigoError);

// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando comparar iguales.
void ValidarComandoIguales(ListaParsing tokens, ListaExpresiones expresiones, int &indiceUno, int &indiceDos, CodigoError &codigoError);

// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando guardar.
void ValidarComandoGuardar(ListaParsing tokens, ListaExpresiones expresiones, int &indice, String &nombreArchivo, CodigoError &error);

// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando recuperar.
void ValidarComandoRecuperar(
    ListaParsing tokens,
    String &nombreArchivo,
    CodigoError &err);

// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando salir.
CodigoError ValidarComandoSalir(ListaParsing tokens);

//    EJECUCION DE COMANDOS
// Ejecuta el comando previamente validado.
// PRECONDICIÓN: Los parámetros deben haber sido validados previamente.
void EjecutarComando(
    TipoComando tipo,
    Boolean esX,
    int num,
    int idx1,
    Operacion op,
    int idx2,
    String nombreArchivo,
    ListaExpresiones &expresiones,
    CodigoError &err);

// Crea una expresión simple y la guarda en la lista.
// PRECONDICIÓN: Los parámetros deben haber sido validados previamente.
void CrearYGuardarExpresionSimple(
    Boolean esX,
    int num,
    ListaExpresiones &expresiones,
    CodigoError &err);

// Crea una expresión compuesta utilizando índices existentes.
// PRECONDICIÓN: Los parámetros deben haber sido validados previamente.
void CrearYGuardarExpresionCompuesta(
    int idx1,
    Operacion op,
    int idx2,
    ListaExpresiones &expresiones,
    CodigoError &err);

// Calcula el resultado de una expresión guardada en memoria.
// PRECONDICIÓN: Los parámetros deben haber sido validados previamente.
void CalcularResultado(
    int indice,
    int valorX,
    ListaExpresiones expresiones,
    int &resultado,
    CodigoError &error);

// Compara si dos expresiones guardadas en memoria son iguales.
// PRECONDICIÓN: Los parámetros deben haber sido validados previamente.
void CompararExpresionesIguales(
    int indice1,
    int indice2,
    ListaExpresiones expresiones,
    Boolean &sonIguales,
    CodigoError &error);

#endif