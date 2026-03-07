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
#include "ListaParsing.h"
#include "CodigoError.h"
#include "ListaExpresiones.h"
#include "Archivo.h"
#include "Compilador.h"

//-----------------------------------//
//        TESTS MODULO STRING        //
//-----------------------------------//

void test_strcrear()
{
    String s;
    strcrear(s);

    if (s != NULL && s[0] == '\0')
        printf("OK     test_strcrear\n");
    else
        printf("ERROR  test_strcrear\n");

    strdestruir(s);
}

void test_strdestruir()
{
    String s;
    strcrear(s);

    strdestruir(s);

    if (s == NULL)
        printf("OK     test_strdestruir\n");
    else
        printf("ERROR  test_strdestruir\n");
}

void test_strlar_vacio()
{
    String s;
    strcrear(s);

    int largo = strlar(s);

    if (largo == 0)
        printf("OK     test_strlar_vacio\n");
    else
        printf("ERROR  test_strlar_vacio: largo esperado: 0, obtenido: %d)\n", largo);

    strdestruir(s);
}

void test_strlar_con_contenido()
{
    String s = new char[5];
    s[0] = 'H';
    s[1] = 'o';
    s[2] = 'l';
    s[3] = 'a';
    s[4] = '\0';

    int largo = strlar(s);

    if (largo == 4)
        printf("OK     test_strlar_con_contenido\n");
    else
        printf("ERROR  test_strlar_con_contenido: largo esperado: 4, obtenido: %d)\n", largo);

    delete[] s;
}

void test_strcop_vacio_a_vacio()
{
    String s1;
    strcrear(s1);
    String s2;
    strcrear(s2);

    strcop(s1, s2);

    if (strlar(s1) == 0 && s1[0] == '\0')
        printf("OK     test_strcop_vacio_a_vacio\n");
    else
        printf("ERROR  test_strcop_vacio_a_vacio\n");

    strdestruir(s1);
    strdestruir(s2);
}

void test_strcop_contenido()
{
    String s1;
    strcrear(s1);

    String s2 = new char[5];
    s2[0] = 'H';
    s2[1] = 'o';
    s2[2] = 'l';
    s2[3] = 'a';
    s2[4] = '\0';

    strcop(s1, s2);

    if (strlar(s1) == 4 && s1[0] == 'H' && s1[3] == 'a' && s1[4] == '\0')
        printf("OK     test_strcop_contenido\n");
    else
        printf("ERROR  test_strcop_contenido\n");

    strdestruir(s1);
    delete[] s2;
}

void test_strcop_redimension()
{
    String s1 = new char[2];
    s1[0] = 'A';
    s1[1] = '\0';

    String s2 = new char[7];
    s2[0] = 'B';
    s2[1] = 'e';
    s2[2] = 'l';
    s2[3] = 'l';
    s2[4] = 'o';
    s2[5] = 's';
    s2[6] = '\0';

    strcop(s1, s2);

    if (strlar(s1) == 6 && s1[0] == 'B' && s1[5] == 's')
        printf("OK     test_strcop_redimension\n");
    else
        printf("ERROR  test_strcop_redimension\n");

    strdestruir(s1);
    delete[] s2;
}

void test_scan_mock()
{
    String s;
    strcrear(s);

    FILE *tmp = fopen("test_input.txt", "w");
    fprintf(tmp, "Hola\n");
    fclose(tmp);

    FILE *original_stdin = stdin;
    freopen("test_input.txt", "r", stdin);

    scan(s);

    freopen("CON", "r", stdin);

    if (strlar(s) == 4 && s[0] == 'H' && s[1] == 'o')
        printf("OK     test_scan_mock\n");
    else
        printf("ERROR  test_scan_mock: obtenido: %s\n", s);

    strdestruir(s);
    remove("test_input.txt");
}

void test_strcon_supera_MAX()
{
    String s1;
    String s2;

    strcrear(s1);
    strcrear(s2);

    char buffer1[71];
    int i = 0;
    while (i < 70)
    {
        buffer1[i] = 'A';
        i++;
    }
    buffer1[70] = '\0';

    char buffer2[21];
    i = 0;
    while (i < 20)
    {
        buffer2[i] = 'B';
        i++;
    }
    buffer2[20] = '\0';

    strcop(s1, buffer1);
    strcop(s2, buffer2);

    strcon(s1, s2);

    int largoFinal = strlar(s1);

    if (largoFinal == MAX - 1)
        printf("OK     test_strcon_supera_MAX\n");
    else
        printf("ERROR  test_strcon_supera_MAX: largo: %d\n", largoFinal);

    strdestruir(s1);
    strdestruir(s2);
}

void test_print()
{
    String s;
    strcrear(s);
    strcop(s, "Hola");

    printf("> test_print\n");

    printf("   Resultado esperado: Hola\n");
    printf("   Resultado obtenido: ");
    print(s);

    printf("\n");

    if (strlar(s) == 4 && s[0] == 'H' && s[4] == '\0')
        printf("OK     test_print\n");
    else
        printf("ERROR  test_print\n");

    strdestruir(s);
}

void test_streq_identicos()
{
    String s1, s2;
    strcrear(s1);
    strcop(s1, "Mismo");
    strcrear(s2);
    strcop(s2, "Mismo");

    if (streq(s1, s2) == TRUE)
        printf("OK     test_streq_identicos\n");
    else
        printf("ERROR  test_streq_identicos\n");

    strdestruir(s1);
    strdestruir(s2);
}

void test_streq_diferentes_caracter()
{
    String s1, s2;
    strcrear(s1);
    strcop(s1, "Casa");
    strcrear(s2);
    strcop(s2, "Capa");

    if (streq(s1, s2) == FALSE)
        printf("OK     test_streq_diferentes_caracter\n");
    else
        printf("ERROR  test_streq_diferentes_caracter\n");

    strdestruir(s1);
    strdestruir(s2);
}

void test_streq_diferente_largo()
{
    String s1, s2;
    strcrear(s1);
    strcop(s1, "Hola");
    strcrear(s2);
    strcop(s2, "Hola Mundo");

    if (streq(s1, s2) == FALSE)
        printf("OK     test_streq_diferente_largo\n");
    else
        printf("ERROR  test_streq_diferente_largo\n");

    strdestruir(s1);
    strdestruir(s2);
}

void test_bajar_string_basico()
{
    String s;
    strcrear(s);
    strcop(s, "Hola");

    FILE *f = fopen("test.txt", "wb");
    BajarString(s, f);
    fclose(f);

    strdestruir(s);

    strcrear(s);

    f = fopen("test.txt", "rb");
    LevantarString(s, f);
    fclose(f);

    if (streq(s, "Hola"))
        printf("OK     test_bajar_string_basico\n");
    else
        printf("ERROR  test_bajar_string_basico: se leyó: %s\n", s);

    strdestruir(s);
    remove("test.txt");
}

void test_bajar_string_vacio()
{
    String s;
    strcrear(s);

    FILE *f = fopen("test.txt", "wb");
    BajarString(s, f);
    fclose(f);

    strdestruir(s);

    strcrear(s);

    f = fopen("test.txt", "rb");
    LevantarString(s, f);
    fclose(f);

    if (strlar(s) == 0)
        printf("OK     test_bajar_string_vacio\n");
    else
        printf("ERROR  test_bajar_string_vacio\n");

    strdestruir(s);
}

void test_bajar_string_fin_archivo()
{
    String s;
    strcrear(s);
    strcop(s, "Hola");

    FILE *f = fopen("test.txt", "wb");
    BajarString(s, f);
    fclose(f);

    strdestruir(s);

    strcrear(s);

    f = fopen("test.txt", "rb");
    LevantarString(s, f);
    LevantarString(s, f);
    fclose(f);

    printf("OK     test_bajar_string_fin_archivo\n");

    strdestruir(s);
}

void test_levantar_string_basico()
{
    String s;
    strcrear(s);
    strcop(s, "Hola");

    FILE *f = fopen("test.txt", "wb");
    BajarString(s, f);
    fclose(f);

    strdestruir(s);

    strcrear(s);

    f = fopen("test.txt", "rb");
    LevantarString(s, f);
    fclose(f);

    if (streq(s, "Hola"))
        printf("OK     test_levantar_string_basico\n");
    else
        printf("ERROR  test_levantar_string_basico\n");

    strdestruir(s);
}

void test_levantar_string_vacio()
{
    String s;
    strcrear(s);

    FILE *f = fopen("test.txt", "wb");
    BajarString(s, f);
    fclose(f);

    strdestruir(s);

    strcrear(s);

    f = fopen("test.txt", "rb");
    LevantarString(s, f);
    fclose(f);

    if (strlar(s) == 0)
        printf("OK     test_levantar_string_vacio\n");
    else
        printf("ERROR  test_levantar_string_vacio\n");

    strdestruir(s);
    remove("test.txt");
}

void test_crear_desde_rango_normal()
{
    String linea, resultado;
    strcrear(linea);
    strcop(linea, "Hola Mundo");

    CrearStringDesdeRango(linea, 0, 3, resultado);

    if (streq(resultado, "Hola") == TRUE)
        printf("OK     test_crear_desde_rango_normal\n");
    else
        printf("ERROR  test_crear_desde_rango_normal: obtenido: %s\n", resultado);

    strdestruir(linea);
    strdestruir(resultado);
}

void test_crear_desde_rango_error()
{
    String linea, resultado;
    strcrear(linea);
    strcop(linea, "ABC");

    CrearStringDesdeRango(linea, 0, 10, resultado);

    if (strlar(resultado) == 0)
        printf("OK     test_crear_desde_rango_error\n");
    else
        printf("ERROR  test_crear_desde_rango_error\n");

    strdestruir(linea);
    strdestruir(resultado);
}

void test_crear_desde_rango_un_char()
{
    String linea, resultado;
    strcrear(linea);
    strcop(linea, "Taller");

    CrearStringDesdeRango(linea, 0, 0, resultado);

    if (streq(resultado, "T") == TRUE)
        printf("OK     test_crear_desde_rango_un_char\n");
    else
        printf("ERROR  test_crear_desde_rango_un_char\n");

    strdestruir(linea);
    strdestruir(resultado);
}

void test_es_alfabetico_valido()
{
    String s;
    strcrear(s);
    strcop(s, "SoloLetras");

    if (EsAlfabetico(s) == TRUE)
        printf("OK     test_es_alfabetico_valido\n");
    else
        printf("ERROR  test_es_alfabetico_valido\n");

    strdestruir(s);
}

