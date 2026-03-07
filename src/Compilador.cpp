#include "Compilador.h"

void LoopPrincipal()
{

    String linea;
    strcrear(linea);
    ListaExpresiones expresiones = NULL;
    ListaParsing tokens = NULL;
    TipoComando tipo;
    CodigoError error = ERR_NINGUNO;

    Boolean esX;
    int num;
    int idx1;
    int idx2;
    int valorX;
    Operacion operador;
    String nombreArchivo;
    strcrear(nombreArchivo);

    expresiones = NULL;

    while (tipo != SALIR)
    {

        printf("Ingrese el comando: ");
        scan(linea);

        TokenizarEntrada(tokens, linea);

        ReconocerYValidarComando(tokens, expresiones,
                                 tipo, esX, num, idx1, operador, idx2, valorX, nombreArchivo, error);

        if (error != ERR_NINGUNO)
        {
            MostrarError(error);
        }
        else
        {
            EjecutarComando(tipo, esX, num, idx1, operador,
                            idx2, nombreArchivo, expresiones,
                            error);

            if (error != ERR_NINGUNO)
                MostrarError(error);
        }
    }

    DestruirListaParsing(tokens);
    DestruirListaExpresiones(expresiones);
    strdestruir(linea);
    strdestruir(nombreArchivo);
}

void ReconocerYValidarComando(ListaParsing tokens, ListaExpresiones expresiones, TipoComando &tipoComando, Boolean &esX, int &num,
                              int &idx1, Operacion &operador, int &idx2, int &valorX, String &nombreArchivo, CodigoError &codigoError)
{
    ReconocerComando(tokens->palabra, tipoComando, codigoError);

    if (codigoError == ERR_NINGUNO)
    {
        switch (tipoComando)
        {
        case SIMPLE:
            ValidarComandoSimple(tokens->sig, esX, num, codigoError);
            break;
        case COMPUESTA:
            ValidarComandoCompuesta(tokens->sig, expresiones, idx1, idx2, operador, codigoError);
            break;
        case CALCULAR:
            ValidarComandoCalcular(tokens->sig, expresiones, num, idx1, codigoError);
            break;
        case MOSTRAR:
            codigoError = ValidarComandoMostrar(tokens->sig, expresiones);
            break;
        case IGUALES:
            ValidarComandoIguales(tokens->sig, expresiones, idx1, idx2, codigoError);
            break;
        case GUARDAR:
            ValidarComandoGuardar(tokens->sig, expresiones, idx1, nombreArchivo, codigoError);
            break;
        case RECUPERAR:
            ValidarComandoRecuperar(tokens->sig, nombreArchivo, codigoError);
            break;
        case SALIR:
            codigoError = ValidarComandoSalir(tokens->sig);
            break;
        }
    }
}

void ReconocerComando(String cmd, TipoComando &tipoComando, CodigoError &codigoError)
{
    codigoError = ERR_NINGUNO;

    String Simple, Compuesta, Calcular, Mostrar, Guardar, Recuperar, Iguales, Salir;

    strcrear(Simple);
    strcrear(Compuesta);
    strcrear(Calcular);
    strcrear(Mostrar);
    strcrear(Guardar);
    strcrear(Recuperar);
    strcrear(Iguales);
    strcrear(Salir);

    strcop(Simple, "simple");
    strcop(Compuesta, "compuesta");
    strcop(Calcular, "calcular");
    strcop(Mostrar, "mostrar");
    strcop(Guardar, "guardar");
    strcop(Recuperar, "recuperar");
    strcop(Iguales, "iguales");
    strcop(Salir, "salir");

    if (streq(cmd, Simple))
    {
        tipoComando = SIMPLE;
    }
    else if (streq(cmd, Compuesta))
    {
        tipoComando = COMPUESTA;
    }
    else if (streq(cmd, Calcular))
    {
        tipoComando = CALCULAR;
    }
    else if (streq(cmd, Mostrar))
    {
        tipoComando = MOSTRAR;
    }
    else if (streq(cmd, Guardar))
    {
        tipoComando = GUARDAR;
    }
    else if (streq(cmd, Recuperar))
    {
        tipoComando = RECUPERAR;
    }
    else if (streq(cmd, Iguales))
    {
        tipoComando = IGUALES;
    }
    else if (streq(cmd, Salir))
    {
        tipoComando = SALIR;
    }
    else
    {
        codigoError = ERR_COMANDO_INVALIDO;
    }

    strdestruir(Simple);
    strdestruir(Compuesta);
    strdestruir(Calcular);
    strdestruir(Mostrar);
    strdestruir(Guardar);
    strdestruir(Recuperar);
    strdestruir(Iguales);
    strdestruir(Salir);
}

