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
        return;
    }else if (c==']' || c=='}')
    {
        return;
    }else
    {
        error();
    }
}

void D(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g')
    {
        V();
        L();
        if (c==':')
        {
            c=getchar();
        }else
        {
            error();
        }
        return;
    }else
    {
        error();
    }
    
}
    
void L(){
    if (c=='a')
    {
        c=getchar();
        G();
        C();
        return;
    }else
    {
        error();
    }
}
void C(){
    if (c==',')
    {
        c=getchar();
        L();
        return;
    }else if(c==':')
    {
        return;   
    }else
    {
        error();
    }
}
void V(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g')
    {
        c=getchar();
        return;
    }else
    {
        error();
    }
}
void G(){
    if (c=='[')
    {
        c=getchar();
        if (c=='e')
        {
            c=getchar();
            if (c==']')
            {
                c=getchar();
                return;
            }
            
        } 
    }
    else
    {
        error();
    }
}
void S(){
    if (/*PRODUCCION A*/)
    {
        /* code */
    }else if(c=='x'){
        X();
        return;
    }else if (c=='i')
    {
        I();
        return
    }else if (c=='w')
    {
        W();
        return;
    }else if (c=='h')
    {
        H();
        return;
    }else if (c=='p')
    {
        N();
        return;
    }else if (c=='u')
    {
        c=getchar();
        U();
        if (c==':')
        {
            c=getchar();
            return;
        }else
        {
            error();
        }
    }else if(c=='t'){
        c=getchar();
        if (c==':')
        {
            c=getchar();
            return;
        }else
        {
            error();
        }
    }else if (c=='[')
    {
        c=getchar();
        if (c=='a')
        {
            c=getchar();
            if (c=='(')
            {
                c=getchar();
                if (c==')')
                {
                    c=getchar();
                    if (c==']')
                    {
                        c==getchar();
                        if (c==':')
                        {
                            c=getchar();
                            return;
                        }else{error();}
                        
                    }else{error();}
                    
                }else{error();}
                
            }else{error();}
            
        }else{error();}
        
    }else{error();}
}   

void U(){
    if (c==':')
    {
        return;
    }else if(c=='('){
        c=getchar();
        F();
        if (c==')')
        {
            c=getchar();
        }else{ error();}
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