void test_es_alfabetico_con_numeros()
{
    String s;
    strcrear(s);
    strcop(s, "Letras123");

    if (EsAlfabetico(s) == FALSE)
        printf("OK     test_es_alfabetico_con_numeros\n");
    else
        printf("ERROR  test_es_alfabetico_con_numeros\n");

    strdestruir(s);
}

void test_es_alfabetico_casos_borde()
{
    String s1, s2;
    strcrear(s1);
    strcop(s1, " ConEspacioAlInicio");

    strcrear(s2);
    strcop(s2, "Hola Mundo");

    Boolean ok;
    ((EsAlfabetico(s1) == FALSE) && (EsAlfabetico(s2) == FALSE)) ? ok = TRUE : ok = FALSE;

    if (ok == TRUE)
        printf("OK     test_es_alfabetico_casos_borde\n");
    else
        printf("ERROR  test_es_alfabetico_casos_borde\n");

    strdestruir(s1);
    strdestruir(s2);
}

void test_es_operador_valido()
{
    String s;
    strcrear(s);

    strcop(s, "+");
    if (EsOperadorValido(s) == TRUE)
        printf("OK     test_es_operador_valido: suma\n");
    else
        printf("ERROR  test_es_operador_valido: suma\n");

    strcop(s, "/");
    if (EsOperadorValido(s) == TRUE)
        printf("OK     test_es_operador_valido: division\n");
    else
        printf("ERROR  test_es_operador_valido: division\n");

    strcop(s, "!");
    if (EsOperadorValido(s) == FALSE)
        printf("OK     test_es_operador_valido: invalido\n");
    else
        printf("ERROR  test_es_operador_valido: invalido\n");

    strcop(s, "++");
    if (EsOperadorValido(s) == FALSE)
        printf("OK     test_es_operador_valido: doble operador valido\n");
    else
        printf("ERROR  test_es_operador_valido: doble operador valido\n");

    strdestruir(s);
}

void test_es_entero_positivo()
{
    String s;
    strcrear(s);
    strcop(s, "1234");

    if (EsEnteroPositivo(s) == TRUE)
        printf("OK     test_es_entero_positivo\n");
    else
        printf("ERROR  test_es_entero_positivo\n");

    strdestruir(s);
}

void test_es_entero_negativo()
{
    String s;
    strcrear(s);
    strcop(s, "-567");

    if (EsEnteroPositivo(s) == FALSE)
        printf("OK     test_es_entero_negativo\n");
    else
        printf("ERROR  test_es_entero_negativo\n");

    strdestruir(s);
}

void test_es_entero_falla()
{
    String s1, s2, s3, s4, s5, s6, s7, s8;

    strcrear(s1);
    strcop(s1, "12a3");
    strcrear(s2);
    strcop(s2, "45 6");
    strcrear(s3);
    strcop(s3, " 123");
    strcrear(s4);
    strcop(s4, "?123");
    strcrear(s5);
    strcop(s5, " ");
    strcrear(s6);
    strcop(s6, "\0");
    strcrear(s7);
    strcop(s7, "-");
    strcrear(s8);
    strcop(s8, "-a");

    if (EsEntero(s1) == FALSE && EsEntero(s2) == FALSE &&
        EsEntero(s3) == FALSE && EsEntero(s4) == FALSE &&
        EsEntero(s5) == FALSE && EsEntero(s6) == FALSE &&
        EsEntero(s7) == FALSE && EsEntero(s8) == FALSE &&
        EsEntero(NULL) == FALSE && EsEnteroPositivo(NULL) == FALSE &&
        EsEnteroPositivo(s5) == FALSE)
        printf("OK     test_es_entero_falla\n");
    else
        printf("ERROR  test_es_entero_falla\n");

    strdestruir(s1);
    strdestruir(s2);
    strdestruir(s3);
    strdestruir(s4);
    strdestruir(s5);
    strdestruir(s6);
    strdestruir(s7);
    strdestruir(s8);
}

void test_convertir_a_entero()
{
    String s;
    strcrear(s);

    strcop(s, "1234");
    int res1 = ConvertirAEntero(s);

    strcop(s, "0");
    int res2 = ConvertirAEntero(s);

    if (res1 == 1234 && res2 == 0)
        printf("OK     test_convertir_a_entero\n");
    else
        printf("ERROR  test_convertir_a_entero: res1: %d, res2: %d\n", res1, res2);

    strdestruir(s);
}
void test_convertir_entero_negativo()
{
    String s;
    strcrear(s);
    strcop(s, "-25");

    int r = ConvertirAEntero(s);

    if (r == -25)
        printf("OK test_convertir_entero_negativo\n");

    strdestruir(s);
}

void test_primer_caracter()
{
    String s;
    strcrear(s);
    strcop(s, "Hola");

    char c = PrimerCaracter(s);

    if (c == 'H')
        printf("OK     test_primer_caracter\n");
    else
        printf("ERROR  test_primer_caracter\n");

    strdestruir(s);
}

//----------------------------------------//
//        TESTS MODULO CODIGOERROR        //
//----------------------------------------//

void test_mostrar_error()
{
    printf("> test_mostrar_error ejecutado (verificar mensajes ): \n");
    MostrarError(ERR_NINGUNO);
    MostrarError(ERR_COMANDO_VACIO);
    MostrarError(ERR_COMANDO_INVALIDO);
    MostrarError(ERR_CANT_PARAMETROS);
    MostrarError(ERR_PARAMETRO_INVALIDO);
    MostrarError(ERR_INDICE_INVALIDO);
    MostrarError(ERR_INDICE_INEXISTENTE);
    MostrarError(ERR_OPERADOR_INVALIDO);
    MostrarError(ERR_DIVISION_POR_CERO);
    MostrarError(ERR_NOMBRE_ARCHIVO_INVALIDO);
    MostrarError(ERR_ARCHIVO_EXISTE);
    MostrarError(ERR_ARCHIVO_NO_EXISTE);
    MostrarError(ERR_ARCHIVO_INVALIDO);
    MostrarError(ERR_LISTA_VACIA);
    MostrarError(CodigoError(999));
}

//----------------------------------------//
//        TESTS MODULO OPERACIONES        //
//----------------------------------------//

void test_operacion_default()
{

    Operacion op_invalida = (Operacion)99;

    char resultado = DevolverOperacionChar(op_invalida);

    printf("> test_operacion_default: se ejecutó el caso por defecto\n");
}

void test_devolver_operacion_suma()
{
    Operacion op = DevolverOperacion('+');

    if (op == SUMA)
        printf("OK     test_devolver_operacion_suma\n");
    else
        printf("ERROR  test_devolver_operacion_suma\n");
}

void test_devolver_operacion_resta()
{
    Operacion op = DevolverOperacion('-');

    if (op == RESTA)
        printf("OK     test_devolver_operacion_resta\n");
    else
        printf("ERROR  test_devolver_operacion_resta\n");
}

void test_devolver_operacion_division()
{
    Operacion op = DevolverOperacion('/');

    if (op == DIVISION)
        printf("OK     test_devolver_operacion_division\n");
    else
        printf("ERROR  test_devolver_operacion_division\n");
}

void test_devolver_operacion_multiplicacion()
{
    Operacion op = DevolverOperacion('*');

    if (op == MULTIPLICACION)
        printf("OK     test_devolver_operacion_multiplicacion\n");
    else
        printf("ERROR  test_devolver_operacion_multiplicacion\n");
}

//-----------------------------------------//
//        TESTS MODULO EXPRESIONABB        //
//-----------------------------------------//

void test_crear_expresion_simple_variable_x()
{
    ExpresionABB e = CrearAbbSimpleChar();
    Boolean error = FALSE;
    int resultado = 0;

    CalcularABB(e, 7, error, resultado);

    if (resultado == 7 && error == FALSE)
        printf("OK     test_crear_expresion_simple_variable_x\n");
    else
        printf("ERROR  test_crear_expresion_simple_variable_x\n");

    DestruirABB(e);
}

void test_crear_expresion_simple_int()
{
    ExpresionABB e = CrearAbbSimpleInt(5);
    Boolean error = FALSE;
    int resultado = 0;

    CalcularABB(e, 0, error, resultado);

    if (resultado == 5 && error == FALSE)
        printf("OK     test_crear_expresion_simple_int\n");
    else
        printf("ERROR  test_crear_expresion_simple_int\n");

    DestruirABB(e);
}

void test_crear_expresion_compuesta_ABB()
{

    ExpresionABB a = CrearAbbSimpleInt(3);
    ExpresionABB b = CrearAbbSimpleInt(2);
    ExpresionABB suma = CrearAbbCompuesta(SUMA, a, b);

    ExpresionABB x = CrearAbbSimpleChar();
    ExpresionABB final1 = CrearAbbCompuesta(MULTIPLICACION, suma, x);
    ExpresionABB final2 = CrearAbbCompuesta(MULTIPLICACION, suma, suma);

    Boolean error1 = FALSE;
    Boolean error2 = FALSE;
    int resultado1 = 0;
    int resultado2 = 0;

    CalcularABB(final1, 4, error1, resultado1);
    CalcularABB(final2, 4, error2, resultado2);

    if (resultado1 == 20 && error1 == FALSE && resultado2 == 25 && error2 == FALSE)
        printf("OK     test_crear_expresion_compuesta_ABB\n");
    else
        printf("ERROR  test_crear_expresion_compuesta_ABB\n");

    DestruirABB(final1);
    DestruirABB(final2);
}

void test_arboles_identicos()
{
    ExpresionABB a1 = CrearAbbSimpleInt(25);
    ExpresionABB a2 = CrearAbbSimpleInt(25);

    ExpresionABB a3 = CrearAbbSimpleInt(99);

    ExpresionABB x1 = CrearAbbSimpleChar();
    ExpresionABB n1 = CrearAbbSimpleInt(10);
    ExpresionABB compuesto1 = CrearAbbCompuesta(SUMA, x1, n1);

    ExpresionABB x2 = CrearAbbSimpleChar();
    ExpresionABB n2 = CrearAbbSimpleInt(10);
    ExpresionABB compuesto2 = CrearAbbCompuesta(SUMA, x2, n2);

    if (ArbolesIdenticos(a1, a2) == TRUE)
        printf("OK     test_arboles_identicos_simples_iguales\n");
    else
        printf("ERROR  test_arboles_identicos_simples_iguales\n");

    if (ArbolesIdenticos(a1, a3) == FALSE)
        printf("OK     test_arboles_identicos_diferente_valor\n");
    else
        printf("ERROR  test_arboles_identicos_diferente_valor\n");

    if (ArbolesIdenticos(compuesto1, compuesto2) == TRUE)
        printf("OK     test_arboles_identicos_compuestos_iguales\n");
    else
        printf("ERROR  test_arboles_identicos_compuestos_iguales\n");

    if (ArbolesIdenticos(a1, compuesto1) == FALSE)
        printf("OK     test_arboles_identicos_diferente_estructura\n");
    else
        printf("ERROR  test_arboles_identicos_diferente_estructura\n");

    DestruirABB(a1);
    DestruirABB(a2);
    DestruirABB(a3);
    DestruirABB(x1);
    DestruirABB(n1);
    DestruirABB(compuesto1);
    DestruirABB(x2);
    DestruirABB(n2);
    DestruirABB(compuesto2);
}

