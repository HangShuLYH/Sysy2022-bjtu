%{
    #include "main.h"
    extern "C"{
        void yyerror(const char *s);
        extern int yylex(void);
    }
%}

%token<intVal> INTCONST
%token<floatVal> FLOATCONST
%token<str> STRING IDENT EQU NE LE GE AND OR INT FLOAT IF ELSE WHILE BREAK CONTINUE RETURN
%token<ch> CHAR ADD SUB MUL DIV MOD LT GT NOT ASSIGN SEMICOLON COMMA LB RB BLB BRB
%%

%%