#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED
#include <stdio.h>
#include "ListaExpresiones.h"

// Indica si un archivo existe
//  PRECONDICIÓN: nombreArchivo es un String válido: alfabético.
Boolean ExisteArchivo(String nombreArchivo);

// Guarda una expresión (ABB) en orden en un archivo.
// PRECONDICIÓN: nombreArchivo es un String válido: alfabético.
void GuardarExpresionEnArchivo(ListaExpresiones lp, String nombreArchivo, int idx);

// Recupera expresiones desde un archivo y las agrega a la lista.
// PRECONDICIÓN: nombreArchivo es un String válido: alfabético.
void RecuperarInsertarExpresionDesdeArchivo(String nombreArchivo, ListaExpresiones &lp);

#endif