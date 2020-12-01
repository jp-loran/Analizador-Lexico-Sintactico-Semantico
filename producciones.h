#include<stdio.h>
char c;
int n=0;
char* arrayAtomos=NULL;
size_t size;

// char leeSiguiente();

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

char leeSiguiente(){
    n++;
    return arrayAtomos[n];
}

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
        printf("Algo esta mal \n");
    }   
}
void DP(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g' || c=='[')
    {
        D();
        DP();
        printf("Estamos en DP \n");
        return;
    }else if(c==']'||c=='}')
    {
        return;
    }
    else
    {
        printf("Algo esta mal ***** \n");
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
        }else{printf("Algo esta mal ****** \n");}
        
        printf("Estamos en D \n");
    
    }else
    {
        printf("Algo esta mal ******** \n");  
    }
}
void V(){
    if (c=='b' || c=='c' || c=='f' || c=='n' || c=='g'){
        c=leeSiguiente();
        printf("Estamos en V \n");
        return;
    }else
    {
        printf("Algo esta mal \n");
    }
    
}
void L(){
    if (c=='a')
    {
        c=leeSiguiente();
        printf("Estamos en L: %c \n",c);
        G();
        C();
        return;
    }else
    {
        printf("Algo esta mal \n");
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
                printf("Estamos en L: %c \n",c);
                return;
            }else{printf("Algo esta mal \n");}
            
        }else{printf("Algo esta mal \n");}
        
    }else if(c==','){
        return;
    }
    else
    {
        printf("Algo esta mal \n");  
    }
    
    
}
void C(){
    if (c==',')
    {
        c=leeSiguiente();
        L();
        printf("Estamos en C \n");
        return;
    }else if(c==':'){
        return;
    }else
    {
        printf("Algo esta mal \n");  
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
                        //B();
                        if (c=='}')
                        {
                            c=leeSiguiente();
                            if (c==']')
                            {
                                c=leeSiguiente();
                                return;
                            }else{printf("Algo esta mal \n");}
                            
                        }else{printf("Algo esta mal \n");}
                        
                    }else{printf("Algo esta mal \n");}
                    
                }else{printf("Algo esta mal \n");}
                
            }else{printf("Algo esta mal \n");}
            
        }else{printf("Algo esta mal \n");}
        
    }else if(c==':'){
        return;
    }else
    {
        printf("Algo esta mal \n");  
    }   
}
void YP(){
    if (c=='[')
    {
        Y();
        YP();
        return;
    }else if (c=='\0')
    {
        return;
    }else
    {
        printf("Algo esta mal \n");  
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
    }
    
    
}
