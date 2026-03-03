#include "Archivo.h"

Boolean ExisteArchivo(String nombreArchivo)
{
    Boolean existe = FALSE;
    FILE *f = fopen(nombreArchivo, "rb");
    if (f != NULL)
    {
        existe = TRUE;
        fclose(f);
    }
    return existe;
}

void GuardarExpresionEnArchivo(String nombreArchivo, Expresion exp, CodigoError &err)
{
    FILE *arch = NULL;
    String nombreCompleto;
    strcrear(nombreCompleto);
    err = ERR_NINGUNO;

    if (err == ERR_NINGUNO)
    {
        strcop(nombreCompleto, nombreArchivo);
        strcon(nombreCompleto, ".txt");
    }

    if (err == ERR_NINGUNO)
    {
        arch = fopen(nombreCompleto, "wb");
        if (arch == NULL)
        {
            err = ERR_ARCHIVO_NO_SE_PUEDE_ABRIR;
        }
    }

    if (err == ERR_NINGUNO)
    {
        BajarExpresion(exp, arch);
        fclose(arch);
    }

    strdestruir(nombreCompleto);
}

void RecuperarExpresionDesdeArchivo(String nombreArchivo, Expresion &exp, CodigoError &err)
{
    FILE *arch = NULL;
    String nombreCompleto;
    strcrear(nombreCompleto);
    err = ERR_NINGUNO;

    strcop(nombreCompleto, nombreArchivo);
    strcon(nombreCompleto, ".txt");

    arch = fopen(nombreCompleto, "rb");

    if (arch == NULL)
    {
        err = ERR_ARCHIVO_NO_EXISTE;
    }
    else
    {
        LevantarExpresion(exp, arch);
        fclose(arch);
    }
    strdestruir(nombreCompleto);
}