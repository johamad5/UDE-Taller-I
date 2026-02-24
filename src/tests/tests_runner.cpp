/*
    tests_runner.cpp

    Este archivo es el ejecutable de tests del proyecto.

    IMPORTANTE:
    En C++ solo puede existir UNA funcion main() por ejecutable.
    Como el proyecto ya tiene un main.cpp para la aplicacion,
    este archivo NO debe compilarse junto con src/main.cpp.

    Como compilar los tests (SIN incluir main.cpp):

    g++ src/Expresion.cpp src/Operacion.cpp src/test/tests_runner.cpp -o tests

    Luego ejecutar:
    ./tests
*/

#include <stdio.h>

// Incluir aqui los .h que quieras testear
// Ejemplo:
// #include "../include/Expresion.h"

void test_ejemplo_simple()
{
    int a = 2;
    int b = 3;

    if (a + b == 5)
    {
        printf("test_ejemplo_simple OK\n");
    }
    else
    {
        printf("test_ejemplo_simple ERROR\n");
    }
}

int main()
{
    printf("Iniciando tests...\n");

    test_ejemplo_simple();

    printf("Fin de los tests.\n");

    return 0;
}