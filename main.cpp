#include <iostream>
#include "driver.hh"
#include "syntax_tree.hh"
#include "IrVisitor.hh"
#include "errors/errors.hh"
#include "MIRBuilder.hh"
driver ddriver;
CompUnit *root;

int main (int argc, char *argv[])
{
    // std::cout << "start..." << std::endl;
    // if(argc < 2){
    //     std::cout << "please enter a file: ./main test.sy" <<std::endl;
    //     exit(0);
    // }
    root = ddriver.parse("../test/quickSort.sy");
    //root->visit(0);
    IrVisitor irVisitor;
    try {
        irVisitor.visit(root);
    }catch (SyntaxError &e) {
        std::cerr << "error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    MIRBuilder mirBuilder(irVisitor);
    mirBuilder.getPreAndSucc();

    irVisitor.print(std::cout);
    std::cout << "end..." <<std::endl;
    return 0;
}