void ValidarComandoSimple(ListaParsing tokens, Boolean &esX, int &num, CodigoError &error)
{
    esX = FALSE;
    num = 0;
    error = ERR_NINGUNO;

    if (CantidadTokens(tokens) != TOKENS_SIMPLE)
        error = ERR_CANT_PARAMETROS;
    else if (tokens != NULL && error == ERR_NINGUNO)
    {
        if (streq(tokens->palabra, "x"))
            esX = TRUE;
        else
        {
            if (EsEntero(tokens->palabra))
                num = ConvertirAEntero(tokens->palabra);
            else
                error = ERR_PARAMETRO_INVALIDO;
        }
    }
}

void ValidarComandoCompuesta(ListaParsing tokens, ListaExpresiones expresiones, int &indiceUno, int &indiceDos, Operacion &operacion, CodigoError &codigoError)
{
    codigoError = ERR_NINGUNO;
    indiceUno = 0;
    indiceDos = 0;

    if (CantidadTokens(tokens) != TOKENS_COMPUESTA)
        codigoError = ERR_CANT_PARAMETROS;
    else
    {
        int i = 1;
        while (tokens != NULL && codigoError == ERR_NINGUNO)
        {
            switch (i)
            {
            case POSICION_TOKEN_PRIMER_INDICE_COMPUESTA:
                if (!EsEnteroPositivo(tokens->palabra))
                    codigoError = ERR_INDICE_INVALIDO;
                else
                {
                    indiceUno = ConvertirAEntero(tokens->palabra);
                    if (!EsIndiceValido(expresiones, indiceUno))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            case POSICION_TOKEN_OPERADOR_COMPUESTA:
                if (!EsOperadorValido(tokens->palabra))
                    codigoError = ERR_OPERADOR_INVALIDO;
                else
                    operacion = DevolverOperacion(PrimerCaracter(tokens->palabra));
                break;

            case POSICION_TOKEN_SEGUNDO_INDICE_COMPUESTA:
                if (!EsEnteroPositivo(tokens->palabra))
                    codigoError = ERR_INDICE_INVALIDO;
                else
                {
                    indiceDos = ConvertirAEntero(tokens->palabra);
                    if (!EsIndiceValido(expresiones, indiceDos))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            }

            tokens = tokens->sig;
            i++;
        }
    }
}

void ValidarComandoCalcular(ListaParsing tokens, ListaExpresiones expresiones, int &valor, int &indice, CodigoError &codigoError)
{
    codigoError = ERR_NINGUNO;
    indice = 0;

    if (CantidadTokens(tokens) != TOKENS_CALCULAR)
        codigoError = ERR_CANT_PARAMETROS;
    else
    {
        int i = 1;
        while (tokens != NULL && codigoError == ERR_NINGUNO)
        {
            switch (i)
            {
            case POSICION_TOKEN_INDICE_CALCULO:
                if (!EsEnteroPositivo(tokens->palabra))
                    codigoError = ERR_INDICE_INVALIDO;
                else
                {
                    indice = ConvertirAEntero(tokens->palabra);
                    if (!EsIndiceValido(expresiones, indice))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            case POSICION_TOKEN_INDICE_VARIABLE:
                if (!EsEntero(tokens->palabra))
                    codigoError = ERR_PARAMETRO_INVALIDO;
                else
                    valor = ConvertirAEntero(tokens->palabra);
                break;
            }

            tokens = tokens->sig;
            i++;
        }
    }
}

void ValidarComandoIguales(ListaParsing tokens, ListaExpresiones expresiones, int &indiceUno, int &indiceDos, CodigoError &codigoError)
{
    codigoError = ERR_NINGUNO;
    indiceUno = 0;
    indiceDos = 0;

    if (CantidadTokens(tokens) != TOKENS_IGUALES)
        codigoError = ERR_CANT_PARAMETROS;
    else
    {
        int i = 1;
        while (tokens != NULL && codigoError == ERR_NINGUNO)
        {
            switch (i)
            {
            case POSICION_TOKEN_PRIMER_INDICE_IGUALES:
                if (!EsEnteroPositivo(tokens->palabra))
                    codigoError = ERR_INDICE_INVALIDO;
                else
                {
                    indiceUno = ConvertirAEntero(tokens->palabra);
                    if (!EsIndiceValido(expresiones, indiceUno))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            case POSICION_TOKEN_SEGUNDO_INDICE_IGUALES:
                if (!EsEnteroPositivo(tokens->palabra))
                    codigoError = ERR_INDICE_INVALIDO;
                else
                {
                    indiceDos = ConvertirAEntero(tokens->palabra);
                    if (!EsIndiceValido(expresiones, indiceDos))
                        codigoError = ERR_INDICE_INVALIDO;
                }
                break;
            }

            tokens = tokens->sig;
            i++;
        }
    }
}

CodigoError ValidarComandoMostrar(ListaParsing tokens, ListaExpresiones expresiones)
{
    CodigoError err = ERR_NINGUNO;

    if (CantidadTokens(tokens) != MOSTRAR_CANT_TOKENS)
    {

        err = ERR_CANT_PARAMETROS;
    }
    else
    {
        if (expresiones == NULL)
            err = ERR_LISTA_VACIA;
    }
    return err;
}

void ValidarComandoGuardar(ListaParsing tokens, ListaExpresiones expresiones,
                           int &indice, String &nombreArchivo, CodigoError &error)
{

    error = ERR_NINGUNO;
    if (CantidadTokens(tokens) != TOKENS_GUARDAR)
        error = ERR_CANT_PARAMETROS;
    else
    {
        int i = 1;
        while (tokens != NULL && error == ERR_NINGUNO)
        {
            switch (i)
            {
            case POSICION_TOKEN_INDICE_GUARDAR:
                if (!EsEnteroPositivo(tokens->palabra))
                    error = ERR_INDICE_INVALIDO;
                else
                {
                    indice = ConvertirAEntero(tokens->palabra);
                    if (!EsIndiceValido(expresiones, indice))
                        error = ERR_INDICE_INVALIDO;
                }
                break;
            case POSICION_TOKEN_NOMBRE_ARCHIVO_GUARDAR:
                if (!EsAlfabetico(tokens->palabra))
                    error = ERR_NOMBRE_ARCHIVO_INVALIDO;
                else if (ExisteArchivo(tokens->palabra))
                    error = ERR_ARCHIVO_EXISTE;
                else
                {
                    strcop(nombreArchivo, tokens->palabra);
                }
                break;
            }

            tokens = tokens->sig;
            i++;
        }
    }
}

void ValidarComandoRecuperar(ListaParsing tokens, String &nombreArchivo, CodigoError &err)
{
    err = ERR_NINGUNO;

    if (CantidadTokens(tokens) != RECUPERAR_CANT_TOKENS)
        err = ERR_CANT_PARAMETROS;
    else
    {
        if (!EsAlfabetico(tokens->palabra))
        {
            err = ERR_ARCHIVO_INVALIDO;
        }
        else if (!ExisteArchivo(tokens->palabra))
        {
            err = ERR_ARCHIVO_NO_EXISTE;
        }
        else
        {
            strcop(nombreArchivo, tokens->palabra);
        }
    }
}

CodigoError ValidarComandoSalir(ListaParsing tokens)
{
    CodigoError err = ERR_NINGUNO;

    if (CantidadTokens(tokens) != SALIR_CANT_TOKENS)
        err = ERR_CANT_PARAMETROS;

    return err;
}

void EjecutarComando(TipoComando tipo, Boolean esX, int num, int idx1, Operacion op, int idx2, String nombreArchivo,
                     ListaExpresiones &lp, CodigoError &err)
{
    Expresion exp;
    Boolean errDiv = FALSE;
    int resultado;

    switch (tipo)
    {
    case SIMPLE:

        CrearInsertarExpresionSimple(lp, esX, num);
        printf("\n\n");

        break;
    case COMPUESTA:

        CrearInsertarExpresionCompuesta(lp, op, idx1, idx2);
        printf("\n\n");

        break;
    case CALCULAR:
        CalcularExpresionPorIndice(lp, idx1, num, errDiv, resultado);
        if (errDiv)
            err = ERR_DIVISION_POR_CERO;
        else
            printf("RESULTADO: %d", resultado);
        printf("\n\n");
        break;
    case MOSTRAR:
        MostrarExpresiones(lp);
        printf("\n\n");
        break;
    case RECUPERAR:

        RecuperarInsertarExpresionDesdeArchivo(nombreArchivo, lp);
        printf("\n\n");

        break;
    case GUARDAR:

        GuardarExpresionEnArchivo(lp, nombreArchivo, idx1);
        printf("\n\n");

        break;
    case IGUALES:
        CompararExpresionesPorIndice(lp, idx1, idx2);
        printf("\n\n");
        break;
    }
}