/*En este archivo se definen las funciones relacionadas a la Tabla de Literales*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*La tabla de literales se manejará como una lista ligada
cada nodo de la lista es una estructura con los campos requeridos*/
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

/*Esta función permite buscar un registro por su cadena
Devuelve un -1 cuando la lista se encuentra vacía o cuando no hay coincidencia
De lo contrario devuelve un 0*/
int buscar_registro_literales(listaLiterales *lista, char* cadena){
    if(lista->primerRegistro==NULL){
        return -1;
    }
    else
    {
        tablaLiterales *actual = lista->primerRegistro;
        if(!strcmp(actual->cadena, cadena)){
            return 0;
        }
        int posicion=0;
        while (actual->siguienteRegistro != 0)
        {
            actual=actual->siguienteRegistro;
            posicion++;
            if(!strcmp(actual->cadena, cadena)){
            return posicion;
            }
        }
        return -1;
    }
    
}

/*Esta función agrega los registros a la tabla de símbolos, haciendo uso de memoria 
dinámica y validando la existencia de los nombres*/
void agregar_registro_literales(listaLiterales *lista, char* cadena){
    if (lista->primerRegistro==NULL)
    {
        tablaLiterales *registro = (tablaLiterales*)malloc(sizeof(tablaLiterales));
        registro->pos=0;
        registro->cadena=cadena;
        registro->siguienteRegistro=NULL;
        lista->primerRegistro=registro;
    }
    else
    {
        tablaLiterales *actual = lista->primerRegistro;
        int posicion;
        while(actual->siguienteRegistro != 0){
            actual=actual->siguienteRegistro;
            posicion++;
        }

        posicion++;
        tablaLiterales *nuevoRegistro;
        nuevoRegistro=(tablaLiterales*)malloc(sizeof(tablaLiterales));
        nuevoRegistro->pos=posicion;
        nuevoRegistro->cadena=cadena;
        nuevoRegistro->siguienteRegistro=NULL;
        actual->siguienteRegistro=nuevoRegistro;
    }
    
}

