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

#include "tablaSimbolos.h"
#include "tokens.h"
#include "catalogos.h"
#include "tablaLiterales.h"
#include "tablaConstantes.h"

FILE *archSal;
FILE *archTablas;
FILE *archTokens;
FILE *archError;

listaSimbolos tabla_simbolos;
listaLiterales tabla_literales;
listaConstantes tabla_constantes_reales;
listaTokens lista_tokens;
int valor;
int obtenerASCII(char *caracter);

%}
constan_ente [1-9][0-9]{0,13}
palabra_res bool|break|case|char|continue|default|do|else|float|for|if|int|return|string|switch|while|void
identificador [A-Za-z][A-Za-z0-9\_]*
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
	    agregar_token(&lista_tokens,4, ascii_asignacion);
        }

{constan_ente} {
        fprintf(archSal,"%s Es un numero entero\n",yytext);
	    agregar_token(&lista_tokens,6, atoi(yytext));
        }
{constante_real} {
         fprintf(archSal, "%s Es una constante real \n", yytext);
         char *constante=malloc(sizeof(yytext));
         strcpy(constante,yytext);
         int pos_cons_real=agregar_registro_constantes(&tabla_constantes_reales, constante);
         agregar_token(&lista_tokens,0, pos_cons_real-1);
      }

{palabra_res} {
	    for (valor = 0; valor <= 16; valor++) 
            {
               if (strcmp(yytext, palabraRes[valor].palabra) == 0) 
               {
                    fprintf(archSal,"%s Es una palabra reservada\n",yytext);
		            agregar_token(&lista_tokens,1, valor);
               }
            }
         }
{potencia} {
         fprintf(archSal,"%s Es operador aritmetico\n",yytext);
		   agregar_token(&lista_tokens,8,0);
         }         
{opera_aritme} {
	    for (valor = 0; valor <= 4; valor++) 
            {
               if (strcmp(yytext, operadorArit[valor].simbolo) == 0) 
               {
                  int ascii_aritmetico= obtenerASCII(yytext);
                  fprintf(archSal,"%s Es operador aritmetico\n",yytext);
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
		            agregar_token(&lista_tokens,2, ascii_especial);
               }
            }
         }
{identificador} {
                fprintf(archSal, "%s Es un identificador\n", yytext);
                char *identificador=malloc(sizeof(yytext));
                strcpy(identificador,yytext);
                int pos_ident=agregar_registro_simbolo(&tabla_simbolos, identificador, -1);
                agregar_token(&lista_tokens,3, pos_ident-1);
                }

{cadena} {
        fprintf(archSal, "%s Es una cadena \n", yytext);
        char *cadena=malloc(sizeof(yytext));
        strcpy(cadena,yytext);
        int pos_cadena=agregar_registro_literales(&tabla_literales, cadena);
        agregar_token(&lista_tokens,7, pos_cadena-1);
        }
{error}  fprintf(archError,"%s Es un Error\n",yytext);

%%
int main(int argc, char *argv[]){
    
    yyin = fopen(argv[1],"r");
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

    fclose(archTablas);
    fclose(archSal);
    fclose(archTokens);
    fclose(archError);

    return 0;
}

int obtenerASCII(char *caracter){
    return (int)*caracter;
}
