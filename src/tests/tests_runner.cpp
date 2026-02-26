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
#include "ExpresionABB.h"

void test_entero_simple()
{
    ExpresionABB e = CrearExpresionSimpleInt(5);
    Boolean error = FALSE;

    int resultado = CalcularABB(e, 0, error);

    if (resultado == 5 && error == FALSE)
        printf("✔ test_entero_simple pasó\n");
    else
        printf("✘ test_entero_simple falló\n");

    DestruirABB(e);
}

void test_variable_x()
{
    ExpresionABB e = CrearExpresionSimpleX('x');
    Boolean error = FALSE;

    int resultado = CalcularABB(e, 7, error);

    if (resultado == 7 && error == FALSE)
        printf("✔ test_variable_x pasó\n");
    else
        printf("✘ test_variable_x falló\n");

    DestruirABB(e);
}

void test_suma()
{
    ExpresionABB a = CrearExpresionSimpleInt(3);
    ExpresionABB b = CrearExpresionSimpleInt(4);

    ExpresionABB e = CrearExpresionCompuesta(SUMA, a, b);

    Boolean error = FALSE;
    int resultado = CalcularABB(e, 0, error);

    if (resultado == 7 && error == FALSE)
        printf("✔ test_suma pasó\n");
    else
        printf("✘ test_suma falló\n");

    DestruirABB(e);
}

void test_multiplicacion_variable()
{
    ExpresionABB a = CrearExpresionSimpleX('x');
    ExpresionABB b = CrearExpresionSimpleInt(2);

    ExpresionABB e = CrearExpresionCompuesta(MULTIPLICACION, a, b);

    Boolean error = FALSE;
    int resultado = CalcularABB(e, 5, error);

    if (resultado == 10 && error == FALSE)
        printf("✔ test_multiplicacion_variable pasó\n");
    else
        printf("✘ test_multiplicacion_variable falló\n");

    DestruirABB(e);
}

void test_expresion_compuesta()
{
    // (3 + 2) * x

    ExpresionABB a = CrearExpresionSimpleInt(3);
    ExpresionABB b = CrearExpresionSimpleInt(2);
    ExpresionABB suma = CrearExpresionCompuesta(SUMA, a, b);

    ExpresionABB x = CrearExpresionSimpleX('x');
    ExpresionABB final = CrearExpresionCompuesta(MULTIPLICACION, suma, x);

    Boolean error = FALSE;
    int resultado = CalcularABB(final, 4, error);

    if (resultado == 20 && error == FALSE)
        printf("✔ test_expresion_compuesta pasó\n");
    else
        printf("✘ test_expresion_compuesta falló\n");

    DestruirABB(final);
}

void test_division_por_cero()
{
    ExpresionABB a = CrearExpresionSimpleInt(10);
    ExpresionABB b = CrearExpresionSimpleInt(0);

    ExpresionABB e = CrearExpresionCompuesta(DIVISION, a, b);

    Boolean error = FALSE;
    int resultado = CalcularABB(e, 0, error);

    if (error == TRUE)
        printf("✔ test_division_por_cero pasó\n");
    else
        printf("✘ test_division_por_cero falló\n");

    DestruirABB(e);
}

int main()
{
    printf("---- Ejecutando tests CalcularABB ----\n\n");

    test_entero_simple();
    test_variable_x();
    test_suma();
    test_multiplicacion_variable();
    test_expresion_compuesta();
    test_division_por_cero();

    printf("\n---- Fin de tests ----\n");

    return 0;
}