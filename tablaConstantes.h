/*En este archivo se definen las funciones relacionadas a la Tabla de Constantes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*La tabla de constantes se manejará como una lista ligada
cada nodo de la lista es una estructura con los campos requeridos*/
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
        registro->pos=0;
        registro->constante_real=constante_real;
        registro->siguienteRegistro=NULL;
        lista->primerRegistro=registro;
        return 0;
    }
    else
    {
        tablaConstantes *actual = lista->primerRegistro;
        int posicion;
        while(actual->siguienteRegistro != 0){
            actual=actual->siguienteRegistro;
            posicion++;
        }

        posicion++;
        tablaConstantes *nuevoRegistro;
        nuevoRegistro=(tablaConstantes*)malloc(sizeof(tablaConstantes));
        nuevoRegistro->pos=posicion;
        nuevoRegistro->constante_real=constante_real;
        nuevoRegistro->siguienteRegistro=NULL;
        actual->siguienteRegistro=nuevoRegistro;
        return posicion;
    }
    
}

