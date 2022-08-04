
add_library(
        driver
        driver.cc
        IrVisitor.cc Value.cc)

add_library(
        lexer STATIC
        lexer.cc
)

add_library(
        parser STATIC
        parser.cc
)
add_library(
        syntax_tree STATIC
        syntax_tree.cc
)
target_link_libraries(
        driver
        parser
        lexer
        syntax_tree
)