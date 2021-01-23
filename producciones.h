#include<stdio.h>
#include<stdlib.h>
// DECLARACION DE VARIABLES GLOBALES
char c; // almacenara el caracter de la cadena de atomos a analizar
int n=0; // contador para ir avanzando en el array que contiene la cadena de atomos
char* arrayAtomos=NULL; // arreglo reservado dinamicamente que almacenara la cadena de atomos  
size_t size; // variable auxiliar que nos permite obtener el tamaño de cada elemento del array

int* arrayValores=NULL;//Arreglo para el campo valor de los tokens
size_t size1=1;//Contador para arreglo dinámico
int v=0;//Contador para la variable siguienteValor() 
int tipo; //Almacena el tipo de dato
int token;//Almacena el valor del siguiente token
int pos;//Almacena la posicion de la variable en la tabla de símbolos

//Declaracion de tablas 
listaSimbolos tabla_simbolos;
listaTokens crear_lista_tokens();
listaLiterales tabla_literales;
listaConstantes tabla_constantes_reales;
listaTokens lista_tokens;

//DECLARACION DE FUNCIONES
char crearArray(FILE* archAtomos);
void P();
void DP();
void Y();
void D();
int V(); //De esta produccion se obtiene el tipo de dato
void L(int tipo); //Esta producción asigna el tipo de dato a la tabla de símbolos
void G();
void C();
void YP();
int VP();//Función que regresa el tipo de dato
void B();
void S();
void U();
void W();
void H();
void X();
void O();
void I();
void J();
void N();
void R();
void K();
void E();
void EP();
void T();
void TP();
void F();
void A();
void M();
void Z();
void Q();
void QP();



//La siguiente funcion lee el archivo atomos.txt y almacena en un arreglo de caracteres los elementos del archivo
//Devuelve el char ubicado en la primer posicion del arreglo
char crearArray(FILE* archAtomos){
    if(archAtomos!= NULL){
            size=1;
            while(getc(archAtomos)!=EOF){
                size++;
            }
        }
        arrayAtomos=(char*)malloc(sizeof(char)*size);
        fseek(archAtomos,0,SEEK_SET);
        for (size_t i =0; i<size-1;i++){
            arrayAtomos[i]=(char)getc(archAtomos);
        }
        
        arrayAtomos[size-1]='\0';
    return arrayAtomos[n];
}

//Función que nos permite ir recorriendo el arreglo de atomos
char leeSiguiente(){
    n++;
    return arrayAtomos[n];
}

//Función que devuelve un error si encuentra errores sintacticos
void error(char* esperado,char c){
    printf("ERROR: Se esperaba %s antes o despues del atomo %c \n",esperado,c);
    exit(EXIT_FAILURE);
}

//Funcion que devuelve el siguiente valor del arreglo arrayValores
int siguienteValor(){
    v++;
    return arrayValores[v-1];
}

//Función que consulta la tabla de símbolos y acutaliza el tipo
//Si ya se ha declarado la variable manda un aviso
void asignaTipo(int tipo, int posicion){
    tablaSimbolos *actual=tabla_simbolos.primerRegistro;
    while(actual !=0){
        if(actual->pos==posicion && actual->tipo!=-1){
          //  printf("Variable '%s' ya declarada \n",actual->nombre);
           // printf("Posicion: %d\n",pos);
            //printf("Tipo: %d\n",tipo);

        }
        else if (actual->pos==posicion && actual->tipo==-1){
            actual->tipo=tipo;
        }
        actual=actual->siguienteRegistro;
    }    
}

//Función que revisa y muestra las variables que no se han declarado
void revisaNoDeclarada(){
    tablaSimbolos *actual=tabla_simbolos.primerRegistro;
    while(actual !=0){
        if(actual->tipo==-1){
            printf("ERROR:Variable '%s' referenciada antes de su declaracion \n",actual->nombre);
        }
        actual=actual->siguienteRegistro;
    }

}

