#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED
#include "Boolean.h"

const int MAX = 80;
typedef char *String;

// Crea un string vacio
void strcrear(String &s);

// Libera la memoria usada por el string
void strdestruir(String &s);

// Devuelve el largo del string s
int strlar(String s);

// Copia el contenido del string s2 en s1
void strcop(String &s1, String s2);

// Lee el string s desde teclado
void scan(String &s);

// Concatena el contenido de s2 al final de s1
void strcon(String &s1, String s2);

// Imprime el string s por pantalla
void print(String s);

// Determina si los strings s1 y s2 son iguales
Boolean streq(String s1, String s2);

// Levanta un string desde un file a memoria                          
// PRECONDICIÓN: f debe ser un archivo abierto para lectura.          
void LevantarString(String &s, FILE *f);

// Baja un string de memoria a un file                                
// PRECONDICIÓN: f debe ser un archivo abierto para escritura.        
void BajarString(String s, FILE *f);

// Crea un String a partir de un rango de otro.
void CrearStringDesdeRango(String linea, int inicio, int fin, String &resultado);

// Detecta si un string posee únicamente caracteres alfabéticos o no
Boolean EsAlfabetico(String s);

// Indica si un token representa un operador válido.
Boolean EsOperadorValido(String token);

// Detecta si el string posee un número entero.
Boolean EsEntero(String s);

// Detecta si el string es un número entero positivo.
Boolean EsEnteroPositivo(String s);

// Convierte un string a número entero.
int ConvertirAEntero(String s);

// Devuelve primer caracter del string.
char PrimerCaracter(String s);

#endif // STRING_H_INCLUDED
