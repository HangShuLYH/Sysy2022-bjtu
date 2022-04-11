cmake_minimum_required(VERSION 3.21)
project(Compiler)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-error=register -std=c++11")
set(CMAKE_CXX_STANDARD 11)

add_executable(Compiler main.cpp Lexer/main.h Lexer/lex.yy.cpp)


#gcc -o xxx lex.yy.c main.c -lfl