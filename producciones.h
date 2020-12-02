#include<stdio.h>
#include<stdlib.h>
// DECLARACION DE VARIABLES GLOBALES
char c; // almacenara el caracter de la cadena de atomos a analizar
int n=0; // contador para ir avanzando en el array que contiene la cadena de atomos
char* arrayAtomos=NULL; // arreglo reservado dinamicamente que almacenara la cadena de atomos  
size_t size; // variable auxiliar que nos permite obtener el tamaño de cada elemento del array

//DECLARACION DE FUNCIONES
char crearArray(FILE* archAtomos);
void P();
void DP();
void Y();
void D();
void V();
void L();
void G();
void C();
void YP();
void VP();
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

void error(char* esperado,char c){
    printf("ERROR: Se esperaba %s antes o despues del atomo %c \n",esperado,c);
    exit(EXIT_FAILURE);
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
    }else if(c=='['||c=='a'||c=='x'||c=='i'||c=='w'||c=='h'||c=='p'||c=='u'||c=='t'||c=='}')
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
        
        V();
        L();
        if (c==':')
        {
            c=leeSiguiente();
            return;
        }else{error(":",c);}
    
    }else
    {
        error("un tipo de dato",c);
    }
}
void V(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g'){
        
        c=leeSiguiente();
        return;
    }else
    {
        error("un tipo de dato",c);
    }
    
}
void L(){
    if (c=='a')
    {
        
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
        
        c=leeSiguiente();
        if (c=='e')
        {
            c=leeSiguiente();
            if (c==']')
            {                
                c=leeSiguiente();
                return;
            }else{error("]",c);}
            
        }else{error("constante entera",c);}
        
    }else if(c==',' ||c==':' ||c==')' ||c=='*' ||c=='/' ||c=='%' ||c=='#' ||c=='+' ||c=='-' ||c=='!' ||c=='?' ||c=='<'||c=='>'||c=='y'||c=='m'){
        
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
                
        c=leeSiguiente();
        L();
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
        
        c=leeSiguiente();
        VP();
        if (c=='a')
        {
            c=leeSiguiente();
            if (c=='(')
            {
                c=leeSiguiente();
                if (c==')')
                {
                    c=leeSiguiente();
                    if (c=='{')
                    {
                        c=leeSiguiente();
                        DP();
                        B();
                        if (c=='}')
                        {
                            c=leeSiguiente();
                            if (c==']')
                            {
                                c=leeSiguiente();
                                return;
                            }else{error("]",c);}
                            
                        }else{error("}",c);}
                        
                    }else{error("{",c);}
                    
                }else{error(")",c);}
                
            }else{error("(",c);}
            
        }else{error("identificador",c);}
        
    }else if(c==':'){
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
void VP(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g')
    {
                
        V();
        return;
    }else if (c=='o')
    {
        c=leeSiguiente();
        return;
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
        
        c=leeSiguiente();
        U();
        if (c==':')
        {
            c=leeSiguiente();
            return;
        }else
        {
            error(":",c);
        }       
        
    }
    else if (c=='t')
    {
        
        c=leeSiguiente();
        if (c==':'){
            c==leeSiguiente();
            return;
        }error(":",c);
    }
    else if(c=='['){
        
        c=leeSiguiente();
        if (c=='a')
        {
            c=leeSiguiente();
            if (c=='(')
            {
                c=leeSiguiente();
                if (c==')')
                {
                    c=leeSiguiente();
                    if (c==']')
                    {
                        c=leeSiguiente();
                        if (c==':')
                        {
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
        
        F();
        if (c==')')
        {
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
        
        c=leeSiguiente();
        if(c=='('){
            R();
            if (c==')')
            {
                c=leeSiguiente();
                if (c=='{')
                {
                    B();
                    if (c=='}')
                    {
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
        
        c=leeSiguiente();
        if (c=='{')
        {
            B();
            if (c=='}')
            {
               c=leeSiguiente();
               if (c=='w')
               {
                   c=leeSiguiente();
                   if (c=='(')
                   {
                       R();
                       if (')')
                       {
                           c=leeSiguiente();
                           if (c==':')
                           {
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
        
        c=leeSiguiente();
        if (c=='(')
        {
            c=leeSiguiente();
            if (c=='a')
            {
                c=leeSiguiente();
                if (c=='{')
                {
                    O();
                    if (c=='d')
                    {
                        c=leeSiguiente();
                        if (c=='[')
                        {
                            B();
                            if (c==']')
                            {
                                c=leeSiguiente();
                                if (c=='}')
                                {
                                    c=leeSiguiente();
                                    return;
                                }else{error("}",c);}
                                
                            }else{error("]",c);}
                            
                        }else{error("[",c);}
                        
                    }else{error("la palabra reservada default",c);}
                    
                }else{error("{",c);}
                
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
        
        c=leeSiguiente();
        if (c=='e')
        {
            c=leeSiguiente();
            if (c=='[')
            {
                B();
                if (c==']')
                {
                    c=leeSiguiente();
                    if (c=='q')
                    {
                        c=leeSiguiente();
                        if (c==':')
                        {
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
        
        c=leeSiguiente();
        if (c=='(')
        {
            R();
            if (c==')')
            {
                c=leeSiguiente();
                if (c=='{')
                {
                    B();
                    if (c=='}')
                    {
                        J();
                        if (c==':')
                        {
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
        c=leeSiguiente();
        if (c=='{'){
            B();
            if (c=='}'){
                return;
            }
            else error("Se espera } en lugar de:",c);
        }
        else error("Se espera { en lugar de:",c);
    }
    else if (c==':'){
        return;
    }else error("Se espera l",c);
}

void N(){
    if (c=='p'){
        c=leeSiguiente();
        if (c=='['){
            c=leeSiguiente();
            if (c=='e'){
                c=leeSiguiente();
                if (c==']'){
                    c=leeSiguiente();
                    if (c=='{'){
                        c=leeSiguiente();
                        B();
                        if (c=='}'){
                            c=leeSiguiente();
                            return;
                        }else error("Se espera }",c);
                    }else error("Se espera {",c);
                }else error("Se espera ]",c);
            }else error("Se espera e",c);
        }else error("Se espera [",c);
    }else error("Se espera p",c);
}

void R(){
    if (c=='(' || c=='a' ||c=='e' || c=='r' || c=='[' ){
        E();
        K();
        E();
        return;
    }else error("Se espera ( o [ o identificador,entero o real",c);
}

void K(){
    if (c=='!' || c=='?' || c=='>' || c=='<' || c=='y' ||c=='m'){
        c=leeSiguiente();
        //printf("Estamos en K, caracter %c",c);
        return;
    }else error("Se espera operador relacional",c);
}

void E(){
    if (c=='(' || c=='a' || c=='e' || c=='r' || c=='['){
        T();
        EP();
        return;
    }else error("Se espera identificador, real, entero o ( [",c);

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
    }else error("Se espera un operador o fin de linea",c);
}

void T(){
    if (c=='(' || c=='a' || c=='e' || c=='r' || c=='['){
        F();
        TP();
        return;
    }else error("Se espera identificador, real, entero o ( [",c);

}

void TP(){
    if (c=='*'){
        c=leeSiguiente();
        F();
        TP();
        return;
    }
    else if(c=='/'){
        c=leeSiguiente();
        F();
        TP();
        return;
    }
    else if(c=='%'){
        c=leeSiguiente();
        F();
        TP();
        return;
    }
    else if(c=='#'){
        c=leeSiguiente();
        F();
        TP();
        return;
    }
    else if(c=='+' ||c=='-' ||c==')' ||c=='!' ||c=='?' ||c=='>' ||c=='<' ||c=='y' ||c=='m' ||c==':' ){
        return;
    }
    else error("Se espera operador aritmetico, relacional  fin de linea",c);
}

void F(){
    if (c=='('){
        c=leeSiguiente();
        E();
        if(c==')'){
            return;
        }else error("Se espera (",c);
    }
    else if(c=='a'){
        c=leeSiguiente();
        G();
        return;
    }
    else if(c=='e'){
        return;
    }
    else if(c=='r'){
        return;
    }
    else if (c=='['){
        c=leeSiguiente();
        if (c=='a'){
            c=leeSiguiente();
            if(c=='('){
                c=leeSiguiente();
                if(c==')'){
                    c=leeSiguiente();
                    if(c==']'){
                        return;
                    }else error("Se espera ]",c);
                }else error("Se espera )",c);
            }else error("(",c);
        }else error("Se espera identificador",c);
    }
    else error("Se espera [",c);
}

void A(){
    if (c=='a'){
        c=leeSiguiente();
        if (c=='='){
            c==leeSiguiente();
            M();
            if (c==':'){
                return;
            }else error("Se espera :",c);
        }else error("Se espera =",c);
    }else error("Se espera identificador",c);
}

void M(){
    if (c=='(' ||c=='a' ||c=='e' ||c=='r' ||c=='[' ||c=='s'){
        QP();
        return;
    }
    else if(c=='+'){
        c=leeSiguiente();
        Q();
        Z();
        return;
    }else error("Se espera identificador, real, entero o string ( [ o +",c);
}

void Z(){
    if(c==','){
        c=leeSiguiente();
        Q();
        Z();
        return;
    }
    else if (c==':'){
        return;
    }
    else error("Se espera , o :",c);
}

void Q(){
    if(c=='a'){
        c=leeSiguiente();
        return;
    }
    else if(c=='s'){
        c=leeSiguiente();
        return;
    }
    else error("Se espera identificador o cadena",c);
    
}

void QP(){
    if(c=='s'){
        c=leeSiguiente();
        return;
    }
    else if(c=='(' ||c=='a' ||c=='e' ||c=='r' ||c=='[' ){
        E();
        return;
    }
    else error("Se espera identificador, real, entero o cadena ( [",c);
}


