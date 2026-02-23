#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED
#include <stdio.h>
#include "ArbolAlumnos.h"

// Determina si existe o no un archivo con el nombre recibido por parámetro
Boolean Existe (String nomArch);

// Cargar el arbol de alumnos con en el archivo de alumnos
void LevantarAlumnos (ABB &a, String nomArch);

// Respaldar en el archivo de alumnos el arbol
void RespaldarAlumnos_Aux (ABB a, FILE * f);
void RespaldarAlumnos (ABB a, String nomArch);

// Cargar la lista de talleres en el archivo de talleres
void LevantarTalleresFinalizados(Lista &l, String nomArch);

// Respaldar en el archivo de talleres la lista
void RespaldarTalleresFinalizados(Lista l, String nomArch);

#endif // ARCHIVO_H_INCLUDED
