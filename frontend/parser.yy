/* file: parser.y */

/* 使用指令％skeleton "glr.cc"选择C++解析器的骨架  skeleton "glr.cc"*/
%skeleton "lalr1.cc"
%require "3.5"
%defines
//%define parser_class_name {parser}
%define api.parser.class {parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <string>
#include "syntax_tree.hh"
class driver;
}
%param {driver& ddriver }
// Location tracking
%locations
%initial-action
{
    // Initialize the initial location.
    @$.begin.filename = @$.end.filename = &ddriver.file;
};

// Enable tracing and verbose errors (which may be wrong!)
%define parse.trace
%define parse.error verbose

// Parser needs to know about the driver:
%code
{
#include "driver.hh"
#define yylex ddriver.lexer.yylex
}

%define api.token.prefix {TOK_}

%token VOID INT FLOAT CONST IF ELSE WHILE BREAK CONTINUE RETURN
%token <std::string>IDENTIFIER
%token <int>INTCONST
%token <float>FLOATCONST
%token LE LT GE GT EQU NE
%token ASSIGN
%token ADD SUB MUL DIV MOD
%token SEMICOLON COMMA LB RB BLB BRB MLB MRB
%token AND OR NOT
%token END

%type <CompUnit*>Begin
%type <CompUnit*>CompUnit
%type <DeclDef*>DeclDef
%type <ConstDecl*>ConstDecl
%type <ConstDef*>ConstDef
%type <ConstDefList*>ConstDefList
%type <ConstExpList*>ConstExpList
%type <ConstInitVal*>ConstInitVal
%type <ConstInitValList*>ConstInitValList
%type <VarDecl*>VarDecl
%type <VarDefList*>VarDefList
%type <VarDef*>VarDef
%type <InitVal*>InitVal
%type <InitValList*>InitValList
%type <FuncDef*>FuncDef
%type <DefType*>DefType
%type <FuncFParams*>FuncFParams
%type <FuncFParam*>FuncFParam
%type <ParamArrayExpList*>ParamArrayExpList
%type <Block*>Block
%type <BlockItemList*>BlockItemList
%type <BlockItem*>BlockItem
%type <Stmt*>Stmt
%type <Exp*>Exp
%type <Cond*>Cond
%type <LVal*>LVal
%type <PrimaryExp*>PrimaryExp
%type <Number*>Number
%type <UnaryExp*>UnaryExp
%type <UnaryOp*>UnaryOp
%type <FuncRParams*>FuncRParams
%type <MulExp*>MulExp
%type <AddExp*>AddExp
%type <RelExp*>RelExp
%type <EqExp*>EqExp
%type <LAndExp*>LAndExp
%type <LOrExp*>LOrExp
%type <ConstExp*>ConstExp

%start Begin

%%
Begin: CompUnit END {
        ddriver.root = $1;
        return 0;
    }
    ;
CompUnit: CompUnit DeclDef {
        $1->declDefList.push_back(std::shared_ptr<DeclDef>($2));
        $$=$1;
    }
    | DeclDef{
        $$=new CompUnit();
        $$->declDefList.push_back(std::shared_ptr<DeclDef>($1));
    }
    ;
DeclDef: ConstDecl{
        $$=new DeclDef();
        $$->constDecl=std::shared_ptr<ConstDecl>($1);
    }
    | VarDecl{
        $$=new DeclDef();
        $$->varDecl=std::shared_ptr<VarDecl>($1);
    }
    | FuncDef{
        $$=new DeclDef();
        $$->funcDef=std::shared_ptr<FuncDef>($1);
    }
    ;
ConstDecl: CONST DefType ConstDefList SEMICOLON{
        $$=new ConstDecl();
        $$->constDefList.swap($3->constDefList);
        $$->defType=std::shared_ptr<DefType>($2);
    }
	;
ConstDefList: ConstDefList COMMA ConstDef{
    $1->constDefList.push_back(std::shared_ptr<ConstDef>($3));
    $$=$1;
}
	| ConstDef{
    $$=new ConstDefList();
    $$->constDefList.push_back(std::shared_ptr<ConstDef>($1));
  }
  ;

ConstDef: IDENTIFIER ConstExpList ASSIGN ConstInitVal{
        $$=new ConstDef();
        $$->identifier=$1;
        $$->constExpList.swap($2->constExpList);
        $$->constInitVal=std::shared_ptr<ConstInitVal>($4);
    }
    ;
ConstExpList: ConstExpList BLB ConstExp BRB{
        $1->constExpList.push_back(std::shared_ptr<ConstExp>($3));
        $$=$1;
    }
    | %empty{
        $$=new ConstExpList();
    }
    ;

