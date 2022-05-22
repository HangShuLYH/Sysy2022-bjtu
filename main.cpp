#include <iostream>
#include "driver.hh"
#include "syntax_tree.hh"
#include "IrVisitor.hh"
driver ddriver;
CompUnit *root;

int main (int argc, char *argv[])
{
    // std::cout << "start..." << std::endl;
    // if(argc < 2){
    //     std::cout << "please enter a file: ./main test.sy" <<std::endl;
    //     exit(0);
    // }
    root = ddriver.parse("../test/test.sy");
    //root->visit(0);
    IrVisitor irVisitor;
    irVisitor.visit(root);
    irVisitor.print();
    irVisitor.getRelated();
    std::cout << "end..." <<std::endl;
    return 0;
}