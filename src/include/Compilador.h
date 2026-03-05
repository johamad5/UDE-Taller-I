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

//  LOOP PRINCIPAL
// Ejecuta el ciclo principal del programa. Lee la entrada del usuario, tokeniza, valida y ejecuta comandos.
// PRECONDICIÓN: La lista de expresiones debe estar correctamente inicializada.
void LoopPrincipal(ListaExpresiones &expresiones);

//  RECONOCIMIENTO Y VALIDACIÓN GENERAL
// Reconoce el comando ingresado y valida sus parámetros. Deja cargados todos los valores necesarios para ejecutar el comando.
void ReconocerYValidarComando(
    ListaParsing tokens,
    ListaExpresiones expresiones,
    TipoComando &tipo,
    Boolean &esX,
    int &num,
    int &idx1,
    char &operador,
    int &idx2,
    int &valorX,
    String &nombreArchivo,
    CodigoError &error);

// Este procedimiento identifica el tipo de comando según el primer token.
TipoComando ReconocerComando(String cmd);

//  VALIDACIONES ESPECIFICAS POR COMANDO
// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando de creación simple.
Boolean ValidarComandoSimple(
    ListaParsing tokens,
    Boolean &esX,
    int &num,
    CodigoError &err);

// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando de creación compuesta.
Boolean ValidarComandoCompuesta(
    ListaParsing tokens,
    int &idx1,
    Operacion &op,
    int &idx2,
    ListaExpresiones expresiones,
    CodigoError &err);

// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando mostrar.
CodigoError ValidarComandoMostrar(
    ListaParsing tokens,
    ListaExpresiones expresiones);

// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando calcular.
Boolean ValidarComandoCalcular(
    ListaParsing tokens,
    int &idx1,
    ListaExpresiones expresiones,
    CodigoError &err);

// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando comparar iguales.
Boolean ValidarComandoIguales(
    ListaParsing tokens,
    int &idx1,
    int &idx2,
    ListaExpresiones expresiones,
    CodigoError &err);

// Valida que todos los parámetros sean válidos para posteriormente ejecutar el comando guardar.
Boolean ValidarComandoGuardar(
    ListaParsing tokens,
    int &idx1,
    String &nombreArchivo,
    ListaExpresiones expresiones,
    CodigoError &err);

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