ConstInitVal:ConstExp{
    $$=new ConstInitVal();
    $$->constExp=std::shared_ptr<ConstExp>($1);
}
	| BLB ConstInitValList BRB{
    $$=new ConstInitVal();
    $$->constInitValList.swap($2->constInitValList);
  }
	| BLB BRB{
    $$=new ConstInitVal();
  }
	;
ConstInitValList:ConstInitValList COMMA ConstInitVal{
    $1->constInitValList.push_back(std::shared_ptr<ConstInitVal>($3));
    $$=$1;
}
	| ConstInitVal{
    $$=new ConstInitValList();
    $$->constInitValList.push_back(std::shared_ptr<ConstInitVal>($1));
  }
	;

VarDecl:DefType VarDefList SEMICOLON{
    $$=new VarDecl();
    $$->varDefList.swap($2->varDefList);
    $$->defType=std::shared_ptr<DefType>($1);
}
    ;

VarDefList:VarDefList COMMA VarDef{
    $1->varDefList.push_back(std::shared_ptr<VarDef>($3));
    $$=$1;
}
	| VarDef{
    $$=new VarDefList();
    $$->varDefList.push_back(std::shared_ptr<VarDef>($1));
  }
	;

VarDef:IDENTIFIER ConstExpList{
    $$=new VarDef();
    $$->identifier=$1;
    $$->constExpList.swap($2->constExpList);
}
	| IDENTIFIER ConstExpList ASSIGN InitVal{
    $$=new VarDef();
    $$->identifier=$1;
    $$->constExpList.swap($2->constExpList);
    $$->initVal=std::shared_ptr<InitVal>($4);
  }
	;
InitVal:Exp{
    $$=new InitVal();
    $$->exp=std::shared_ptr<Exp>($1);
}
	| BLB BRB{
    $$=new InitVal();
  }
	| BLB InitValList BRB{
    $$=new InitVal();
    $$->initValList.swap($2->initValList);
  }
	;
InitValList:InitValList COMMA InitVal{
    $1->initValList.push_back(std::shared_ptr<InitVal>($3));
    $$=$1;
  }
  | InitVal{
    $$=new InitValList();
    $$->initValList.push_back(std::shared_ptr<InitVal>($1));
  }
	;

FuncDef:DefType IDENTIFIER LB RB Block{
    $$=new FuncDef();
    $$->defType=std::shared_ptr<DefType>($1);
    $$->identifier=$2;
    $$->block=std::shared_ptr<Block>($5);
}
	| DefType IDENTIFIER LB FuncFParams RB Block{
    $$=new FuncDef();
    $$->defType=std::shared_ptr<DefType>($1);
    $$->identifier=$2;
    $$->funcFParams=std::shared_ptr<FuncFParams>($4);
    $$->block=std::shared_ptr<Block>($6);
  }
	;
DefType: VOID{
        $$=new DefType();
        $$->type=type_specifier::TYPE_VOID;
    }
    | INT{
        $$=new DefType();
        $$->type=type_specifier::TYPE_INT;
    }
    | FLOAT{
        $$=new DefType();
        $$->type=type_specifier::TYPE_FLOAT;
    }
    ;
FuncFParams:FuncFParams COMMA FuncFParam{
    $1->funcFParamList.push_back(std::shared_ptr<FuncFParam>($3));
    $$=$1;
}
	| FuncFParam{
    $$=new FuncFParams();
    $$->funcFParamList.push_back(std::shared_ptr<FuncFParam>($1));
  }
	;

FuncFParam:DefType IDENTIFIER MLB MRB ParamArrayExpList{
    $$=new FuncFParam();
    $$->defType=std::shared_ptr<DefType>($1);
    $$->identifier=$2;
    $$->expList.swap($5->expList);
}
	| DefType IDENTIFIER{
    $$=new FuncFParam();
    $$->defType=std::shared_ptr<DefType>($1);
    $$->identifier=$2;
  }
	;

ParamArrayExpList: ParamArrayExpList MLB Exp MRB{
        $1->expList.push_back(std::shared_ptr<Exp>($3));
        $$=$1;
    }
    | %empty{
        $$=new ParamArrayExpList();
    }
    ;

Block:BLB BlockItemList BRB{
    $$=new Block();
    $$->blockItemList.swap($2->blockItemList);
}
	;

BlockItemList:BlockItemList BlockItem{
    $1->blockItemList.push_back(std::shared_ptr<BlockItem>($2));
    $$=$1;
}
	| %empty{
    $$=new BlockItemList();
  }
	;

