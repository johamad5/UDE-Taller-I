#include "Archivo.h"

Boolean ExisteArchivo(String nombreArchivo)
{
    Boolean existe = FALSE;

    String nombreCompleto;
    strcrear(nombreCompleto);
    strcop(nombreCompleto, nombreArchivo);

    String extension;
    extension = new char[5];
    extension[0] = '.';
    extension[1] = 't';
    extension[2] = 'x';
    extension[3] = 't';
    extension[4] = '\0';
    strcon(nombreCompleto, extension);

    FILE *f = fopen(nombreCompleto, "rb");

    if (f != NULL)
    {
        existe = TRUE;
        fclose(f);
    }

    strdestruir(extension);
    strdestruir(nombreCompleto);

    return existe;
}

void GuardarExpresionEnArchivo(ListaExpresiones lp, String nombreArchivo, int idx)
{
    FILE *arch = NULL;

    String nombreCompleto;
    strcrear(nombreCompleto);
    strcop(nombreCompleto, nombreArchivo);

    String extension;
    extension = new char[5];
    extension[0] = '.';
    extension[1] = 't';
    extension[2] = 'x';
    extension[3] = 't';
    extension[4] = '\0';

    strcon(nombreCompleto, extension);

    arch = fopen(nombreCompleto, "wb");

    if (arch != NULL)
    {
        BajarExpresionEnLista(lp, idx, arch);
        fclose(arch);
    }

    strdestruir(extension);
    strdestruir(nombreCompleto);
}

void RecuperarInsertarExpresionDesdeArchivo(String nombreArchivo, ListaExpresiones &lp)
{
    FILE *arch = NULL;

    String nombreCompleto;
    strcrear(nombreCompleto);
    strcop(nombreCompleto, nombreArchivo);

    String extension;
    extension = new char[5];
    extension[0] = '.';
    extension[1] = 't';
    extension[2] = 'x';
    extension[3] = 't';
    extension[4] = '\0';

    strcon(nombreCompleto, extension);

    arch = fopen(nombreCompleto, "rb");

    LevantarInsertarExpresion(lp, arch);
    fclose(arch);

    remove(nombreCompleto);

    strdestruir(extension);
    strdestruir(nombreCompleto);
}