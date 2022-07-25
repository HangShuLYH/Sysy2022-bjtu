#include <iostream>
#include "driver.hh"
#include "syntax_tree.hh"
#include "IrVisitor.hh"
#include "errors/errors.hh"
#include "MIRBuilder.hh"
#include "optimize/DominateTree.hh"
#include "optimize/Mem2reg.hh"
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
    try {
        irVisitor.visit(root);
    }catch (SyntaxError &e) {
        std::cerr << "error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    MIRBuilder mirBuilder(&irVisitor);
    mirBuilder.getPreAndSucc();

    DominateTree dominateTree(&irVisitor);
    dominateTree.execute();
    
    Mem2reg mem2reg(&irVisitor);
    mem2reg.execute();

    irVisitor.print(std::cout);

    std::cout << "end..." <<std::endl;
    return 0;
}