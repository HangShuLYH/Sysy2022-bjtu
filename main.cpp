#include <iostream>
#include "driver.hh"
#include "syntax_tree.hh"
#include "IrVisitor.hh"
#include "errors.hh"
#include "MIRBuilder.hh"
#include "codegen.hh"
#include "DominateTree.hh"
#include "Mem2reg.hh"
#include "OptimizeAdaptor.hh"
#include <sys/resource.h>

driver ddriver;
CompUnit *root;
int main(int argc, char *argv[]) {
    // increase stack size
    const rlim_t kStackSize = 64L * 1024L * 1024L;
    struct rlimit rl;
    int result;
    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0) {
        if (rl.rlim_cur < kStackSize) {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
                std::cerr << "setrlimit failed, use ulimit -s unlimited instead."
                          << std::endl;
        }
    }
    std::string inputFileName;
    std::string outputFileName = "a.s";
    bool printAST = false;
    bool printIR = false;
    bool optimize_O2 = false;
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-o") {
            outputFileName = argv[i + 1];
            i++;
        } else if (std::string(argv[i]) == "-g") {
            printIR = true;
        } else if (std::string(argv[i]) == "-tree") {
            printAST = true;
        } else if (std::string(argv[i]) == "-O2") {
            optimize_O2 = true;
        } else {
            inputFileName = argv[i];
        }
    }

    root = ddriver.parse(inputFileName);
    if (printAST) {
        root->visit(0);
    }
    IrVisitor irVisitor;
    try {
        irVisitor.visit(root);
    } catch (SyntaxError &e) {
        std::cerr << "error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    MIRBuilder mirBuilder(irVisitor);
    mirBuilder.getPreAndSucc();
    if (false) {
        DominateTree dominateTree(&irVisitor);
        dominateTree.execute();

        Mem2reg mem2reg(&irVisitor);
        mem2reg.execute();

        optimizeAdaptor(&irVisitor);
        moveBackOperand(&irVisitor);
    }

    if (printIR) {
        irVisitor.print(std::cout);
    }
    std::ofstream out(outputFileName);
    Codegen codegen(irVisitor, out);
    codegen.generateProgramCode();
//codegen.regAlloc();
//std::cout << "end..." <<std::endl;
    return 0;
}