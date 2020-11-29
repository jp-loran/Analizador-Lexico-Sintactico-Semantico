#include <stdio.h> 

void P();
void YP();
void Y();
void VP();
void DP();
void B();
void error();
char leerSiguiente(char atomo[]);

char c;
char n;


void P(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g' || c=='[')
    {
        DP();
        Y();
        YP();
        return;
    }
    else
    {
        error();
    }   
}
void YP(){
    if (c=='[')
    {
        Y();
        YP();
    }
    else if(c == '\0'){
        return;
    }
    else
    {
        error();
    }
}
void Y(){
    if (c=='[')
    {
        c=getchar();
        VP();
        if (c=='a')
        {
            c=getchar();
            if (c=='(')
            {
                c=getchar();
                if (c==')')
                {
                    c=getchar();
                    if (c=='{')
                    {
                        c=getchar();
                        DP();
                        B();
                        if (c=='}')
                        {
                            c=getchar();
                            if (c==']')
                            {
                                c=getchar();
                            } else{ error(); }
                            
                        } else{ error(); }
                        
                    } else{ error(); }
                    
                } else{ error(); }
                
            } else{ error(); }
            
        } else{ error(); }
    }else{ error(); }
    
}
void VP(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g')
    {
        V();
    }
    else if(c=='o'){
        c=getchar();
        return;
    }
    else
    {
        error();
    }
}
void DP(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g')
    {
        D();
        DP();
    }else if (c==']' || c=='}')
    {
        return;
    }
    
    

}

void B(){
    printf("Produccion B");
}

/*Función de error*/

void error(){
    printf("Encontré un error");
}

char leerSiguiente(char atomo[]){
    return atomo[n+1];
}