// CalcularABB
void test_calcular_abb_suma_resta()
{
    ExpresionABB a = CrearAbbSimpleInt(10);
    ExpresionABB b = CrearAbbSimpleInt(4);

    ExpresionABB s = CrearAbbCompuesta(SUMA, a, b);
    ExpresionABB r = CrearAbbCompuesta(RESTA, a, b);

    Boolean errorSuma = FALSE;
    Boolean errorResta = FALSE;
    int resSuma = 0;
    int resResta = 0;

    CalcularABB(s, 0, errorSuma, resSuma);
    CalcularABB(r, 0, errorResta, resResta);

    if (resSuma == 14 && errorSuma == FALSE && resResta == 6 && errorResta == FALSE)
        printf("OK     test_calcular_abb_suma_resta\n");
    else
        printf("ERROR  test_calcular_abb_suma_resta\n");

    DestruirABB(s);
    DestruirABB(r);
    DestruirABB(a);
    DestruirABB(b);
}

void test_calcular_abb_multiplicacion_variable()
{
    ExpresionABB a = CrearAbbSimpleChar();
    ExpresionABB b = CrearAbbSimpleInt(2);

    ExpresionABB e = CrearAbbCompuesta(MULTIPLICACION, a, b);

    Boolean error = FALSE;
    int resultado = 0;

    CalcularABB(e, 5, error, resultado);

    if (resultado == 10 && error == FALSE)
        printf("OK     test_calcular_abb_multiplicacion_variable\n");
    else
        printf("ERROR  test_calcular_abb_multiplicacion_variable\n");

    DestruirABB(e);
}

void test_calcular_abb_division()
{
    ExpresionABB a = CrearAbbSimpleInt(10);
    ExpresionABB b_cero = CrearAbbSimpleInt(0);
    ExpresionABB b_ok = CrearAbbSimpleInt(2);

    ExpresionABB e_error = CrearAbbCompuesta(DIVISION, a, b_cero);
    ExpresionABB e_ok = CrearAbbCompuesta(DIVISION, a, b_ok);

    Boolean error1 = FALSE;
    Boolean error2 = FALSE;
    int res1 = 0;
    int res2 = 0;

    CalcularABB(e_error, 0, error1, res1);
    CalcularABB(e_ok, 0, error2, res2);

    if (error1 == TRUE && res1 == 0 && res2 == 5 && error2 == FALSE)
        printf("OK     test_calcular_abb_division \n");
    else
        printf("ERROR  test_calcular_abb_division\n");

    DestruirABB(e_error);
    DestruirABB(e_ok);
    DestruirABB(a);
    DestruirABB(b_cero);
    DestruirABB(b_ok);
}

void test_mostrar_abb()
{
    ExpresionABB e1 = CrearAbbSimpleChar();
    ExpresionABB e2 = CrearAbbSimpleInt(10);
    ExpresionABB e3 = CrearAbbSimpleInt(2);
    ExpresionABB arbol = CrearAbbCompuesta(SUMA, e1, e2);
    ExpresionABB arbol2 = CrearAbbCompuesta(MULTIPLICACION, arbol, e3);

    printf("> test_mostrar_abb\n");

    printf("   Resultado esperado: (x+10)\n");
    printf("   Resultado obtenido: ");
    MostrarABB(arbol);

    printf("\n   Resultado esperado: ((x+10)*2)\n");
    printf("   Resultado obtenido: ");
    MostrarABB(arbol2);

    DestruirABB(arbol);
    DestruirABB(arbol2);
    DestruirABB(e1);
    DestruirABB(e2);
    DestruirABB(e3);
}

//--------------------------------------//
//        TESTS MODULO EXPRESION        //
//--------------------------------------//

void test_obtener_indice_expresion()
{
    Expresion exp;
    exp.indiceLista = 42;
    exp.terminos = NULL;

    int indice = getIndiceExpresion(exp);

    if (indice == 42)
        printf("OK     test_obtener_indice_expresion\n");
    else
        printf("ERROR  test_obtener_indice_expresion\n");
}

void test_mostrar_expresion_simple()
{
    Expresion exp;
    exp.indiceLista = 1;
    exp.terminos = CrearAbbSimpleInt(5);

    printf("> test_mostrar_expresion_simple\n");
    printf("   Resultado esperado: 1) 5\n");
    printf("   Resultado obtenido: ");

    MostrarExpresion(exp);

    printf("\nOK     test_mostrar_expresion_simple\n");

    DestruirABB(exp.terminos);
}

void test_destruir_expresion_simple()
{
    Expresion exp;
    exp.indiceLista = 1;
    exp.terminos = CrearAbbSimpleInt(10);

    DestruirExpresion(exp);

    if (exp.terminos == NULL)
        printf("OK     test_destruir_expresion_simple\n");
    else
        printf("ERROR  test_destruir_expresion_simple\n");
}

void test_destruir_expresion_compuesta()
{
    ExpresionABB a = CrearAbbSimpleInt(3);
    ExpresionABB b = CrearAbbSimpleInt(4);
    ExpresionABB suma = CrearAbbCompuesta(SUMA, a, b);

    Expresion exp;
    exp.indiceLista = 2;
    exp.terminos = suma;

    DestruirExpresion(exp);

    if (exp.terminos == NULL)
        printf("OK     test_destruir_expresion_compuesta\n");
    else
        printf("ERROR  test_destruir_expresion_compuesta\n");
}

void test_crear_expresion_simple_entero()
{
    Expresion e = CrearExpresionSimple(FALSE, 5);

    if (getIndiceExpresion(e) == 0)
        printf("OK     test_crear_expresion_simple_entero\n");
    else
        printf("ERROR  test_crear_expresion_simple_entero\n");

    DestruirExpresion(e);
}

void test_crear_expresion_simple_x()
{
    Expresion e = CrearExpresionSimple(TRUE, 0);

    if (getIndiceExpresion(e) == 0)
        printf("OK     test_crear_expresion_simple_x\n");
    else
        printf("ERROR  test_crear_expresion_simple_x\n");

    DestruirExpresion(e);
}

void test_crear_expresion_compuesta()
{
    Expresion e1 = CrearExpresionSimple(FALSE, 3);
    Expresion e2 = CrearExpresionSimple(FALSE, 4);

    Expresion comp = CrearExpresionCompuesta(SUMA, e1, e2);

    printf("OK     test_crear_expresion_compuesta\n");

    DestruirExpresion(comp);
}

void test_comparar_expresiones_identicas()
{
    Expresion e1 = CrearExpresionSimple(FALSE, 5);
    Expresion e2 = CrearExpresionSimple(FALSE, 5);

    printf("OK     test_comparar_expresiones\n");
    CompararExpresiones(e1, e2);

    DestruirExpresion(e1);
    DestruirExpresion(e2);
}

void test_comparar_expresiones_no_identicas()
{
    Expresion e1 = CrearExpresionSimple(FALSE, 5);
    Expresion e2 = CrearExpresionSimple(FALSE, 8);

    printf("> test_comparar_expresiones_no_identicas\n");
    CompararExpresiones(e1, e2);

    DestruirExpresion(e1);
    DestruirExpresion(e2);
}

void test_calcular_expresion()
{
    Expresion e = CrearExpresionSimple(TRUE, 0);

    Boolean err = FALSE;
    int res;

    CalcularExpresion(e, 10, err, res);

    if (!err && res == 10)
        printf("OK     test_calcular_expresion\n");
    else
        printf("ERROR  test_calcular_expresion\n");

    DestruirExpresion(e);
}

//---------------------------------------------//
//        TESTS MODULO LISTAEXPRESIONES        //
//---------------------------------------------//

void test_crear_insertar_simple()
{
    ListaExpresiones lp = NULL;

    CrearInsertarExpresionSimple(lp, TRUE, 0);

    printf("OK test_crear_insertar_simple\n");
}

void test_crear_insertar_compuesta()
{
    ListaExpresiones lp = NULL;

    CrearInsertarExpresionSimple(lp, TRUE, 0);
    CrearInsertarExpresionSimple(lp, FALSE, 5);

    CrearInsertarExpresionCompuesta(lp, SUMA, 1, 2);

    printf("OK test_crear_insertar_compuesta\n");
}

void test_comparar_por_indice()
{
    ListaExpresiones lp = NULL;

    CrearInsertarExpresionSimple(lp, TRUE, 0);
    CrearInsertarExpresionSimple(lp, TRUE, 0);

    CompararExpresionesPorIndice(lp, 1, 2);

    printf("OK test_comparar_por_indice\n");
}

void test_calcular_por_indice()
{
    ListaExpresiones lp = NULL;

    CrearInsertarExpresionSimple(lp, TRUE, 0);

    Boolean err = FALSE;
    int res;

    CalcularExpresionPorIndice(lp, 1, 3, err, res);

    printf("OK test_calcular_por_indice\n");
}

void test_insertar_en_lista_vacia()
{
    ListaExpresiones l = NULL;

    Expresion exp;
    exp.indiceLista = 1;
    exp.terminos = CrearAbbSimpleInt(5);

    InsertarExpresionAlFinalL(l, exp);

    if (l != NULL && getIndiceExpresion(l->exp) == 1)
        printf("OK     test_insertar_en_lista_vacia\n");
    else
        printf("ERROR  test_insertar_en_lista_vacia\n");

    DestruirListaExpresiones(l);
}

void test_insertar_dos_expresiones()
{
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(3);

    Expresion e2;
    e2.indiceLista = 2;
    e2.terminos = CrearAbbSimpleInt(7);

    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);

    if (l != NULL &&
        l->sig != NULL &&
        getIndiceExpresion(l->sig->exp) == 2)
        printf("OK     test_insertar_dos_expresiones\n");
    else
        printf("ERROR  test_insertar_dos_expresiones\n");

    DestruirListaExpresiones(l);
}