//CUERPO DE LAS PRODUCCIONES
void P(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g'|| c=='[')
    {
        DP();
        Y();
        YP();
        return;
    }
    else
    {
        error("un tipo de dato o [",c);
    }   
}
void DP(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g')
    {
        D();
        DP();
        
        return;
    }else if(c=='['||c=='a'||c=='x'||c=='i'||c=='w'||c=='h'||c=='p'||c=='u'||c=='t')
    {
        return;
    }
    else
    {
        error("una palabra reservada, un identificador, ] o }",c);
    }
}
void D(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g')
    {
        
        tipo=V();
        L(tipo);
        if (c==':')
        {
            token=siguienteValor();
            c=leeSiguiente();
            return;
        }else{error(":",c);}
    
    }else
    {
        error("un tipo de dato",c);
    }
}
int V(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g'){
        tipo=siguienteValor();
        c=leeSiguiente();
        
    }else
    {
        error("un tipo de dato",c);
    }
    return tipo;
    
}
void L(int tipo){
    if (c=='a')
    {
        pos=siguienteValor();
        asignaTipo(tipo,pos);
        c=leeSiguiente();
        G();
        C();
        return;
    }else
    {
        error("un identificador",c);
    }
    
   
}
void G(){
    if (c=='[')
    {
        token=siguienteValor();
        c=leeSiguiente();
        if (c=='e')
        {
            token=siguienteValor();
            c=leeSiguiente();
            if (c==']')
            {                
                token=siguienteValor();
                c=leeSiguiente();
                return;
            }else{error("]",c);}
            
        }else{error("constante entera",c);}
        
    }else if(c==',' ||c==':' ||c==')' ||c=='*' ||c=='/' ||c=='%' ||c=='#' ||c=='+' ||c=='-' ||c=='!' ||c=='?' ||c=='<'||c=='>'||c=='y'||c=='m'||c=='='){
        return;
    }
    else
    {
        error("[, :, ), , , un operador aritmeico o un operador relacional",c);  
    }
    
    
}
void C(){
    if (c==',')
    {
        token=siguienteValor();
        c=leeSiguiente();
        L(tipo);
        return;
    }else if(c==':'){
        return;
    }else
    {
        error(" , o :",c);  
    }
}
void Y(){
    if (c=='[')
    {   
        token=siguienteValor();
        
        c=leeSiguiente();
        tipo=VP();

        if (c=='a')
        {   
            pos=siguienteValor();
            asignaTipo(tipo,pos);
            c=leeSiguiente();
            if (c=='(')
            {
                token=siguienteValor();
                
                c=leeSiguiente();
                if (c==')')
                {
                    token=siguienteValor();
                    
                    c=leeSiguiente();
                    if (c=='{')
                    {
                        token=siguienteValor();
                        
                        c=leeSiguiente();
                        DP();
                        B();
                        if (c=='}')
                        {
                            token=siguienteValor();
                            
                            c=leeSiguiente();
                            if (c==']')
                            {
                                token=siguienteValor();
                                
                                c=leeSiguiente();
                                return;
                            }else{error("]",c);}
                            
                        }else{error("}",c);}
                        
                    }else{error("{",c);}
                    
                }else{error(")",c);}
                
            }else{error("(",c);}
            
        }else{error("identificador",c);}
        
    }else if(c==':'){
        token=siguienteValor();
        return;
    }else
    {
        error(" [ o :",c);  
    }   
}
void YP(){
    if (c=='[')
    {
        Y();
        YP();
        return;
    }else if (c=='\0' || c==']')
    {    
        return;
    }else
    {
        error("[, ] o simbolo de fin de cadena",c);  
    }
}
int VP(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g')
    {
                
        tipo=V();
        return tipo;
    }else if (c=='o')
    {
        tipo=siguienteValor();
        c=leeSiguiente();     
        return tipo;
    }else{
        error("un tipo de dato",c);
    }
}
void B(){
    if (c=='['||c=='a'||c=='x'||c=='i'||c=='w'||c=='h'||c=='p'||c=='u'||c=='t')
    {
        
        S();
        B();
        return;
    }
    else if(c=='}'||c==']'){
        return;
    }
    else
    {
        error("una palabra reservada, un identificador, [,] o }",c);
    }
}
void S(){ 
    if (c=='a')
    {
        
        A();
        return;
    }
    else if (c=='x')
    {
        
        X();
        return;
    }
    else if (c=='i')
    {
        
        I();
        return;
    }
    else if(c=='w')
    {
        
        W();
        return;
    }
    else if (c=='h')
    {
        
        H();
        return;
    }
    else if(c=='p')
    {
        
        N();
        return;
    }
    else if (c=='u')
    {
        token=siguienteValor();
        
        c=leeSiguiente();
        U();
        if (c==':')
        {
            token=siguienteValor();
            
            c=leeSiguiente();
            return;
        }else
        {
            error(":",c);
        }       
        
    }
    else if (c=='t')
    {
        token=siguienteValor();
        
        c=leeSiguiente();
        if (c==':'){
            token=siguienteValor();
            
            c=leeSiguiente();
            return;
        }error(":",c);
    }
    else if(c=='['){
        token=siguienteValor();
        c=leeSiguiente();
        if (c=='a')
        {
            token=siguienteValor();
            c=leeSiguiente();
            if (c=='(')
            {
                token=siguienteValor();
                c=leeSiguiente();
                if (c==')')
                {
                    token=siguienteValor();
                    c=leeSiguiente();
                    if (c==']')
                    {
                        token=siguienteValor();
                        c=leeSiguiente();
                        if (c==':')
                        {
                            token=siguienteValor();
                            c=leeSiguiente();
                            return;
                        }else{error(":",c);}
                        
                    }else{error("]",c);}
                    
                }else{error(")",c);}
                
            }else{error("(",c);}
            
        }else{error("identificador",c);}
        
    } 
    else
    {
        error("un identificador, palabra reservada o [ ",c);
    }
      
}
void U(){
    if(c==':'){
        return;
    }
    else if(c=='('){
        token=siguienteValor();
        c=leeSiguiente();
        F();
        if (c==')')
        {
            token=siguienteValor();
            c=leeSiguiente();
            return;
        }else
        {
            error(")",c);
        }
    }
    else
    {
        error(": o (",c);
    }   
}
void W(){
    if (c=='w')
    {   
        token=siguienteValor();
        c=leeSiguiente();
        if(c=='('){
            token=siguienteValor();
            c=leeSiguiente();
            R();
            if (c==')')
            {
                token=siguienteValor();
                c=leeSiguiente();
                if (c=='{')
                {
                    token=siguienteValor();
                    c=leeSiguiente();
                    B();
                    if (c=='}')
                    {
                        token=siguienteValor();
                        c=leeSiguiente();
                        return;
                    }else{error("}",c);}
                    
                }else{error("{",c);}
                
            }else{error(")",c);}
            
        }else{error("(",c);}
    }else
    {
        error("la palabra reservada while",c);
    }   
}
void H(){
    if (c=='h')
    {
        token=siguienteValor();
           
        c=leeSiguiente();
        if (c=='{')
        {
            token=siguienteValor();
                        
            c=leeSiguiente();
            B();
            if (c=='}')
            {
                token=siguienteValor();
                    
               c=leeSiguiente();
               if (c=='w')
               {
                           token=siguienteValor();
        
                   c=leeSiguiente();
                   if (c=='(')
                   {
                             token=siguienteValor();
          
                       c=leeSiguiente();
                       R();
                       if (')')
                       {
                                   token=siguienteValor();
        
                           c=leeSiguiente();
                           if (c==':')
                           {
                                       token=siguienteValor();
        
                               c=leeSiguiente();
                               return;
                           }else{error(":",c);}
                           
                       }else{error(")",c);}
                       
                   }else{error("(",c);}
                   
               }else{error("la palabra reservada while",c);}
               
            }else{error("}",c);}
            
        }else{error("{",c);}
        
    }else
    {
        error("la palabra reservada do",c);
    }
}
void X(){
    if (c=='x')
    {
        token=siguienteValor();
        
        c=leeSiguiente();
        if (c=='(')
        {
            token=siguienteValor();
            
            c=leeSiguiente();
            
            if (c=='a')
            {
                token=siguienteValor();
            
                c=leeSiguiente();
                if(c==')'){
                    token=siguienteValor();
            
                    c=leeSiguiente();
                    if (c=='{')
                    {
                        token=siguienteValor();
        
                        c=leeSiguiente();
                        O();
                        if (c=='d')
                        {
                            token=siguienteValor();
            
                            c=leeSiguiente();
                            if (c=='[')
                            {
                                token=siguienteValor();
           
                                c=leeSiguiente();
                                B();
                                if (c==']')
                                {
                                    token=siguienteValor();
        
                                    c=leeSiguiente();
                                    if (c=='}')
                                    {
                                        token=siguienteValor();
            
                                        c=leeSiguiente();
                                        return;
                                    }else{error("}",c);}
                                    
                                }else{error("]",c);}
                                
                            }else{error("[",c);}
                            
                        }else{error("la palabra reservada default",c);}
                        
                    }else{error("{",c);}

                }else{error(")",c);}

            }else{error("un idendtificador",c);}
            
        }else{error("(",c);}
        
    }else
    {
        error("la palabra reservada switch",c);
    }   
}
void O(){
    if (c=='k')
    {
        token=siguienteValor();
        
        c=leeSiguiente();
        if (c=='e')
        {
            token=siguienteValor();
            
            c=leeSiguiente();
            if (c=='[')
            {
                token=siguienteValor();
            
                c=leeSiguiente();
                B();
                if (c==']')
                {
                    token=siguienteValor();
            
                    c=leeSiguiente();
                    if (c=='q')
                    {
                        token=siguienteValor();
            
                        c=leeSiguiente();
                        if (c==':')
                        {
                            token=siguienteValor();
            
                            c=leeSiguiente();
                            O();
                            return;
                        }else{error(":",c);}
                        
                    }else{error("la palabra reservada break",c);}
                    
                }else{error("]",c);}
                
                
            }else{error("[",c);}
            
        }else{error("una constante numerica entera",c);}
        
    }
    else if(c=='d')
    {
        return;
    }
    else
    {
        error("la palabra reservada case o default",c);
    }   
}
void I(){
    if(c=='i'){
        token=siguienteValor();
        
        c=leeSiguiente();
        if (c=='(')
        {
            token=siguienteValor();
                
            c=leeSiguiente();
            R();
            if (c==')')
            {
                token=siguienteValor();
                                
                c=leeSiguiente();
                if (c=='{')
                {
                    token=siguienteValor();
                    
                    c=leeSiguiente();
                    B();
                    if (c=='}')
                    {
                        token=siguienteValor();
                        
                        c=leeSiguiente();
                        J();
                        if (c==':')
                        {
                            token=siguienteValor();
                            
                            c=leeSiguiente();
                            return;
                        }else{error(":",c);}
                        
                    }else{error("}",c);}
                    
                }else{error("{",c);}
                
            }else{error(")",c);}
            
        }else{error("(",c);}
        
    }else{
        error("la palabra reservada if",c);
    }
}
void J(){
    if (c=='l'){
        token=siguienteValor();
        
        c=leeSiguiente();
        if (c=='{'){
            token=siguienteValor();
                        
            c=leeSiguiente();
            B();
            if (c=='}'){
                token=siguienteValor();
                
                c=leeSiguiente();
                return;
            }
            else error("}",c);
        }
        else error("{",c);
    }
    else if (c==':'){
        return;
    }else error("else",c);
}
void N(){
    if (c=='p'){
        token=siguienteValor();
            
        c=leeSiguiente();
        if (c=='['){
            token=siguienteValor();
            
            c=leeSiguiente();
            if (c=='e'){
                token=siguienteValor();
        
                c=leeSiguiente();
                if (c==']'){
                    token=siguienteValor();
            
                    c=leeSiguiente();
                    if (c=='{'){
                        token=siguienteValor();
            
                        c=leeSiguiente();
                        B();
                        if (c=='}'){
                            token=siguienteValor();
            
                            c=leeSiguiente();
                            return;
                        }else error(" }",c);
                    }else error(" {",c);
                }else error(" ]",c);
            }else error(" entero",c);
        }else error(" [",c);
    }else error(" for",c);
}
void R(){
    if (c=='(' || c=='a' ||c=='e' || c=='r' || c=='[' ){
        E();
        K();
        E();
        return;
    }else error(" ( o [ o identificador,entero o real",c);
}
void K(){
    if (c=='!' || c=='?' || c=='>' || c=='<' || c=='y' ||c=='m'){
        token=siguienteValor();
        c=leeSiguiente();
        return;
    }else error(" operador relacional",c);
}
void E(){
    if (c=='(' || c=='a' || c=='e' || c=='r' || c=='['){
        T();
        EP();
        return;
    }else error("identificador, real, entero o ( [",c);

}
void EP(){
    if (c=='+'){
        c=leeSiguiente();
        T();
        EP();
        return;
    }
    else if (c=='-'){
        c=leeSiguiente();
        T();
        EP();
    }
    else if (c==')' || c=='!' || c=='?' || c=='>'|| c=='<'|| c=='y'|| c=='m'|| c==':'){
        return;
    }else error("operador o fin de linea",c);
}
void T(){
    if (c=='(' || c=='a' || c=='e' || c=='r' || c=='['){
        F();
        TP();
        return;
    }else error("identificador, real, entero o ( [",c);

}
void TP(){
    if (c=='*'){
        token=siguienteValor();
        c=leeSiguiente();
        F();
        TP();
        return;
    }
    else if(c=='/'){
        token=siguienteValor();
        c=leeSiguiente();
        F();
        TP();
        return;
    }
    else if(c=='%'){
        token=siguienteValor();
        c=leeSiguiente();
        F();
        TP();
        return;
    }
    else if(c=='#'){
        token=siguienteValor();
        c=leeSiguiente();
        F();
        TP();
        return;
    }
    else if(c=='+' ||c=='-' ||c==')' ||c=='!' ||c=='?' ||c=='>' ||c=='<' ||c=='y' ||c=='m' ||c==':' ){
        return;
    }
    else error("operador aritmetico, relacional  fin de linea",c);
}
void F(){
    if (c=='('){
        token=siguienteValor();
        
        c=leeSiguiente();
        E();
        if(c==')'){
            token=siguienteValor();
            
            c=leeSiguiente();
            return;
        }else error("(",c);
    }
    else if(c=='a'){
        token=siguienteValor();
        
        c=leeSiguiente();
        G();
        return;
    }
    else if(c=='e'){
        token=siguienteValor();
        
        c=leeSiguiente();
        return;
    }
    else if(c=='r'){
        token=siguienteValor();
        
        c=leeSiguiente();
        return;
    }
    else if (c=='['){
        token=siguienteValor();
        c=leeSiguiente();
        if (c=='a'){
            token=siguienteValor();
            c=leeSiguiente();
            if(c=='('){
                token=siguienteValor();
                c=leeSiguiente();
                if(c==')'){
                    token=siguienteValor();
                    c=leeSiguiente();
                    if(c==']'){
                        token=siguienteValor();
                        c=leeSiguiente();
                        return;
                    }else{error(" ]",c);}
                }else {error(" )",c);}
            }else {error("(",c);}
        }else {error("identificador",c);}
    }
    else {error("[",c);}
}
void A(){
    if (c=='a'){
        token=siguienteValor();
        
        c=leeSiguiente();
        G();
        if (c=='='){
            token=siguienteValor();
            
            c=leeSiguiente();
            M();
            if (c==':'){
                token=siguienteValor();
                
                c=leeSiguiente();
                return;
            }else {error(":",c);}
        }else {error("=",c);}
    }else {error("identificador",c);}
}
void M(){
    if (c=='(' ||c=='a' ||c=='e' ||c=='r' ||c=='[' ||c=='s'){
        QP();
        return;
    }
    else if(c=='+'){
        token=siguienteValor();
        c=leeSiguiente();
        Q();
        Z();
        return;
    }else {error("identificador, real, entero o cadena ( [ o +",c);}
}
void Z(){
    if(c==','){
        token=siguienteValor();
        c=leeSiguiente();
        Q();
        Z();
        return;
    }
    else if (c==':'){
        return;
    }
    else {error(" , o :",c);}
}
void Q(){
    if(c=='a'){
        token=siguienteValor();
        
        c=leeSiguiente();
        G();
        return;
    }
    else if(c=='s'){
        token=siguienteValor();
        
        c=leeSiguiente();
        return;
    }
    else {error("identificador o cadena",c);}
    
}
void QP(){
    if(c=='s'){
        token=siguienteValor();
        
        c=leeSiguiente();
        return;
    }
    else if(c=='(' ||c=='a' ||c=='e' ||c=='r' ||c=='[' ){
        E();
        return;
    }
    else {error("identificador, real, entero o cadena ( [",c);}
}
 