BlockItem:ConstDecl{
    $$=new BlockItem();
    $$->constDecl=std::shared_ptr<ConstDecl>($1);
}
	| VarDecl{
    $$=new BlockItem();
    $$->varDecl=std::shared_ptr<VarDecl>($1);
  }
	| Stmt{
    $$=new BlockItem();
    $$->stmt=std::shared_ptr<Stmt>($1);
  }
	;

Stmt: LVal ASSIGN Exp SEMICOLON{
        $$=new Stmt();
        $$->lVal=std::shared_ptr<LVal>($1);
        $$->exp=std::shared_ptr<Exp>($3);
    }
    |Exp SEMICOLON{
        $$=new Stmt();
        $$->exp=std::shared_ptr<Exp>($1);
    }
    |SEMICOLON{
        $$=new Stmt();
    }
    |Block{
        $$=new Stmt();
        $$->block=std::shared_ptr<Block>($1);
    }
    |IF LB Cond RB Stmt{
        $$=new Stmt();
        $$->cond=std::shared_ptr<Cond>($3);
        $$->stmt1=std::shared_ptr<Stmt>($5);
        $$->isSelect=true;
    }
    |IF LB Cond RB Stmt ELSE Stmt{
        $$=new Stmt();
        $$->cond=std::shared_ptr<Cond>($3);
        $$->stmt1=std::shared_ptr<Stmt>($5);
        $$->stmt2=std::shared_ptr<Stmt>($7);
        $$->isSelect=true;
    }
    |WHILE LB Cond RB Stmt{
        $$=new Stmt();
        $$->cond=std::shared_ptr<Cond>($3);
        $$->stmt1=std::shared_ptr<Stmt>($5);
        $$->isIteration=true;
    }
    |BREAK SEMICOLON{
        $$=new Stmt();
        $$->isBreak=true;
    }
    |CONTINUE SEMICOLON{
        $$=new Stmt();
        $$->isContinue=true;
    }
    |RETURN SEMICOLON{
        $$=new Stmt();
        $$->isReturn=true;
    }
    |RETURN Exp SEMICOLON{
        $$=new Stmt();
        $$->exp=std::shared_ptr<Exp>($2);
        $$->isReturn=true;
    }
    ;

Exp:AddExp{
    $$=new Exp();
    $$->addExp=std::shared_ptr<AddExp>($1);
}
    ;

Cond:LOrExp{
    $$=new Cond();
    $$->lOrExp=std::shared_ptr<LOrExp>($1);
}
	;
LVal:IDENTIFIER ParamArrayExpList{
    $$=new LVal();
    $$->identifier=$1;
    $$->expList.swap($2->expList);
}
	;

PrimaryExp:LB Exp RB{
    $$=new PrimaryExp();
    $$->exp=std::shared_ptr<Exp>($2);
}
	| LVal{
    $$=new PrimaryExp();
    $$->lVal=std::shared_ptr<LVal>($1);
  }
	| Number{
    $$=new PrimaryExp();
    $$->number=std::shared_ptr<Number>($1);
  }
	;
Number:INTCONST{
    $$=new Number();
    $$->type=type_specifier::TYPE_INT;
    $$->intNum=$1;
    }
    |FLOATCONST{
    $$=new Number();
    $$->type=type_specifier::TYPE_FLOAT;
    $$->floatNum=$1;
    }
	;

UnaryExp:PrimaryExp{
    $$=new UnaryExp();
    $$->primaryExp=std::shared_ptr<PrimaryExp>($1);
}
	| IDENTIFIER LB FuncRParams RB{
    $$=new UnaryExp();
    $$->identifier=$1;
    $$->funcRParams=std::shared_ptr<FuncRParams>($3);
  }
    | IDENTIFIER LB RB{
    $$=new UnaryExp();
    $$->identifier=$1;
    }
	| UnaryOp UnaryExp{
    $$=new UnaryExp();
    $$->unaryOp=std::shared_ptr<UnaryOp>($1);
    $$->unaryExp=std::shared_ptr<UnaryExp>($2);
  }
	;
UnaryOp: ADD{
    $$=new UnaryOp();
    $$->op=unaryop::OP_POS;
}
	| SUB{
	$$=new UnaryOp();
    $$->op=unaryop::OP_NEG;
    }
	| NOT{
	$$=new UnaryOp();
	$$->op=unaryop::OP_NOT;
	}
	;
