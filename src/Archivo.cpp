#include "Archivo.h"

Boolean ExisteArchivo(String nombreArchivo)
{
    Boolean existe = FALSE;

    String nombreCompleto;
    strcrear(nombreCompleto);
    strcop(nombreCompleto, nombreArchivo);
    strcon(nombreCompleto, ".txt");

    FILE *f = fopen(nombreCompleto, "rb");

    if (f != NULL)
    {
        existe = TRUE;
        fclose(f);
    }

    strdestruir(nombreCompleto);
    return existe;
}

void GuardarExpresionEnArchivo(String nombreArchivo, Expresion exp)
{
    FILE *arch = NULL;
    String nombreCompleto;
    strcrear(nombreCompleto);

    strcop(nombreCompleto, nombreArchivo);
    strcon(nombreCompleto, ".txt");

    arch = fopen(nombreCompleto, "wb");

    if (arch != NULL)
    {
        BajarExpresion(exp, arch);
        fclose(arch);
    }

    strdestruir(nombreCompleto);
}

Expresion RecuperarExpresionDesdeArchivo(String nombreArchivo)
{
    Expresion exp;

    FILE *arch = NULL;
    String nombreCompleto;
    strcrear(nombreCompleto);

    strcop(nombreCompleto, nombreArchivo);
    strcon(nombreCompleto, ".txt");

    arch = fopen(nombreCompleto, "rb");

    LevantarExpresion(exp, arch);
    fclose(arch);
    remove(nombreCompleto);

    strdestruir(nombreCompleto);
    return exp;
}