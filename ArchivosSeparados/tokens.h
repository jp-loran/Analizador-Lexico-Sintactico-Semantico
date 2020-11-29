/*En este archivo se encuentran las funciones relacionadas a la creación de los tokens*/
#include <stdio.h>


/*Los tokens se tratarán de la misma forma que la tabla de símbolos, es decir,
mediante una lista ligada donde cada nodo es una estructura con los datos del token*/
typedef struct Token
{
    int clase;
    int posicion;
    char atomo;
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

char atomo(int clase, float posicion){
    int valor_int=(int)valor;
    switch(clase){
        case 0:
            return 'r';
            break;
        case 1:
        case 2:
        case 3:
            return 'a';
            break;
        case 4:
            return '=';
            break;
        case 5:
        case 6
    }
}