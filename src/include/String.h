#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED
#include "Boolean.h"
#include <stdio.h>

const int MAX = 80;
typedef char * String;

// Crea un string vacio
void strcrear (String &s);

// Libera la memoria usada por el string
void strdestruir (String &s);

// Devuelve el largo del string s
int strlar (String s);

// Copia el contenido del string s2 en s1
void strcop (String &s1, String s2);

// Lee el string s desde teclado
void scan (String &s);

// Concatena el contenido de s2 al final de s1
void strcon (String &s1, String s2);

// Intercambia los contenidos de s1 y s2
void strswp (String &s1, String &s2);

// Imprime el string s por pantalla
void print (String s);

// Levanta un string desde un file a memoria
//PRECONDICION: El archivo viene abierto para lectura
void Bajar_String (String s, FILE * f);

// Baja un string de memoria a un file
// PRECONDICION: El archivo viene abierto para escritura
void Levantar_String (String &s, FILE * f);

// Determina si s1 es alfab�ticamente menor que s2
Boolean strmen (String s1, String s2);

// Determina si los strings s1 y s2 son iguales
Boolean streq (String s1, String s2);

// Crea un String a partir de un rango de otro.
void CrearStringDesdeRango(String linea, int inicio, int fin, String &resultado);

// Detecta si un string posee únicamente caracteres alfabéticos o no
Boolean EsAlfabetico(String s);

// Indica si un token representa un operador válido.
Boolean EsOperadorValido(String token);

// Indica si un token representa un entero válido.
Boolean EsEnteroValido(String token);

// Detecta si el string posee un número entero.
Boolean EsEntero(String s);

// Detecta si el string es un número entero positivo.
Boolean EsEnteroPositivo(String s);

// Convierte un string a número entero.
int ConvertirAEntero(String s);

// Devuelve primer caracter del string.
 char PrimerCaracter(String s);


#endif // STRING_H_INCLUDED
