%{
    #include "main.h"
%}
delim [ \t\n\r]
whitespace {delim}+
digit [0-9]
nonzeroDigit [1-9]
octalDigit [0-7]
hexadecimalDigit [0-9a-fA-F]
hexadecimalPrefix "0x"|"0X"
decimalConst {nonzeroDigit}{digit}*
octalConst "0"{octalDigit}*
hexcadecimalConst {hexadecimalPrefix}{hexadecimalDigit}*
digitSequence {digit}+
fractionalPart {digitSequence}"\."{digitSequence}?
exponentPart ("e"|"E")("+"|"-"){digitSequence}
decimalFractionalConst {fractionalPart}{exponentPart}
decimalNofractionConst {digitSequence}{exponentPart}
hexadecimalDigitSequence {hexadecimalDigit}+
hexadecimalFractionalPart {hexadecimalDigitSequence}"\."{hexadecimalDigitSequence}?
binaryExponentPart ("P"|"p")("+"|"-"){digitSequence}
hexadecimalFractionalConst {hexadecimalPrefix}{hexadecimalFractionalPart}{binaryExponentPart}
hexadecimalNofractionConst {hexadecimalPrefix}{hexadecimalDigitSequence}{binaryExponentPart}
letter [A-Za-z_]
ident {letter}({letter}|{digit})*
wrongIdent ({digit}+){letter}({letter}|{digit})*
lineComment "//"[^\n]*
comment "/*"([^\*]|(\*)*[^\*/])*(\*)*"*/"
%%
{whitespace} {;}
{comment} {;}
{lineComment} {;}
"int" {
     return INT;
}
"float" {
      return FLOAT;
}
"if" {
    return IF;
}
"else" {
    return ELSE;
}
"while" {
    return WHILE;
}
"break" {
    return BREAK;
}
"continue" {
    return CONTINUE;
}
"return" {
    return RETURN;
}
{ident} {
    return IDENT;
}
{decimalConst} {
    /*TODO:
    需要计算值
    */
    return INTCONST;
}
{octalConst} {
    /*TODO:
    需要计算值
    */
    return INTCONST;
}
{hexcadecimalConst} {
    /*TODO:
    需要计算值
    */
    return INTCONST;
}
{decimalFractionalConst} {
    /*TODO:
    需要计算值
    */
    return INTCONST;
}
{decimalNofractionConst} {
    /*TODO:
    需要计算值
    */
    return FLOATCONST;
}
{hexadecimalFractionalConst} {
    /*TODO:
    需要计算值
    */
    return FLOATCONST;
}
{hexadecimalNofractionConst} {
    /*TODO:
    需要计算值
    */
    return FLOATCONST;
}
"<=" {
    return LE;
}
"<" {
    return LT;
}
">=" {
    return GE;
}
">" {
    return GT;
}
"==" {
    return EQU;
}
"=" {
    return ASSIGN;
}
"+" {
    return ADD;
}
"-" {
    return SUB;
}
"*" {
    return MUL;
}
"/" {
    return DIV;
}
"%" {
    return MOD;
}
";" {
    return SEMICOLON;
}
"," {
    return COMMA;
}
"(" {
    return LB;
}
")" {
    return RB;
}
"{" {
    return BLB;
}
"}" {
    return BRB;
}
"[" {
    return MLB;
}
"]" {
    return MRB;
}
"&&" {
    return AND;
}
"||" {
    return OR;
}
"!=" {
    return NE;
}
"!" {
    return NOT;
}
{wrongIdent} {;}
%%
int yywrap(){
    return 1;
}