//En este archivo se definen las estructuras de los catalogos a utilizar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Estructura para definir Palabras reservadas {valor palabra}
struct palabraS{
    char palabra[10]; //Palabra
    int valor;        //Valor 
} palabraRes[17] = {
                    {"bool",0},{"break",1},{"case",2},{"char",3},
                    {"continue",4},{"default",5},{"do",6},{"else",7},
                    {"float",8},{"for",9},{"if",10},{"int",11},
                    {"return",12},{"string",13},{"switch",14},{"while",15},
                    {"void",16}
                   };
				   
//Estructura para definir Operadores relacionales {valor,operador}
struct opRelacional {
    char operador[2]; //Operador 
    int valor;        //Valor
} operadorRel[6] = {{"!=",0},{"==",1},{">",2},{"<",3},{">=",4},{"<=",5}};

//Estructura para definir operadores aritmeticos {simbolo,valor,atomo}
struct opAritmetico {
    int indice;
    char simbolo[2];    //Operador 
    char valor[2];        //Valor
} operadorArit[6] = {{0,"**","0"},{1,"+","+"},{2,"-","-"},{3,"*","*"},
                    {4,"/","/"},{5,"%","%"}
                  };

//Estructura para definir Caracteres Especiales {valor, caracter}
struct opEspecial {
    char *operador; //Operador
    int valor;        //Valor 
} caracterEsp[8] = {{"{",123},{"}",125},{",",44},
                    {":",58},{"(",40},{")",41},
                    {"[",91} ,{"]",93}
                   };