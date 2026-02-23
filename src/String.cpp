#include "String.h"
void strcrear(String &s)
{
    s = new char[1];
    s[0] = '\0';
}
void strdestruir(String &s)
{
    delete [] s;
    s = NULL;
}
int strlar(String s)
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}
void strcop(String &s1,String s2)
{
    int i = 0;
    int largo = strlar(s2) + 1;
    delete [] s1;
    s1 = new char[largo];
    while (s2[i] != '\0')
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}
void scan(String &s)
{
    String aux = new char[MAX];
    int i=0;
    char c;
    //fflush (stdin);
    scanf ("%c", &c);
    while ((c!= '\n' && i < MAX-1))
    {
        aux[i] = c;
        i++;
        scanf ("%c", &c);
    }
    aux[i] = '\0';
    strcop (s,aux);
    strdestruir (aux);
}
void strcon(String &s1,String s2)
{
    String aux;
    strcrear (aux);
    strcop (aux, s1);
    int largo = strlar (s1) + strlar (s2) + 1;
    if (largo > MAX)
        largo = MAX;
    delete [] s1;
    s1 = new char[largo];
    int i = 0;
    while (aux[i] != '\0')
    {
        s1[i] = aux[i];
        i++;
    }
    int j = 0;
    while (s2[j] != '\0' && i < MAX-1)
    {
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i] = '\0';
    strdestruir (aux);
}
void strswp(String &s1, String &s2)
{
    String aux;
    aux = s1;
    s1 = s2;
    s2 = aux;
}
void print(String s)
{
    int i = 0;
    while(s[i]!= '\0')
    {
        printf ("%c", s[i]);
        i++;
    }
}
Boolean strmen(String s1, String s2)
{
    int i = 0;
    Boolean encontre = FALSE;
    Boolean menor = FALSE;
    while ((!encontre) && (s1[i] != '\0') && (s2[i] != '\0'))
    {
        if (s1[i] != s2[i])
            encontre = TRUE;
        if (s1[i] < s2[i])
            menor = TRUE;
        i++;
    }
    if ((!encontre) && (s2[i]!='\0'))
        menor = TRUE;
    return menor;
}
Boolean streq(String s1,String s2)
{
    int i = 0;
    Boolean iguales = TRUE;
    while (iguales && (s1[i] != '\0') && (s2[i] != '\0'))
    {
        if (s1[i] != s2[i])
            iguales = FALSE;
        i++;
    }
    if ((s1[i] != '\0') || (s2[i] != '\0'))
        iguales = FALSE;
    return iguales;
}

void Bajar_String(String s, FILE * f)
{
    int i=0;
    while (s[i] != '\0')
    {
        fwrite (&s[i], sizeof(char), 1, f);
        i++;
    }
// escribo el '\0'
    fwrite (&s[i], sizeof(char), 1, f);
}

void Levantar_String(String &s, FILE * f)
{
    int i=0;
    String aux;
    aux = new char[MAX];
    fread (&aux[i], sizeof(char), 1, f);
    while (!feof(f) && (aux[i] != '\0'))
    {
        i++;
        fread (&aux[i], sizeof(char), 1, f);
    }
    if (feof(f))
        aux[i] = '\0';
    strcop (s, aux);
    delete [] aux;
}


void CrearStringDesdeRango(String linea, int inicio, int fin, String &resultado){

    int longitud = 0, i=inicio, j=0; 

    if (inicio<=fin){

        longitud = (inicio-fin) + 1;

        strcrear(resultado);
    }
    
    while (linea[i] != '\0' && inicio<=fin)
    {
        resultado[j] = linea[i];
        i++;
        j++;
    }
    resultado[j] = '\0';
    
}

Boolean EsAlfabetico(String s){
    Boolean esLetra = TRUE;
    int i = 0;

    if (s==NULL || s == ''){
        esLetra=FALSE;
    }

    if(esLetra){
        while (s[i] != '\0' && esLetra){
            if(!(s[i]>='A' && s[i]<='Z' || s[i]>='a' && s[i]<='z')){
                esLetra=FALSE;   
            }else{
                i++;
            }
        }
    }

    return esLetra;
}

Boolean EsOperadorValido(String token){
    Boolean esValido = FALSE;
    int largo = 0;

    largo = strlar(token);

    if( token != NULL && largo == 1){
        if(token == '+' || token == '-' || token == '*' || token == '/'){
            esValido = TRUE;
        }
    }
    
    return esValido;
}

// REVISAR / NO ESTABA DENTRO DE LOS PSEUDOCODIGOS
Boolean EsEnteroValido(String token);

Boolean EsEntero(String s){
    Boolean esEntero = TRUE;
    int i = 0;

    if (s==NULL || s == ''){
        esEntero=FALSE;
    }

    if(esEntero){
        if(s[i] != '-' &&  !(s[i]>='0' && s[i]<='9')){
            esEntero= FALSE;
        }else{
            i++;
        }

        while (s[i] != '\0' && esEntero){
            if(!(s[i]>='0' && s[i]<='9')){

                esEntero=FALSE;   
                
            }else{
                i++;
            }
        }
    }

    return esEntero;
}

// Detecta si el string es un número entero positivo.
Boolean EsEnteroPositivo(String s){

    Boolean esEntero = TRUE;
    int i = 0;

    if (s==NULL || s == ''){
        esEntero=FALSE;
    }

    if(esEntero){

        while (s[i] != '\0' && esEntero){
            if(!(s[i]>='0' && s[i]<='9')){

                esEntero=FALSE;   
                
            }else{
                i++;
            }

        }
    }
    return esEntero;

}

int ConvertirAEntero(String s){
    int i = 0,  resultado = 0, potencia = 1;

    i = strlar(s-1);

    for(i; i>=0; i--){
        resultado += s[i] * potencia;
        potencia = potencia * 10;

    }

    return resultado;
}


 char PrimerCaracter(String s){    
    return s[0];
 }