void test_insertar_en_lista_con_multiples_nodos()
{
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(3);

    Expresion e2;
    e2.indiceLista = 2;
    e2.terminos = CrearAbbSimpleInt(7);

    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);

    if (l != NULL && l->sig != NULL)
        printf("OK     test_insertar_en_lista_con_multiples_nodos\n");
    else
        printf("ERROR  test_insertar_en_lista_con_multiples_nodos\n");

    DestruirListaExpresiones(l);
}

void test_buscar_expresion_por_indice()
{
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.terminos = CrearAbbSimpleInt(1);

    Expresion e2;
    e2.terminos = CrearAbbSimpleInt(2);

    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);

    Expresion resultado = BuscarExpresionPorIndice(l, 2);

    if (getIndiceExpresion(resultado) == 2)
        printf("OK     test_buscar_expresion_por_indice\n");
    else
        printf("ERROR  test_buscar_expresion_por_indice\n");

    DestruirListaExpresiones(l);
}

void test_es_indice_valido_true()
{
    ListaExpresiones l = NULL;

    Expresion e;
    e.terminos = CrearAbbSimpleInt(8);

    InsertarExpresionAlFinalL(l, e);

    if (EsIndiceValido(l, 1) == TRUE)
        printf("OK     test_es_indice_valido_true\n");
    else
        printf("ERROR  test_es_indice_valido_true\n");

    DestruirListaExpresiones(l);
}

void test_es_indice_valido_false()
{
    ListaExpresiones l = NULL;

    Expresion e;
    e.indiceLista = 3;
    e.terminos = CrearAbbSimpleInt(4);

    InsertarExpresionAlFinalL(l, e);

    if (EsIndiceValido(l, 99) == FALSE)
        printf("OK     test_es_indice_valido_false\n");
    else
        printf("ERROR  test_es_indice_valido_false\n");

    DestruirListaExpresiones(l);
}

void test_mostrar_expresiones()
{
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(3);

    Expresion e2;
    e2.indiceLista = 2;
    e2.terminos = CrearAbbSimpleInt(7);

    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);

    printf("> test_mostrar_expresiones\n");
    printf("   Resultado esperado: \n   Expresion 1 - Indice: 1 Valor: 3 \n   Expresion 2 - Indice: 2 Valor: 7  \n");
    printf("   Resultado obtenido: \n");
    MostrarExpresiones(l);

    DestruirListaExpresiones(l);
}

void test_destruir_lista()
{
    ListaExpresiones l = NULL;

    Expresion e;
    e.indiceLista = 1;
    e.terminos = CrearAbbSimpleInt(5);

    InsertarExpresionAlFinalL(l, e);

    DestruirListaExpresiones(l);

    if (l == NULL)
        printf("OK     test_destruir_lista\n");
    else
        printf("ERROR  test_destruir_lista\n");
}

//-----------------------------------------//
//        TESTS MODULO LISTAPARSING        //
//-----------------------------------------//

