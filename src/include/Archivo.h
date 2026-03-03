#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED
#include <stdio.h>
#include "CodigoError.h"
#include "ListaExpresiones.h"
#include "String.h"

// Indica si un archivo existe
//  PRECONDICIÓN: nombreArchivo es un String válido: alfabético.
Boolean ExisteArchivo(String nombreArchivo);

// Guarda una expresión (ABB) en orden en un archivo.
// PRECONDICIÓN: nombreArchivo es un String válido: alfabético.
void GuardarExpresionEnArchivo(String nombreArchivo, Expresion exp, CodigoError &err);

// Recupera expresiones desde un archivo y las agrega a la lista.
// PRECONDICIÓN: nombreArchivo es un String válido: alfabético.
void RecuperarExpresionDesdeArchivo(String nombreArchivo, Expresion &lista, CodigoError &err);

#endif