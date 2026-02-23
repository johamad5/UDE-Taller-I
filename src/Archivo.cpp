#include "Archivo.h"

Boolean Existe(String nomArch)
{
    Boolean existeArchivo = TRUE;
    FILE * f = fopen (nomArch, "rb");
    if (f == NULL)
        existeArchivo = FALSE;
    else
        fclose (f);
    return existeArchivo;
}

void LevantarAlumnos(ABB &a, String nomArch)
{
    FILE * f = fopen (nomArch, "rb");
    Alumno buffer;
    strcrear(buffer.nombre);
    strcrear(buffer.apellido);
    strcrear(buffer.direccion);
    strcrear(buffer.telefono);
    LevantarAlumno(buffer, f);
    while (!feof(f))
    {
        AgregarAlumno(a, buffer);
        LevantarAlumno(buffer, f);
    }
    fclose (f);
}

void RespaldarAlumnos_Aux(ABB a, FILE * f)
{
    if(a != NULL)
    {
        BajarAlumno(a -> info,f);
        RespaldarAlumnos_Aux (a -> hizq, f);
        RespaldarAlumnos_Aux (a -> hder, f);
    }
}

void RespaldarAlumnos(ABB a, String nomArch)
{

    FILE * f = fopen (nomArch, "wb");
    RespaldarAlumnos_Aux (a, f);
    fclose (f);

}

void LevantarTalleresFinalizados(Lista &l, String nomArch)
{

    FILE * f = fopen (nomArch, "rb");
    RegistroTaller buffer;
    Crear(l);
    LevantaRegistroTaller(buffer, f);
    while(!feof(f))
    {
        InsertarUltimo(l, buffer);
        LevantaRegistroTaller(buffer, f);
    }
    fclose (f);
}

void RespaldarTalleresFinalizados(Lista l, String nomArch)
{
    FILE * f = fopen (nomArch, "wb");
    while(l != NULL)
    {
        BajarRegistroTaller(l -> info, f);
        l = l -> sig;
    }
    fclose (f);
}


