#include <iostream>
#include "driver.hh"
// #include "syntax_tree_printer.hh"

driver ddriver;
CompUnit *root;

int main (int argc, char *argv[])
{
    std::cout << "start..." << std::endl;
    root = ddriver.parse(argv[1]);
    root->visit(0);
    std::cout << "end..." <<std::endl;
    return 0;
}
