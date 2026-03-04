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
#include "String.h"
#include "CodigoError.h"
#include "Expresion.h"
#include "ListaExpresiones.h"
#include "Archivo.h"
#include "Compilador.h"

void test_arboles_identicos()
{
    // --- CASO 1: Árboles idénticos ---
    ExpresionABB a1 = CrearExpresionSimpleInt(25);
    ExpresionABB a2 = CrearExpresionSimpleInt(25);

    // --- CASO 2: Diferente dato (mismo tipo) ---
    ExpresionABB a3 = CrearExpresionSimpleInt(99);

    // --- CASO 3: Árboles compuestos idénticos ---
    // Usamos SUMA (o el valor que corresponda a tu enum)
    ExpresionABB x1 = CrearExpresionSimpleX('x');
    ExpresionABB n1 = CrearExpresionSimpleInt(10);
    ExpresionABB compuesto1 = CrearExpresionCompuesta(SUMA, x1, n1);

    ExpresionABB x2 = CrearExpresionSimpleX('x');
    ExpresionABB n2 = CrearExpresionSimpleInt(10);
    ExpresionABB compuesto2 = CrearExpresionCompuesta(SUMA, x2, n2);

    // --- CASO 4: Diferente estructura (uno simple vs uno compuesto) ---

    printf("\n--- TEST ARBOLES IDENTICOS ---\n");

    if (ArbolesIdenticos(a1, a2) == TRUE)
        printf("OK     Caso 1: Simples iguales\n");
    else
        printf("ERROR  Caso 1: Simples iguales\n");

    if (ArbolesIdenticos(a1, a3) == FALSE)
        printf("OK     Caso 2: Diferente valor detectado\n");
    else
        printf("ERROR  Caso 2: Diferente valor detectado\n");

    if (ArbolesIdenticos(compuesto1, compuesto2) == TRUE)
        printf("OK     Caso 3: Compuestos iguales\n");
    else
        printf("ERROR  Caso 3: Compuestos iguales\n");

    if (ArbolesIdenticos(a1, compuesto1) == FALSE)
        printf("OK     Caso 4: Diferente estructura detectada\n");
    else
        printf("ERROR  Caso 4: Diferente estructura detectada\n");

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

void test_entero_simple()
{
    ExpresionABB e = CrearExpresionSimpleInt(5);
    Boolean error = FALSE;

    int resultado = CalcularABB(e, 0, error);

    if (resultado == 5 && error == FALSE)
        printf("OK     test_entero_simple\n");
    else
        printf("ERROR  test_entero_simple\n");

    DestruirABB(e);
}

void test_variable_x()
{
    ExpresionABB e = CrearExpresionSimpleX('x');
    Boolean error = FALSE;

    int resultado = CalcularABB(e, 7, error);

    if (resultado == 7 && error == FALSE)
        printf("OK     test_variable_x\n");
    else
        printf("ERROR  test_variable_x\n");

    DestruirABB(e);
}

void test_suma_resta()
{
    ExpresionABB a = CrearExpresionSimpleInt(10);
    ExpresionABB b = CrearExpresionSimpleInt(4);

    ExpresionABB s = CrearExpresionCompuesta(SUMA, a, b);
    ExpresionABB r = CrearExpresionCompuesta(RESTA, a, b);

    Boolean errorSuma = FALSE;
    Boolean errorResta = FALSE;

    int resSuma = CalcularABB(s, 0, errorSuma);
    int resResta = CalcularABB(r, 0, errorResta);

    if (resSuma == 14 && errorSuma == FALSE && resResta == 6 && errorResta == FALSE)
        printf("OK     test_suma_resta\n");
    else
        printf("ERROR  test_suma_resta\n");

    DestruirABB(s);
    DestruirABB(r);
    DestruirABB(a);
    DestruirABB(b);
}

void test_multiplicacion_variable()
{
    ExpresionABB a = CrearExpresionSimpleX('x');
    ExpresionABB b = CrearExpresionSimpleInt(2);

    ExpresionABB e = CrearExpresionCompuesta(MULTIPLICACION, a, b);

    Boolean error = FALSE;
    int resultado = CalcularABB(e, 5, error);

    if (resultado == 10 && error == FALSE)
        printf("OK     test_multiplicacion_variable\n");
    else
        printf("ERROR  test_multiplicacion_variable\n");

    DestruirABB(e);
}

void test_expresion_compuesta()
{

    ExpresionABB a = CrearExpresionSimpleInt(3);
    ExpresionABB b = CrearExpresionSimpleInt(2);
    ExpresionABB suma = CrearExpresionCompuesta(SUMA, a, b);

    ExpresionABB x = CrearExpresionSimpleX('x');
    ExpresionABB final1 = CrearExpresionCompuesta(MULTIPLICACION, suma, x);
    ExpresionABB final2 = CrearExpresionCompuesta(MULTIPLICACION, suma, suma);

    Boolean error1 = FALSE;
    Boolean error2 = FALSE;
    int resultado1 = CalcularABB(final1, 4, error1);
    int resultado2 = CalcularABB(final2, 4, error2);

    if (resultado1 == 20 && error1 == FALSE && resultado2 == 25 && error2 == FALSE)
        printf("OK     test_expresion_compuesta\n");
    else
        printf("ERROR  test_expresion_compuesta\n");

    DestruirABB(final1);
    DestruirABB(final2);
}

void test_division()
{
    ExpresionABB a = CrearExpresionSimpleInt(10);
    ExpresionABB b_cero = CrearExpresionSimpleInt(0);
    ExpresionABB b_ok = CrearExpresionSimpleInt(2);

    ExpresionABB e_error = CrearExpresionCompuesta(DIVISION, a, b_cero);
    ExpresionABB e_ok = CrearExpresionCompuesta(DIVISION, a, b_ok);

    Boolean error1 = FALSE;
    Boolean error2 = FALSE;

    int res1 = CalcularABB(e_error, 0, error1); // Caso if (der == 0)
    int res2 = CalcularABB(e_ok, 0, error2);    // Caso else (izq / der)

    if (error1 == TRUE && res1 == 0 && res2 == 5 && error2 == FALSE)
        printf("OK     test_division \n");
    else
        printf("ERROR  test_division\n");

    DestruirABB(e_error);
    DestruirABB(e_ok);
    DestruirABB(a);
    DestruirABB(b_cero);
    DestruirABB(b_ok);
}

void test_mostrar_abb()
{
    ExpresionABB e1 = CrearExpresionSimpleX('x');
    ExpresionABB e2 = CrearExpresionSimpleInt(10);
    ExpresionABB e3 = CrearExpresionSimpleInt(2);
    ExpresionABB arbol = CrearExpresionCompuesta(SUMA, e1, e2);
    ExpresionABB arbol2 = CrearExpresionCompuesta(MULTIPLICACION, arbol, e3);

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

void test_tokenizar_simple()
{
    String linea = NULL;
    strcrear(linea);
    strcop(linea, "hola mundo");

    ListaParsing lp = NULL;
    TokenizarEntrada(lp, linea);

    int cant = CantidadTokens(lp);

    if (cant == 2)
        printf("OK     test_tokenizar_simple\n");
    else
        printf("ERROR  test_tokenizar_simple\n");

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

void test_espacios_multiples()
{
    String linea = NULL;
    strcrear(linea);
    strcop(linea, "   hola    mundo   test   ");

    ListaParsing lp = NULL;
    TokenizarEntrada(lp, linea);

    int cant = CantidadTokens(lp);

    if (cant == 3)
        printf("OK     test_espacios_multiples\n");
    else
        printf("ERROR  test_espacios_multiples\n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

void test_mostrar_error()
{
    printf("> test_mostrar_error ejecutado (verificar mensajes ):");
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
    MostrarError(ERR_ARCHIVO_NO_SE_PUEDE_ABRIR);
    MostrarError(ERR_LISTA_VACIA);

    // Caso default (valor inexistente)
    MostrarError(CodigoError(999));
}

//--------------------//
//  MODULO EXPRESION  //
//--------------------//
void test_obtener_indice_expresion()
{
    Expresion exp;
    exp.indiceLista = 42;
    exp.terminos = NULL;

    int indice = ObtenerIndiceExpresion(exp);

    if (indice == 42)
        printf("OK     test_obtener_indice_expresion\n");
    else
        printf("ERROR  test_obtener_indice_expresion\n");
}

void test_mostrar_expresion_simple()
{
    Expresion exp;
    exp.indiceLista = 1;
    exp.terminos = CrearExpresionSimpleInt(5);

    printf("> test_mostrar_expresion_simple\n");

    printf("   Resultado esperado: 5\n");
    printf("   Resultado obtenido: ");
    MostrarExpresion(exp);
    DestruirExpresion(exp);
    printf("\n");
}

void test_destruir_expresion_simple()
{
    Expresion exp;
    exp.indiceLista = 1;
    exp.terminos = CrearExpresionSimpleInt(10);

    DestruirExpresion(exp);

    if (exp.terminos == NULL)
        printf("OK     test_destruir_expresion_simple\n");
    else
        printf("ERROR  test_destruir_expresion_simple\n");
}

void test_destruir_expresion_compuesta()
{
    ExpresionABB a = CrearExpresionSimpleInt(3);
    ExpresionABB b = CrearExpresionSimpleInt(4);
    ExpresionABB suma = CrearExpresionCompuesta(SUMA, a, b);

    Expresion exp;
    exp.indiceLista = 2;
    exp.terminos = suma;

    DestruirExpresion(exp);

    if (exp.terminos == NULL)
        printf("OK     test_destruir_expresion_compuesta\n");
    else
        printf("ERROR  test_destruir_expresion_compuesta\n");
}

//---------------------------//
//  MODULO LISTAEXPRESIONES  //
//---------------------------//

void test_insertar_en_lista_vacia()
{
    ListaExpresiones l = NULL;

    Expresion exp;
    exp.indiceLista = 1;
    exp.terminos = CrearExpresionSimpleInt(5);

    InsertarExpresionAlFinalL(l, exp);

    if (l != NULL && ObtenerIndiceExpresion(l->exp) == 1)
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
    e1.terminos = CrearExpresionSimpleInt(3);

    Expresion e2;
    e2.indiceLista = 2;
    e2.terminos = CrearExpresionSimpleInt(7);

    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);

    if (l != NULL &&
        l->sig != NULL &&
        ObtenerIndiceExpresion(l->sig->exp) == 2)
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
    e1.terminos = CrearExpresionSimpleInt(10);

    Expresion e2;
    e2.indiceLista = 2;
    e2.terminos = CrearExpresionSimpleInt(20);

    Expresion e3;
    e3.indiceLista = 3;
    e3.terminos = CrearExpresionSimpleInt(30);

    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);
    InsertarExpresionAlFinalL(l, e3);

    NodoL *aux = l;
    while (aux->sig != NULL)
    {
        aux = aux->sig;
    }

    if (ObtenerIndiceExpresion(aux->exp) == 3)
        printf("OK     test_insertar_en_lista_con_multiples_nodos\n");
    else
        printf("ERROR  test_insertar_en_lista_con_multiples_nodos\n");

    DestruirListaExpresiones(l);
}

void test_buscar_expresion_por_indice()
{
    ListaExpresiones l = NULL;

    Expresion e1;
    e1.indiceLista = 10;
    e1.terminos = CrearExpresionSimpleInt(1);

    Expresion e2;
    e2.indiceLista = 20;
    e2.terminos = CrearExpresionSimpleInt(2);

    InsertarExpresionAlFinalL(l, e1);
    InsertarExpresionAlFinalL(l, e2);

    Expresion resultado = BuscarExpresionPorIndice(l, 20);

    if (ObtenerIndiceExpresion(resultado) == 20)
        printf("OK     test_buscar_expresion_por_indice\n");
    else
        printf("ERROR  test_buscar_expresion_por_indice\n");

    DestruirListaExpresiones(l);
}

void test_es_indice_valido_true()
{
    ListaExpresiones l = NULL;

    Expresion e;
    e.indiceLista = 5;
    e.terminos = CrearExpresionSimpleInt(8);

    InsertarExpresionAlFinalL(l, e);

    if (EsIndiceValido(l, 5) == TRUE)
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
    e.terminos = CrearExpresionSimpleInt(4);

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
    e1.terminos = CrearExpresionSimpleInt(3);

    Expresion e2;
    e2.indiceLista = 2;
    e2.terminos = CrearExpresionSimpleInt(7);

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
    e.terminos = CrearExpresionSimpleInt(5);

    InsertarExpresionAlFinalL(l, e);

    DestruirListaExpresiones(l);

    if (l == NULL)
        printf("OK     test_destruir_lista\n");
    else
        printf("ERROR  test_destruir_lista\n");
}

//-----------------------//
//        STRING        //
//---------------------//

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

// Caso importante: s1 es pequeño y s2 es mucho más grande
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

    strcop(s1, s2); // Debe hacer delete[] de 'A' y crear espacio para 'Bellos'

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

void test_strcon_supera_MAX()
{
    String s1;
    String s2;

    strcrear(s1);
    strcrear(s2);

    // Crear string de 70 caracteres
    char buffer1[71];
    int i = 0;
    while (i < 70)
    {
        buffer1[i] = 'A';
        i++;
    }
    buffer1[70] = '\0';

    // Crear string de 20 caracteres
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

    if (largoFinal == MAX - 1) // debería quedar truncado
        printf("OK     test_strcon_supera_MAX\n");
    else
        printf("ERROR  test_strcon_supera_MAX: largo: %d\n", largoFinal);

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
    FILE *f = fopen("test_string.bin", "wb");
    char palabra[] = "Hola";
    fwrite(palabra, sizeof(char), 5, f);
    fclose(f);

    String s;
    strcrear(s);
    f = fopen("test_string.bin", "rb");

    BajarString(s, f);

    fclose(f);

    if (streq(s, "Hola"))
        printf("OK     test_bajar_string_basico\n");
    else
        printf("ERROR  test_bajar_string_basico: se leyó: %s\n", s);

    strdestruir(s);
    remove("test_string.bin");
}

void test_bajar_string_vacio()
{
    // Caso de borde: un archivo que solo tiene el terminador nulo
    FILE *f = fopen("test_vacio.bin", "wb");
    char nulo = '\0';
    fwrite(&nulo, sizeof(char), 1, f);
    fclose(f);

    String s;
    strcrear(s);
    f = fopen("test_vacio.bin", "rb");

    BajarString(s, f);

    fclose(f);

    if (strlar(s) == 0)
        printf("OK     test_bajar_string_vacio\n");
    else
        printf("ERROR  test_bajar_string_vacio\n");

    strdestruir(s);
    remove("test_vacio.bin");
}

void test_bajar_string_fin_archivo()
{

    FILE *f_out = fopen("test_eof.dat", "wb");
    char letras[3] = {'A', 'B', 'C'};
    fwrite(letras, sizeof(char), 3, f_out);
    fclose(f_out);

    // 2. Intentar bajarlo
    FILE *f_in = fopen("test_eof.dat", "rb");
    String s;
    strcrear(s);

    // Aquí BajarString llegará al final del archivo, no encontrará '\0',
    // y entrará 'if (feof(f)) aux[i] = '\0';'
    BajarString(s, f_in);
    fclose(f_in);

    // 3. Verificación
    // Si la línea aux[i] = '\0' funcionó, el string debe ser "ABC"
    if (streq(s, "ABC") == TRUE && strlar(s) == 3)
        printf("OK     test_bajar_string_fin_archivo\n");
    else
        printf("ERROR  test_bajar_string_fin_archivo\n");

    strdestruir(s);
    remove("test_eof.dat");
}

void test_levantar_string_basico()
{
    String s;
    strcrear(s);
    strcop(s, "Hola");

    FILE *f = fopen("test_save.bin", "wb");
    LevantarString(s, f);
    fclose(f);

    f = fopen("test_save.bin", "rb");
    char buffer[10];
    size_t leidos = fread(buffer, sizeof(char), 5, f);
    fclose(f);

    if (leidos == 5 && streq(buffer, "Hola") == TRUE && buffer[4] == '\0')
        printf("OK     test_levantar_string_basico\n");
    else
        printf("ERROR  test_levantar_string_basico\n");

    strdestruir(s);
    remove("test_save.bin");
}

void test_levantar_string_vacio()
{
    String s;
    strcrear(s);

    FILE *f = fopen("test_empty_save.bin", "wb");
    LevantarString(s, f);
    fclose(f);

    f = fopen("test_empty_save.bin", "rb");
    char c;
    size_t leidos = fread(&c, sizeof(char), 1, f);
    fclose(f);

    if (leidos == 1 && c == '\0')
        printf("OK     test_levantar_string_vacio\n");
    else
        printf("ERROR  test_levantar_string_vacio\n");

    strdestruir(s);
    remove("test_empty_save.bin");
}

void test_crear_desde_rango_normal()
{
    String linea, resultado;
    strcrear(linea);
    strcop(linea, "Hola Mundo");
    // Queremos sacar "Hola" (del índice 0 al 3)

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

    // Caso de error: fin fuera de rango (largo es 3, índice máx es 2)
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

    bool ok = (EsAlfabetico(s1) == FALSE && EsAlfabetico(s2) == FALSE);

    if (ok)
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

    // Test 4: Caso de borde - Operador válido pero con más caracteres
    // Tu código pide largo == 1, así que "++" debería ser FALSE
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

//---------------------//
//      OPERACION      //
//--------------------//

void test_operacion_default()
{

    Operacion op_invalida = (Operacion)99;

    char resultado = DevolverOperacion(op_invalida);

    printf("OK     test_operacion_default pasó (se ejecutó el caso por defecto)\n");
}

//--------------------------//
//      MODULO ARCHIVO     //
//------------------------//

void test_existe_archivo_true()
{
    String nombre = NULL;
    strcrear(nombre);
    strcop(nombre, "archivo_test_existente.dat");

    FILE *f = fopen(nombre, "wb");
    if (f != NULL)
    {
        fprintf(f, "contenido de prueba");
        fclose(f);
    }

    if (ExisteArchivo(nombre) == TRUE)
        printf("OK     test_existe_archivo_true\n");
    else
        printf("ERROR  test_existe_archivo_true\n");

    remove(nombre);
    strdestruir(nombre);
}

void test_existe_archivo_false()
{
    String nombre = NULL;
    strcrear(nombre);
    strcop(nombre, "este_archivo_no_existe_12345.dat");

    if (ExisteArchivo(nombre) == FALSE)
        printf("OK     test_existe_archivo_false\n");
    else
        printf("ERROR  test_existe_archivo_false\n");

    strdestruir(nombre);
}

void test_existe_archivo_null()
{
    // Caso de borde: pasar un NULL o string vacío
    String nombre = NULL;
    strcrear(nombre); // string vacío ""

    if (ExisteArchivo(nombre) == FALSE)
        printf("OK     test_existe_archivo_vacio\n");
    else
        printf("ERROR  test_existe_archivo_vacio\n");

    strdestruir(nombre);
}

void test_guardar_recuperar_expresion_archivo_ok()
{

    Expresion exp, expRecuperada;
    CodigoError err;

    // Crear subárbol izquierdo: (3 + x)
    ExpresionABB n3 = CrearExpresionSimpleInt(3);
    ExpresionABB nx = CrearExpresionSimpleX('x');
    ExpresionABB suma = CrearExpresionCompuesta(SUMA, n3, nx);

    // Crear subárbol derecho: (10 - 2)
    ExpresionABB n10 = CrearExpresionSimpleInt(10);
    ExpresionABB n2 = CrearExpresionSimpleInt(2);
    ExpresionABB resta = CrearExpresionCompuesta(RESTA, n10, n2);

    // Crear raíz: ( (3 + x) * (10 - 2) )
    ExpresionABB raiz = CrearExpresionCompuesta(MULTIPLICACION, suma, resta);

    exp.indiceLista = 99;
    exp.terminos = raiz;

    String nombreBase = "test_integracion";

    GuardarExpresionEnArchivo(nombreBase, exp, err);

    if (err != ERR_NINGUNO)
    {
        printf("ERROR  test_guardar_recuperar_expresion_archivo_ok: Error al guardar (%d)\n", err);
    }
    else
    {
        RecuperarExpresionDesdeArchivo(nombreBase, expRecuperada, err);

        if (err != ERR_NINGUNO)
        {
            printf("ERROR  test_guardar_recuperar_expresion_archivo_ok: Error al recuperar (%d)\n", err);
        }
        else
        {
            if (ArbolesIdenticos(exp.terminos, expRecuperada.terminos) == TRUE)
                printf("OK     test_guardar_recuperar_expresion_archivo_ok\n");
            else
                printf("ERROR  test_guardar_recuperar_expresion_archivo_ok: La expresion guardada y la recuperada NO coincide\n");

            DestruirExpresion(expRecuperada);
        }
    }

    remove("test_integracion.txt");
    DestruirExpresion(exp);
}

void test_Recuperar_Archivo_NoExiste()
{
    Expresion exp;
    CodigoError err;

    RecuperarExpresionDesdeArchivo("archivo_que_no_existe", exp, err);

    if (err == ERR_ARCHIVO_NO_EXISTE)
        printf("OK: detecto archivo inexistente.\n");
    else
        printf("ERROR: no detecto archivo inexistente.\n");
}

void test_Guardar_Archivo_NoSePuedeAbrir()
{
    Expresion exp;
    CodigoError err;

    // Nombre inválido con caracteres prohibidos
    GuardarExpresionEnArchivo("///", exp, err);

    if (err == ERR_ARCHIVO_NO_SE_PUEDE_ABRIR)
        printf("OK: detecto error al abrir archivo.\n");
    else
        printf("ERROR: no detecto error al abrir.\n");
}

//---------------------------//
//     MODULO COMPILADOR     //
//---------------------------//

// ValidarComandoMostrar
void test_validar_mostrar_ok()
{
    CodigoError err;

    String linea = NULL;
    strcrear(linea);
    strcop(linea, "TEST");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    ListaExpresiones expresiones = NULL;
    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearExpresionSimpleInt(10);
    InsertarExpresionAlFinalL(expresiones, e1);

    Boolean res = ValidarComandoMostrar(tokens, expresiones, err);

    if (res)
        printf("OK     test_validar_mostrar_ok\n");
    else
        printf("ERROR  test_validar_mostrar_ok\n");

    strdestruir(linea);
    DestruirListaParsing(tokens);
    DestruirListaExpresiones(expresiones);
}

void test_validar_mostrar_error_tokens()
{
    CodigoError err;

    String linea = NULL;
    strcrear(linea);
    strcop(linea, "TEST TEST");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    ListaExpresiones expresiones = NULL;
    Expresion e1;
    e1.indiceLista = 1;
    e1.terminos = CrearExpresionSimpleInt(10);
    InsertarExpresionAlFinalL(expresiones, e1);

    Boolean res = ValidarComandoMostrar(tokens, expresiones, err);

    if (res == FALSE && err == ERR_CANT_PARAMETROS)
        printf("OK     test_validar_mostrar_error_tokens\n");
    else
        printf("ERROR  test_validar_mostrar_error_tokens\n");

    strdestruir(linea);
    DestruirListaParsing(tokens);
    DestruirListaExpresiones(expresiones);
}

void test_validar_mostrar_lista_null()
{
    CodigoError err;

    String linea = NULL;
    strcrear(linea);
    strcop(linea, "TEST");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    ListaExpresiones expresiones = NULL;

    Boolean res = ValidarComandoMostrar(tokens, expresiones, err);

    if (res == FALSE && err == ERR_LISTA_VACIA)
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
    strcop(linea, "TEST TEST");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    strcrear(nombreArchivo);
    strcop(nombreArchivo, "test");

    FILE *file = fopen(nombreArchivo, "wb");

    Boolean res = ValidarComandoRecuperar(tokens, nombreArchivo, err);

    if (res)
        printf("OK     test_validar_recuperar_ok\n");
    else
        printf("ERROR  test_validar_recuperar_ok\n");

    fclose(file);
    remove("test.bin");

    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(tokens);
}

void test_validar_recuperar_error_tokens()
{
    CodigoError err;

    String linea = NULL, nombreArchivo = NULL;
    strcrear(linea);
    strcop(linea, "TEST");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    strcrear(nombreArchivo);
    strcop(nombreArchivo, "testdos");

    FILE *file = fopen(nombreArchivo, "wb");

    Boolean res = ValidarComandoRecuperar(tokens, nombreArchivo, err);

    if (!res && err == ERR_CANT_PARAMETROS)
        printf("OK     test_validar_recuperar_error_tokens\n");
    else
        printf("ERROR  test_validar_recuperar_error_tokens\n");

    fclose(file);

    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(tokens);
}

void test_validar_recuperar_error_archivo_invalido()
{
    CodigoError err;

    String linea = NULL, nombreArchivo = NULL;
    strcrear(linea);
    strcop(linea, "TEST TEST");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    strcrear(nombreArchivo);
    strcop(nombreArchivo, "test3");

    FILE *file = fopen(nombreArchivo, "wb");

    Boolean res = ValidarComandoRecuperar(tokens, nombreArchivo, err);

    if (!res && err == ERR_ARCHIVO_INVALIDO)
        printf("OK     test_validar_recuperar_error_archivo_invalido\n");
    else
        printf("ERROR  test_validar_recuperar_error_archivo_invalido\n");

    fclose(file);
    strdestruir(linea);
    strdestruir(nombreArchivo);
    DestruirListaParsing(tokens);
}

void test_validar_recuperar_error_archivo_inexistente()
{
    CodigoError err;

    String linea = NULL, nombreArchivo = NULL;
    strcrear(linea);
    strcop(linea, "TEST TEST");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    strcrear(nombreArchivo);
    strcop(nombreArchivo, "testCUATRO");

    Boolean res = ValidarComandoRecuperar(tokens, nombreArchivo, err);

    if (!res && err == ERR_ARCHIVO_NO_EXISTE)
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
    CodigoError err;

    String linea = NULL;
    strcrear(linea);
    strcop(linea, "TEST");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    Boolean res = ValidarComandoSalir(tokens, err);

    if (res)
        printf("OK     test_validar_salir_ok\n");
    else
        printf("ERROR  test_validar_salir_ok\n");

    strdestruir(linea);
    DestruirListaParsing(tokens);
}

void test_validar_salir_error_tokens()
{
    CodigoError err;

    String linea = NULL;
    strcrear(linea);
    strcop(linea, "TEST TEST");

    ListaParsing tokens = NULL;
    TokenizarEntrada(tokens, linea);

    Boolean res = ValidarComandoSalir(tokens, err);

    if (!res && err == ERR_CANT_PARAMETROS)
        printf("OK     test_validar_salir_error_tokens\n");
    else
        printf("ERROR  test_validar_salir_error_tokens\n");
}

int main()
{
    printf("---- Ejecutando tests CalcularABB ----\n");
    test_entero_simple();
    test_variable_x();
    test_suma_resta();
    test_multiplicacion_variable();
    test_expresion_compuesta();
    test_arboles_identicos();
    test_division();
    test_mostrar_abb();
    printf("\n--------------------------------\n\n");

    printf("---- Ejecutando tests String ----\n");
    // strcrear y strdestruir
    test_strcrear();
    test_strdestruir();
    // strlar
    test_strlar_vacio();
    test_strlar_con_contenido();
    // strcop
    test_strcop_contenido();
    test_strcop_redimension();
    test_strcop_vacio_a_vacio();
    // print y scan
    test_print();
    test_scan_mock();
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
    // EsEntero
    test_es_entero_positivo();
    test_es_entero_negativo();
    test_es_entero_falla();
    test_convertir_a_entero();
    test_primer_caracter();
    test_es_operador_valido();
    test_strcon_supera_MAX();
    printf("\n--------------------------------\n\n");

    printf("---- Ejecutando tests Operacion ----\n");
    test_operacion_default();
    printf("\n--------------------------------\n\n");

    printf("\n---- Ejecutando tests ListaParsing ----\n");
    test_tokenizar_simple();
    test_token_en_posicion();
    test_cantidad_tokens();
    test_espacios_multiples();
    printf("\n--------------------------------\n\n");

    printf("---- Ejecutando tests CodigoError ----\n");
    test_mostrar_error();
    printf("\n--------------------------------\n\n");

    printf("---- Ejecutando tests Expresion ----\n");
    test_obtener_indice_expresion();
    test_mostrar_expresion_simple();
    test_destruir_expresion_simple();
    test_destruir_expresion_compuesta();
    printf("\n--------------------------------\n\n");

    printf("---- Ejecutando tests ListaExpresiones ----\n");
    test_insertar_en_lista_vacia();
    test_insertar_dos_expresiones();
    test_insertar_en_lista_con_multiples_nodos();
    test_buscar_expresion_por_indice();
    test_es_indice_valido_true();
    test_es_indice_valido_false();
    test_mostrar_expresiones();
    test_destruir_lista();
    printf("\n--------------------------------\n\n");

    printf("---- Ejecutando tests Archivo ----\n");
    test_existe_archivo_true();
    test_existe_archivo_false();
    test_existe_archivo_null();
    test_guardar_recuperar_expresion_archivo_ok();
    test_Recuperar_Archivo_NoExiste();
    test_Guardar_Archivo_NoSePuedeAbrir();
    printf("\n--------------------------------\n\n");

    printf("---- Ejecutando tests Compilador ----\n");
    // ValidarComandoSimple

    // ValidarComandoCompuesta

    // ValidarComandoMostrar
    test_validar_mostrar_ok();
    test_validar_mostrar_error_tokens();
    test_validar_mostrar_lista_null();
    // ValidarComandoCalcular

    // ValidarComandoIguales

    // ValidarComandoGuardar

    // ValidarComandoRecuperar
    test_validar_recuperar_ok();
    test_validar_recuperar_error_tokens();
    test_validar_recuperar_error_archivo_invalido();
    test_validar_recuperar_error_archivo_inexistente();
    // ValidarComandoSalir
    test_validar_salir_ok();
    test_validar_salir_error_tokens();
    printf("\n--------------------------------\n\n");

    return 0;
}