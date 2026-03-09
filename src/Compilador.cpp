#include "Compilador.h"

void LoopPrincipal()
{

    String linea;
    strcrear(linea);
    ListaExpresiones expresiones = NULL;
    ListaParsing tokens = NULL;
    TipoComando tipo=SIMPLE;
    CodigoError error;

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
        DestruirListaParsing(tokens);
        tokens = NULL;
        error = ERR_NINGUNO;
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

    Simple = new char[7];
    Simple[0] = 's';
    Simple[1] = 'i';
    Simple[2] = 'm';
    Simple[3] = 'p';
    Simple[4] = 'l';
    Simple[5] = 'e';
    Simple[6] = '\0';

    Compuesta = new char[10];
    Compuesta[0] = 'c';
    Compuesta[1] = 'o';
    Compuesta[2] = 'm';
    Compuesta[3] = 'p';
    Compuesta[4] = 'u';
    Compuesta[5] = 'e';
    Compuesta[6] = 's';
    Compuesta[7] = 't';
    Compuesta[8] = 'a';
    Compuesta[9] = '\0';

    Calcular = new char[9];
    Calcular[0] = 'c';
    Calcular[1] = 'a';
    Calcular[2] = 'l';
    Calcular[3] = 'c';
    Calcular[4] = 'u';
    Calcular[5] = 'l';
    Calcular[6] = 'a';
    Calcular[7] = 'r';
    Calcular[8] = '\0';

    Mostrar = new char[8];
    Mostrar[0] = 'm';
    Mostrar[1] = 'o';
    Mostrar[2] = 's';
    Mostrar[3] = 't';
    Mostrar[4] = 'r';
    Mostrar[5] = 'a';
    Mostrar[6] = 'r';
    Mostrar[7] = '\0';

    Guardar = new char[8];
    Guardar[0] = 'g';
    Guardar[1] = 'u';
    Guardar[2] = 'a';
    Guardar[3] = 'r';
    Guardar[4] = 'd';
    Guardar[5] = 'a';
    Guardar[6] = 'r';
    Guardar[7] = '\0';

    Recuperar = new char[10];
    Recuperar[0] = 'r';
    Recuperar[1] = 'e';
    Recuperar[2] = 'c';
    Recuperar[3] = 'u';
    Recuperar[4] = 'p';
    Recuperar[5] = 'e';
    Recuperar[6] = 'r';
    Recuperar[7] = 'a';
    Recuperar[8] = 'r';
    Recuperar[9] = '\0';

    Iguales = new char[8];
    Iguales[0] = 'i';
    Iguales[1] = 'g';
    Iguales[2] = 'u';
    Iguales[3] = 'a';
    Iguales[4] = 'l';
    Iguales[5] = 'e';
    Iguales[6] = 's';
    Iguales[7] = '\0';

    Salir = new char[6];
    Salir[0] = 's';
    Salir[1] = 'a';
    Salir[2] = 'l';
    Salir[3] = 'i';
    Salir[4] = 'r';
    Salir[5] = '\0';

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
        String X = new char[2];
        X[0] = 'x';
        X[1] = '\0';

        if (streq(tokens->palabra, X))
            esX = TRUE;
        else
        {
            if (EsEntero(tokens->palabra))
                num = ConvertirAEntero(tokens->palabra);
            else
                error = ERR_PARAMETRO_INVALIDO;
        }
        strdestruir(X);
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
    case SALIR:
        printf("Hasta la vista, baby! \n");
        break;
    }
}