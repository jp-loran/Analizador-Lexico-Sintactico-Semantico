%{
/*
Autores: Juan Pablo Alvarez Loran
         Carlos Tovar Herrera
Descripción: Este programa reconoce las clases de componentes léxicos definidos dentro de la clase.
             Los resultados se almacenan en distintos archivos de salida.
Fecha de elaboración: 25 de Octubre de 2020
Fecha de entrega: 29 de Octubre de 2020
Instrucciones de ejecucion
        $flex analizador.l
        $gcc lex.yy.c -lfl
        $./a.out nombre_archivo.txt  
*/
#include "producPrueba.h"

FILE *archSal, *archTablas, *archTokens, *archError;
FILE *archAtomos;

int valor;
int obtenerASCII(char *caracter);

//Estructura para definir Palabras reservadas {valor palabra}
struct palabraS{
    char palabra[10]; //Palabra
    int valor;        //Valor
    char atomo[2];     //atomo

} palabraRes[17] = {
                    {"bool",0,"b"},{"break",1,"q"},{"case",2,"k"},{"char",3,"c"},
                    {"continue",4,"t"},{"default",5,"d"},{"do",6,"h"},{"else",7,"l"},
                    {"float",8,"f"},{"for",9,"p"},{"if",10,"i"},{"int",11,"n"},
                    {"return",12,"u"},{"string",13,"g"},{"switch",14,"x"},{"while",15,"w"},
                    {"void",16,"o"}
                   };
				   
//Estructura para definir Operadores relacionales {valor,operador}
struct opRelacional {
    char operador[2]; //Operador 
    int valor;        //Valor
    char atomo[2];     //atomo
} operadorRel[6] = {{"!=",0,"!"},{"==",1,"?"},{">",2,">"},{"<",3,"<"},{">=",4,"y"},{"<=",5,"m"}};

//Estructura para definir operadores aritmeticos {indice,simbolo,valor}
struct opAritmetico {
    int indice;
    char simbolo[2];    //Operador 
    char atomo[2];        //Valor
} operadorArit[5] = {{0,"+","+"},{1,"-","-"},{2,"*","*"},
                    {3,"/","/"},{4,"%","%"}
                  };

//Estructura para definir Caracteres Especiales {operador valor}
struct opEspecial {
    char *operador; //Operador
    int valor;        //Valor 
} caracterEsp[8] = {{"{",123},{"}",125},{",",44},
                    {":",58},{"(",40},{")",41},
                    {"[",91} ,{"]",93}
                   };


/*La tabla se símbolos se manejará como una lista ligada
cada nodo de la lista es una estructura con los campos requeridos*/
int posicion=0;
typedef struct tablaSimbolos{
    int pos;
    char* nombre;
    int tipo;
    struct tablaSimbolos* siguienteRegistro;
}tablaSimbolos;

typedef struct{
    struct tablaSimbolos* primerRegistro;
}listaSimbolos;

/*Con esta función inicializamos nuestra tabla de símbolos*/
listaSimbolos crear_tabla_simbolos(){
    listaSimbolos lista;
    lista.primerRegistro=NULL;
    return lista;
}

/*Esta función nos permite mostrar el contenido de nuestra lista ligada o tabla de símbolos
 dentro del archivo de salida que se le pase como parámetro*/
void mostrar_tabla_simbolos(FILE *archivo,listaSimbolos lista){
    if(lista.primerRegistro==NULL)
        fprintf(archivo,"Tabla de simbolos vacia");
    else{
        tablaSimbolos *actual=lista.primerRegistro;
        fprintf(archivo," TABLA DE SIMBOLOS\n");
        fprintf(archivo," _________________________________________\n");
	    fprintf(archivo,"|Posicion|     Nombre      |     Tipo    | \n");
        fprintf(archivo," -----------------------------------------\n");
        while(actual !=0){
            fprintf(archivo,"\t%d \t\t%s\t\t%d \n",actual->pos,actual->nombre,actual->tipo);
            actual=actual->siguienteRegistro;
        }
    }
}

/*Esta función permite buscar un registro por su nombre
Devuelve un -1 cuando la lista se encuentra vacía o cuando no hay coincidencia
De lo contrario devuelve un 0*/
int buscar_registro_simbolo(listaSimbolos *lista, char* nombre){
    if(lista->primerRegistro==NULL){
        return -1;
    }
    else
    {
        tablaSimbolos *actual = lista->primerRegistro;
        if(!strcmp(actual->nombre, nombre)){
            return 0;
        }
        while (actual->siguienteRegistro != 0)
        {
            actual=actual->siguienteRegistro;
            if(!strcmp(actual->nombre, nombre)){
            return posicion;
            }
        }
        return -1;
    }
    
}

/*Esta función agrega los registros a la tabla de símbolos, haciendo uso de memoria 
dinámica y validando la existencia de los nombres*/
int agregar_registro_simbolo(listaSimbolos *lista, char* nombre, int tipo){
    if(buscar_registro_simbolo(lista,nombre)==-1){
        if (lista->primerRegistro==NULL)
        {
            tablaSimbolos *registro = (tablaSimbolos*)malloc(sizeof(tablaSimbolos));
            registro->pos=posicion;
            registro->nombre=nombre;
            registro->tipo=tipo;
            registro->siguienteRegistro=NULL;
            lista->primerRegistro=registro;
            posicion ++;
            return posicion;
        }
        else
        {
            tablaSimbolos *actual = lista->primerRegistro;
            while(actual->siguienteRegistro != 0){
                actual=actual->siguienteRegistro;
                
            }
            tablaSimbolos *nuevoRegistro;
            nuevoRegistro=(tablaSimbolos*)malloc(sizeof(tablaSimbolos));
            nuevoRegistro->pos=posicion;
            nuevoRegistro->nombre=nombre;
            nuevoRegistro->tipo=tipo;
            nuevoRegistro->siguienteRegistro=NULL;
            actual->siguienteRegistro=nuevoRegistro;
            posicion ++;
            return posicion;
        }
    }
}

listaSimbolos crear_tabla_simbolos();
void mostrar_tabla_simbolos(FILE *archivo,listaSimbolos lista);
int buscar_registro_simbolo(listaSimbolos *lista, char* nombre);
int agregar_registro_simbolo(listaSimbolos *lista, char* nombre, int tipo);

/*La tabla de literales se manejará como una lista ligada
cada nodo de la lista es una estructura con los campos requeridos*/
int posicionLiteral = 0;
typedef struct tablaLiterales{
    int pos;
    char* cadena;
    struct tablaLiterales* siguienteRegistro;
}tablaLiterales;

typedef struct{
    struct tablaLiterales* primerRegistro;
}listaLiterales;

/*Con esta función inicializamos nuestra tabla de símbolos*/
listaLiterales crear_tabla_literales(){
    listaLiterales lista;
    lista.primerRegistro=NULL;
    return lista;
}

/*Esta función nos permite mostrar el contenido de nuestra lista ligada o tabla de literales
 dentro del archivo de salida que se le pase como parámetro*/
void mostrar_tabla_literales(FILE *archivo,listaLiterales lista){
    if(lista.primerRegistro==NULL)
        fprintf(archivo,"Tabla de literales vacia");
    else{
        tablaLiterales *actual=lista.primerRegistro;
        fprintf(archivo," TABLA DE CADENAS\n");
        fprintf(archivo," _____________________________________\n");
	    fprintf(archivo,"|Posicion|         Cadena            |  \n");
        fprintf(archivo,"--------------------------------------  \n");     
        while(actual !=0){
            fprintf(archivo,"  %d \t   %s \n",actual->pos,actual->cadena);
            actual=actual->siguienteRegistro;
        }
    }
}

/*Esta función agrega los registros a la tabla de símbolos, haciendo uso de memoria 
dinámica y validando la existencia de los nombres*/
int agregar_registro_literales(listaLiterales *lista, char* cadena){
    if (lista->primerRegistro==NULL)
    {
        tablaLiterales *registro = (tablaLiterales*)malloc(sizeof(tablaLiterales));
        registro->pos=posicionLiteral;
        registro->cadena=cadena;
        registro->siguienteRegistro=NULL;
        lista->primerRegistro=registro;
        posicionLiteral++;
    }
    else
    {
        tablaLiterales *actual = lista->primerRegistro;
        int posicion;
        while(actual->siguienteRegistro != 0){
            actual=actual->siguienteRegistro;
        }
        tablaLiterales *nuevoRegistro;
        nuevoRegistro=(tablaLiterales*)malloc(sizeof(tablaLiterales));
        nuevoRegistro->pos=posicionLiteral;
        nuevoRegistro->cadena=cadena;
        nuevoRegistro->siguienteRegistro=NULL;
        actual->siguienteRegistro=nuevoRegistro;
        posicionLiteral++;
    }
    return posicionLiteral; 
}
//Funciones a usar en la tabla de literales
listaLiterales crear_tabla_literales();
void mostrar_tabla_literales(FILE *archivo,listaLiterales lista);
int agregar_registro_literales(listaLiterales *lista, char* cadena);

/*La tabla de constantes se manejará como una lista ligada
cada nodo de la lista es una estructura con los campos requeridos*/
int posicionConstante = 0; 
typedef struct tablaConstantes{
    int pos;
    char* constante_real;
    struct tablaConstantes* siguienteRegistro;
}tablaConstantes;

typedef struct{
    struct tablaConstantes* primerRegistro;
}listaConstantes;

/*Con esta función inicializamos nuestra tabla de constantes*/
listaConstantes crear_tabla_constantes(){
    listaConstantes lista;
    lista.primerRegistro=NULL;
    return lista;
}

/*Esta función nos permite mostrar el contenido de nuestra lista ligada o tabla de constantes
 dentro del archivo de salida que se le pase como parámetro*/
void mostrar_tabla_constantes(FILE *archivo,listaConstantes lista){
    if(lista.primerRegistro==NULL)
        fprintf(archivo,"Tabla de constantes vacia");
    else{
        tablaConstantes *actual=lista.primerRegistro;
        fprintf(archivo," TABLA DE CONSTANTES\n");
        fprintf(archivo," ________________________________\n");
	    fprintf(archivo,"|Posicion|       Constante      | \n");
        fprintf(archivo,"---------------------------------\n");        
        while(actual !=0){
            fprintf(archivo,"  %d \t\t   %s \n",actual->pos,actual->constante_real);
            actual=actual->siguienteRegistro;
        }
    }
}

/*Esta función agrega los registros a la tabla de símbolos, haciendo uso de memoria 
dinámica y validando la existencia de los nombres*/
int agregar_registro_constantes(listaConstantes *lista, char* constante_real){
    if (lista->primerRegistro==NULL)
    {
        tablaConstantes *registro = (tablaConstantes*)malloc(sizeof(tablaConstantes));
        registro->pos=posicionConstante;
        registro->constante_real=constante_real;
        registro->siguienteRegistro=NULL;
        lista->primerRegistro=registro;
        posicionConstante++;
    }
    else
    {
        tablaConstantes *actual = lista->primerRegistro;
        while(actual->siguienteRegistro != 0){
            actual=actual->siguienteRegistro;
        }
        tablaConstantes *nuevoRegistro;
        nuevoRegistro=(tablaConstantes*)malloc(sizeof(tablaConstantes));
        nuevoRegistro->pos=posicionConstante;
        nuevoRegistro->constante_real=constante_real;
        nuevoRegistro->siguienteRegistro=NULL;
        actual->siguienteRegistro=nuevoRegistro;
        posicionConstante++;
    }
    return posicionConstante;    
}
//Definicion de las funciones a usar
listaConstantes crear_tabla_constantes();
void mostrar_tabla_constantes(FILE *archivo,listaConstantes lista);
int agregar_registro_constantes(listaConstantes *lista, char* constante_real);

/*Los tokens se tratarán de la misma forma que la tabla de símbolos, es decir,
mediante una lista ligada donde cada nodo es una estructura con los datos del token*/
typedef struct Token
{
    int clase;
    int posicion;
    struct Token* siguienteToken;
}Token;

typedef struct 
{
    struct Token* primerToken;
}listaTokens;

/*Función para incializar la lista*/
listaTokens crear_lista_tokens(){
    listaTokens lista;
    lista.primerToken=NULL;
    return lista;
}

/*Función para mostrar los tokens en un archivo*/
void mostrar_lista_tokens(FILE *archivo, listaTokens lista){
    fprintf(archivo, "--|Lista de tokens|--\n");
    if (lista.primerToken==NULL){
        fprintf(archivo, "Lista de tokens vacía");
    }
    else{
        Token *actual= lista.primerToken;
        while (actual != 0)
        {
            if (actual->clase==2|actual->clase==4|(actual->clase==8 && actual->posicion!=0))
            {
            fprintf(archivo, "(%d\t,\t%c)\n", actual->clase,(char)actual->posicion);            
            }
            else{
            fprintf(archivo, "(%d\t,\t%d)\n", actual->clase,actual->posicion);            
            }
            actual=actual->siguienteToken;
        }  
    }
}

/*Funcion que nos permite agregar tokens a la lista usando memoria dinámica*/
void agregar_token(listaTokens *lista, int clase, int posicion){
    if (lista->primerToken==NULL){
        Token *token = (Token*)malloc(sizeof(Token));
        token->clase=clase;
        token->posicion=posicion;
        token->siguienteToken=NULL;
        lista->primerToken=token; 
    }    
    else
    {
        Token *actual= lista->primerToken;
        while (actual->siguienteToken!=0)
        {
            actual=actual->siguienteToken;
        }
        Token *nuevoToken;
        nuevoToken = (Token*)malloc(sizeof(Token));
        nuevoToken->clase=clase;
        nuevoToken->posicion=posicion;
        nuevoToken->siguienteToken=NULL;
        actual->siguienteToken=nuevoToken;
    }   
}

listaTokens crear_lista_tokens();
void mostrar_lista_tokens(FILE *archivo, listaTokens lista);
void agregar_token(listaTokens *lista, int clase, int posicion);

listaSimbolos tabla_simbolos;
listaLiterales tabla_literales;
listaConstantes tabla_constantes_reales;
listaTokens lista_tokens;
%}
constan_ente [1-9][0-9]{0,13}
palabra_res bool|break|case|char|continue|default|do|else|float|for|if|int|return|string|switch|while|void
identificador [A-Za-z][A-Za-z0-9_]*
cadena \"[A-Z|.|a-z|0-9| |!|\[|\]|”|#|$|%|&|/|(|)|=|?|¡|/|*|\-|+|¬|>|<|¿|¬|°|@]*\"
constante_real [0-9]+[.]?[0-9]+([E|e][\-+]?[0-9]+)?
sim_especial \{|\}|,|:|\(|\)|\[|\]
opera_aritme (\+)|(\*)|(-)|(\/)|(\%)
potencia \*\*
asignacion =
opera_rela (<=)|(>=)|(<)|(!=)|(>)|(==)
comentario @[\"A-Z|.|a-z|0-9| |!|\[|\]|”|#|$|%|&|/|(|)|=|?|¡|/|*|\-|+|¬|>|<|¿|¬|°|@\"]*
error [^constan_entepalabra_residentificadorconstante_realsim_especialopera_aritmepotenciaasignacionopera_relacomentario \n]
%%
{comentario} {
            fprintf(archSal,"%s Es un comentario, por lo tanto se descarta\n",yytext);
            }
{asignacion} {
        fprintf(archSal,"%s Es un operador de asignacion\n",yytext);
        int ascii_asignacion= obtenerASCII(yytext);
        fprintf(archAtomos,"%c",ascii_asignacion);
	    agregar_token(&lista_tokens,4, ascii_asignacion);
        }

{constan_ente} {
        fprintf(archSal,"%s Es un numero entero\n",yytext);
        fprintf(archAtomos,"e");
	    agregar_token(&lista_tokens,6, atoi(yytext));
        }
{constante_real} {
         fprintf(archSal, "%s Es una constante real \n", yytext);
         char *constante=malloc(sizeof(yytext));
         strcpy(constante,yytext);
         fprintf(archAtomos,"r");
         int pos_cons_real=agregar_registro_constantes(&tabla_constantes_reales, constante);
         agregar_token(&lista_tokens,0, pos_cons_real-1);
      }

{palabra_res} {
	    for (valor = 0; valor <= 16; valor++) 
            {
               if (strcmp(yytext, palabraRes[valor].palabra) == 0) 
               {
                    fprintf(archSal,"%s Es una palabra reservada\n",yytext);
                    fprintf(archAtomos,"%s",palabraRes[valor].atomo);
		            agregar_token(&lista_tokens,1, valor);
               }
            }
         }
{potencia} {
         fprintf(archSal,"%s Es operador aritmetico\n",yytext);
         fprintf(archAtomos,"#");
		   agregar_token(&lista_tokens,8,0);
         }         
{opera_aritme} {
	    for (valor = 0; valor <= 4; valor++) 
            {
               if (strcmp(yytext, operadorArit[valor].simbolo) == 0) 
               {
                  int ascii_aritmetico= obtenerASCII(yytext);
                  fprintf(archSal,"%s Es operador aritmetico\n",yytext);
                  fprintf(archAtomos,"%s",operadorArit[valor].atomo);
		            agregar_token(&lista_tokens,8, ascii_aritmetico);
               }
            }
         }
{opera_rela} {
	    for (valor = 0; valor <= 5; valor++) 
            {
               if (strcmp(yytext, operadorRel[valor].operador) == 0) 
               {
                    fprintf(archSal,"%s Es operador relacional\n",yytext);
                    fprintf(archAtomos,"%s",operadorRel[valor].atomo);
		            agregar_token(&lista_tokens,5, operadorRel[valor].valor);
               }
            }
         }
{sim_especial} {
	    for (valor = 0; valor <= 7; valor++) 
            {
               if (strcmp(yytext, caracterEsp[valor].operador) == 0) 
               {
                  int ascii_especial= obtenerASCII(yytext);
                    fprintf(archSal,"%s Es simbolo especial\n",yytext);
                    fprintf(archAtomos,"%s",caracterEsp[valor].operador);
		            agregar_token(&lista_tokens,2, ascii_especial);
               }
            }
         }
{identificador} {
                fprintf(archSal, "%s Es un identificador\n", yytext);
                char *identificador=malloc(sizeof(yytext));
                strcpy(identificador,yytext);
                fprintf(archAtomos,"a");
                int pos_ident=agregar_registro_simbolo(&tabla_simbolos, identificador, -1);
                agregar_token(&lista_tokens,3, pos_ident-1);
                }

{cadena} {
        fprintf(archSal, "%s Es una cadena \n", yytext);
        char *cadena=malloc(sizeof(yytext));
        strcpy(cadena,yytext);
        fprintf(archAtomos,"s");
        int pos_cadena=agregar_registro_literales(&tabla_literales, cadena);
        agregar_token(&lista_tokens,7, pos_cadena-1);
        }
{error}  fprintf(archError,"%s Es un Error\n",yytext);
%%

int main(int argc, char *argv[]){
    
    yyin = fopen(argv[1],"r");
    archAtomos = fopen("atomos.txt","w");
    archSal = fopen("salida.txt","w");
    archTablas=fopen("tablas.txt","w");
    archTokens=fopen("tokens.txt","w");
    archError = fopen("error.txt","w");
    fprintf(archError,"--|LISTA DE ERRORES|--\n");

    tabla_simbolos=crear_tabla_simbolos();
    tabla_literales=crear_tabla_literales();
    yylex();

    mostrar_tabla_simbolos(archTablas,tabla_simbolos);
    fprintf(archTablas,"\n\n");
    mostrar_tabla_literales(archTablas, tabla_literales);
    fprintf(archTablas,"\n\n");
    mostrar_tabla_constantes(archTablas, tabla_constantes_reales);
    mostrar_lista_tokens(archTokens, lista_tokens);

    fclose(archAtomos);
    fclose(archTablas);
    fclose(archSal);
    fclose(archTokens);
    fclose(archError);


    archAtomos = fopen("atomos.txt","r");
    
    c=crearArray(archAtomos);

    fclose(archAtomos);

    P();
    return 0;
}

int obtenerASCII(char *caracter){
    return (int)*caracter;
}

