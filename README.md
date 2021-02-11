# Analizador Lexico Sintáctico y Semántico
Analizador desarrollado en lex/flex, el cual realiza primero un análisis léxico, después un análisis sintáctico y finalmente un análisis semántico recursivo.  
La gramática y lenguaje que reconoce el analizador se encuentran en el archivo **gramatica.pdf**.  
Las funciones que realiza son las siguientes:

- Generación de tokens  
- Generación de cadena de átomos  
- Identificar componentes léxicos  
- Señalar errores de sintáxis  
- Señalar variables no declaradas  
- Señalar variables declaradas más de una vez  

## Instrucciones de ejecución
Para su ejecución en una terminal de Linux:
1. flex lexico-sintactico.l
2. gcc lex.yy.c -lfl
3. ./a.out prueba.txt