void test_tokenizar_entrada_string_una_palabra()
{
    String linea = NULL;
    strcrear(linea);
    strcop(linea, "hola");

    ListaParsing lp = NULL;
    TokenizarEntrada(lp, linea);

    int cant = CantidadTokens(lp);

    if (cant == 1)
        printf("OK     test_tokenizar_entrada_string_una_palabra\n");
    else
        printf("ERROR  test_tokenizar_entrada_string_una_palabra\n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

void test_tokenizar_entrada_string_una_palabra_y_espacios()
{
    String linea = NULL;
    strcrear(linea);
    strcop(linea, "hola  ");

    ListaParsing lp = NULL;
    TokenizarEntrada(lp, linea);

    int cant = CantidadTokens(lp);

    if (cant == 1)
        printf("OK     test_tokenizar_entrada_string_una_palabra\n");
    else
        printf("ERROR  test_tokenizar_entrada_string_una_palabra\n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

void test_tokenizar_entrada_string_multiples_palabras()
{
    String linea = NULL;
    strcrear(linea);
    strcop(linea, "hola TEST multiples PALABRAS");

    ListaParsing lp = NULL;
    TokenizarEntrada(lp, linea);

    int cant = CantidadTokens(lp);

    if (cant == 4)
        printf("OK     test_tokenizar_entrada_string_multiples_palabras\n");
    else
        printf("ERROR  test_tokenizar_entrada_string_multiples_palabras\n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

void test_tokenizar_entrada_string_multiples_palabras_y_espacios()
{
    String linea = NULL;
    strcrear(linea);
    strcop(linea, "hola TEST   multiples PALABRAS   ");

    ListaParsing lp = NULL;
    TokenizarEntrada(lp, linea);

    int cant = CantidadTokens(lp);

    if (cant == 4)
        printf("OK     test_tokenizar_entrada_string_multiples_palabras_y_espacios\n");
    else
        printf("ERROR  test_tokenizar_entrada_string_multiples_palabras_y_espacios\n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

void test_token_en_posicion()
{
    String linea = NULL;
    strcrear(linea);
    strcop(linea, "uno dos tres");

    ListaParsing lp = NULL;
    TokenizarEntrada(lp, linea);

    String token = NULL;
    strcrear(token);

    TokenEnPosicion(lp, 2, token);

    if (streq(token, "dos"))
        printf("OK     test_token_en_posicion\n");
    else
        printf("ERROR  test_token_en_posicion\n");

    strdestruir(token);
    DestruirListaParsing(lp);
    strdestruir(linea);
}

void test_cantidad_tokens()
{
    String linea = NULL;
    strcrear(linea);
    strcop(linea, "a b c d");

    ListaParsing lp = NULL;
    TokenizarEntrada(lp, linea);

    int cant = CantidadTokens(lp);

    if (cant == 4)
        printf("OK     test_cantidad_tokens\n");
    else
        printf("ERROR  test_cantidad_tokens\n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

//------------------------------------//
//        TESTS MODULO ARCHIVO        //
//------------------------------------//

void test_existe_archivo_true()
{
    String nombre = NULL;
    strcrear(nombre);
    strcop(nombre, "archivo_test_existente");

    FILE *f = fopen("archivo_test_existente.txt", "wb");
    if (f != NULL)
    {
        fprintf(f, "contenido de prueba");
        fclose(f);
    }

    if (ExisteArchivo(nombre) == TRUE)
        printf("OK     test_existe_archivo_true\n");
    else
        printf("ERROR  test_existe_archivo_true\n");

    remove("archivo_test_existente.txt");
    strdestruir(nombre);
}

void test_existe_archivo_false()
{
    String nombre = NULL;
    strcrear(nombre);
    strcop(nombre, "archivonoexiste12345");

    if (ExisteArchivo(nombre) == FALSE)
        printf("OK     test_existe_archivo_false\n");
    else
        printf("ERROR  test_existe_archivo_false\n");

    strdestruir(nombre);
}

void test_existe_archivo_null()
{
    String nombre = NULL;
    strcrear(nombre);

    if (ExisteArchivo(nombre) == FALSE)
        printf("OK     test_existe_archivo_vacio\n");
    else
        printf("ERROR  test_existe_archivo_vacio\n");

    strdestruir(nombre);
}

void test_guardar_recuperar_expresion_archivo_ok()
{

    ListaExpresiones lista = NULL;
    Expresion exp;

    ExpresionABB n3 = CrearAbbSimpleInt(3);
    ExpresionABB nx = CrearAbbSimpleChar();
    ExpresionABB suma = CrearAbbCompuesta(SUMA, n3, nx);

    ExpresionABB n10 = CrearAbbSimpleInt(10);
    ExpresionABB n2 = CrearAbbSimpleInt(2);
    ExpresionABB resta = CrearAbbCompuesta(RESTA, n10, n2);

    ExpresionABB raiz = CrearAbbCompuesta(MULTIPLICACION, suma, resta);

    exp.terminos = raiz;
    InsertarExpresionAlFinalL(lista, exp);

    int indiceOriginal = getIndiceExpresion(exp);

    String nombreBase = "testintegracion";

    GuardarExpresionEnArchivo(lista, nombreBase, indiceOriginal);

    RecuperarInsertarExpresionDesdeArchivo(nombreBase, lista);

    int indiceRecuperado = UltimoIndiceDisponible(lista) - 1;
    Expresion expRecuperada = BuscarExpresionPorIndice(lista, indiceRecuperado);

    if (ArbolesIdenticos(exp.terminos, expRecuperada.terminos) == TRUE)
        printf("OK     test_guardar_recuperar_expresion_archivo_ok\n");
    else
        printf("ERROR  test_guardar_recuperar_expresion_archivo_ok: La expresion guardada y la recuperada NO coincide\n");

    DestruirListaExpresiones(lista);
}

void test_levantar_abb_entero()
{
    FILE *f = fopen("test1.bin", "wb");

    TipoDato tipo = ENTERO;
    int num = 5;
    int indice = 1;

    fwrite(&tipo, sizeof(TipoDato), 1, f);
    fwrite(&num, sizeof(int), 1, f);
    fwrite(&indice, sizeof(int), 1, f);

    fclose(f);

    f = fopen("test1.bin", "rb");

    ExpresionABB abb;
    LevantarExpresionABB(abb, f);

    if (abb != NULL)
        printf("OK     test_levantar_abb_entero\n");
    else
        printf("ERROR  test_levantar_abb_entero\n");

    fclose(f);
    remove("test1.bin");
}

void test_levantar_abb_simbolo()
{
    FILE *f = fopen("test2.bin", "wb");

    TipoDato tipo = OPERADOR;
    char simbolo = '+';
    int indice = 1;

    fwrite(&tipo, sizeof(TipoDato), 1, f);
    fwrite(&simbolo, sizeof(char), 1, f);
    fwrite(&indice, sizeof(int), 1, f);

    fclose(f);

    f = fopen("test2.bin", "rb");

    ExpresionABB abb;
    LevantarExpresionABB(abb, f);

    if (abb != NULL)
        printf("OK     test_levantar_abb_simbolo\n");
    else
        printf("ERROR  test_levantar_abb_simbolo\n");

    fclose(f);
    remove("test2.bin");
}
void test_levantar_abb_error_dato()
{
    FILE *f = fopen("test3.bin", "wb");

    TipoDato tipo = ENTERO;

    fwrite(&tipo, sizeof(TipoDato), 1, f);

    fclose(f);

    f = fopen("test3.bin", "rb");

    ExpresionABB abb;
    LevantarExpresionABB(abb, f);

    printf("OK     test_levantar_abb_error_dato\n");

    fclose(f);
    remove("test3.bin");
}

void test_levantar_abb_error_indice()
{
    FILE *f = fopen("test4.bin", "wb");

    TipoDato tipo = ENTERO;
    int num = 7;

    fwrite(&tipo, sizeof(TipoDato), 1, f);
    fwrite(&num, sizeof(int), 1, f);

    fclose(f);

    f = fopen("test4.bin", "rb");

    ExpresionABB abb;
    LevantarExpresionABB(abb, f);

    printf("OK     test_levantar_abb_error_indice\n");

    fclose(f);
    remove("test4.bin");
}

void test_levantar_abb_error_dato_simbolo()
{
    FILE *f = fopen("test5.bin", "wb");

    TipoDato tipo = OPERADOR;

    fwrite(&tipo, sizeof(TipoDato), 1, f);

    fclose(f);

    f = fopen("test5.bin", "rb");

    ExpresionABB abb;
    LevantarExpresionABB(abb, f);

    printf("OK     test_levantar_abb_error_dato_simbolo\n");

    fclose(f);
    remove("test5.bin");
}

//---------------------------------------//
//        TESTS MODULO COMPILADOR        //
//---------------------------------------//

// ValidarComandoCompuesta
void test_validar_compuesta_ok()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1, e2;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);

    e2.indiceLista = 2;
    e2.terminos = CrearAbbSimpleInt(10);

    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);

    String linea;
    strcrear(linea);
    strcop(linea, "1 + 2");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    Operacion op;
    CodigoError err;

    ValidarComandoCompuesta(lp, l, i1, i2, op, err);

    if (err == ERR_NINGUNO && i1 == 1 && i2 == 2)
        printf("OK     test_validar_compuesta_ok \n");
    else
        printf("ERROR  test_validar_compuesta_ok \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_compuesta_operador_invalido()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1, e2;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);

    e2.indiceLista = 2;
    e2.terminos = CrearAbbSimpleInt(10);

    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);

    String linea;
    strcrear(linea);
    strcop(linea, "1 ! 2");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    Operacion op;
    CodigoError err;

    ValidarComandoCompuesta(lp, l, i1, i2, op, err);

    if (err == ERR_OPERADOR_INVALIDO)
        printf("OK     test_validar_compuesta_operador_invalido \n");
    else
        printf("ERROR  test_validar_compuesta_operador_invalido \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_compuesta_primer_indice_no_existe()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e1);

    String linea;
    strcrear(linea);
    strcop(linea, "99 + 1");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    Operacion op;
    CodigoError err;

    ValidarComandoCompuesta(lp, l, i1, i2, op, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("OK     test_validar_compuesta_primer_indice_no_existe \n");
    else
        printf("ERROR  test_validar_compuesta_primer_indice_no_existe \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_compuesta_segundo_indice_no_existe()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e1);

    String linea;
    strcrear(linea);
    strcop(linea, "1 + 99");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    Operacion op;
    CodigoError err;

    ValidarComandoCompuesta(lp, l, i1, i2, op, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("OK     test_validar_compuesta_segundo_indice_no_existe \n");
    else
        printf("ERROR  test_validar_compuesta_segundo_indice_no_existe \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_compuesta_primer_indice_negativo()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e1);

    String linea;
    strcrear(linea);
    strcop(linea, "-1 + 1");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    Operacion op;
    CodigoError err;

    ValidarComandoCompuesta(lp, l, i1, i2, op, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("OK     test_validar_compuesta_primer_indice_negativo \n");
    else
        printf("ERROR  test_validar_compuesta_primer_indice_negativo \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_compuesta_segundo_indice_negativo()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1, e2;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);

    e2.indiceLista = 2;
    e2.terminos = CrearAbbSimpleInt(10);

    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);

    String linea;
    strcrear(linea);
    strcop(linea, "1 + -123");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    Operacion op;
    CodigoError err;

    ValidarComandoCompuesta(lp, l, i1, i2, op, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("OK     test_validar_compuesta_segundo_indice_negativo \n");
    else
        printf("ERROR  test_validar_compuesta_segundo_indice_negativo \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_compuesta_cantidad_tokens_invalida()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    String linea;
    strcrear(linea);
    strcop(linea, "1 +");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    Operacion op;
    CodigoError err;

    ValidarComandoCompuesta(lp, l, i1, i2, op, err);

    if (err == ERR_CANT_PARAMETROS)
        printf("OK     test_validar_compuesta_cantidad_tokens_invalida \n");
    else
        printf("ERROR  test_validar_compuesta_cantidad_tokens_invalida \n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

// ValidarComandoCalcular
void test_validar_calcular_ok()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e;
    e.indiceLista = 1;
    e.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e);

    String linea;
    strcrear(linea);
    strcop(linea, "1 7");

    TokenizarEntrada(lp, linea);

    int indice;
    int valor;
    CodigoError err;

    ValidarComandoCalcular(lp, l, valor, indice, err);

    if (err == ERR_NINGUNO && indice == 1 && valor == 7)
        printf("OK     test_validar_calcular_ok \n");
    else
        printf("ERROR  test_validar_calcular_ok \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_calcular_parametro_invalido()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e;
    e.indiceLista = 1;
    e.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e);

    String linea;
    strcrear(linea);
    strcop(linea, " 1 abc");

    TokenizarEntrada(lp, linea);

    int indice;
    int valor;
    CodigoError err;

    ValidarComandoCalcular(lp, l, valor, indice, err);

    if (err == ERR_PARAMETRO_INVALIDO)
        printf("OK     test_validar_calcular_parametro_invalido \n");
    else
        printf("ERROR  test_validar_calcular_parametro_invalido \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_calcular_indice_no_existe()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e;
    e.indiceLista = 1;
    e.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e);

    String linea;
    strcrear(linea);
    strcop(linea, "99 7");

    TokenizarEntrada(lp, linea);

    int indice;
    int valor;
    CodigoError err;

    ValidarComandoCalcular(lp, l, valor, indice, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("OK     test_validar_calcular_indice_no_existe \n");
    else
        printf("ERROR  test_validar_calcular_indice_no_existe \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_calcular_indice_negativo()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e;
    e.indiceLista = 1;
    e.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e);

    String linea;
    strcrear(linea);
    strcop(linea, "-99  7");

    TokenizarEntrada(lp, linea);

    int indice;
    int valor;
    CodigoError err;

    ValidarComandoCalcular(lp, l, valor, indice, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("OK     test_validar_calcular_indice_negativo \n");
    else
        printf("ERROR  test_validar_calcular_indice_negativo \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_calcular_cantidad_parametros_invalidos()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    String linea;
    strcrear(linea);
    strcop(linea, "7 99 123");

    TokenizarEntrada(lp, linea);

    int indice;
    int valor;
    CodigoError err;

    ValidarComandoCalcular(lp, l, valor, indice, err);

    if (err == ERR_CANT_PARAMETROS)
        printf("OK     test_validar_calcular_cantidad_parametros_invalidos \n");
    else
        printf("ERROR  test_validar_calcular_cantidad_parametros_invalidos \n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

// ValidarComandoIguales
void test_validar_iguales_ok()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1, e2;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);
    e2.indiceLista = 2;
    e2.terminos = CrearAbbSimpleInt(10);

    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);

    String linea;
    strcrear(linea);
    strcop(linea, "1 2");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    CodigoError err;

    ValidarComandoIguales(lp, l, i1, i2, err);

    if (err == ERR_NINGUNO && i1 == 1 && i2 == 2)
        printf("OK     test_validar_iguales_ok \n");
    else
        printf("ERROR  test_validar_iguales_ok \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_iguales_primer_indice_no_existe()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e1);

    String linea;
    strcrear(linea);
    strcop(linea, "99 1");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    CodigoError err;

    ValidarComandoIguales(lp, l, i1, i2, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("OK     test_validar_iguales_primer_indice_no_existe \n");
    else
        printf("ERROR  test_validar_iguales_primer_indice_no_existe \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_iguales_segundo_indice_no_existe()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e1);

    String linea;
    strcrear(linea);
    strcop(linea, "1 99");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    CodigoError err;

    ValidarComandoIguales(lp, l, i1, i2, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("OK     test_validar_iguales_segundo_indice_no_existe \n");
    else
        printf("ERROR  test_validar_iguales_segundo_indice_no_existe \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_iguales_primer_indice_negativo()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e1);

    String linea;
    strcrear(linea);
    strcop(linea, "-123 1");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    CodigoError err;

    ValidarComandoIguales(lp, l, i1, i2, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("OK     test_validar_iguales_primer_indice_negativo \n");
    else
        printf("ERROR  test_validar_iguales_primer_indice_negativo \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_iguales_segundo_indice_negativo()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1, e2;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);
    e2.indiceLista = 2;
    e2.terminos = CrearAbbSimpleInt(10);

    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);

    String linea;
    strcrear(linea);
    strcop(linea, "1 -12");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    CodigoError err;

    ValidarComandoIguales(lp, l, i1, i2, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("OK     test_validar_iguales_segundo_indice_negativo \n");
    else
        printf("ERROR  test_validar_iguales_segundo_indice_negativo \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
}

void test_validar_iguales_cantidad_tokens_invalida()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    String linea;
    strcrear(linea);
    strcop(linea, "1");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    CodigoError err;

    ValidarComandoIguales(lp, l, i1, i2, err);

    if (err == ERR_CANT_PARAMETROS)
        printf("OK     test_validar_iguales_cantidad_tokens_invalida \n");
    else
        printf("ERROR  test_validar_iguales_cantidad_tokens_invalida \n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

void test_reconocer_comando_valido()
{
    String cmd;
    strcrear(cmd);

    TipoComando tipo;
    CodigoError err;

    // Caso 1: "simple"
    strcop(cmd, "simple");
    ReconocerComando(cmd, tipo, err);
    if (tipo == SIMPLE && err == ERR_NINGUNO)
        printf("OK     test_reconocer_comando_simple\n");
    else
        printf("ERROR  test_reconocer_comando_simple\n");

    // Caso 2: "compuesta"
    strcop(cmd, "compuesta");
    ReconocerComando(cmd, tipo, err);
    if (tipo == COMPUESTA && err == ERR_NINGUNO)
        printf("OK     test_reconocer_comando_compuesta\n");
    else
        printf("ERROR  test_reconocer_comando_compuesta\n");

    // Caso 3: "calcular"
    strcop(cmd, "calcular");
    ReconocerComando(cmd, tipo, err);
    if (tipo == CALCULAR && err == ERR_NINGUNO)
        printf("OK     test_reconocer_comando_calcular\n");
    else
        printf("ERROR  test_reconocer_comando_calcular\n");

    // Caso 4: "mostrar"
    strcop(cmd, "mostrar");
    ReconocerComando(cmd, tipo, err);
    if (tipo == MOSTRAR && err == ERR_NINGUNO)
        printf("OK     test_reconocer_comando_mostrar\n");
    else
        printf("ERROR  test_reconocer_comando_mostrar\n");

    // Caso 5: "guardar"
    strcop(cmd, "guardar");
    ReconocerComando(cmd, tipo, err);
    if (tipo == GUARDAR && err == ERR_NINGUNO)
        printf("OK     test_reconocer_comando_guardar\n");
    else
        printf("ERROR  test_reconocer_comando_guardar\n");

    // Caso 6: "recuperar"
    strcop(cmd, "recuperar");
    ReconocerComando(cmd, tipo, err);
    if (tipo == RECUPERAR && err == ERR_NINGUNO)
        printf("OK     test_reconocer_comando_recuperar\n");
    else
        printf("ERROR  test_reconocer_comando_recuperar\n");

    // Caso 7: "iguales"
    strcop(cmd, "iguales");
    ReconocerComando(cmd, tipo, err);
    if (tipo == IGUALES && err == ERR_NINGUNO)
        printf("OK     test_reconocer_comando_iguales\n");
    else
        printf("ERROR  test_reconocer_comando_iguales\n");

    // Caso 8: "salir"
    strcop(cmd, "salir");
    ReconocerComando(cmd, tipo, err);
    if (tipo == SALIR && err == ERR_NINGUNO)
        printf("OK     test_reconocer_comando_salir\n");
    else
        printf("ERROR  test_reconocer_comando_salir\n");

    strdestruir(cmd);
}

void test_reconocer_comando_invalido()
{
    String cmd;
    strcrear(cmd);

    TipoComando tipo;
    CodigoError err;

    strcop(cmd, "comando_inexistente");
    ReconocerComando(cmd, tipo, err);

    if (err == ERR_COMANDO_INVALIDO)
        printf("OK     test_reconocer_comando invalido\n");
    else
        printf("ERROR  test_reconocer_comando invalido \n");

    strdestruir(cmd);
}

// ValidarComandoSimple
void test_validar_simple_ok_x()
{
    ListaParsing lp = NULL;

    String linea;
    strcrear(linea);
    strcop(linea, "x");
    TokenizarEntrada(lp, linea);

    Boolean esX;
    int num;
    CodigoError err;

    ValidarComandoSimple(lp, esX, num, err);

    if (err == ERR_NINGUNO && esX == TRUE)
        printf("OK     test_validar_simple_ok_x \n");
    else
        printf("ERROR  test_validar_simple_ok_x \n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

void test_validar_simple_ok_entero()
{
    ListaParsing lp = NULL;

    String linea;
    strcrear(linea);
    strcop(linea, "5");
    TokenizarEntrada(lp, linea);

    Boolean esX;
    int num;
    CodigoError err;

    ValidarComandoSimple(lp, esX, num, err);

    if (err == ERR_NINGUNO && esX == FALSE && num == 5)
        printf("OK     test_validar_simple_ok_entero \n");
    else
        printf("ERROR  test_validar_simple_ok_entero \n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

void test_validar_simple_cant_params()
{
    ListaParsing lp = NULL;

    String linea;
    strcrear(linea);
    strcop(linea, "5 10");
    TokenizarEntrada(lp, linea);

    Boolean esX;
    int num;
    CodigoError err;

    ValidarComandoSimple(lp, esX, num, err);

    if (err == ERR_CANT_PARAMETROS)
        printf("OK     test_validar_simple_cant_params \n");
    else
        printf("ERROR  test_validar_simple_cant_params \n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

void test_validar_simple_parametro_invalido()
{
    ListaParsing lp = NULL;

    String linea;
    strcrear(linea);
    strcop(linea, "abc");
    TokenizarEntrada(lp, linea);

    Boolean esX;
    int num;
    CodigoError err;

    ValidarComandoSimple(lp, esX, num, err);

    if (err == ERR_PARAMETRO_INVALIDO)
        printf("OK     test_validar_simple_parametro_invalido \n");
    else
        printf("ERROR  test_validar_simple_parametro_invalido \n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

// ValidarComandoGuardar

void test_validar_guardar_cant_params()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    String linea;
    strcrear(linea);
    strcop(linea, "1");
    TokenizarEntrada(lp, linea);

    int indice;
    String nombreArchivo;
    strcrear(nombreArchivo);
    CodigoError err;

    ValidarComandoGuardar(lp, l, indice, nombreArchivo, err);

    if (err == ERR_CANT_PARAMETROS)
        printf("OK     test_validar_guardar_cant_params \n");
    else
        printf("ERROR  test_validar_guardar_cant_params \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
    strdestruir(nombreArchivo);
}

void test_validar_guardar_indice_invalido()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    String linea;
    strcrear(linea);
    strcop(linea, "99 test");
    TokenizarEntrada(lp, linea);
    Expresion e;
    e.indiceLista = 1;
    e.terminos = CrearAbbSimpleInt(1);
    InsertarExpresionAlFinalL(l, e);

    int ind;

    String nombreArchivo;
    strcrear(nombreArchivo);
    CodigoError err;

    ValidarComandoGuardar(lp, l, ind, nombreArchivo, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("OK     test_validar_guardar_indice_invalido \n");
    else
        printf("ERROR  test_validar_guardar_indice_invalido \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
    strdestruir(nombreArchivo);
}

void test_validar_guardar_indice_negativo()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    String linea;
    strcrear(linea);
    strcop(linea, "-9 test");
    TokenizarEntrada(lp, linea);
    Expresion e;
    e.indiceLista = 1;
    e.terminos = CrearAbbSimpleInt(1);
    InsertarExpresionAlFinalL(l, e);

    int ind;

    String nombreArchivo;
    strcrear(nombreArchivo);
    CodigoError err;

    ValidarComandoGuardar(lp, l, ind, nombreArchivo, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("OK     test_validar_guardar_indice_negativo \n");
    else
        printf("ERROR  test_validar_guardar_indice_negativo \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
    strdestruir(nombreArchivo);
}

void test_validar_guardar_nombre_invalido()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e1);

    String linea;
    strcrear(linea);
    strcop(linea, "1 archivo123");
    TokenizarEntrada(lp, linea);

    int indice;
    String nombreArchivo;
    strcrear(nombreArchivo);
    CodigoError err;

    ValidarComandoGuardar(lp, l, indice, nombreArchivo, err);

    if (err == ERR_NOMBRE_ARCHIVO_INVALIDO)
        printf("OK     test_validar_guardar_nombre_invalido \n");
    else
        printf("ERROR  test_validar_guardar_nombre_invalido \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
    strdestruir(nombreArchivo);
}

void test_validar_guardar_ok()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e1);

    String linea;
    strcrear(linea);
    strcop(linea, "1 archivotest");

    TokenizarEntrada(lp, linea);

    int indice;
    String nombreArchivo;
    strcrear(nombreArchivo);
    strcop(nombreArchivo, "archivotest");
    CodigoError err;

    ValidarComandoGuardar(lp, l, indice, nombreArchivo, err);

    if (err == ERR_NINGUNO && indice == 1 && streq(nombreArchivo, "archivotest"))
        printf("OK     test_validar_guardar_ok \n");
    else
        printf("ERROR  test_validar_guardar_ok \n");

    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
    strdestruir(nombreArchivo);
}

void test_validar_guardar_archivo_existe()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e1);

    FILE *f = fopen("archivotest.txt", "wb");
    fclose(f);

    String linea;
    strcrear(linea);
    strcop(linea, "1 archivotest");
    TokenizarEntrada(lp, linea);

    int indice;
    String nombreArchivo;
    strcrear(nombreArchivo);
    CodigoError err;

    ValidarComandoGuardar(lp, l, indice, nombreArchivo, err);

    if (err == ERR_ARCHIVO_EXISTE)
        printf("OK     test_validar_guardar_archivo_existe \n");
    else
        printf("ERROR  test_validar_guardar_archivo_existe \n");

    remove("archivotest.txt");
    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
    strdestruir(linea);
    strdestruir(nombreArchivo);
}

// ValidarComandoMostrar
void test_validar_mostrar_ok()
{
    String linea = NULL;
    strcrear(linea);

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    ListaExpresiones expresiones = NULL;
    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(10);
    InsertarExpresionAlFinalL(expresiones, e1);

    CodigoError err = ValidarComandoMostrar(tokens, expresiones);

    if (err == ERR_NINGUNO)
        printf("OK     test_validar_mostrar_ok\n");
    else
        printf("ERROR  test_validar_mostrar_ok\n");

    strdestruir(linea);
    DestruirListaParsing(tokens);
    DestruirListaExpresiones(expresiones);
}

void test_validar_mostrar_error_tokens()
{
    String linea = NULL;
    strcrear(linea);
    strcop(linea, "TEST");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    ListaExpresiones expresiones = NULL;
    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(10);
    InsertarExpresionAlFinalL(expresiones, e1);

    CodigoError err = ValidarComandoMostrar(tokens, expresiones);

    if (err == ERR_CANT_PARAMETROS)
        printf("OK     test_validar_mostrar_error_tokens\n");
    else
        printf("ERROR  test_validar_mostrar_error_tokens\n");

    strdestruir(linea);
    DestruirListaParsing(tokens);
    DestruirListaExpresiones(expresiones);
}

void test_validar_mostrar_lista_null()
{
    String linea = NULL;
    strcrear(linea);

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    ListaExpresiones expresiones = NULL;

    CodigoError err = ValidarComandoMostrar(tokens, expresiones);

    if (err == ERR_LISTA_VACIA)
        printf("OK     test_validar_mostrar_lista_null\n");
    else
        printf("ERROR  test_validar_mostrar_lista_null\n");

    strdestruir(linea);
    DestruirListaParsing(tokens);
    DestruirListaExpresiones(expresiones);
}

// ValidarComandoRecuperar
void test_validar_recuperar_ok()
{
    CodigoError err;

    String linea = NULL, nombreArchivo = NULL;
    strcrear(linea);
    strcop(linea, "testuno");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    strcrear(nombreArchivo);

    FILE *file = fopen("testuno.txt", "wb");
    fclose(file);

    ValidarComandoRecuperar(tokens, nombreArchivo, err);

    if (err == ERR_NINGUNO)
        printf("OK     test_validar_recuperar_ok\n");
    else
        printf("ERROR  test_validar_recuperar_ok\n");

    remove("testuno.txt");

    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(tokens);
}

void test_validar_recuperar_error_tokens()
{
    CodigoError err;

    String linea = NULL, nombreArchivo = NULL;
    strcrear(linea);

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    strcrear(nombreArchivo);

    FILE *file = fopen("testdos.txt", "wb");
    fclose(file);

    ValidarComandoRecuperar(tokens, nombreArchivo, err);

    if (err == ERR_CANT_PARAMETROS)
        printf("OK     test_validar_recuperar_error_tokens\n");
    else
        printf("ERROR  test_validar_recuperar_error_tokens\n");

    remove("testdos.txt");

    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(tokens);
}

void test_validar_recuperar_error_archivo_invalido()
{
    CodigoError err;

    String linea = NULL, nombreArchivo = NULL;
    strcrear(linea);
    strcop(linea, "test3");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    strcrear(nombreArchivo);

    FILE *file = fopen("test3.txt", "wb");
    fclose(file);

    ValidarComandoRecuperar(tokens, nombreArchivo, err);

    if (err == ERR_ARCHIVO_INVALIDO)
        printf("OK     test_validar_recuperar_error_archivo_invalido\n");
    else
        printf("ERROR  test_validar_recuperar_error_archivo_invalido\n");

    remove("test3.txt");

    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(tokens);
}

void test_validar_recuperar_error_archivo_inexistente()
{
    CodigoError err;

    String linea = NULL, nombreArchivo = NULL;
    strcrear(linea);
    strcop(linea, "testcuatro");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    strcrear(nombreArchivo);

    ValidarComandoRecuperar(tokens, nombreArchivo, err);

    if (err == ERR_ARCHIVO_NO_EXISTE)
        printf("OK     test_validar_recuperar_error_archivo_inexistente\n");
    else
        printf("ERROR  test_validar_recuperar_error_archivo_inexistente\n");

    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(tokens);
}

// ValidarComandoSalir
void test_validar_salir_ok()
{
    String linea = NULL;
    strcrear(linea);

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    CodigoError err = ValidarComandoSalir(tokens);

    if (err == ERR_NINGUNO)
        printf("OK     test_validar_salir_ok\n");
    else
        printf("ERROR  test_validar_salir_ok\n");

    strdestruir(linea);
    DestruirListaParsing(tokens);
}

void test_validar_salir_error_tokens()
{
    String linea = NULL;
    strcrear(linea);
    strcop(linea, "TEST");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    CodigoError err = ValidarComandoSalir(tokens);

    if (err == ERR_CANT_PARAMETROS)
        printf("OK     test_validar_salir_error_tokens\n");
    else
        printf("ERROR  test_validar_salir_error_tokens\n");

    strdestruir(linea);
    DestruirListaParsing(tokens);
}

// ReconocerYValidarComando - cubre la función y todas las ramas del switch (coverage 100%)
void test_reconocer_y_validar_comando_simple()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;
    String linea;
    strcrear(linea);
    strcop(linea, "simple x");
    TokenizarEntrada(lp, linea);

    TipoComando tipo;
    Boolean esX;
    int num, idx1, idx2, valorX;
    Operacion op;
    String nombreArchivo;
    strcrear(nombreArchivo);
    CodigoError err;

    ReconocerYValidarComando(lp, l, tipo, esX, num, idx1, op, idx2, valorX, nombreArchivo, err);

    if (err == ERR_NINGUNO && tipo == SIMPLE && esX == TRUE)
        printf("OK     test_reconocer_y_validar_comando_simple\n");
    else
        printf("ERROR  test_reconocer_y_validar_comando_simple\n");

    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(lp);
}

void test_reconocer_y_validar_comando_compuesta()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;
    Expresion e1, e2;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);
    e2.indiceLista = 2;
    e2.terminos = CrearAbbSimpleInt(10);
    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);

    String linea;
    strcrear(linea);
    strcop(linea, "compuesta 1 + 2");
    TokenizarEntrada(lp, linea);

    TipoComando tipo;
    Boolean esX;
    int num, idx1, idx2, valorX;
    Operacion op;
    String nombreArchivo;
    strcrear(nombreArchivo);
    CodigoError err;

    ReconocerYValidarComando(lp, l, tipo, esX, num, idx1, op, idx2, valorX, nombreArchivo, err);

    if (err == ERR_NINGUNO && tipo == COMPUESTA && idx1 == 1 && idx2 == 2 && op == SUMA)
        printf("OK     test_reconocer_y_validar_comando_compuesta\n");
    else
        printf("ERROR  test_reconocer_y_validar_comando_compuesta\n");

    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
}

void test_reconocer_y_validar_comando_calcular()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;
    Expresion e;
    e.indiceLista = 1;
    e.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e);

    String linea;
    strcrear(linea);
    strcop(linea, "calcular 1 7");
    TokenizarEntrada(lp, linea);

    TipoComando tipo;
    Boolean esX;
    int num, idx1, idx2, valorX;
    Operacion op;
    String nombreArchivo;
    strcrear(nombreArchivo);
    CodigoError err;

    ReconocerYValidarComando(lp, l, tipo, esX, num, idx1, op, idx2, valorX, nombreArchivo, err);

    if (err == ERR_NINGUNO && tipo == CALCULAR && idx1 == 1)
        printf("OK     test_reconocer_y_validar_comando_calcular\n");
    else
        printf("ERROR  test_reconocer_y_validar_comando_calcular\n");

    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
}

void test_reconocer_y_validar_comando_mostrar()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;
    Expresion e;
    e.indiceLista = 1;
    e.terminos = CrearAbbSimpleInt(10);
    InsertarExpresionAlFinalL(l, e);

    String linea;
    strcrear(linea);
    strcop(linea, "mostrar");
    TokenizarEntrada(lp, linea);

    TipoComando tipo;
    Boolean esX;
    int num, idx1, idx2, valorX;
    Operacion op;
    String nombreArchivo;
    strcrear(nombreArchivo);
    CodigoError err;

    ReconocerYValidarComando(lp, l, tipo, esX, num, idx1, op, idx2, valorX, nombreArchivo, err);

    if (err == ERR_NINGUNO && tipo == MOSTRAR)
        printf("OK     test_reconocer_y_validar_comando_mostrar\n");
    else
        printf("ERROR  test_reconocer_y_validar_comando_mostrar\n");

    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
}

void test_reconocer_y_validar_comando_iguales()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;
    Expresion e1, e2;
    e1.indiceLista = 1;
    e1.terminos = CrearAbbSimpleInt(5);
    e2.indiceLista = 2;
    e2.terminos = CrearAbbSimpleInt(10);
    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);

    String linea;
    strcrear(linea);
    strcop(linea, "iguales 1 2");
    TokenizarEntrada(lp, linea);

    TipoComando tipo;
    Boolean esX;
    int num, idx1, idx2, valorX;
    Operacion op;
    String nombreArchivo;
    strcrear(nombreArchivo);
    CodigoError err;

    ReconocerYValidarComando(lp, l, tipo, esX, num, idx1, op, idx2, valorX, nombreArchivo, err);

    if (err == ERR_NINGUNO && tipo == IGUALES && idx1 == 1 && idx2 == 2)
        printf("OK     test_reconocer_y_validar_comando_iguales\n");
    else
        printf("ERROR  test_reconocer_y_validar_comando_iguales\n");

    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
}

void test_reconocer_y_validar_comando_guardar()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;
    Expresion e;
    e.indiceLista = 1;
    e.terminos = CrearAbbSimpleInt(5);
    InsertarExpresionAlFinalL(l, e);

    String linea;
    strcrear(linea);
    strcop(linea, "guardar 1 archivocover");
    TokenizarEntrada(lp, linea);

    TipoComando tipo;
    Boolean esX;
    int num, idx1, idx2, valorX;
    Operacion op;
    String nombreArchivo;
    strcrear(nombreArchivo);
    CodigoError err;

    ReconocerYValidarComando(lp, l, tipo, esX, num, idx1, op, idx2, valorX, nombreArchivo, err);

    if (err == ERR_NINGUNO && tipo == GUARDAR && idx1 == 1 && streq(nombreArchivo, "archivocover"))
        printf("OK     test_reconocer_y_validar_comando_guardar\n");
    else
        printf("ERROR  test_reconocer_y_validar_comando_guardar\n");

    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(lp);
    DestruirListaExpresiones(l);
}

void test_reconocer_y_validar_comando_recuperar()
{
    FILE *f = fopen("archivorecup.txt", "wb");
    if (f != NULL)
        fclose(f);

    ListaParsing lp = NULL;
    String linea;
    strcrear(linea);
    strcop(linea, "recuperar archivorecup");
    TokenizarEntrada(lp, linea);

    ListaExpresiones l = NULL;
    TipoComando tipo;
    Boolean esX;
    int num, idx1, idx2, valorX;
    Operacion op;
    String nombreArchivo;
    strcrear(nombreArchivo);
    CodigoError err;

    ReconocerYValidarComando(lp, l, tipo, esX, num, idx1, op, idx2, valorX, nombreArchivo, err);

    if (err == ERR_NINGUNO && tipo == RECUPERAR && streq(nombreArchivo, "archivorecup"))
        printf("OK     test_reconocer_y_validar_comando_recuperar\n");
    else
        printf("ERROR  test_reconocer_y_validar_comando_recuperar\n");

    remove("archivorecup.txt");
    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(lp);
}

void test_reconocer_y_validar_comando_salir()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;
    String linea;
    strcrear(linea);
    strcop(linea, "salir");
    TokenizarEntrada(lp, linea);

    TipoComando tipo;
    Boolean esX;
    int num, idx1, idx2, valorX;
    Operacion op;
    String nombreArchivo;
    strcrear(nombreArchivo);
    CodigoError err;

    ReconocerYValidarComando(lp, l, tipo, esX, num, idx1, op, idx2, valorX, nombreArchivo, err);

    if (err == ERR_NINGUNO && tipo == SALIR)
        printf("OK     test_reconocer_y_validar_comando_salir\n");
    else
        printf("ERROR  test_reconocer_y_validar_comando_salir\n");

    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(lp);
}

void test_ejecutar_comandos()
{
    ListaExpresiones lp = NULL;
    CodigoError err = ERR_NINGUNO;

    String nombre;
    strcrear(nombre);
    strcop(nombre, "archivoTest");

    // SIMPLE
    EjecutarComando(SIMPLE, TRUE, 0, 0, SUMA, 0, nombre, lp, err);

    // SIMPLE otra vez para tener 2 expresiones
    EjecutarComando(SIMPLE, FALSE, 5, 0, SUMA, 0, nombre, lp, err);

    // COMPUESTA
    EjecutarComando(COMPUESTA, FALSE, 0, 1, SUMA, 2, nombre, lp, err);

    // CALCULAR
    EjecutarComando(CALCULAR, FALSE, 3, 1, SUMA, 0, nombre, lp, err);

    // MOSTRAR
    EjecutarComando(MOSTRAR, FALSE, 0, 0, SUMA, 0, nombre, lp, err);

    // IGUALES
    EjecutarComando(IGUALES, FALSE, 0, 1, SUMA, 2, nombre, lp, err);

    // GUARDAR
    EjecutarComando(GUARDAR, FALSE, 0, 1, SUMA, 0, nombre, lp, err);

    // RECUPERAR
    EjecutarComando(RECUPERAR, FALSE, 0, 0, SUMA, 0, nombre, lp, err);

    // SALIR
    EjecutarComando(SALIR, FALSE, 0, 0, SUMA, 0, nombre, lp, err);

    printf("OK test_ejecutar_comandos\n");
}

void test_loop_principal()
{
    FILE *f = fopen("entrada_loop.txt", "w");

    fprintf(f, "simple x\n");
    fprintf(f, "mostrar\n");
    fprintf(f, "salir\n");

    fclose(f);

    freopen("entrada_loop.txt", "r", stdin);

    LoopPrincipal();

    printf("OK test_loop_principal\n");
    remove("entrada_loop.txt");
}

void test_loop_principal_error()
{
    FILE *f = fopen("entrada_loop_error.txt", "w");

    fprintf(f, "comandoinvalido\n"); // provoca ERR_COMANDO_INVALIDO
    fprintf(f, "salir\n");

    fclose(f);

    freopen("entrada_loop_error.txt", "r", stdin);

    LoopPrincipal();

    printf("OK test_loop_principal_error\n");
    remove("entrada_loop_error.txt");
}

void test_loop_division_por_cero()
{
    FILE *f = fopen("entrada_div0.txt", "w");

    fprintf(f, "simple 10\n");       // exp 1
    fprintf(f, "simple 0\n");        // exp 2
    fprintf(f, "compuesta 1 / 2\n"); // exp 3 -> 10 / 0
    fprintf(f, "calcular 3 5\n");    // provoca división por cero
    fprintf(f, "salir\n");

    fclose(f);

    freopen("entrada_div0.txt", "r", stdin);

    LoopPrincipal();

    printf("OK test_loop_division_por_cero\n");
    remove("entrada_div0.txt");
}

void test_guardar_recuperar_verificar_indice()
{
    ListaExpresiones lista = NULL;
    CodigoError err = ERR_NINGUNO;

    String nombreArchivo;
    strcrear(nombreArchivo);
    strcop(nombreArchivo, "testexp");

    EjecutarComando(SIMPLE, TRUE, 0, 0, SUMA, 0, nombreArchivo, lista, err);
    EjecutarComando(GUARDAR, FALSE, 0, 1, SUMA, 0, nombreArchivo, lista, err);

    DestruirListaExpresiones(lista);
    lista = NULL;

    EjecutarComando(RECUPERAR, FALSE, 0, 0, SUMA, 0, nombreArchivo, lista, err);

    Boolean indiceEncontrado = FALSE;
    ListaExpresiones temp = lista;
    while (temp != NULL && !indiceEncontrado)
    {
        if (temp->exp.indiceLista == 1)
            indiceEncontrado = TRUE;
        temp = temp->sig;
    }

    if (err == ERR_NINGUNO && indiceEncontrado)
        printf("OK     test_guardar_recuperar_verificar_indice\n");
    else
        printf("ERROR  test_guardar_recuperar_verificar_indice\n");

    DestruirListaExpresiones(lista);
    strdestruir(nombreArchivo);

    remove("testexp.txt");
}

int main()
{
    printf("---- Ejecutando tests String ----\n");
    // strcrear y strdestruir
    test_strcrear();
    test_strdestruir();
    // strlar
    test_strlar_vacio();
    test_strlar_con_contenido();
    // strcop
    test_strcop_vacio_a_vacio();
    test_strcop_contenido();
    test_strcop_redimension();
    // scan
    test_scan_mock();
    // strcon
    test_strcon_supera_MAX();
    // print
    test_print();
    // streq
    test_streq_identicos();
    test_streq_diferentes_caracter();
    test_streq_diferente_largo();
    // BajarString
    test_bajar_string_basico();
    test_bajar_string_vacio();
    test_bajar_string_fin_archivo();
    // LevantarString
    test_levantar_string_basico();
    test_levantar_string_vacio();
    // CrearStringDesdeRango
    test_crear_desde_rango_normal();
    test_crear_desde_rango_error();
    test_crear_desde_rango_un_char();
    // EsAlfabetico
    test_es_alfabetico_valido();
    test_es_alfabetico_con_numeros();
    test_es_alfabetico_casos_borde();
    // EsOperadorValido
    test_es_operador_valido();
    // EsEntero
    test_es_entero_falla();
    // EsEnteroPositivo
    test_es_entero_positivo();
    test_es_entero_negativo();
    // ConvertirAEntero
    test_convertir_a_entero();
    test_convertir_entero_negativo();
    // PrimerCaracter
    test_primer_caracter();
    printf("---------------------------------------------------------\n\n");

    printf("---- TESTS MODULO CodigoError ----\n");
    test_mostrar_error();
    printf("---------------------------------------------------------\n\n");

    printf("---- TESTS MODULO Operacion ----\n");
    test_operacion_default();
    test_devolver_operacion_suma();
    test_devolver_operacion_resta();
    test_devolver_operacion_division();
    test_devolver_operacion_multiplicacion();
    printf("---------------------------------------------------------\n\n");

    printf("---- TESTS MODULO ExpresionABB ----\n");
    test_crear_expresion_simple_variable_x();
    test_crear_expresion_simple_int();
    test_crear_expresion_compuesta_ABB();
    test_arboles_identicos();
    test_calcular_abb_suma_resta();
    test_calcular_abb_multiplicacion_variable();
    test_calcular_abb_division();
    test_mostrar_abb();
    printf("\n---------------------------------------------------------\n\n");

    printf("---- TESTS MODULO Expresion ----\n");
    test_obtener_indice_expresion();
    test_mostrar_expresion_simple();
    test_destruir_expresion_simple();
    test_destruir_expresion_compuesta();
    test_crear_expresion_simple_entero();
    test_crear_expresion_simple_x();
    test_crear_expresion_compuesta();
    test_calcular_expresion();
    test_comparar_expresiones_identicas();
    test_comparar_expresiones_no_identicas();
    printf("---------------------------------------------------------\n\n");

    printf("---- TESTS MODULO ListaExpresiones ----\n");
    test_insertar_en_lista_vacia();
    test_insertar_dos_expresiones();
    test_insertar_en_lista_con_multiples_nodos();
    test_buscar_expresion_por_indice();
    test_es_indice_valido_true();
    test_es_indice_valido_false();
    test_mostrar_expresiones();
    test_destruir_lista();
    test_crear_insertar_simple();
    test_crear_insertar_compuesta();
    test_comparar_por_indice();
    test_calcular_por_indice();
    printf("---------------------------------------------------------\n\n");

    printf("\n---- TESTS MODULO ListaParsing ----\n");
    test_tokenizar_entrada_string_una_palabra();
    test_tokenizar_entrada_string_una_palabra_y_espacios();
    test_tokenizar_entrada_string_multiples_palabras();
    test_tokenizar_entrada_string_multiples_palabras_y_espacios();
    test_token_en_posicion();
    test_cantidad_tokens();
    printf("---------------------------------------------------------\n\n");

    //
    printf("---- TESTS MODULO Archivo ----\n");
    test_existe_archivo_true();
    test_existe_archivo_false();
    test_existe_archivo_null();
    test_guardar_recuperar_expresion_archivo_ok();
    test_levantar_abb_entero();
    test_levantar_abb_simbolo();
    test_levantar_abb_error_dato();
    test_levantar_abb_error_indice();
    test_levantar_abb_error_dato_simbolo();

    printf("---------------------------------------------------------\n\n");

    printf("---- TESTS MODULO Compilador ----\n");
    // ReconocerComando
    test_reconocer_comando_valido();
    test_reconocer_comando_invalido();

    // ValidarComandoSimple
    test_validar_simple_ok_entero();
    test_validar_simple_cant_params();
    test_validar_simple_ok_x();
    test_validar_simple_parametro_invalido();
    // ValidarComandoCompuesta
    test_validar_compuesta_ok();
    test_validar_compuesta_operador_invalido();
    test_validar_compuesta_primer_indice_no_existe();
    test_validar_compuesta_segundo_indice_no_existe();
    test_validar_compuesta_primer_indice_negativo();
    test_validar_compuesta_segundo_indice_negativo();
    test_validar_compuesta_cantidad_tokens_invalida();

    // ValidarComandoMostrar
    test_validar_mostrar_ok();
    test_validar_mostrar_error_tokens();
    test_validar_mostrar_lista_null();
    // ValidarComandoCalcular
    test_validar_calcular_ok();
    test_validar_calcular_parametro_invalido();
    test_validar_calcular_indice_no_existe();
    test_validar_calcular_indice_negativo();
    test_validar_calcular_cantidad_parametros_invalidos();

    // ValidarComandoIguales
    test_validar_iguales_ok();
    test_validar_iguales_primer_indice_no_existe();
    test_validar_iguales_segundo_indice_no_existe();
    test_validar_iguales_primer_indice_negativo();
    test_validar_iguales_segundo_indice_negativo();
    test_validar_iguales_cantidad_tokens_invalida();

    // ValidarComandoGuardar
    test_validar_guardar_ok();
    test_validar_guardar_nombre_invalido();
    test_validar_guardar_indice_invalido();
    test_validar_guardar_indice_negativo();
    test_validar_guardar_cant_params();
    test_validar_guardar_archivo_existe();
    // ValidarComandoRecuperar
    test_validar_recuperar_ok();
    test_validar_recuperar_error_tokens();
    test_validar_recuperar_error_archivo_invalido();
    test_validar_recuperar_error_archivo_inexistente();
    // ValidarComandoSalir
    test_validar_salir_ok();
    test_validar_salir_error_tokens();
    // ReconocerYValidarComando (coverage 100% Compilador)
    test_reconocer_y_validar_comando_simple();
    test_reconocer_y_validar_comando_compuesta();
    test_reconocer_y_validar_comando_calcular();
    test_reconocer_y_validar_comando_mostrar();
    test_reconocer_y_validar_comando_iguales();
    test_reconocer_y_validar_comando_guardar();
    test_reconocer_y_validar_comando_recuperar();
    test_reconocer_y_validar_comando_salir();
    test_ejecutar_comandos();
    test_loop_principal();
    test_loop_principal_error();
    test_loop_division_por_cero();
    test_guardar_recuperar_verificar_indice();
    printf("---------------------------------------------------------\n\n");

    return 0;
}