FuncRParams:FuncRParams COMMA Exp{
    $1->expList.push_back(std::shared_ptr<Exp>($3));
    $$=$1;
    }
    |Exp{
        $$=new FuncRParams();
        $$->expList.push_back(std::shared_ptr<Exp>($1));
    }
    ;

MulExp:UnaryExp{
    $$=new MulExp();
    $$->unaryExp=std::shared_ptr<UnaryExp>($1);
}
	| MulExp MUL UnaryExp{
    $$=new MulExp();
    $$->mulExp=std::shared_ptr<MulExp>($1);
    $$->unaryExp=std::shared_ptr<UnaryExp>($3);
    $$->op=mulop::OP_MUL;
  }
	| MulExp DIV UnaryExp{
    $$=new MulExp();
    $$->mulExp=std::shared_ptr<MulExp>($1);
    $$->unaryExp=std::shared_ptr<UnaryExp>($3);
    $$->op=mulop::OP_DIV;
  }
	| MulExp MOD UnaryExp{
    $$=new MulExp();
    $$->mulExp=std::shared_ptr<MulExp>($1);
    $$->unaryExp=std::shared_ptr<UnaryExp>($3);
    $$->op=mulop::OP_MOD;
  }
	;

AddExp:MulExp{
    $$=new AddExp();
    $$->mulExp=std::shared_ptr<MulExp>($1);
}
	| AddExp ADD MulExp{
    $$=new AddExp();
    $$->addExp=std::shared_ptr<AddExp>($1);
    $$->mulExp=std::shared_ptr<MulExp>($3);
    $$->op=addop::OP_ADD;
  }
	| AddExp SUB MulExp{
    $$=new AddExp();
    $$->addExp=std::shared_ptr<AddExp>($1);
    $$->mulExp=std::shared_ptr<MulExp>($3);
    $$->op=addop::OP_SUB;
  }
	;

RelExp:AddExp{
    $$=new RelExp();
    $$->addExp=std::shared_ptr<AddExp>($1);
}
	| RelExp LT AddExp{
    $$=new RelExp();
    $$->relExp=std::shared_ptr<RelExp>($1);
    $$->addExp=std::shared_ptr<AddExp>($3);
    $$->op=relop::OP_LT;
  }
	| RelExp GT AddExp{
    $$=new RelExp();
    $$->relExp=std::shared_ptr<RelExp>($1);
    $$->addExp=std::shared_ptr<AddExp>($3);
    $$->op=relop::OP_GT;
  }
	| RelExp LE AddExp{
    $$=new RelExp();
    $$->relExp=std::shared_ptr<RelExp>($1);
    $$->addExp=std::shared_ptr<AddExp>($3);
    $$->op=relop::OP_LE;
  }
	| RelExp GE AddExp{
    $$=new RelExp();
    $$->relExp=std::shared_ptr<RelExp>($1);
    $$->addExp=std::shared_ptr<AddExp>($3);
    $$->op=relop::OP_GE;
  }
	;
EqExp:RelExp{
    $$=new EqExp();
    $$->relExp=std::shared_ptr<RelExp>($1);
  }
	| EqExp EQU RelExp{
    $$=new EqExp();
    $$->eqExp=std::shared_ptr<EqExp>($1);
    $$->relExp=std::shared_ptr<RelExp>($3);
    $$->op=relop::OP_EQU;
  }
	| EqExp NE RelExp{
    $$=new EqExp();
    $$->eqExp=std::shared_ptr<EqExp>($1);
    $$->relExp=std::shared_ptr<RelExp>($3);
    $$->op=relop::OP_NE;
  }
	;
LAndExp:EqExp {
    $$=new LAndExp();
    $$->eqExp=std::shared_ptr<EqExp>($1);
  }
	| LAndExp AND EqExp{
    $$=new LAndExp();
    $$->lAndExp=std::shared_ptr<LAndExp>($1);
    $$->eqExp=std::shared_ptr<EqExp>($3);
  }
	;
LOrExp:LAndExp{
    $$=new LOrExp();
    $$->lAndExp=std::shared_ptr<LAndExp>($1);
  }
	| LOrExp OR LAndExp{
    $$=new LOrExp();
    $$->lOrExp=std::shared_ptr<LOrExp>($1);
    $$->lAndExp=std::shared_ptr<LAndExp>($3);
  }
	;
ConstExp:AddExp{
    $$=new ConstExp();
    $$->addExp=std::shared_ptr<AddExp>($1);
  }
	;
%%
/*Parser实现错误处理接口*/
void yy::parser::error (const location_type& l,
                          const std::string& m)
{
    ddriver.error(l, m);
}