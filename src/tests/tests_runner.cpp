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
        printf("✔ Caso 1: Simples iguales OK\n");
    else
        printf("✘ Caso 1: Falló\n");

    if (ArbolesIdenticos(a1, a3) == FALSE)
        printf("✔ Caso 2: Diferente valor detectado OK\n");
    else
        printf("✘ Caso 2: Falló\n");

    if (ArbolesIdenticos(compuesto1, compuesto2) == TRUE)
        printf("✔ Caso 3: Compuestos iguales OK\n");
    else
        printf("✘ Caso 3: Falló\n");

    if (ArbolesIdenticos(a1, compuesto1) == FALSE)
        printf("✔ Caso 4: Diferente estructura detectada OK\n");
    else
        printf("✘ Caso 4: Falló\n");

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
        printf("✔ test_suma_resta pasó\n");
    else
        printf("✘ test_suma_resta falló\n");

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
        printf("✔ test_multiplicacion_variable pasó\n");
    else
        printf("✘ test_multiplicacion_variable falló\n");

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
        printf("✔ test_expresion_compuesta pasó\n");
    else
        printf("✘ test_expresion_compuesta falló\n");

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
        printf("✔ test_division pasó (Caminos if/else cubiertos)\n");
    else
        printf("✘ test_division falló\n");

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

    ExpresionABB arbol = CrearExpresionCompuesta(SUMA, e1, e2);

    printf("Arbol generado internamente con parentesis.\n");
    printf("Se espera ver algo similar a: (x)+ (10)\n");
    printf("Resultado obtenido: ");

    MostrarABB(arbol);

    DestruirABB(arbol);
    DestruirABB(e1);
    DestruirABB(e2);
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
        printf("✔ test_tokenizar_simple pasó\n");
    else
        printf("✘ test_tokenizar_simple falló\n");

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
        printf("✔ test_token_en_posicion pasó\n");
    else
        printf("✘ test_token_en_posicion falló\n");

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
        printf("✔ test_cantidad_tokens pasó\n");
    else
        printf("✘ test_cantidad_tokens falló\n");

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
        printf("✔ test_espacios_multiples pasó\n");
    else
        printf("✘ test_espacios_multiples falló\n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

void test_mostrar_error()
{
    printf("\n---- Ejecutando test_mostrar_error ----\n\n");

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

    printf("✔ test_mostrar_error ejecutado (verificar mensajes arriba)\n");
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
        printf("✔ test_obtener_indice_expresion pasó\n");
    else
        printf("✘ test_obtener_indice_expresion falló\n");
}

void test_mostrar_expresion_simple()
{
    Expresion exp;
    exp.indiceLista = 1;
    exp.terminos = CrearExpresionSimpleInt(5);

    printf("\n✔ test_mostrar_expresion_simple pasó\n");

    DestruirABB(exp.terminos);
}

void test_destruir_expresion_simple()
{
    Expresion exp;
    exp.indiceLista = 1;
    exp.terminos = CrearExpresionSimpleInt(10);

    DestruirExpresion(exp);

    if (exp.terminos == NULL)
        printf("✔ test_destruir_expresion_simple pasó\n");
    else
        printf("✘ test_destruir_expresion_simple falló\n");
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
        printf("✔ test_destruir_expresion_compuesta pasó\n");
    else
        printf("✘ test_destruir_expresion_compuesta falló\n");
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
        printf("✔ test_insertar_en_lista_vacia pasó\n");
    else
        printf("✘ test_insertar_en_lista_vacia falló\n");

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
        printf("✔ test_insertar_varias_expresiones pasó\n");
    else
        printf("✘ test_insertar_varias_expresiones falló\n");

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
        printf("✔ test_insertar_en_lista_con_multiples_nodos pasó\n");
    else
        printf("✘ test_insertar_en_lista_con_multiples_nodos falló\n");

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
        printf("✔ test_buscar_expresion_por_indice pasó\n");
    else
        printf("✘ test_buscar_expresion_por_indice falló\n");

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
        printf("✔ test_es_indice_valido_true pasó\n");
    else
        printf("✘ test_es_indice_valido_true falló\n");

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
        printf("✔ test_es_indice_valido_false pasó\n");
    else
        printf("✘ test_es_indice_valido_false falló\n");

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

    MostrarExpresiones(l);

    printf("✔ test_mostrar_expresiones pasó\n");

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
        printf("✔ test_destruir_lista pasó\n");
    else
        printf("✘ test_destruir_lista falló\n");
}

//-----------------------//
//        STRING        //
//---------------------//

void test_strcrear()
{
    String s;
    strcrear(s);

    if (s != NULL && s[0] == '\0')
        printf("✔ test_strcrear pasó\n");
    else
        printf("✘ test_strcrear falló\n");

    strdestruir(s);
}

void test_strdestruir()
{
    String s;
    strcrear(s);

    strdestruir(s);

    if (s == NULL)
        printf("✔ test_strdestruir pasó\n");
    else
        printf("✘ test_strdestruir falló (el puntero no es NULL)\n");
}

void test_strlar_vacio()
{
    String s;
    strcrear(s);

    int largo = strlar(s);

    if (largo == 0)
        printf("✔ test_strlar_vacio pasó\n");
    else
        printf("✘ test_strlar_vacio falló (largo esperado: 0, obtenido: %d)\n", largo);

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
        printf("✔ test_strlar_con_contenido pasó\n");
    else
        printf("✘ test_strlar_con_contenido falló (largo esperado: 4, obtenido: %d)\n", largo);

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
        printf("✔ test_strcop_vacio_a_vacio pasó\n");
    else
        printf("✘ test_strcop_vacio_a_vacio falló\n");

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
        printf("✔ test_strcop_contenido pasó\n");
    else
        printf("✘ test_strcop_contenido falló\n");

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
        printf("✔ test_strcop_redimension pasó\n");
    else
        printf("✘ test_strcop_redimension falló\n");

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
        printf("✔ test_scan_mock pasó (leyó 'Hola' sin intervención humana)\n");
    else
        printf("✘ test_scan_mock falló (obtenido: %s)\n", s);

    strdestruir(s);
    remove("test_input.txt");
}

void test_print()
{
    String s;
    strcrear(s);
    strcop(s, "Hola");

    printf("[Salida esperada: Hola] -> Salida real: ");

    print(s);

    printf("\n");

    if (strlar(s) == 4 && s[0] == 'H' && s[4] == '\0')
        printf("✔ test_print pasó (verificar visualmente arriba)\n");
    else
        printf("✘ test_print falló\n");

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
        printf("✔ test_streq_identicos pasó\n");
    else
        printf("✘ test_streq_identicos falló\n");

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
        printf("✔ test_strcon_supera_MAX pasó (if largo > MAX cubierto)\n");
    else
        printf("✘ test_strcon_supera_MAX falló (largo: %d)\n", largoFinal);

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
        printf("✔ test_streq_diferentes_caracter pasó\n");
    else
        printf("✘ test_streq_diferentes_caracter falló\n");

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
        printf("✔ test_streq_diferente_largo pasó\n");
    else
        printf("✘ test_streq_diferente_largo falló\n");

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
        printf("✔ test_bajar_string_basico pasó\n");
    else
        printf("✘ test_bajar_string_basico falló (se leyó: %s)\n", s);

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
        printf("✔ test_bajar_string_vacio pasó\n");
    else
        printf("✘ test_bajar_string_vacio falló\n");

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
        printf("✔ test_bajar_string_fin_archivo pasó (Línea de feof cubierta)\n");
    else
        printf("✘ test_bajar_string_fin_archivo falló\n");

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
        printf("✔ test_levantar_string_basico pasó\n");
    else
        printf("✘ test_levantar_string_basico falló\n");

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
        printf("✔ test_levantar_string_vacio pasó\n");
    else
        printf("✘ test_levantar_string_vacio falló\n");

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
        printf("✔ test_crear_desde_rango_normal pasó\n");
    else
        printf("✘ test_crear_desde_rango_normal falló (obtenido: %s)\n", resultado);

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
        printf("✔ test_crear_desde_rango_error pasó (devolvió string vacío)\n");
    else
        printf("✘ test_crear_desde_rango_error falló\n");

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
        printf("✔ test_crear_desde_rango_un_char pasó\n");
    else
        printf("✘ test_crear_desde_rango_un_char falló\n");

    strdestruir(linea);
    strdestruir(resultado);
}

void test_es_alfabetico_valido()
{
    String s;
    strcrear(s);
    strcop(s, "SoloLetras");

    if (EsAlfabetico(s) == TRUE)
        printf("✔ test_es_alfabetico_valido pasó\n");
    else
        printf("✘ test_es_alfabetico_valido falló\n");

    strdestruir(s);
}

void test_es_alfabetico_con_numeros()
{
    String s;
    strcrear(s);
    strcop(s, "Letras123");

    if (EsAlfabetico(s) == FALSE)
        printf("✔ test_es_alfabetico_con_numeros pasó\n");
    else
        printf("✘ test_es_alfabetico_con_numeros falló\n");

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
        printf("✔ test_es_alfabetico_casos_borde pasó\n");
    else
        printf("✘ test_es_alfabetico_casos_borde falló\n");

    strdestruir(s1);
    strdestruir(s2);
}

void test_es_operador_valido()
{
    String s;
    strcrear(s);

    strcop(s, "+");
    if (EsOperadorValido(s) == TRUE)
        printf("✔ test_es_operador_suma pasó\n");
    else
        printf("✘ test_es_operador_suma falló\n");

    strcop(s, "/");
    if (EsOperadorValido(s) == TRUE)
        printf("✔ test_es_operador_division pasó\n");
    else
        printf("✘ test_es_operador_division falló\n");

    strcop(s, "!");
    if (EsOperadorValido(s) == FALSE)
        printf("✔ test_es_operador_invalido pasó\n");
    else
        printf("✘ test_es_operador_invalido falló\n");

    // Test 4: Caso de borde - Operador válido pero con más caracteres
    // Tu código pide largo == 1, así que "++" debería ser FALSE
    strcop(s, "++");
    if (EsOperadorValido(s) == FALSE)
        printf("✔ test_es_operador_doble_falla pasó\n");
    else
        printf("✘ test_es_operador_doble_falla falló\n");

    strdestruir(s);
}

void test_es_entero_positivo()
{
    String s;
    strcrear(s);
    strcop(s, "1234");

    if (EsEnteroPositivo(s) == TRUE)
        printf("✔ test_es_entero_positivo pasó\n");
    else
        printf("✘ test_es_entero_positivo falló\n");

    strdestruir(s);
}

void test_es_entero_negativo()
{
    String s;
    strcrear(s);
    strcop(s, "-567");

    if (EsEnteroPositivo(s) == FALSE)
        printf("✔ test_es_entero_negativo pasó\n");
    else
        printf("✘ test_es_entero_negativo falló\n");

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
        printf("✔ test_es_entero_falla pasó (Todos los caminos de error cubiertos)\n");
    else
        printf("✘ test_es_entero_falla falló\n");

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
        printf("✔ test_convertir_a_entero_simple pasó\n");
    else
        printf("✘ test_convertir_a_entero_simple falló (res1: %d, res2: %d)\n", res1, res2);

    strdestruir(s);
}

void test_primer_caracter()
{
    String s;
    strcrear(s);
    strcop(s, "Hola");

    char c = PrimerCaracter(s);

    if (c == 'H')
        printf("✔ test_primer_caracter pasó\n");
    else
        printf("✘ test_primer_caracter falló\n");

    strdestruir(s);
}

//---------------------//
//      OPERACION      //
//--------------------//

void test_operacion_default()
{

    Operacion op_invalida = (Operacion)99;

    char resultado = DevolverOperacionChar(op_invalida);

    printf("✔ test_operacion_default pasó (se ejecutó el caso por defecto)\n");
}

void test_devolver_operacion_suma()
{
    Operacion op = DevolverOperacion('+');

    if (op == SUMA)
        printf("✔ test_devolver_operacion_suma pasó\n");
    else
        printf("✘ test_devolver_operacion_suma falló\n");
}

void test_devolver_operacion_resta()
{
    Operacion op = DevolverOperacion('-');

    if (op == RESTA)
        printf("✔ test_devolver_operacion_resta pasó\n");
    else
        printf("✘ test_devolver_operacion_resta falló\n");
}

void test_devolver_operacion_multiplicacion()
{
    Operacion op = DevolverOperacion('*');

    if (op == MULTIPLICACION)
        printf("✔ test_devolver_operacion_multiplicacion pasó\n");
    else
        printf("✘ test_devolver_operacion_multiplicacion falló\n");
}

void test_devolver_operacion_division()
{
    Operacion op = DevolverOperacion('/');

    if (op == DIVISION)
        printf("✔ test_devolver_operacion_division pasó\n");
    else
        printf("✘ test_devolver_operacion_division falló\n");
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
        printf("✔ test_existe_archivo_true pasó\n");
    else
        printf("✘ test_existe_archivo_true falló\n");

    remove(nombre);
    strdestruir(nombre);
}

void test_existe_archivo_false()
{
    String nombre = NULL;
    strcrear(nombre);
    strcop(nombre, "este_archivo_no_existe_12345.dat");

    if (ExisteArchivo(nombre) == FALSE)
        printf("✔ test_existe_archivo_false pasó\n");
    else
        printf("✘ test_existe_archivo_false falló\n");

    strdestruir(nombre);
}

void test_existe_archivo_null()
{
    // Caso de borde: pasar un NULL o string vacío
    String nombre = NULL;
    strcrear(nombre); // string vacío ""

    if (ExisteArchivo(nombre) == FALSE)
        printf("✔ test_existe_archivo_vacio pasó\n");
    else
        printf("✘ test_existe_archivo_vacio falló\n");

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
        printf("✘ FALLO: Error al guardar (%d)\n", err);
    }
    else
    {
        RecuperarExpresionDesdeArchivo(nombreBase, expRecuperada, err);

        if (err != ERR_NINGUNO)
        {
            printf("✘ FALLO: Error al recuperar (%d)\n", err);
        }
        else
        {
            if (ArbolesIdenticos(exp.terminos, expRecuperada.terminos) == TRUE)
                printf("✔ PASO: Expresion compleja recuperada correctamente\n");
            else
                printf("✘ FALLO: La expresion compleja NO coincide\n");

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

//--------------------------//
//     MODULO COMPILADOR    //
//--------------------------//

// ==========================
//        COMPUESTA
// ==========================

void test_validar_compuesta_ok()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1, e2;
    e1.indiceLista = 1;
    e1.terminos = CrearExpresionSimpleInt(5);

    e2.indiceLista = 2;
    e2.terminos = CrearExpresionSimpleInt(10);

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
        printf("✔ test_validar_compuesta_ok pasó\n");
    else
        printf("✘ test_validar_compuesta_ok falló\n");

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
    e1.terminos = CrearExpresionSimpleInt(5);

    e2.indiceLista = 2;
    e2.terminos = CrearExpresionSimpleInt(10);

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
        printf("✔ test_validar_compuesta_operador_invalido pasó\n");
    else
        printf("✘ test_validar_compuesta_operador_invalido falló\n");

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
    e1.terminos = CrearExpresionSimpleInt(5);
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
        printf("✔ test_validar_compuesta_primer_indice_no_existe pasó\n");
    else
        printf("✘ test_validar_compuesta_primer_indice_no_existe falló\n");

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
    e1.terminos = CrearExpresionSimpleInt(5);
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
        printf("✔ test_validar_compuesta_segundo_indice_no_existe pasó\n");
    else
        printf("✘ test_validar_compuesta_segundo_indice_no_existe falló\n");

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
    e1.terminos = CrearExpresionSimpleInt(5);
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
        printf("✔ test_validar_compuesta_primer_indice_negativo pasó\n");
    else
        printf("✘ test_validar_compuesta_primer_indice_negativo falló\n");

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
    e1.terminos = CrearExpresionSimpleInt(5);

    e2.indiceLista = 2;
    e2.terminos = CrearExpresionSimpleInt(10);

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
        printf("✔ test_validar_compuesta_segundo_indice_negativo pasó\n");
    else
        printf("✘ test_validar_compuesta_segundo_indice_negativo falló\n");

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
        printf("✔ test_validar_compuesta_cantidad_tokens_invalida pasó\n");
    else
        printf("✘ test_validar_compuesta_cantidad_tokens_invalida falló\n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

// ==========================
//         CALCULAR
// ==========================

void test_validar_calcular_ok()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e;
    e.indiceLista = 1;
    e.terminos = CrearExpresionSimpleInt(5);
    InsertarExpresionAlFinalL(l, e);

    String linea;
    strcrear(linea);
    strcop(linea, "7 1");

    TokenizarEntrada(lp, linea);

    int indice;
    CodigoError err;

    ValidarComandoCalcular(lp, l, indice, err);

    if (err == ERR_NINGUNO && indice == 1)
        printf("✔ test_validar_calcular_ok pasó\n");
    else
        printf("✘ test_validar_calcular_ok falló\n");

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
    e.terminos = CrearExpresionSimpleInt(5);
    InsertarExpresionAlFinalL(l, e);

    String linea;
    strcrear(linea);
    strcop(linea, "abc 1");

    TokenizarEntrada(lp, linea);

    int indice;
    CodigoError err;

    ValidarComandoCalcular(lp, l, indice, err);

    if (err == ERR_PARAMETRO_INVALIDO)
        printf("✔ test_validar_calcular_parametro_invalido pasó\n");
    else
        printf("✘ test_validar_calcular_parametro_invalido falló\n");

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
    e.terminos = CrearExpresionSimpleInt(5);
    InsertarExpresionAlFinalL(l, e);

    String linea;
    strcrear(linea);
    strcop(linea, "7 99");

    TokenizarEntrada(lp, linea);

    int indice;
    CodigoError err;

    ValidarComandoCalcular(lp, l, indice, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("✔ test_validar_calcular_indice_no_existe pasó\n");
    else
        printf("✘ test_validar_calcular_indice_no_existe falló\n");

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
    e.terminos = CrearExpresionSimpleInt(5);
    InsertarExpresionAlFinalL(l, e);

    String linea;
    strcrear(linea);
    strcop(linea, "7 -99");

    TokenizarEntrada(lp, linea);

    int indice;
    CodigoError err;

    ValidarComandoCalcular(lp, l, indice, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("✔ test_validar_calcular_indice_negativo pasó\n");
    else
        printf("✘ test_validar_calcular_indice_negativo falló\n");

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
    CodigoError err;

    ValidarComandoCalcular(lp, l, indice, err);

    if (err == ERR_CANT_PARAMETROS)
        printf("✔ test_validar_calcular_cantidad_parametros_invalidos pasó\n");
    else
        printf("✘ test_validar_calcular_cantidad_parametros_invalidos falló\n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

// ==========================
//          IGUALES
// ==========================

void test_validar_iguales_ok()
{
    ListaParsing lp = NULL;
    ListaExpresiones l = NULL;

    Expresion e1, e2;
    e1.indiceLista = 1;
    e1.terminos = CrearExpresionSimpleInt(5);
    e2.indiceLista = 2;
    e2.terminos = CrearExpresionSimpleInt(10);

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
        printf("✔ test_validar_iguales_ok pasó\n");
    else
        printf("✘ test_validar_iguales_ok falló\n");

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
    e1.terminos = CrearExpresionSimpleInt(5);
    InsertarExpresionAlFinalL(l, e1);

    String linea;
    strcrear(linea);
    strcop(linea, "99 1");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    CodigoError err;

    ValidarComandoIguales(lp, l, i1, i2, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("✔ test_validar_iguales_primer_indice_no_existe pasó\n");
    else
        printf("✘ test_validar_iguales_primer_indice_no_existe falló\n");

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
    e1.terminos = CrearExpresionSimpleInt(5);
    InsertarExpresionAlFinalL(l, e1);

    String linea;
    strcrear(linea);
    strcop(linea, "1 99");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    CodigoError err;

    ValidarComandoIguales(lp, l, i1, i2, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("✔ test_validar_iguales_segundo_indice_no_existe pasó\n");
    else
        printf("✘ test_validar_iguales_segundo_indice_no_existe falló\n");

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
    e1.terminos = CrearExpresionSimpleInt(5);
    InsertarExpresionAlFinalL(l, e1);

    String linea;
    strcrear(linea);
    strcop(linea, "-123 1");

    TokenizarEntrada(lp, linea);

    int i1, i2;
    CodigoError err;

    ValidarComandoIguales(lp, l, i1, i2, err);

    if (err == ERR_INDICE_INVALIDO)
        printf("✔ test_validar_iguales_primer_indice_negativo pasó\n");
    else
        printf("✘ test_validar_iguales_primer_indice_negativo falló\n");

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
    e1.terminos = CrearExpresionSimpleInt(5);
    e2.indiceLista = 2;
    e2.terminos = CrearExpresionSimpleInt(10);

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
        printf("✔ test_validar_iguales_segundo_indice_negativo pasó\n");
    else
        printf("✘ test_validar_iguales_segundo_indice_negativo falló\n");

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
        printf("✔ test_validar_iguales_cantidad_tokens_invalida pasó\n");
    else
        printf("✘ test_validar_iguales_cantidad_tokens_invalida falló\n");

    DestruirListaParsing(lp);
    strdestruir(linea);
}

int main()
{

    printf("---- Ejecutando tests CalcularABB ----\n\n");

    test_entero_simple();
    test_variable_x();
    test_suma_resta();
    test_multiplicacion_variable();
    test_expresion_compuesta();
    test_arboles_identicos();
    test_division();
    test_mostrar_abb();

    printf("\n---- Fin de tests CalcularABB ----\n");

    printf("---- Ejecutando tests String ----");
    test_strcrear();
    test_strdestruir();
    // casos strlar
    test_strlar_vacio();
    test_strlar_con_contenido();
    // casos strcop
    test_strcop_contenido();
    test_strcop_redimension();
    test_strcop_vacio_a_vacio();
    // print y scan
    test_print();
    test_scan_mock();
    // casos streq
    test_streq_identicos();
    test_streq_diferentes_caracter();
    test_streq_diferente_largo();
    // casos bajar
    test_bajar_string_basico();
    test_bajar_string_vacio();
    test_bajar_string_fin_archivo();
    // casos levantar
    test_levantar_string_basico();
    test_levantar_string_vacio();
    // casos crear desde rango
    test_crear_desde_rango_normal();
    test_crear_desde_rango_error();
    test_crear_desde_rango_un_char();
    // casos es alfabetico
    test_es_alfabetico_valido();
    test_es_alfabetico_con_numeros();
    test_es_alfabetico_casos_borde();
    // casos es entero
    test_es_entero_positivo();
    test_es_entero_negativo();
    test_es_entero_falla();
    test_convertir_a_entero();
    test_primer_caracter();
    test_es_operador_valido();
    test_strcon_supera_MAX();

    printf("\n---- Fin de tests String ----\n");

    printf("---- Ejecutando tests Operacion ----");

    test_operacion_default();
    test_devolver_operacion_suma();
    test_devolver_operacion_resta();
    test_devolver_operacion_division();
    test_devolver_operacion_multiplicacion();

    printf("\n---- Fin de tests Operacion ----\n");

    printf("\n---- Ejecutando tests ListaParsing ----\n\n");

    test_tokenizar_simple();
    test_token_en_posicion();
    test_cantidad_tokens();
    test_espacios_multiples();

    printf("\n---- Fin de tests ----\n");

    printf("\n---- Ejecutando tests CodigoError ----\n\n");

    test_mostrar_error();

    printf("\n---- Fin de tests ----\n");

    printf("\n---- Ejecutando tests Expresion ----\n\n");

    test_obtener_indice_expresion();
    test_mostrar_expresion_simple();
    test_destruir_expresion_simple();
    test_destruir_expresion_compuesta();

    printf("\n---- Fin de tests ----\n");

    printf("\n---- Ejecutando tests ListaExpresiones ----\n\n");

    test_insertar_en_lista_vacia();
    test_insertar_dos_expresiones();
    test_insertar_en_lista_con_multiples_nodos();
    test_buscar_expresion_por_indice();
    test_es_indice_valido_true();
    test_es_indice_valido_false();
    test_mostrar_expresiones();
    test_destruir_lista();

    printf("\n---- Fin de tests ----\n");

    printf("\n---- Ejecutando tests Archivo ----\n\n");

    test_existe_archivo_true();
    test_existe_archivo_false();
    test_existe_archivo_null();

    test_guardar_recuperar_expresion_archivo_ok();
    test_Recuperar_Archivo_NoExiste();
    test_Guardar_Archivo_NoSePuedeAbrir();

    printf("\n---- Fin de tests ----\n");

    printf("\n========== INICIO TESTS MODULO COMPILADOR ==========\n\n");

    // =====================
    // COMPUESTA
    // =====================
    test_validar_compuesta_ok();
    test_validar_compuesta_operador_invalido();
    test_validar_compuesta_primer_indice_no_existe();
    test_validar_compuesta_segundo_indice_no_existe();
    test_validar_compuesta_primer_indice_negativo();
    test_validar_compuesta_segundo_indice_negativo();
    test_validar_compuesta_cantidad_tokens_invalida();

    // =====================
    // CALCULAR
    // =====================
    test_validar_calcular_ok();
    test_validar_calcular_parametro_invalido();
    test_validar_calcular_indice_no_existe();
    test_validar_calcular_indice_negativo();
    test_validar_calcular_cantidad_parametros_invalidos();

    // =====================
    // IGUALES
    // =====================
    test_validar_iguales_ok();
    test_validar_iguales_primer_indice_no_existe();
    test_validar_iguales_segundo_indice_no_existe();
    test_validar_iguales_primer_indice_negativo();
    test_validar_iguales_segundo_indice_negativo();
    test_validar_iguales_cantidad_tokens_invalida();

    printf("\n========== FIN TESTS MODULO COMPILADOR ==========\n");

    return 0;
}