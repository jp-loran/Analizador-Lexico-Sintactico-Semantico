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

FILE *archSal;
FILE *archTablas;
listaSimbolos tabla_simbolos;
%}
identificador [A-Za-z][A-Za-z0-9\_]*
%%
{identificador} {fprintf(archSal, "%s es un identificador\n", yytext);
                char *identificador=malloc(sizeof(yytext));
                strcpy(identificador,yytext);
                agregar_registro_simbolo(&tabla_simbolos, identificador, -1);
                }
%%
int main(int argc, char *argv[]){
    yyin = fopen(argv[1],"r");
    archSal = fopen("salida.txt","w");
    archTablas=fopen("tablas.txt","w");
    tabla_simbolos=crear_tabla_simbolos();
    yylex();
    mostrar_tabla_simbolos(archTablas,tabla_simbolos);
    fclose(archTablas);
    fclose(archSal);
    return 0;
}
