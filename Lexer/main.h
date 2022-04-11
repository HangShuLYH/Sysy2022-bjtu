//
// Created by 6220302 on 2022-04-10.
//

#ifndef COMPILER_MAIN_H
#define COMPILER_MAIN_H

#include <string>
#include <stdio.h>
typedef enum TokenKind{
    /*去除0*/
    START,
    /*标识符*/
    IDENT,
    /*数字常量*/
    INTCONST, //整型数
    FLOATCONST,  //浮点数
    /*算术运算符*/
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    /*关系运算符*/
    EQU,    //==
    NE,    //!=
    LT,     //<
    GT,    //>
    LE,    //<=
    GE,     //>=
    /*逻辑运算符*/
    NOT,
    AND,
    OR,
    /*赋值运算符*/
    ASSIGN,
    /*保留字*/
    INT,
    FLOAT,
    IF,
    ELSE,
    WHILE,
    BREAK,
    CONTINUE,
    RETURN,
    /*单界限分界符*/
    SEMICOLON, //  ;
    COMMA,  //  ,
    LB,   // (
    RB,   // )
    BLB,  //  {
    BRB,  //  }
    MLB,   // [
    MRB,   // ]

}TokenKind;
typedef struct Type{
    int intVal;
    float floatVal;
}Type;
#define YYSTYPE Type

#endif //COMPILER_MAIN_H
