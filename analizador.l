%{
/*
Autores: Juan Pablo Alvarez Loran
         Carlos Tovar Herrera
Descripción: Este programa reconoce las clases de componentes léxicos definidos dentro de la clase.
             Los resultados se almacenan en distintos archivos de salida.
Fecha de elaboración: 25 de Octubre de 2020
Fecha de entrega: 29 de Octubre de 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablaSimbolos.h"
#include "tokens.h"
#include "catalogos.h"
#include "tablaLiterales.h"
#include "tablaConstantes.h"

FILE *archSal;
FILE *archTablas;
FILE *archTokens;

listaSimbolos tabla_simbolos;
listaLiterales tabla_literales;
listaConstantes tabla_constantes_reales;
listaTokens lista_tokens;

%}
identificador [A-Za-z][A-Za-z0-9\_]*
cadena \"[A-Z|.|a-z|0-9| |!|\[|\]|”|#|$|%|&|/|(|)|=|?|¡|/|*|\-|+|¬|>|<|¿|¬|°|@]*\"
constante_real [0-9]+[.]?[0-9]+([Ee][\-+]?[0-9]+)?
%%
{constante_real} {fprintf(archSal, "%s es una constante real \n", yytext);
         char *constante=malloc(sizeof(yytext));
         strcpy(constante,yytext);
         int pos_cons_real=agregar_registro_constantes(&tabla_constantes_reales, constante);
         agregar_token(&lista_tokens,0, pos_cons_real);}
{identificador} {fprintf(archSal, "%s es un identificador\n", yytext);
                char *identificador=malloc(sizeof(yytext));
                strcpy(identificador,yytext);
                int pos_ident=agregar_registro_simbolo(&tabla_simbolos, identificador, -1);
                agregar_token(&lista_tokens,3, pos_ident);}
{cadena} {fprintf(archSal, "%s es una cadena \n", yytext);
         char *cadena=malloc(sizeof(yytext));
         strcpy(cadena,yytext);
         int pos_cadena=agregar_registro_literales(&tabla_literales, cadena);
         agregar_token(&lista_tokens,7, pos_cadena);}


%%
int main(int argc, char *argv[]){
    
    yyin = fopen(argv[1],"r");
    archSal = fopen("salida.txt","w");
    archTablas=fopen("tablas.txt","w");
    archTokens=fopen("tokens.txt","w");

    tabla_simbolos=crear_tabla_simbolos();
    tabla_literales=crear_tabla_literales();

    yylex();

    mostrar_tabla_simbolos(archTablas,tabla_simbolos);
    fprintf(archTablas,"\n\n");
    mostrar_tabla_literales(archTablas, tabla_literales);
    fprintf(archTablas,"\n\n");
    mostrar_tabla_constantes(archTablas, tabla_constantes_reales);
    mostrar_lista_tokens(archTokens, lista_tokens);

    fclose(archTablas);
    fclose(archSal);
    fclose(archTokens);

    return 0;
}
