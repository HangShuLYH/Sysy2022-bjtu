%{
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>

#include "driver.hh"
#include "parser.hh"

# undef yywrap
# define yywrap() 1

#define YY_USER_ACTION  loc.columns (yyleng);

#define YY_NO_UNISTD_H

extern driver ddriver;
%}
%option noyywrap nounput batch debug noinput
%x COMMENT

digit [0-9]
nonzeroDigit [1-9]
octalDigit [0-7]
hexadecimalDigit [0-9a-fA-F]
hexadecimalPrefix "0x"|"0X"
decimalConst {nonzeroDigit}{digit}*
octalConst "0"{octalDigit}*
hexcadecimalConst {hexadecimalPrefix}{hexadecimalDigit}*

digitSequence {digit}+
fractionalPart ({digitSequence}"\."{digitSequence}?)|({digitSequence}?"\."{digitSequence})
exponentPart ("e"|"E")("+"|"-")?{digitSequence}
decimalFractionalConst {fractionalPart}{exponentPart}?
decimalNofractionConst {digitSequence}{exponentPart}
hexadecimalDigitSequence {hexadecimalDigit}+
hexadecimalFractionalPart ({hexadecimalDigitSequence}"\."{hexadecimalDigitSequence}?)|({hexadecimalDigitSequence}?"\."{hexadecimalDigitSequence})
binaryExponentPart ("P"|"p")("+"|"-")?{digitSequence}
hexadecimalFractionalConst {hexadecimalPrefix}{hexadecimalFractionalPart}{binaryExponentPart}
hexadecimalNofractionConst {hexadecimalPrefix}{hexadecimalDigitSequence}{binaryExponentPart}
letter [A-Za-z_]
ident {letter}({letter}|{digit})*

%%
"/*" {
    BEGIN(COMMENT);
}
<COMMENT>"*/" {
    BEGIN(INITIAL);
}
<COMMENT>([^*]|\n)+|.
<COMMENT><<EOF>> {
    std::cout << "Error:Unterminated comment!" << std::endl;
    BEGIN(INITIAL);
}
"//".*\n
[ \t\n\f] {
    ;
}
"void" {
    return yy::parser::make_VOID(loc);
}
"int" {
     return yy::parser::make_INT(loc);
}
"float" {
      return yy::parser::make_FLOAT(loc);
}
"const" {
      return yy::parser::make_CONST(loc);
}
"if" {
    return yy::parser::make_IF(loc);
}
"else" {
    return yy::parser::make_ELSE(loc);
}
"while" {
    return yy::parser::make_WHILE(loc);
}
"break" {
    return yy::parser::make_BREAK(loc);
}
"continue" {
    return yy::parser::make_CONTINUE(loc);
}
"return" {
    return yy::parser::make_RETURN(loc);
}
{ident} {
    return yy::parser::make_IDENTIFIER(ddriver.lexer.YYText(),loc);
}
{decimalConst} {
    return yy::parser::make_INTCONST((int)std::strtol(ddriver.lexer.YYText(),NULL,10),loc);
}
{octalConst} {
    return yy::parser::make_INTCONST((int)std::strtol(ddriver.lexer.YYText(),NULL,8),loc);
}
{hexcadecimalConst} {
    return yy::parser::make_INTCONST((int)std::strtol(ddriver.lexer.YYText(),NULL,16),loc);
}
{decimalFractionalConst} {
    return yy::parser::make_FLOATCONST((float)atof(ddriver.lexer.YYText()),loc);
}
{decimalNofractionConst} {
    float x;
    sscanf(ddriver.lexer.YYText(), "%f",&x);
    return yy::parser::make_FLOATCONST(x,loc);
}
{hexadecimalFractionalConst} {
    float x;
    sscanf(ddriver.lexer.YYText(), "%f",&x);
    return yy::parser::make_FLOATCONST(x,loc);
}
{hexadecimalNofractionConst} {
    float x;
    sscanf(ddriver.lexer.YYText(), "%f",&x);
    return yy::parser::make_FLOATCONST(x,loc);
}
"<=" {
    return yy::parser::make_LE(loc);
}
"<" {
    return yy::parser::make_LT(loc);
}
">=" {
    return yy::parser::make_GE(loc);
}
">" {
    return yy::parser::make_GT(loc);
}
"==" {
    return yy::parser::make_EQU(loc);
}
"=" {
    return yy::parser::make_ASSIGN(loc);
}
"+" {
    return yy::parser::make_ADD(loc);
}
"-" {
    return yy::parser::make_SUB(loc);
}
"*" {
    return yy::parser::make_MUL(loc);
}
"/" {
    return yy::parser::make_DIV(loc);
}
"%" {
    return yy::parser::make_MOD(loc);
}
";" {
    return yy::parser::make_SEMICOLON(loc);
}
"," {
    return yy::parser::make_COMMA(loc);
}
"(" {
    return yy::parser::make_LB(loc);
}
")" {
    return yy::parser::make_RB(loc);
}
"{" {
    return yy::parser::make_BLB(loc);
}
"}" {
    return yy::parser::make_BRB(loc);
}
"[" {
    return yy::parser::make_MLB(loc);
}
"]" {
    return yy::parser::make_MRB(loc);
}
"&&" {
    return yy::parser::make_AND(loc);
}
"||" {
    return yy::parser::make_OR(loc);
}
"!=" {
    return yy::parser::make_NE(loc);
}
"!" {
    return yy::parser::make_NOT(loc);
}

<<EOF>> {
    return yy::parser::make_END(loc);
}

. {
std::cout << "Lex Error!" << std::endl;
}
%%

int yyFlexLexer::yylex() {
    std::cerr << "'int yyFlexLexer::yylex()' should never be called." << std::endl;
    exit(1);
}
