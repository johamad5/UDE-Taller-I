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

void GuardarExpresionEnArchivo(ListaExpresiones lp, String nombreArchivo, int idx)
{
    FILE *arch = NULL;
    String nombreCompleto;
    strcrear(nombreCompleto);

    strcop(nombreCompleto, nombreArchivo);
    strcon(nombreCompleto, ".txt");

    arch = fopen(nombreCompleto, "wb");

    if (arch != NULL)
    {
        BajarExpresionEnLista(lp, idx, arch);
        fclose(arch);
    }

    strdestruir(nombreCompleto);
}

void RecuperarInsertarExpresionDesdeArchivo(String nombreArchivo, ListaExpresiones lp)
{
    FILE *arch = NULL;
    String nombreCompleto;
    strcrear(nombreCompleto);

    strcop(nombreCompleto, nombreArchivo);
    strcon(nombreCompleto, ".txt");

    arch = fopen(nombreCompleto, "rb");

    LevantarInsertarExpresion(lp, arch);
    fclose(arch);
    remove(nombreCompleto);

    strdestruir(nombreCompleto);
}