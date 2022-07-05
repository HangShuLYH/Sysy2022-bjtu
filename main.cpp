#include <iostream>
#include "driver.hh"
#include "syntax_tree.hh"
#include "IrVisitor.hh"
#include "errors/errors.hh"
#include "MIRBuilder.hh"
#include "codegen.hh"
driver ddriver;
CompUnit *root;

int main (int argc, char *argv[])
{
    // std::cout << "start..." << std::endl;
    // if(argc < 2){
    //     std::cout << "please enter a file: ./main test.sy" <<std::endl;
    //     exit(0);
    // }
    root = ddriver.parse("../test/lin1.sy");
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
    Codegen codegen(irVisitor);
    codegen.regAlloc();
    std::cout << "end..." <<std::endl;
    return 0;
}
/*
 *
 * end pre and succ:
globalVars:
	int* @a
.entryBB:
entry::BB0
	int* @a = AllocaI
	StoreI 1 int* @a
define int@f(int @0)
f::BB0
	int* @1 = AllocaI
	StoreI int @0 int* @1
	goto f::BB6
f::BB6
	int @2 = LoadI int* @a
	int @3 = EQUI int @2 1
	goto int @3 ？ f::BB7 : f::BB9
f::BB7
	int* @4 = AllocaI
	int @5 = LoadI int* @a
	StoreI int @5 int* @4
	goto f::BB6
f::BB9
	ret int 0
define int@main()
main::BB5
	int @0 = LoadI int* @a
	int @1 = EQUI int @0 1
	goto int @1 ？ main::BB6 : main::BB8
main::BB6
	int* @2 = AllocaI
	int @3 = LoadI int* @a
	StoreI int @3 int* @2
	goto main::BB5
main::BB8
	ret int 0
 * */