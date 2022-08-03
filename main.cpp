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
driver ddriver;
CompUnit *root;
int main(int argc, char *argv[]) {

//    std::vector<int> v{1,2,5,6,7};
//    for (auto it = v.begin();it != v.end();it++) {
//        int x = *it;
//        if (x == 2) {
//            it = v.erase(it);
//            it = v.insert(it,3);
//            it = v.insert(it,4);
////            it = v.insert(it,3);
////            it = v.insert(it, 4);
////            it = v.insert(it,9);
////            it = v.insert(it,10);
//            it = it + 1;
//        }
//        std::cout << x << "\n";
//    }
////    for (int x:v) {
////        std::cout << x << "\n";
////    }
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
        std::cerr << "error: " << e.what()<< "\n";
        return EXIT_FAILURE;
    }
    MIRBuilder mirBuilder(irVisitor);
    mirBuilder.getPreAndSucc();
    if (optimize_O2) {
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
/*
 *
globalVars:
	const float @a = 10.5
	const float @x = -1
	const int* @qq
	int* @y
	int* @m
	const int @b = 20
.entryBB:
entry::BB0
	const int* @qq = AllocaI(4)
	int* @0 = GEP const int* @qq 0
	StoreI -3 int* @0
	int* @1 = GEP const int* @qq 1
	StoreI 2 int* @1
	int* @2 = GEP const int* @qq 2
	StoreI 7 int* @2
	int* @3 = GEP const int* @qq 3
	StoreI 8 int* @3
	int* @y = AllocaI
	StoreI 10 int* @y
	int* @m = AllocaI(5)
	int* @4 = GEP int* @m 0
	StoreI 1 int* @4
	int* @5 = GEP int* @m 1
	StoreI 2 int* @5
	int* @6 = GEP int* @m 2
	StoreI 3 int* @6
	int* @7 = GEP int* @m 3
	StoreI 4 int* @7
	int* @8 = GEP int* @m 4
	StoreI 5 int* @8
define void@quickSort(int* @0,int @1,int @2)
quickSort::BB0
	int** @3 = AllocaI
	StoreI int* @0 int** @3
	int* @4 = AllocaI
	StoreI int @1 int* @4
	int* @5 = AllocaI
	StoreI int @2 int* @5
	int* @6 = AllocaI
	int @7 = LoadI int* @4
	int* @8 = GEP const int* @qq int @7
	int @9 = LoadI int* @8
	StoreI int @9 int* @6
	int* @11 = AllocaI(5)
	int* @12 = GEP int* @11 0
	StoreI 1 int* @12
	int* @13 = GEP int* @11 1
	StoreI 2 int* @13
	int* @14 = GEP int* @11 2
	StoreI 3 int* @14
	int* @15 = GEP int* @11 3
	StoreI 4 int* @15
	int* @16 = GEP int* @11 4
	StoreI 5 int* @16
	float* @17 = AllocaF
	StoreF -3 float* @17
	int* @18 = AllocaI
	StoreI 3 int* @18
	int* @19 = AllocaI
	float @20 = LoadI float* @17
	float @21 = NEG float @20
	int @22 = LoadI int* @18
	float @23 = CastInt2Float int @22
	float @24 = DivF float @23 10.5
	float @25 = AddF float @21 float @24
	float @26 = AddF float @25 0
	int @27 = CastFloat2Int float @26
	StoreI int @27 int* @19
	int* @28 = AllocaI
	int* @29 = AllocaI
	int* @30 = AllocaI
	int* @31 = AllocaI
	int* @32 = LoadI int** @3
	int @33 = LoadI int* @28
	int* @34 = GEP int* @32 int @33
	int @35 = LoadI int* @29
	StoreI int @35 int* @34
	int @36 = LoadI int* @4
	int @37 = LoadI int* @5
	int @38 = LTI int @36 int @37
	goto int @38 ？ quickSort::BB5 : quickSort::BB32
quickSort::BB5
	int @39 = LoadI int* @4
	StoreI int @39 int* @30
	int @40 = LoadI int* @4
	StoreI int @40 int* @28
	int @41 = LoadI int* @5
	StoreI int @41 int* @29
	goto quickSort::BB9
quickSort::BB9
	int @42 = LoadI int* @28
	int @43 = LoadI int* @29
	int @44 = LTI int @42 int @43
	goto int @44 ？ quickSort::BB15 : quickSort::BB30
quickSort::BB15
	int* @45 = LoadI int** @3
	int @46 = LoadI int* @28
	int* @47 = GEP int* @45 int @46
	int @48 = LoadI int* @47
	int* @49 = LoadI int** @3
	int @50 = LoadI int* @30
	int* @51 = GEP int* @49 int @50
	int @52 = LoadI int* @51
	int @53 = LEI int @48 int @52
	goto int @53 ？ quickSort::BB16 : quickSort::BB22
quickSort::BB16
	int @54 = LoadI int* @28
	int @55 = LoadI int* @5
	int @56 = LTI int @54 int @55
	goto int @56 ？ quickSort::BB17 : quickSort::BB22
quickSort::BB17
	int @57 = LoadI int* @28
	int @58 = AddI int @57 1
	StoreI int @58 int* @28
	goto quickSort::BB15
quickSort::BB22
	int* @59 = LoadI int** @3
	int @60 = LoadI int* @29
	int* @61 = GEP int* @59 int @60
	int @62 = LoadI int* @61
	int* @63 = LoadI int** @3
	int @64 = LoadI int* @30
	int* @65 = GEP int* @63 int @64
	int @66 = LoadI int* @65
	int @67 = GTI int @62 int @66
	goto int @67 ？ quickSort::BB23 : quickSort::BB27
quickSort::BB23
	int @68 = LoadI int* @29
	int @69 = SubI int @68 1
	StoreI int @69 int* @29
	goto quickSort::BB22
quickSort::BB27
	int @70 = LoadI int* @28
	int @71 = LoadI int* @29
	int @72 = LTI int @70 int @71
	goto int @72 ？ quickSort::BB28 : quickSort::BB9
quickSort::BB28
	int* @73 = LoadI int** @3
	int @74 = LoadI int* @28
	int* @75 = GEP int* @73 int @74
	int @76 = LoadI int* @75
	StoreI int @76 int* @31
	int* @77 = LoadI int** @3
	int @78 = LoadI int* @28
	int* @79 = GEP int* @77 int @78
	int* @80 = LoadI int** @3
	int @81 = LoadI int* @29
	int* @82 = GEP int* @80 int @81
	int @83 = LoadI int* @82
	StoreI int @83 int* @79
	int* @84 = LoadI int** @3
	int @85 = LoadI int* @29
	int* @86 = GEP int* @84 int @85
	int @87 = LoadI int* @31
	StoreI int @87 int* @86
	goto quickSort::BB9
quickSort::BB30
	int* @88 = LoadI int** @3
	int @89 = LoadI int* @30
	int* @90 = GEP int* @88 int @89
	int @91 = LoadI int* @90
	StoreI int @91 int* @31
	int* @92 = LoadI int** @3
	int @93 = LoadI int* @30
	int* @94 = GEP int* @92 int @93
	int* @95 = LoadI int** @3
	int @96 = LoadI int* @29
	int* @97 = GEP int* @95 int @96
	int @98 = LoadI int* @97
	StoreI int @98 int* @94
	int* @99 = LoadI int** @3
	int @100 = LoadI int* @29
	int* @101 = GEP int* @99 int @100
	int @102 = LoadI int* @31
	StoreI int @102 int* @101
	int* @103 = LoadI int** @3
	int @104 = LoadI int* @4
	int @105 = LoadI int* @29
	int @106 = SubI int @105 1
	call quickSort(int* @103 , int @104 , int @106)
	int* @107 = LoadI int** @3
	int @108 = LoadI int* @29
	int @109 = AddI int @108 1
	int @110 = LoadI int* @5
	call quickSort(int* @107 , int @109 , int @110)
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