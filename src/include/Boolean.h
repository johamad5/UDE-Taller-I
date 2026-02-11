#ifndef BOOLEAN_H_INCLUDED
#define BOOLEAN_H_INCLUDED
#include <stdio.h>

typedef enum {FALSE, TRUE} Boolean;

// Cargar valor boolean desde teclado
void Cargar(Boolean &b);

// Mostrar valor booleano en pantalla
void Despliegue(Boolean b);

#endif // BOOLEAN_H_INCLUDED