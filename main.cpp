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
//    Codegen codegen(irVisitor,std::cerr);
//    codegen.generateProgramCode();
    //codegen.regAlloc();
    if(irVisitor.functions[1] == NULL) {
        std::cout << "NULL!\n";
    } else {
        std::cout << "ok\n";
    }
    std::cout << "end..." <<std::endl;
    return 0;
}
/*
 *
 globalVars:
	const float @a = 10.5
	const float @x = -1
	const int* @qq
	const int @b = 20
.entryBB:
entry::BB0
	const int* @qq = AllocaI(8)
	int* @0 = GEP const int* @qq 0
	StoreI -3 int* @0
	int* @1 = GEP const int* @qq 1
	StoreI 2 int* @1
	int* @3 = GEP const int* @qq 2
	StoreI 3 int* @3
	int* @3 = GEP const int* @qq 3
	StoreI 0 int* @3
	int* @5 = GEP const int* @qq 4
	StoreI 5 int* @5
	int* @5 = GEP const int* @qq 5
	StoreI 0 int* @5
	int* @6 = GEP const int* @qq 6
	StoreI 7 int* @6
	int* @7 = GEP const int* @qq 7
	StoreI 8 int* @7
define void@quickSort(int* @0,int @1,int @2)
quickSort::BB0
	int** @3 = AllocaI
	StoreI int* @0 int** @3
	int* @4 = AllocaI
	StoreI int @1 int* @4
	int* @5 = AllocaI
	StoreI int @2 int* @5
	int* @6 = AllocaI
	StoreI const int* @qq int* @6
	int* @8 = AllocaI(5)
	int* @9 = GEP int* @8 0
	StoreI 1 int* @9
	int* @10 = GEP int* @8 1
	StoreI 2 int* @10
	int* @11 = GEP int* @8 2
	StoreI 3 int* @11
	int* @12 = GEP int* @8 3
	StoreI 4 int* @12
	int* @13 = GEP int* @8 4
	StoreI 5 int* @13
	float* @14 = AllocaF
	StoreF 2 float* @14
	int* @16 = AllocaI
	StoreI 3 int* @16
	int* @17 = AllocaI
	float @18 = LoadI float* @14
	float @19 = NEG float @18
	int @20 = LoadI int* @16
	float @21 = CastInt2Float int @20
	float @22 = DivF float @21 10.5
	float @23 = AddF float @19 float @22
	float @24 = AddF float @23 0
	int @25 = CastFloat2Int float @24
	StoreI int @25 int* @17
	int* @26 = AllocaI
	int* @27 = AllocaI
	int* @28 = AllocaI
	int* @29 = AllocaI
	int* @30 = LoadI int** @3
	int @31 = LoadI int* @26
	int* @32 = GEP int* @30 int @31
	int @33 = LoadI int* @27
	StoreI int @33 int* @32
	int @34 = LoadI int* @4
	int @35 = LoadI int* @5
	int @36 = LTI int @34 int @35
	goto int @36 ？ quickSort::BB5 : quickSort::BB32
quickSort::BB5
	int @37 = LoadI int* @4
	StoreI int @37 int* @28
	int @38 = LoadI int* @4
	StoreI int @38 int* @26
	int @39 = LoadI int* @5
	StoreI int @39 int* @27
	goto quickSort::BB9
quickSort::BB9
	int @40 = LoadI int* @26
	int @41 = LoadI int* @27
	int @42 = LTI int @40 int @41
	goto int @42 ？ quickSort::BB15 : quickSort::BB30
quickSort::BB15
	int* @43 = LoadI int** @3
	int @44 = LoadI int* @26
	int* @45 = GEP int* @43 int @44
	int @46 = LoadI int* @45
	int* @47 = LoadI int** @3
	int @48 = LoadI int* @28
	int* @49 = GEP int* @47 int @48
	int @50 = LoadI int* @49
	int @51 = LEI int @46 int @50
	goto int @51 ？ quickSort::BB16 : quickSort::BB22
quickSort::BB16
	int @52 = LoadI int* @26
	int @53 = LoadI int* @5
	int @54 = LTI int @52 int @53
	goto int @54 ？ quickSort::BB17 : quickSort::BB22
quickSort::BB17
	int @55 = LoadI int* @26
	int @56 = AddI int @55 1
	StoreI int @56 int* @26
	goto quickSort::BB15
quickSort::BB22
	int* @57 = LoadI int** @3
	int @58 = LoadI int* @27
	int* @59 = GEP int* @57 int @58
	int @60 = LoadI int* @59
	int* @61 = LoadI int** @3
	int @62 = LoadI int* @28
	int* @63 = GEP int* @61 int @62
	int @64 = LoadI int* @63
	int @65 = GTI int @60 int @64
	goto int @65 ？ quickSort::BB23 : quickSort::BB27
quickSort::BB23
	int @66 = LoadI int* @27
	int @67 = SubI int @66 1
	StoreI int @67 int* @27
	goto quickSort::BB22
quickSort::BB27
	int @68 = LoadI int* @26
	int @69 = LoadI int* @27
	int @70 = LTI int @68 int @69
	goto int @70 ？ quickSort::BB28 : quickSort::BB9
quickSort::BB28
	int* @71 = LoadI int** @3
	int @72 = LoadI int* @26
	int* @73 = GEP int* @71 int @72
	int @74 = LoadI int* @73
	StoreI int @74 int* @29
	int* @75 = LoadI int** @3
	int @76 = LoadI int* @26
	int* @77 = GEP int* @75 int @76
	int* @78 = LoadI int** @3
	int @79 = LoadI int* @27
	int* @80 = GEP int* @78 int @79
	int @81 = LoadI int* @80
	StoreI int @81 int* @77
	int* @82 = LoadI int** @3
	int @83 = LoadI int* @27
	int* @84 = GEP int* @82 int @83
	int @85 = LoadI int* @29
	StoreI int @85 int* @84
	goto quickSort::BB9
quickSort::BB30
	int* @86 = LoadI int** @3
	int @87 = LoadI int* @28
	int* @88 = GEP int* @86 int @87
	int @89 = LoadI int* @88
	StoreI int @89 int* @29
	int* @90 = LoadI int** @3
	int @91 = LoadI int* @28
	int* @92 = GEP int* @90 int @91
	int* @93 = LoadI int** @3
	int @94 = LoadI int* @27
	int* @95 = GEP int* @93 int @94
	int @96 = LoadI int* @95
	StoreI int @96 int* @92
	int* @97 = LoadI int** @3
	int @98 = LoadI int* @27
	int* @99 = GEP int* @97 int @98
	int @100 = LoadI int* @29
	StoreI int @100 int* @99
	int* @101 = LoadI int** @3
	int @102 = LoadI int* @4
	int @103 = LoadI int* @27
	int @104 = SubI int @103 1
	call quickSort(int* @101 , int @102 , int @104)
	int* @105 = LoadI int** @3
	int @106 = LoadI int* @27
	int @107 = AddI int @106 1
	int @108 = LoadI int* @5
	call quickSort(int* @105 , int @107 , int @108)
	goto quickSort::BB32
quickSort::BB32
	ret
define int@main()
main::BB0
	int* @0 = AllocaI
	StoreI 20 int* @0
	int* @1 = AllocaI(9)
	int* @2 = GEP int* @1 0
	StoreI 1 int* @2
	int* @3 = GEP int* @1 1
	StoreI 2 int* @3
	int* @4 = GEP int* @1 2
	StoreI 3 int* @4
	int* @5 = GEP int* @1 3
	StoreI 4 int* @5
	int* @6 = GEP int* @1 4
	StoreI 5 int* @6
	int* @7 = GEP int* @1 5
	StoreI 6 int* @7
	int* @8 = GEP int* @1 6
	StoreI 7 int* @8
	int* @9 = GEP int* @1 7
	StoreI 8 int* @9
	int* @10 = GEP int* @1 8
	StoreI 9 int* @10
	call quickSort(int* @1 , 0 , 8)
	ret int 0
 * */