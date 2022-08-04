// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.hh"


// Unqualified %code blocks.
#line 34 "parser.yy"

#include "driver.hh"
#define yylex ddriver.lexer.yylex

#line 50 "parser.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 141 "parser.cc"


    /* Return YYSTR after stripping away unnecessary quotes and
       backslashes, so that it's suitable for yyerror.  The heuristic is
       that double-quoting is unnecessary unless the string contains an
       apostrophe, a comma, or backslash (other than backslash-backslash).
       YYSTR is taken from yytname.  */
    std::string
    parser::yytnamerr_ (const char *yystr)
    {
        if (*yystr == '"')
        {
            std::string yyr;
            char const *yyp = yystr;

            for (;;)
                switch (*++yyp)
                {
                    case '\'':
                    case ',':
                        goto do_not_strip_quotes;

                    case '\\':
                        if (*++yyp != '\\')
                            goto do_not_strip_quotes;
                        else
                            goto append;

                    append:
                    default:
                        yyr += *yyp;
                        break;

                    case '"':
                        return yyr;
                }
            do_not_strip_quotes: ;
        }

        return yystr;
    }


    /// Build a parser object.
    parser::parser (driver& ddriver_yyarg)
#if YYDEBUG
            : yydebug_ (false),
              yycdebug_ (&std::cerr),
#else
            :
#endif
              ddriver (ddriver_yyarg)
    {}

    parser::~parser ()
    {}

    parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
    {}

    /*---------------.
    | Symbol types.  |
    `---------------*/



    // by_state.
    parser::by_state::by_state () YY_NOEXCEPT
            : state (empty_state)
    {}

    parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
            : state (that.state)
    {}

    void
    parser::by_state::clear () YY_NOEXCEPT
    {
        state = empty_state;
    }

    void
    parser::by_state::move (by_state& that)
    {
        state = that.state;
        that.clear ();
    }

    parser::by_state::by_state (state_type s) YY_NOEXCEPT
            : state (s)
    {}

    parser::symbol_number_type
    parser::by_state::type_get () const YY_NOEXCEPT
    {
        if (state == empty_state)
            return empty_symbol;
        else
            return yystos_[+state];
    }

    parser::stack_symbol_type::stack_symbol_type ()
    {}

    parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
            : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
    {
        switch (that.type_get ())
        {
            case 80: // AddExp
                value.YY_MOVE_OR_COPY< AddExp* > (YY_MOVE (that.value));
                break;

            case 65: // AssignStmt
                value.YY_MOVE_OR_COPY< AssignStmt* > (YY_MOVE (that.value));
                break;

            case 61: // Block
                value.YY_MOVE_OR_COPY< Block* > (YY_MOVE (that.value));
                break;

            case 63: // BlockItem
                value.YY_MOVE_OR_COPY< BlockItem* > (YY_MOVE (that.value));
                break;

            case 62: // BlockItemList
                value.YY_MOVE_OR_COPY< BlockItemList* > (YY_MOVE (that.value));
                break;

            case 68: // BreakStmt
                value.YY_MOVE_OR_COPY< BreakStmt* > (YY_MOVE (that.value));
                break;

            case 42: // Begin
            case 43: // CompUnit
                value.YY_MOVE_OR_COPY< CompUnit* > (YY_MOVE (that.value));
                break;

            case 72: // Cond
                value.YY_MOVE_OR_COPY< Cond* > (YY_MOVE (that.value));
                break;

            case 45: // ConstDecl
                value.YY_MOVE_OR_COPY< ConstDecl* > (YY_MOVE (that.value));
                break;

            case 47: // ConstDef
                value.YY_MOVE_OR_COPY< ConstDef* > (YY_MOVE (that.value));
                break;

            case 46: // ConstDefList
                value.YY_MOVE_OR_COPY< ConstDefList* > (YY_MOVE (that.value));
                break;

            case 85: // ConstExp
                value.YY_MOVE_OR_COPY< ConstExp* > (YY_MOVE (that.value));
                break;

            case 48: // ConstExpList
                value.YY_MOVE_OR_COPY< ConstExpList* > (YY_MOVE (that.value));
                break;

            case 49: // ConstInitVal
                value.YY_MOVE_OR_COPY< ConstInitVal* > (YY_MOVE (that.value));
                break;

            case 50: // ConstInitValList
                value.YY_MOVE_OR_COPY< ConstInitValList* > (YY_MOVE (that.value));
                break;

            case 69: // ContinueStmt
                value.YY_MOVE_OR_COPY< ContinueStmt* > (YY_MOVE (that.value));
                break;

            case 44: // DeclDef
                value.YY_MOVE_OR_COPY< DeclDef* > (YY_MOVE (that.value));
                break;

            case 57: // DefType
                value.YY_MOVE_OR_COPY< DefType* > (YY_MOVE (that.value));
                break;

            case 82: // EqExp
                value.YY_MOVE_OR_COPY< EqExp* > (YY_MOVE (that.value));
                break;

            case 71: // Exp
                value.YY_MOVE_OR_COPY< Exp* > (YY_MOVE (that.value));
                break;

            case 56: // FuncDef
                value.YY_MOVE_OR_COPY< FuncDef* > (YY_MOVE (that.value));
                break;

            case 59: // FuncFParam
                value.YY_MOVE_OR_COPY< FuncFParam* > (YY_MOVE (that.value));
                break;

            case 58: // FuncFParams
                value.YY_MOVE_OR_COPY< FuncFParams* > (YY_MOVE (that.value));
                break;

            case 78: // FuncRParams
                value.YY_MOVE_OR_COPY< FuncRParams* > (YY_MOVE (that.value));
                break;

            case 54: // InitVal
                value.YY_MOVE_OR_COPY< InitVal* > (YY_MOVE (that.value));
                break;

            case 55: // InitValList
                value.YY_MOVE_OR_COPY< InitValList* > (YY_MOVE (that.value));
                break;

            case 67: // IterationStmt
                value.YY_MOVE_OR_COPY< IterationStmt* > (YY_MOVE (that.value));
                break;

            case 83: // LAndExp
                value.YY_MOVE_OR_COPY< LAndExp* > (YY_MOVE (that.value));
                break;

            case 84: // LOrExp
                value.YY_MOVE_OR_COPY< LOrExp* > (YY_MOVE (that.value));
                break;

            case 73: // LVal
                value.YY_MOVE_OR_COPY< LVal* > (YY_MOVE (that.value));
                break;

            case 79: // MulExp
                value.YY_MOVE_OR_COPY< MulExp* > (YY_MOVE (that.value));
                break;

            case 75: // Number
                value.YY_MOVE_OR_COPY< Number* > (YY_MOVE (that.value));
                break;

            case 60: // ParamArrayExpList
                value.YY_MOVE_OR_COPY< ParamArrayExpList* > (YY_MOVE (that.value));
                break;

            case 74: // PrimaryExp
                value.YY_MOVE_OR_COPY< PrimaryExp* > (YY_MOVE (that.value));
                break;

            case 81: // RelExp
                value.YY_MOVE_OR_COPY< RelExp* > (YY_MOVE (that.value));
                break;

            case 70: // ReturnStmt
                value.YY_MOVE_OR_COPY< ReturnStmt* > (YY_MOVE (that.value));
                break;

            case 66: // SelectStmt
                value.YY_MOVE_OR_COPY< SelectStmt* > (YY_MOVE (that.value));
                break;

            case 64: // Stmt
                value.YY_MOVE_OR_COPY< Stmt* > (YY_MOVE (that.value));
                break;

            case 76: // UnaryExp
                value.YY_MOVE_OR_COPY< UnaryExp* > (YY_MOVE (that.value));
                break;

            case 77: // UnaryOp
                value.YY_MOVE_OR_COPY< UnaryOp* > (YY_MOVE (that.value));
                break;

            case 51: // VarDecl
                value.YY_MOVE_OR_COPY< VarDecl* > (YY_MOVE (that.value));
                break;

            case 53: // VarDef
                value.YY_MOVE_OR_COPY< VarDef* > (YY_MOVE (that.value));
                break;

            case 52: // VarDefList
                value.YY_MOVE_OR_COPY< VarDefList* > (YY_MOVE (that.value));
                break;

            case 16: // FLOATCONST
                value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
                break;

            case 15: // INTCONST
                value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
                break;

            case 13: // STRING
            case 14: // IDENTIFIER
                value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
                break;

            default:
                break;
        }

#if 201103L <= YY_CPLUSPLUS
        // that is emptied.
        that.state = empty_state;
#endif
    }

    parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
            : super_type (s, YY_MOVE (that.location))
    {
        switch (that.type_get ())
        {
            case 80: // AddExp
                value.move< AddExp* > (YY_MOVE (that.value));
                break;

            case 65: // AssignStmt
                value.move< AssignStmt* > (YY_MOVE (that.value));
                break;

            case 61: // Block
                value.move< Block* > (YY_MOVE (that.value));
                break;

            case 63: // BlockItem
                value.move< BlockItem* > (YY_MOVE (that.value));
                break;

            case 62: // BlockItemList
                value.move< BlockItemList* > (YY_MOVE (that.value));
                break;

            case 68: // BreakStmt
                value.move< BreakStmt* > (YY_MOVE (that.value));
                break;

            case 42: // Begin
            case 43: // CompUnit
                value.move< CompUnit* > (YY_MOVE (that.value));
                break;

            case 72: // Cond
                value.move< Cond* > (YY_MOVE (that.value));
                break;

            case 45: // ConstDecl
                value.move< ConstDecl* > (YY_MOVE (that.value));
                break;

            case 47: // ConstDef
                value.move< ConstDef* > (YY_MOVE (that.value));
                break;

            case 46: // ConstDefList
                value.move< ConstDefList* > (YY_MOVE (that.value));
                break;

            case 85: // ConstExp
                value.move< ConstExp* > (YY_MOVE (that.value));
                break;

            case 48: // ConstExpList
                value.move< ConstExpList* > (YY_MOVE (that.value));
                break;

            case 49: // ConstInitVal
                value.move< ConstInitVal* > (YY_MOVE (that.value));
                break;

            case 50: // ConstInitValList
                value.move< ConstInitValList* > (YY_MOVE (that.value));
                break;

            case 69: // ContinueStmt
                value.move< ContinueStmt* > (YY_MOVE (that.value));
                break;

            case 44: // DeclDef
                value.move< DeclDef* > (YY_MOVE (that.value));
                break;

            case 57: // DefType
                value.move< DefType* > (YY_MOVE (that.value));
                break;

            case 82: // EqExp
                value.move< EqExp* > (YY_MOVE (that.value));
                break;

            case 71: // Exp
                value.move< Exp* > (YY_MOVE (that.value));
                break;

            case 56: // FuncDef
                value.move< FuncDef* > (YY_MOVE (that.value));
                break;

            case 59: // FuncFParam
                value.move< FuncFParam* > (YY_MOVE (that.value));
                break;

            case 58: // FuncFParams
                value.move< FuncFParams* > (YY_MOVE (that.value));
                break;

            case 78: // FuncRParams
                value.move< FuncRParams* > (YY_MOVE (that.value));
                break;

            case 54: // InitVal
                value.move< InitVal* > (YY_MOVE (that.value));
                break;

            case 55: // InitValList
                value.move< InitValList* > (YY_MOVE (that.value));
                break;

            case 67: // IterationStmt
                value.move< IterationStmt* > (YY_MOVE (that.value));
                break;

            case 83: // LAndExp
                value.move< LAndExp* > (YY_MOVE (that.value));
                break;

            case 84: // LOrExp
                value.move< LOrExp* > (YY_MOVE (that.value));
                break;

            case 73: // LVal
                value.move< LVal* > (YY_MOVE (that.value));
                break;

            case 79: // MulExp
                value.move< MulExp* > (YY_MOVE (that.value));
                break;

            case 75: // Number
                value.move< Number* > (YY_MOVE (that.value));
                break;

            case 60: // ParamArrayExpList
                value.move< ParamArrayExpList* > (YY_MOVE (that.value));
                break;

            case 74: // PrimaryExp
                value.move< PrimaryExp* > (YY_MOVE (that.value));
                break;

            case 81: // RelExp
                value.move< RelExp* > (YY_MOVE (that.value));
                break;

            case 70: // ReturnStmt
                value.move< ReturnStmt* > (YY_MOVE (that.value));
                break;

            case 66: // SelectStmt
                value.move< SelectStmt* > (YY_MOVE (that.value));
                break;

            case 64: // Stmt
                value.move< Stmt* > (YY_MOVE (that.value));
                break;

            case 76: // UnaryExp
                value.move< UnaryExp* > (YY_MOVE (that.value));
                break;

            case 77: // UnaryOp
                value.move< UnaryOp* > (YY_MOVE (that.value));
                break;

            case 51: // VarDecl
                value.move< VarDecl* > (YY_MOVE (that.value));
                break;

            case 53: // VarDef
                value.move< VarDef* > (YY_MOVE (that.value));
                break;

            case 52: // VarDefList
                value.move< VarDefList* > (YY_MOVE (that.value));
                break;

            case 16: // FLOATCONST
                value.move< float > (YY_MOVE (that.value));
                break;

            case 15: // INTCONST
                value.move< int > (YY_MOVE (that.value));
                break;

            case 13: // STRING
            case 14: // IDENTIFIER
                value.move< std::string > (YY_MOVE (that.value));
                break;

            default:
                break;
        }

        // that is emptied.
        that.type = empty_symbol;
    }

#if YY_CPLUSPLUS < 201103L
    parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 80: // AddExp
        value.copy< AddExp* > (that.value);
        break;

      case 65: // AssignStmt
        value.copy< AssignStmt* > (that.value);
        break;

      case 61: // Block
        value.copy< Block* > (that.value);
        break;

      case 63: // BlockItem
        value.copy< BlockItem* > (that.value);
        break;

      case 62: // BlockItemList
        value.copy< BlockItemList* > (that.value);
        break;

      case 68: // BreakStmt
        value.copy< BreakStmt* > (that.value);
        break;

      case 42: // Begin
      case 43: // CompUnit
        value.copy< CompUnit* > (that.value);
        break;

      case 72: // Cond
        value.copy< Cond* > (that.value);
        break;

      case 45: // ConstDecl
        value.copy< ConstDecl* > (that.value);
        break;

      case 47: // ConstDef
        value.copy< ConstDef* > (that.value);
        break;

      case 46: // ConstDefList
        value.copy< ConstDefList* > (that.value);
        break;

      case 85: // ConstExp
        value.copy< ConstExp* > (that.value);
        break;

      case 48: // ConstExpList
        value.copy< ConstExpList* > (that.value);
        break;

      case 49: // ConstInitVal
        value.copy< ConstInitVal* > (that.value);
        break;

      case 50: // ConstInitValList
        value.copy< ConstInitValList* > (that.value);
        break;

      case 69: // ContinueStmt
        value.copy< ContinueStmt* > (that.value);
        break;

      case 44: // DeclDef
        value.copy< DeclDef* > (that.value);
        break;

      case 57: // DefType
        value.copy< DefType* > (that.value);
        break;

      case 82: // EqExp
        value.copy< EqExp* > (that.value);
        break;

      case 71: // Exp
        value.copy< Exp* > (that.value);
        break;

      case 56: // FuncDef
        value.copy< FuncDef* > (that.value);
        break;

      case 59: // FuncFParam
        value.copy< FuncFParam* > (that.value);
        break;

      case 58: // FuncFParams
        value.copy< FuncFParams* > (that.value);
        break;

      case 78: // FuncRParams
        value.copy< FuncRParams* > (that.value);
        break;

      case 54: // InitVal
        value.copy< InitVal* > (that.value);
        break;

      case 55: // InitValList
        value.copy< InitValList* > (that.value);
        break;

      case 67: // IterationStmt
        value.copy< IterationStmt* > (that.value);
        break;

      case 83: // LAndExp
        value.copy< LAndExp* > (that.value);
        break;

      case 84: // LOrExp
        value.copy< LOrExp* > (that.value);
        break;

      case 73: // LVal
        value.copy< LVal* > (that.value);
        break;

      case 79: // MulExp
        value.copy< MulExp* > (that.value);
        break;

      case 75: // Number
        value.copy< Number* > (that.value);
        break;

      case 60: // ParamArrayExpList
        value.copy< ParamArrayExpList* > (that.value);
        break;

      case 74: // PrimaryExp
        value.copy< PrimaryExp* > (that.value);
        break;

      case 81: // RelExp
        value.copy< RelExp* > (that.value);
        break;

      case 70: // ReturnStmt
        value.copy< ReturnStmt* > (that.value);
        break;

      case 66: // SelectStmt
        value.copy< SelectStmt* > (that.value);
        break;

      case 64: // Stmt
        value.copy< Stmt* > (that.value);
        break;

      case 76: // UnaryExp
        value.copy< UnaryExp* > (that.value);
        break;

      case 77: // UnaryOp
        value.copy< UnaryOp* > (that.value);
        break;

      case 51: // VarDecl
        value.copy< VarDecl* > (that.value);
        break;

      case 53: // VarDef
        value.copy< VarDef* > (that.value);
        break;

      case 52: // VarDefList
        value.copy< VarDefList* > (that.value);
        break;

      case 16: // FLOATCONST
        value.copy< float > (that.value);
        break;

      case 15: // INTCONST
        value.copy< int > (that.value);
        break;

      case 13: // STRING
      case 14: // IDENTIFIER
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 80: // AddExp
        value.move< AddExp* > (that.value);
        break;

      case 65: // AssignStmt
        value.move< AssignStmt* > (that.value);
        break;

      case 61: // Block
        value.move< Block* > (that.value);
        break;

      case 63: // BlockItem
        value.move< BlockItem* > (that.value);
        break;

      case 62: // BlockItemList
        value.move< BlockItemList* > (that.value);
        break;

      case 68: // BreakStmt
        value.move< BreakStmt* > (that.value);
        break;

      case 42: // Begin
      case 43: // CompUnit
        value.move< CompUnit* > (that.value);
        break;

      case 72: // Cond
        value.move< Cond* > (that.value);
        break;

      case 45: // ConstDecl
        value.move< ConstDecl* > (that.value);
        break;

      case 47: // ConstDef
        value.move< ConstDef* > (that.value);
        break;

      case 46: // ConstDefList
        value.move< ConstDefList* > (that.value);
        break;

      case 85: // ConstExp
        value.move< ConstExp* > (that.value);
        break;

      case 48: // ConstExpList
        value.move< ConstExpList* > (that.value);
        break;

      case 49: // ConstInitVal
        value.move< ConstInitVal* > (that.value);
        break;

      case 50: // ConstInitValList
        value.move< ConstInitValList* > (that.value);
        break;

      case 69: // ContinueStmt
        value.move< ContinueStmt* > (that.value);
        break;

      case 44: // DeclDef
        value.move< DeclDef* > (that.value);
        break;

      case 57: // DefType
        value.move< DefType* > (that.value);
        break;

      case 82: // EqExp
        value.move< EqExp* > (that.value);
        break;

      case 71: // Exp
        value.move< Exp* > (that.value);
        break;

      case 56: // FuncDef
        value.move< FuncDef* > (that.value);
        break;

      case 59: // FuncFParam
        value.move< FuncFParam* > (that.value);
        break;

      case 58: // FuncFParams
        value.move< FuncFParams* > (that.value);
        break;

      case 78: // FuncRParams
        value.move< FuncRParams* > (that.value);
        break;

      case 54: // InitVal
        value.move< InitVal* > (that.value);
        break;

      case 55: // InitValList
        value.move< InitValList* > (that.value);
        break;

      case 67: // IterationStmt
        value.move< IterationStmt* > (that.value);
        break;

      case 83: // LAndExp
        value.move< LAndExp* > (that.value);
        break;

      case 84: // LOrExp
        value.move< LOrExp* > (that.value);
        break;

      case 73: // LVal
        value.move< LVal* > (that.value);
        break;

      case 79: // MulExp
        value.move< MulExp* > (that.value);
        break;

      case 75: // Number
        value.move< Number* > (that.value);
        break;

      case 60: // ParamArrayExpList
        value.move< ParamArrayExpList* > (that.value);
        break;

      case 74: // PrimaryExp
        value.move< PrimaryExp* > (that.value);
        break;

      case 81: // RelExp
        value.move< RelExp* > (that.value);
        break;

      case 70: // ReturnStmt
        value.move< ReturnStmt* > (that.value);
        break;

      case 66: // SelectStmt
        value.move< SelectStmt* > (that.value);
        break;

      case 64: // Stmt
        value.move< Stmt* > (that.value);
        break;

      case 76: // UnaryExp
        value.move< UnaryExp* > (that.value);
        break;

      case 77: // UnaryOp
        value.move< UnaryOp* > (that.value);
        break;

      case 51: // VarDecl
        value.move< VarDecl* > (that.value);
        break;

      case 53: // VarDef
        value.move< VarDef* > (that.value);
        break;

      case 52: // VarDefList
        value.move< VarDefList* > (that.value);
        break;

      case 16: // FLOATCONST
        value.move< float > (that.value);
        break;

      case 15: // INTCONST
        value.move< int > (that.value);
        break;

      case 13: // STRING
      case 14: // IDENTIFIER
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

    template <typename Base>
    void
    parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
    {
        if (yymsg)
            YY_SYMBOL_PRINT (yymsg, yysym);
    }

#if YYDEBUG
    template <typename Base>
    void
    parser::yy_print_ (std::ostream& yyo,
                       const basic_symbol<Base>& yysym) const
    {
        std::ostream& yyoutput = yyo;
        YYUSE (yyoutput);
        symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
        // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
        yyo << (yytype < yyntokens_ ? "token" : "nterm")
            << ' ' << yytname_[yytype] << " ("
            << yysym.location << ": ";
        YYUSE (yytype);
        yyo << ')';
    }
#endif

    void
    parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
    {
        if (m)
            YY_SYMBOL_PRINT (m, sym);
        yystack_.push (YY_MOVE (sym));
    }

    void
    parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
    {
#if 201103L <= YY_CPLUSPLUS
        yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
        stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
    }

    void
    parser::yypop_ (int n)
    {
        yystack_.pop (n);
    }

#if YYDEBUG
    std::ostream&
    parser::debug_stream () const
    {
        return *yycdebug_;
    }

    void
    parser::set_debug_stream (std::ostream& o)
    {
        yycdebug_ = &o;
    }


    parser::debug_level_type
    parser::debug_level () const
    {
        return yydebug_;
    }

    void
    parser::set_debug_level (debug_level_type l)
    {
        yydebug_ = l;
    }
#endif // YYDEBUG

    parser::state_type
    parser::yy_lr_goto_state_ (state_type yystate, int yysym)
    {
        int yyr = yypgoto_[yysym - yyntokens_] + yystate;
        if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
            return yytable_[yyr];
        else
            return yydefgoto_[yysym - yyntokens_];
    }

    bool
    parser::yy_pact_value_is_default_ (int yyvalue)
    {
        return yyvalue == yypact_ninf_;
    }

    bool
    parser::yy_table_value_is_error_ (int yyvalue)
    {
        return yyvalue == yytable_ninf_;
    }

    int
    parser::operator() ()
    {
        return parse ();
    }

    int
    parser::parse ()
    {
        int yyn;
        /// Length of the RHS of the rule being reduced.
        int yylen = 0;

        // Error handling.
        int yynerrs_ = 0;
        int yyerrstatus_ = 0;

        /// The lookahead symbol.
        symbol_type yyla;

        /// The locations where the error started and ended.
        stack_symbol_type yyerror_range[3];

        /// The return value of parse ().
        int yyresult;

#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
        {
            YYCDEBUG << "Starting parse\n";


            // User initialization code.
#line 23 "parser.yy"
            {
                // Initialize the initial location.
                yyla.location.begin.filename = yyla.location.end.filename = &ddriver.file;
            }

#line 1195 "parser.cc"


            /* Initialize the stack.  The initial state will be set in
               yynewstate, since the latter expects the semantical and the
               location values to have been already stored, initialize these
               stacks with a primary value.  */
            yystack_.clear ();
            yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

            /*-----------------------------------------------.
            | yynewstate -- push a new symbol on the stack.  |
            `-----------------------------------------------*/
            yynewstate:
            YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

            // Accept?
            if (yystack_[0].state == yyfinal_)
                YYACCEPT;

            goto yybackup;


            /*-----------.
            | yybackup.  |
            `-----------*/
            yybackup:
            // Try to take a decision without lookahead.
            yyn = yypact_[+yystack_[0].state];
            if (yy_pact_value_is_default_ (yyn))
                goto yydefault;

            // Read a lookahead token.
            if (yyla.empty ())
            {
                YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
                try
#endif // YY_EXCEPTIONS
                {
                    symbol_type yylookahead (yylex (ddriver));
                    yyla.move (yylookahead);
                }
#if YY_EXCEPTIONS
                catch (const syntax_error& yyexc)
                {
                    YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
                    error (yyexc);
                    goto yyerrlab1;
                }
#endif // YY_EXCEPTIONS
            }
            YY_SYMBOL_PRINT ("Next token is", yyla);

            /* If the proper action on seeing token YYLA.TYPE is to reduce or
               to detect an error, take that action.  */
            yyn += yyla.type_get ();
            if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
            {
                goto yydefault;
            }

            // Reduce or error.
            yyn = yytable_[yyn];
            if (yyn <= 0)
            {
                if (yy_table_value_is_error_ (yyn))
                    goto yyerrlab;
                yyn = -yyn;
                goto yyreduce;
            }

            // Count tokens shifted since error; after three, turn off error status.
            if (yyerrstatus_)
                --yyerrstatus_;

            // Shift the lookahead token.
            yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
            goto yynewstate;


            /*-----------------------------------------------------------.
            | yydefault -- do the default action for the current state.  |
            `-----------------------------------------------------------*/
            yydefault:
            yyn = yydefact_[+yystack_[0].state];
            if (yyn == 0)
                goto yyerrlab;
            goto yyreduce;


            /*-----------------------------.
            | yyreduce -- do a reduction.  |
            `-----------------------------*/
            yyreduce:
            yylen = yyr2_[yyn];
            {
                stack_symbol_type yylhs;
                yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
                /* Variants are always initialized to an empty instance of the
                   correct type. The default '$$ = $1' action is NOT applied
                   when using variants.  */
                switch (yyr1_[yyn])
                {
                    case 80: // AddExp
                        yylhs.value.emplace< AddExp* > ();
                        break;

                    case 65: // AssignStmt
                        yylhs.value.emplace< AssignStmt* > ();
                        break;

                    case 61: // Block
                        yylhs.value.emplace< Block* > ();
                        break;

                    case 63: // BlockItem
                        yylhs.value.emplace< BlockItem* > ();
                        break;

                    case 62: // BlockItemList
                        yylhs.value.emplace< BlockItemList* > ();
                        break;

                    case 68: // BreakStmt
                        yylhs.value.emplace< BreakStmt* > ();
                        break;

                    case 42: // Begin
                    case 43: // CompUnit
                        yylhs.value.emplace< CompUnit* > ();
                        break;

                    case 72: // Cond
                        yylhs.value.emplace< Cond* > ();
                        break;

                    case 45: // ConstDecl
                        yylhs.value.emplace< ConstDecl* > ();
                        break;

                    case 47: // ConstDef
                        yylhs.value.emplace< ConstDef* > ();
                        break;

                    case 46: // ConstDefList
                        yylhs.value.emplace< ConstDefList* > ();
                        break;

                    case 85: // ConstExp
                        yylhs.value.emplace< ConstExp* > ();
                        break;

                    case 48: // ConstExpList
                        yylhs.value.emplace< ConstExpList* > ();
                        break;

                    case 49: // ConstInitVal
                        yylhs.value.emplace< ConstInitVal* > ();
                        break;

                    case 50: // ConstInitValList
                        yylhs.value.emplace< ConstInitValList* > ();
                        break;

                    case 69: // ContinueStmt
                        yylhs.value.emplace< ContinueStmt* > ();
                        break;

                    case 44: // DeclDef
                        yylhs.value.emplace< DeclDef* > ();
                        break;

                    case 57: // DefType
                        yylhs.value.emplace< DefType* > ();
                        break;

                    case 82: // EqExp
                        yylhs.value.emplace< EqExp* > ();
                        break;

                    case 71: // Exp
                        yylhs.value.emplace< Exp* > ();
                        break;

                    case 56: // FuncDef
                        yylhs.value.emplace< FuncDef* > ();
                        break;

                    case 59: // FuncFParam
                        yylhs.value.emplace< FuncFParam* > ();
                        break;

                    case 58: // FuncFParams
                        yylhs.value.emplace< FuncFParams* > ();
                        break;

                    case 78: // FuncRParams
                        yylhs.value.emplace< FuncRParams* > ();
                        break;

                    case 54: // InitVal
                        yylhs.value.emplace< InitVal* > ();
                        break;

                    case 55: // InitValList
                        yylhs.value.emplace< InitValList* > ();
                        break;

                    case 67: // IterationStmt
                        yylhs.value.emplace< IterationStmt* > ();
                        break;

                    case 83: // LAndExp
                        yylhs.value.emplace< LAndExp* > ();
                        break;

                    case 84: // LOrExp
                        yylhs.value.emplace< LOrExp* > ();
                        break;

                    case 73: // LVal
                        yylhs.value.emplace< LVal* > ();
                        break;

                    case 79: // MulExp
                        yylhs.value.emplace< MulExp* > ();
                        break;

                    case 75: // Number
                        yylhs.value.emplace< Number* > ();
                        break;

                    case 60: // ParamArrayExpList
                        yylhs.value.emplace< ParamArrayExpList* > ();
                        break;

                    case 74: // PrimaryExp
                        yylhs.value.emplace< PrimaryExp* > ();
                        break;

                    case 81: // RelExp
                        yylhs.value.emplace< RelExp* > ();
                        break;

                    case 70: // ReturnStmt
                        yylhs.value.emplace< ReturnStmt* > ();
                        break;

                    case 66: // SelectStmt
                        yylhs.value.emplace< SelectStmt* > ();
                        break;

                    case 64: // Stmt
                        yylhs.value.emplace< Stmt* > ();
                        break;

                    case 76: // UnaryExp
                        yylhs.value.emplace< UnaryExp* > ();
                        break;

                    case 77: // UnaryOp
                        yylhs.value.emplace< UnaryOp* > ();
                        break;

                    case 51: // VarDecl
                        yylhs.value.emplace< VarDecl* > ();
                        break;

                    case 53: // VarDef
                        yylhs.value.emplace< VarDef* > ();
                        break;

                    case 52: // VarDefList
                        yylhs.value.emplace< VarDefList* > ();
                        break;

                    case 16: // FLOATCONST
                        yylhs.value.emplace< float > ();
                        break;

                    case 15: // INTCONST
                        yylhs.value.emplace< int > ();
                        break;

                    case 13: // STRING
                    case 14: // IDENTIFIER
                        yylhs.value.emplace< std::string > ();
                        break;

                    default:
                        break;
                }


                // Default location.
                {
                    stack_type::slice range (yystack_, yylen);
                    YYLLOC_DEFAULT (yylhs.location, range, yylen);
                    yyerror_range[1].location = yylhs.location;
                }

                // Perform the reduction.
                YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
                try
#endif // YY_EXCEPTIONS
                {
                    switch (yyn)
                    {
                        case 2:
#line 101 "parser.yy"
                        {
                            ddriver.root = yystack_[1].value.as < CompUnit* > ();
                            return 0;
                        }
#line 1511 "parser.cc"
                            break;

                        case 3:
#line 106 "parser.yy"
                        {
                            yystack_[1].value.as < CompUnit* > ()->declDefList.push_back(std::shared_ptr<DeclDef>(yystack_[0].value.as < DeclDef* > ()));
                            yylhs.value.as < CompUnit* > ()=yystack_[1].value.as < CompUnit* > ();
                        }
#line 1520 "parser.cc"
                            break;

                        case 4:
#line 110 "parser.yy"
                        {
                            yylhs.value.as < CompUnit* > ()=new CompUnit();
                            yylhs.value.as < CompUnit* > ()->declDefList.push_back(std::shared_ptr<DeclDef>(yystack_[0].value.as < DeclDef* > ()));
                        }
#line 1529 "parser.cc"
                            break;

                        case 5:
#line 115 "parser.yy"
                        {
                            yylhs.value.as < DeclDef* > ()=new DeclDef();
                            yylhs.value.as < DeclDef* > ()->constDecl=std::shared_ptr<ConstDecl>(yystack_[0].value.as < ConstDecl* > ());
                        }
#line 1538 "parser.cc"
                            break;

                        case 6:
#line 119 "parser.yy"
                        {
                            yylhs.value.as < DeclDef* > ()=new DeclDef();
                            yylhs.value.as < DeclDef* > ()->varDecl=std::shared_ptr<VarDecl>(yystack_[0].value.as < VarDecl* > ());
                        }
#line 1547 "parser.cc"
                            break;

                        case 7:
#line 123 "parser.yy"
                        {
                            yylhs.value.as < DeclDef* > ()=new DeclDef();
                            yylhs.value.as < DeclDef* > ()->funcDef=std::shared_ptr<FuncDef>(yystack_[0].value.as < FuncDef* > ());
                        }
#line 1556 "parser.cc"
                            break;

                        case 8:
#line 128 "parser.yy"
                        {
                            yylhs.value.as < ConstDecl* > ()=new ConstDecl();
                            yylhs.value.as < ConstDecl* > ()->constDefList.swap(yystack_[1].value.as < ConstDefList* > ()->constDefList);
                            yylhs.value.as < ConstDecl* > ()->defType=std::shared_ptr<DefType>(yystack_[2].value.as < DefType* > ());
                        }
#line 1566 "parser.cc"
                            break;

                        case 9:
#line 134 "parser.yy"
                        {
                            yystack_[2].value.as < ConstDefList* > ()->constDefList.push_back(std::shared_ptr<ConstDef>(yystack_[0].value.as < ConstDef* > ()));
                            yylhs.value.as < ConstDefList* > ()=yystack_[2].value.as < ConstDefList* > ();
                        }
#line 1575 "parser.cc"
                            break;

                        case 10:
#line 138 "parser.yy"
                        {
                            yylhs.value.as < ConstDefList* > ()=new ConstDefList();
                            yylhs.value.as < ConstDefList* > ()->constDefList.push_back(std::shared_ptr<ConstDef>(yystack_[0].value.as < ConstDef* > ()));
                        }
#line 1584 "parser.cc"
                            break;

                        case 11:
#line 144 "parser.yy"
                        {
                            yylhs.value.as < ConstDef* > ()=new ConstDef();
                            yylhs.value.as < ConstDef* > ()->identifier=yystack_[3].value.as < std::string > ();
                            yylhs.value.as < ConstDef* > ()->constExpList.swap(yystack_[2].value.as < ConstExpList* > ()->constExpList);
                            yylhs.value.as < ConstDef* > ()->constInitVal=std::shared_ptr<ConstInitVal>(yystack_[0].value.as < ConstInitVal* > ());
                        }
#line 1595 "parser.cc"
                            break;

                        case 12:
#line 151 "parser.yy"
                        {
                            yystack_[3].value.as < ConstExpList* > ()->constExpList.push_back(std::shared_ptr<ConstExp>(yystack_[1].value.as < ConstExp* > ()));
                            yylhs.value.as < ConstExpList* > ()=yystack_[3].value.as < ConstExpList* > ();
                        }
#line 1604 "parser.cc"
                            break;

                        case 13:
#line 155 "parser.yy"
                        {
                            yylhs.value.as < ConstExpList* > ()=new ConstExpList();
                        }
#line 1612 "parser.cc"
                            break;

                        case 14:
#line 160 "parser.yy"
                        {
                            yylhs.value.as < ConstInitVal* > ()=new ConstInitVal();
                            yylhs.value.as < ConstInitVal* > ()->constExp=std::shared_ptr<ConstExp>(yystack_[0].value.as < ConstExp* > ());
                        }
#line 1621 "parser.cc"
                            break;

                        case 15:
#line 164 "parser.yy"
                        {
                            yylhs.value.as < ConstInitVal* > ()=new ConstInitVal();
                            yylhs.value.as < ConstInitVal* > ()->constInitValList.swap(yystack_[1].value.as < ConstInitValList* > ()->constInitValList);
                        }
#line 1630 "parser.cc"
                            break;

                        case 16:
#line 168 "parser.yy"
                        {
                            yylhs.value.as < ConstInitVal* > ()=new ConstInitVal();
                        }
#line 1638 "parser.cc"
                            break;

                        case 17:
#line 172 "parser.yy"
                        {
                            yystack_[2].value.as < ConstInitValList* > ()->constInitValList.push_back(std::shared_ptr<ConstInitVal>(yystack_[0].value.as < ConstInitVal* > ()));
                            yylhs.value.as < ConstInitValList* > ()=yystack_[2].value.as < ConstInitValList* > ();
                        }
#line 1647 "parser.cc"
                            break;

                        case 18:
#line 176 "parser.yy"
                        {
                            yylhs.value.as < ConstInitValList* > ()=new ConstInitValList();
                            yylhs.value.as < ConstInitValList* > ()->constInitValList.push_back(std::shared_ptr<ConstInitVal>(yystack_[0].value.as < ConstInitVal* > ()));
                        }
#line 1656 "parser.cc"
                            break;

                        case 19:
#line 182 "parser.yy"
                        {
                            yylhs.value.as < VarDecl* > ()=new VarDecl();
                            yylhs.value.as < VarDecl* > ()->varDefList.swap(yystack_[1].value.as < VarDefList* > ()->varDefList);
                            yylhs.value.as < VarDecl* > ()->defType=std::shared_ptr<DefType>(yystack_[2].value.as < DefType* > ());
                        }
#line 1666 "parser.cc"
                            break;

                        case 20:
#line 189 "parser.yy"
                        {
                            yystack_[2].value.as < VarDefList* > ()->varDefList.push_back(std::shared_ptr<VarDef>(yystack_[0].value.as < VarDef* > ()));
                            yylhs.value.as < VarDefList* > ()=yystack_[2].value.as < VarDefList* > ();
                        }
#line 1675 "parser.cc"
                            break;

                        case 21:
#line 193 "parser.yy"
                        {
                            yylhs.value.as < VarDefList* > ()=new VarDefList();
                            yylhs.value.as < VarDefList* > ()->varDefList.push_back(std::shared_ptr<VarDef>(yystack_[0].value.as < VarDef* > ()));
                        }
#line 1684 "parser.cc"
                            break;

                        case 22:
#line 199 "parser.yy"
                        {
                            yylhs.value.as < VarDef* > ()=new VarDef();
                            yylhs.value.as < VarDef* > ()->identifier=yystack_[1].value.as < std::string > ();
                            yylhs.value.as < VarDef* > ()->constExpList.swap(yystack_[0].value.as < ConstExpList* > ()->constExpList);
                        }
#line 1694 "parser.cc"
                            break;

                        case 23:
#line 204 "parser.yy"
                        {
                            yylhs.value.as < VarDef* > ()=new VarDef();
                            yylhs.value.as < VarDef* > ()->identifier=yystack_[3].value.as < std::string > ();
                            yylhs.value.as < VarDef* > ()->constExpList.swap(yystack_[2].value.as < ConstExpList* > ()->constExpList);
                            yylhs.value.as < VarDef* > ()->initVal=std::shared_ptr<InitVal>(yystack_[0].value.as < InitVal* > ());
                        }
#line 1705 "parser.cc"
                            break;

                        case 24:
#line 211 "parser.yy"
                        {
                            yylhs.value.as < InitVal* > ()=new InitVal();
                            yylhs.value.as < InitVal* > ()->exp=std::shared_ptr<Exp>(yystack_[0].value.as < Exp* > ());
                        }
#line 1714 "parser.cc"
                            break;

                        case 25:
#line 215 "parser.yy"
                        {
                            yylhs.value.as < InitVal* > ()=new InitVal();
                        }
#line 1722 "parser.cc"
                            break;

                        case 26:
#line 218 "parser.yy"
                        {
                            yylhs.value.as < InitVal* > ()=new InitVal();
                            yylhs.value.as < InitVal* > ()->initValList.swap(yystack_[1].value.as < InitValList* > ()->initValList);
                        }
#line 1731 "parser.cc"
                            break;

                        case 27:
#line 223 "parser.yy"
                        {
                            yystack_[2].value.as < InitValList* > ()->initValList.push_back(std::shared_ptr<InitVal>(yystack_[0].value.as < InitVal* > ()));
                            yylhs.value.as < InitValList* > ()=yystack_[2].value.as < InitValList* > ();
                        }
#line 1740 "parser.cc"
                            break;

                        case 28:
#line 227 "parser.yy"
                        {
                            yylhs.value.as < InitValList* > ()=new InitValList();
                            yylhs.value.as < InitValList* > ()->initValList.push_back(std::shared_ptr<InitVal>(yystack_[0].value.as < InitVal* > ()));
                        }
#line 1749 "parser.cc"
                            break;

                        case 29:
#line 233 "parser.yy"
                        {
                            yylhs.value.as < FuncDef* > ()=new FuncDef();
                            yylhs.value.as < FuncDef* > ()->defType=std::shared_ptr<DefType>(yystack_[4].value.as < DefType* > ());
                            yylhs.value.as < FuncDef* > ()->identifier=yystack_[3].value.as < std::string > ();
                            yylhs.value.as < FuncDef* > ()->block=std::shared_ptr<Block>(yystack_[0].value.as < Block* > ());
                        }
#line 1760 "parser.cc"
                            break;

                        case 30:
#line 239 "parser.yy"
                        {
                            yylhs.value.as < FuncDef* > ()=new FuncDef();
                            yylhs.value.as < FuncDef* > ()->defType=std::shared_ptr<DefType>(yystack_[5].value.as < DefType* > ());
                            yylhs.value.as < FuncDef* > ()->identifier=yystack_[4].value.as < std::string > ();
                            yylhs.value.as < FuncDef* > ()->funcFParams=std::shared_ptr<FuncFParams>(yystack_[2].value.as < FuncFParams* > ());
                            yylhs.value.as < FuncDef* > ()->block=std::shared_ptr<Block>(yystack_[0].value.as < Block* > ());
                        }
#line 1772 "parser.cc"
                            break;

                        case 31:
#line 247 "parser.yy"
                        {
                            yylhs.value.as < DefType* > ()=new DefType();
                            yylhs.value.as < DefType* > ()->type=type_specifier::TYPE_VOID;
                        }
#line 1781 "parser.cc"
                            break;

                        case 32:
#line 251 "parser.yy"
                        {
                            yylhs.value.as < DefType* > ()=new DefType();
                            yylhs.value.as < DefType* > ()->type=type_specifier::TYPE_INT;
                        }
#line 1790 "parser.cc"
                            break;

                        case 33:
#line 255 "parser.yy"
                        {
                            yylhs.value.as < DefType* > ()=new DefType();
                            yylhs.value.as < DefType* > ()->type=type_specifier::TYPE_FLOAT;
                        }
#line 1799 "parser.cc"
                            break;

                        case 34:
#line 260 "parser.yy"
                        {
                            yystack_[2].value.as < FuncFParams* > ()->funcFParamList.push_back(std::shared_ptr<FuncFParam>(yystack_[0].value.as < FuncFParam* > ()));
                            yylhs.value.as < FuncFParams* > ()=yystack_[2].value.as < FuncFParams* > ();
                        }
#line 1808 "parser.cc"
                            break;

                        case 35:
#line 264 "parser.yy"
                        {
                            yylhs.value.as < FuncFParams* > ()=new FuncFParams();
                            yylhs.value.as < FuncFParams* > ()->funcFParamList.push_back(std::shared_ptr<FuncFParam>(yystack_[0].value.as < FuncFParam* > ()));
                        }
#line 1817 "parser.cc"
                            break;

                        case 36:
#line 270 "parser.yy"
                        {
                            yylhs.value.as < FuncFParam* > ()=new FuncFParam();
                            yylhs.value.as < FuncFParam* > ()->defType=std::shared_ptr<DefType>(yystack_[4].value.as < DefType* > ());
                            yylhs.value.as < FuncFParam* > ()->identifier=yystack_[3].value.as < std::string > ();
                            yylhs.value.as < FuncFParam* > ()->isArray = true;
                            yylhs.value.as < FuncFParam* > ()->expList.swap(yystack_[0].value.as < ParamArrayExpList* > ()->expList);
                        }
#line 1829 "parser.cc"
                            break;

                        case 37:
#line 277 "parser.yy"
                        {
                            yylhs.value.as < FuncFParam* > ()=new FuncFParam();
                            yylhs.value.as < FuncFParam* > ()->isArray = false;
                            yylhs.value.as < FuncFParam* > ()->defType=std::shared_ptr<DefType>(yystack_[1].value.as < DefType* > ());
                            yylhs.value.as < FuncFParam* > ()->identifier=yystack_[0].value.as < std::string > ();
                        }
#line 1840 "parser.cc"
                            break;

                        case 38:
#line 285 "parser.yy"
                        {
                            yystack_[3].value.as < ParamArrayExpList* > ()->expList.push_back(std::shared_ptr<Exp>(yystack_[1].value.as < Exp* > ()));
                            yylhs.value.as < ParamArrayExpList* > ()=yystack_[3].value.as < ParamArrayExpList* > ();
                        }
#line 1849 "parser.cc"
                            break;

                        case 39:
#line 289 "parser.yy"
                        {
                            yylhs.value.as < ParamArrayExpList* > ()=new ParamArrayExpList();
                        }
#line 1857 "parser.cc"
                            break;

                        case 40:
#line 294 "parser.yy"
                        {
                            yylhs.value.as < Block* > ()=new Block();
                            yylhs.value.as < Block* > ()->blockItemList.swap(yystack_[1].value.as < BlockItemList* > ()->blockItemList);
                        }
#line 1866 "parser.cc"
                            break;

                        case 41:
#line 300 "parser.yy"
                        {
                            yystack_[1].value.as < BlockItemList* > ()->blockItemList.push_back(std::shared_ptr<BlockItem>(yystack_[0].value.as < BlockItem* > ()));
                            yylhs.value.as < BlockItemList* > ()=yystack_[1].value.as < BlockItemList* > ();
                        }
#line 1875 "parser.cc"
                            break;

                        case 42:
#line 304 "parser.yy"
                        {
                            yylhs.value.as < BlockItemList* > ()=new BlockItemList();
                        }
#line 1883 "parser.cc"
                            break;

                        case 43:
#line 309 "parser.yy"
                        {
                            yylhs.value.as < BlockItem* > ()=new BlockItem();
                            yylhs.value.as < BlockItem* > ()->constDecl=std::shared_ptr<ConstDecl>(yystack_[0].value.as < ConstDecl* > ());
                        }
#line 1892 "parser.cc"
                            break;

                        case 44:
#line 313 "parser.yy"
                        {
                            yylhs.value.as < BlockItem* > ()=new BlockItem();
                            yylhs.value.as < BlockItem* > ()->varDecl=std::shared_ptr<VarDecl>(yystack_[0].value.as < VarDecl* > ());
                        }
#line 1901 "parser.cc"
                            break;

                        case 45:
#line 317 "parser.yy"
                        {
                            yylhs.value.as < BlockItem* > ()=new BlockItem();
                            yylhs.value.as < BlockItem* > ()->stmt=std::shared_ptr<Stmt>(yystack_[0].value.as < Stmt* > ());
                        }
#line 1910 "parser.cc"
                            break;

                        case 46:
#line 323 "parser.yy"
                        {
                            yylhs.value.as < Stmt* > ()=new Stmt();
                            yylhs.value.as < Stmt* > ()->assignStmt = std::shared_ptr<AssignStmt>(yystack_[0].value.as < AssignStmt* > ());
                        }
#line 1919 "parser.cc"
                            break;

                        case 47:
#line 327 "parser.yy"
                        {
                            yylhs.value.as < Stmt* > ()=new Stmt();
                            yylhs.value.as < Stmt* > ()->exp = std::shared_ptr<Exp>(yystack_[1].value.as < Exp* > ());
                        }
#line 1928 "parser.cc"
                            break;

                        case 48:
#line 331 "parser.yy"
                        {

                        }
#line 1936 "parser.cc"
                            break;

                        case 49:
#line 334 "parser.yy"
                        {
                            yylhs.value.as < Stmt* > ()=new Stmt();
                            yylhs.value.as < Stmt* > ()->block=std::shared_ptr<Block>(yystack_[0].value.as < Block* > ());
                        }
#line 1945 "parser.cc"
                            break;

                        case 50:
#line 338 "parser.yy"
                        {
                            yylhs.value.as < Stmt* > ()=new Stmt();
                            yylhs.value.as < Stmt* > ()->selectStmt = std::shared_ptr<SelectStmt>(yystack_[0].value.as < SelectStmt* > ());
                        }
#line 1954 "parser.cc"
                            break;

                        case 51:
#line 342 "parser.yy"
                        {
                            yylhs.value.as < Stmt* > ()=new Stmt();
                            yylhs.value.as < Stmt* > ()->iterationStmt = std::shared_ptr<IterationStmt>(yystack_[0].value.as < IterationStmt* > ());
                        }
#line 1963 "parser.cc"
                            break;

                        case 52:
#line 346 "parser.yy"
                        {
                            yylhs.value.as < Stmt* > ()=new Stmt();
                            yylhs.value.as < Stmt* > ()->breakStmt = std::shared_ptr<BreakStmt>(yystack_[0].value.as < BreakStmt* > ());
                        }
#line 1972 "parser.cc"
                            break;

                        case 53:
#line 350 "parser.yy"
                        {
                            yylhs.value.as < Stmt* > ()=new Stmt();
                            yylhs.value.as < Stmt* > ()->continueStmt = std::shared_ptr<ContinueStmt>(yystack_[0].value.as < ContinueStmt* > ());
                        }
#line 1981 "parser.cc"
                            break;

                        case 54:
#line 354 "parser.yy"
                        {
                            yylhs.value.as < Stmt* > ()=new Stmt();
                            yylhs.value.as < Stmt* > ()->returnStmt = std::shared_ptr<ReturnStmt>(yystack_[0].value.as < ReturnStmt* > ());
                        }
#line 1990 "parser.cc"
                            break;

                        case 55:
#line 359 "parser.yy"
                        {
                            yylhs.value.as < AssignStmt* > ()=new AssignStmt();
                            yylhs.value.as < AssignStmt* > ()->lVal=std::shared_ptr<LVal>(yystack_[3].value.as < LVal* > ());
                            yylhs.value.as < AssignStmt* > ()->exp=std::shared_ptr<Exp>(yystack_[1].value.as < Exp* > ());
                        }
#line 2000 "parser.cc"
                            break;

                        case 56:
#line 365 "parser.yy"
                        {
                            yylhs.value.as < SelectStmt* > ()=new SelectStmt();
                            yylhs.value.as < SelectStmt* > ()->cond=std::shared_ptr<Cond>(yystack_[2].value.as < Cond* > ());
                            yylhs.value.as < SelectStmt* > ()->ifStmt=std::shared_ptr<Stmt>(yystack_[0].value.as < Stmt* > ());
                        }
#line 2010 "parser.cc"
                            break;

                        case 57:
#line 370 "parser.yy"
                        {
                            yylhs.value.as < SelectStmt* > ()=new SelectStmt();
                            yylhs.value.as < SelectStmt* > ()->cond=std::shared_ptr<Cond>(yystack_[4].value.as < Cond* > ());
                            yylhs.value.as < SelectStmt* > ()->ifStmt=std::shared_ptr<Stmt>(yystack_[2].value.as < Stmt* > ());
                            yylhs.value.as < SelectStmt* > ()->elseStmt=std::shared_ptr<Stmt>(yystack_[0].value.as < Stmt* > ());
                        }
#line 2021 "parser.cc"
                            break;

                        case 58:
#line 377 "parser.yy"
                        {
                            yylhs.value.as < IterationStmt* > ()=new IterationStmt();
                            yylhs.value.as < IterationStmt* > ()->cond=std::shared_ptr<Cond>(yystack_[2].value.as < Cond* > ());
                            yylhs.value.as < IterationStmt* > ()->stmt=std::shared_ptr<Stmt>(yystack_[0].value.as < Stmt* > ());
                        }
#line 2031 "parser.cc"
                            break;

                        case 59:
#line 383 "parser.yy"
                        {
                            yylhs.value.as < BreakStmt* > ()=new BreakStmt();
                        }
#line 2039 "parser.cc"
                            break;

                        case 60:
#line 387 "parser.yy"
                        {
                            yylhs.value.as < ContinueStmt* > ()=new ContinueStmt();
                        }
#line 2047 "parser.cc"
                            break;

                        case 61:
#line 391 "parser.yy"
                        {
                            yylhs.value.as < ReturnStmt* > ()=new ReturnStmt();
                        }
#line 2055 "parser.cc"
                            break;

                        case 62:
#line 394 "parser.yy"
                        {
                            yylhs.value.as < ReturnStmt* > ()=new ReturnStmt();
                            yylhs.value.as < ReturnStmt* > ()->exp=std::shared_ptr<Exp>(yystack_[1].value.as < Exp* > ());
                        }
#line 2064 "parser.cc"
                            break;

                        case 63:
#line 399 "parser.yy"
                        {
                            yylhs.value.as < Exp* > ()=new Exp();
                            yylhs.value.as < Exp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
                        }
#line 2073 "parser.cc"
                            break;

                        case 64:
#line 405 "parser.yy"
                        {
                            yylhs.value.as < Cond* > ()=new Cond();
                            yylhs.value.as < Cond* > ()->lOrExp=std::shared_ptr<LOrExp>(yystack_[0].value.as < LOrExp* > ());
                        }
#line 2082 "parser.cc"
                            break;

                        case 65:
#line 410 "parser.yy"
                        {
                            yylhs.value.as < LVal* > ()=new LVal();
                            yylhs.value.as < LVal* > ()->identifier=yystack_[1].value.as < std::string > ();
                            yylhs.value.as < LVal* > ()->expList.swap(yystack_[0].value.as < ParamArrayExpList* > ()->expList);
                        }
#line 2092 "parser.cc"
                            break;

                        case 66:
#line 417 "parser.yy"
                        {
                            yylhs.value.as < PrimaryExp* > ()=new PrimaryExp();
                            yylhs.value.as < PrimaryExp* > ()->exp=std::shared_ptr<Exp>(yystack_[1].value.as < Exp* > ());
                        }
#line 2101 "parser.cc"
                            break;

                        case 67:
#line 421 "parser.yy"
                        {
                            yylhs.value.as < PrimaryExp* > ()=new PrimaryExp();
                            yylhs.value.as < PrimaryExp* > ()->lVal=std::shared_ptr<LVal>(yystack_[0].value.as < LVal* > ());
                        }
#line 2110 "parser.cc"
                            break;

                        case 68:
#line 425 "parser.yy"
                        {
                            yylhs.value.as < PrimaryExp* > ()=new PrimaryExp();
                            yylhs.value.as < PrimaryExp* > ()->number=std::shared_ptr<Number>(yystack_[0].value.as < Number* > ());
                        }
#line 2119 "parser.cc"
                            break;

                        case 69:
#line 430 "parser.yy"
                        {
                            yylhs.value.as < Number* > ()=new Number();
                            yylhs.value.as < Number* > ()->type=type_specifier::TYPE_INT;
                            yylhs.value.as < Number* > ()->intNum=yystack_[0].value.as < int > ();
                        }
#line 2129 "parser.cc"
                            break;

                        case 70:
#line 435 "parser.yy"
                        {
                            yylhs.value.as < Number* > ()=new Number();
                            yylhs.value.as < Number* > ()->type=type_specifier::TYPE_FLOAT;
                            yylhs.value.as < Number* > ()->floatNum=yystack_[0].value.as < float > ();
                        }
#line 2139 "parser.cc"
                            break;

                        case 71:
#line 442 "parser.yy"
                        {
                            yylhs.value.as < UnaryExp* > ()=new UnaryExp();
                            yylhs.value.as < UnaryExp* > ()->primaryExp=std::shared_ptr<PrimaryExp>(yystack_[0].value.as < PrimaryExp* > ());
                        }
#line 2148 "parser.cc"
                            break;

                        case 72:
#line 446 "parser.yy"
                        {
                            yylhs.value.as < UnaryExp* > ()=new UnaryExp();
                            yylhs.value.as < UnaryExp* > ()->identifier=yystack_[3].value.as < std::string > ();
                            yylhs.value.as < UnaryExp* > ()->funcRParams=std::shared_ptr<FuncRParams>(yystack_[1].value.as < FuncRParams* > ());
                        }
#line 2158 "parser.cc"
                            break;

                        case 73:
#line 451 "parser.yy"
                        {
                            yylhs.value.as < UnaryExp* > ()=new UnaryExp();
                            yylhs.value.as < UnaryExp* > ()->identifier=yystack_[2].value.as < std::string > ();
                        }
#line 2167 "parser.cc"
                            break;

                        case 74:
#line 455 "parser.yy"
                        {
                            yylhs.value.as < UnaryExp* > ()=new UnaryExp();
                            yylhs.value.as < UnaryExp* > ()->unaryOp=std::shared_ptr<UnaryOp>(yystack_[1].value.as < UnaryOp* > ());
                            yylhs.value.as < UnaryExp* > ()->unaryExp=std::shared_ptr<UnaryExp>(yystack_[0].value.as < UnaryExp* > ());
                        }
#line 2177 "parser.cc"
                            break;

                        case 75:
#line 460 "parser.yy"
                        {
                            yylhs.value.as < UnaryExp* > ()=new UnaryExp();
                            yylhs.value.as < UnaryExp* > ()->stringConst=yystack_[0].value.as < std::string > ();
                        }
#line 2186 "parser.cc"
                            break;

                        case 76:
#line 465 "parser.yy"
                        {
                            yylhs.value.as < UnaryOp* > ()=new UnaryOp();
                            yylhs.value.as < UnaryOp* > ()->op=unaryop::OP_POS;
                        }
#line 2195 "parser.cc"
                            break;

                        case 77:
#line 469 "parser.yy"
                        {
                            yylhs.value.as < UnaryOp* > ()=new UnaryOp();
                            yylhs.value.as < UnaryOp* > ()->op=unaryop::OP_NEG;
                        }
#line 2204 "parser.cc"
                            break;

                        case 78:
#line 473 "parser.yy"
                        {
                            yylhs.value.as < UnaryOp* > ()=new UnaryOp();
                            yylhs.value.as < UnaryOp* > ()->op=unaryop::OP_NOT;
                        }
#line 2213 "parser.cc"
                            break;

                        case 79:
#line 478 "parser.yy"
                        {
                            yystack_[2].value.as < FuncRParams* > ()->expList.push_back(std::shared_ptr<Exp>(yystack_[0].value.as < Exp* > ()));
                            yylhs.value.as < FuncRParams* > ()=yystack_[2].value.as < FuncRParams* > ();
                        }
#line 2222 "parser.cc"
                            break;

                        case 80:
#line 482 "parser.yy"
                        {
                            yylhs.value.as < FuncRParams* > ()=new FuncRParams();
                            yylhs.value.as < FuncRParams* > ()->expList.push_back(std::shared_ptr<Exp>(yystack_[0].value.as < Exp* > ()));
                        }
#line 2231 "parser.cc"
                            break;

                        case 81:
#line 488 "parser.yy"
                        {
                            yylhs.value.as < MulExp* > ()=new MulExp();
                            yylhs.value.as < MulExp* > ()->unaryExp=std::shared_ptr<UnaryExp>(yystack_[0].value.as < UnaryExp* > ());
                        }
#line 2240 "parser.cc"
                            break;

                        case 82:
#line 492 "parser.yy"
                        {
                            yylhs.value.as < MulExp* > ()=new MulExp();
                            yylhs.value.as < MulExp* > ()->mulExp=std::shared_ptr<MulExp>(yystack_[2].value.as < MulExp* > ());
                            yylhs.value.as < MulExp* > ()->unaryExp=std::shared_ptr<UnaryExp>(yystack_[0].value.as < UnaryExp* > ());
                            yylhs.value.as < MulExp* > ()->op=mulop::OP_MUL;
                        }
#line 2251 "parser.cc"
                            break;

                        case 83:
#line 498 "parser.yy"
                        {
                            yylhs.value.as < MulExp* > ()=new MulExp();
                            yylhs.value.as < MulExp* > ()->mulExp=std::shared_ptr<MulExp>(yystack_[2].value.as < MulExp* > ());
                            yylhs.value.as < MulExp* > ()->unaryExp=std::shared_ptr<UnaryExp>(yystack_[0].value.as < UnaryExp* > ());
                            yylhs.value.as < MulExp* > ()->op=mulop::OP_DIV;
                        }
#line 2262 "parser.cc"
                            break;

                        case 84:
#line 504 "parser.yy"
                        {
                            yylhs.value.as < MulExp* > ()=new MulExp();
                            yylhs.value.as < MulExp* > ()->mulExp=std::shared_ptr<MulExp>(yystack_[2].value.as < MulExp* > ());
                            yylhs.value.as < MulExp* > ()->unaryExp=std::shared_ptr<UnaryExp>(yystack_[0].value.as < UnaryExp* > ());
                            yylhs.value.as < MulExp* > ()->op=mulop::OP_MOD;
                        }
#line 2273 "parser.cc"
                            break;

                        case 85:
#line 512 "parser.yy"
                        {
                            yylhs.value.as < AddExp* > ()=new AddExp();
                            yylhs.value.as < AddExp* > ()->mulExp=std::shared_ptr<MulExp>(yystack_[0].value.as < MulExp* > ());
                        }
#line 2282 "parser.cc"
                            break;

                        case 86:
#line 516 "parser.yy"
                        {
                            yylhs.value.as < AddExp* > ()=new AddExp();
                            yylhs.value.as < AddExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[2].value.as < AddExp* > ());
                            yylhs.value.as < AddExp* > ()->mulExp=std::shared_ptr<MulExp>(yystack_[0].value.as < MulExp* > ());
                            yylhs.value.as < AddExp* > ()->op=addop::OP_ADD;
                        }
#line 2293 "parser.cc"
                            break;

                        case 87:
#line 522 "parser.yy"
                        {
                            yylhs.value.as < AddExp* > ()=new AddExp();
                            yylhs.value.as < AddExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[2].value.as < AddExp* > ());
                            yylhs.value.as < AddExp* > ()->mulExp=std::shared_ptr<MulExp>(yystack_[0].value.as < MulExp* > ());
                            yylhs.value.as < AddExp* > ()->op=addop::OP_SUB;
                        }
#line 2304 "parser.cc"
                            break;

                        case 88:
#line 530 "parser.yy"
                        {
                            yylhs.value.as < RelExp* > ()=new RelExp();
                            yylhs.value.as < RelExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
                        }
#line 2313 "parser.cc"
                            break;

                        case 89:
#line 534 "parser.yy"
                        {
                            yylhs.value.as < RelExp* > ()=new RelExp();
                            yylhs.value.as < RelExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[2].value.as < RelExp* > ());
                            yylhs.value.as < RelExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
                            yylhs.value.as < RelExp* > ()->op=relop::OP_LT;
                        }
#line 2324 "parser.cc"
                            break;

                        case 90:
#line 540 "parser.yy"
                        {
                            yylhs.value.as < RelExp* > ()=new RelExp();
                            yylhs.value.as < RelExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[2].value.as < RelExp* > ());
                            yylhs.value.as < RelExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
                            yylhs.value.as < RelExp* > ()->op=relop::OP_GT;
                        }
#line 2335 "parser.cc"
                            break;

                        case 91:
#line 546 "parser.yy"
                        {
                            yylhs.value.as < RelExp* > ()=new RelExp();
                            yylhs.value.as < RelExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[2].value.as < RelExp* > ());
                            yylhs.value.as < RelExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
                            yylhs.value.as < RelExp* > ()->op=relop::OP_LE;
                        }
#line 2346 "parser.cc"
                            break;

                        case 92:
#line 552 "parser.yy"
                        {
                            yylhs.value.as < RelExp* > ()=new RelExp();
                            yylhs.value.as < RelExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[2].value.as < RelExp* > ());
                            yylhs.value.as < RelExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
                            yylhs.value.as < RelExp* > ()->op=relop::OP_GE;
                        }
#line 2357 "parser.cc"
                            break;

                        case 93:
#line 559 "parser.yy"
                        {
                            yylhs.value.as < EqExp* > ()=new EqExp();
                            yylhs.value.as < EqExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[0].value.as < RelExp* > ());
                        }
#line 2366 "parser.cc"
                            break;

                        case 94:
#line 563 "parser.yy"
                        {
                            yylhs.value.as < EqExp* > ()=new EqExp();
                            yylhs.value.as < EqExp* > ()->eqExp=std::shared_ptr<EqExp>(yystack_[2].value.as < EqExp* > ());
                            yylhs.value.as < EqExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[0].value.as < RelExp* > ());
                            yylhs.value.as < EqExp* > ()->op=relop::OP_EQU;
                        }
#line 2377 "parser.cc"
                            break;

                        case 95:
#line 569 "parser.yy"
                        {
                            yylhs.value.as < EqExp* > ()=new EqExp();
                            yylhs.value.as < EqExp* > ()->eqExp=std::shared_ptr<EqExp>(yystack_[2].value.as < EqExp* > ());
                            yylhs.value.as < EqExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[0].value.as < RelExp* > ());
                            yylhs.value.as < EqExp* > ()->op=relop::OP_NE;
                        }
#line 2388 "parser.cc"
                            break;

                        case 96:
#line 576 "parser.yy"
                        {
                            yylhs.value.as < LAndExp* > ()=new LAndExp();
                            yylhs.value.as < LAndExp* > ()->eqExp=std::shared_ptr<EqExp>(yystack_[0].value.as < EqExp* > ());
                        }
#line 2397 "parser.cc"
                            break;

                        case 97:
#line 580 "parser.yy"
                        {
                            yylhs.value.as < LAndExp* > ()=new LAndExp();
                            yylhs.value.as < LAndExp* > ()->lAndExp=std::shared_ptr<LAndExp>(yystack_[2].value.as < LAndExp* > ());
                            yylhs.value.as < LAndExp* > ()->eqExp=std::shared_ptr<EqExp>(yystack_[0].value.as < EqExp* > ());
                        }
#line 2407 "parser.cc"
                            break;

                        case 98:
#line 586 "parser.yy"
                        {
                            yylhs.value.as < LOrExp* > ()=new LOrExp();
                            yylhs.value.as < LOrExp* > ()->lAndExp=std::shared_ptr<LAndExp>(yystack_[0].value.as < LAndExp* > ());
                        }
#line 2416 "parser.cc"
                            break;

                        case 99:
#line 590 "parser.yy"
                        {
                            yylhs.value.as < LOrExp* > ()=new LOrExp();
                            yylhs.value.as < LOrExp* > ()->lOrExp=std::shared_ptr<LOrExp>(yystack_[2].value.as < LOrExp* > ());
                            yylhs.value.as < LOrExp* > ()->lAndExp=std::shared_ptr<LAndExp>(yystack_[0].value.as < LAndExp* > ());
                        }
#line 2426 "parser.cc"
                            break;

                        case 100:
#line 596 "parser.yy"
                        {
                            yylhs.value.as < ConstExp* > ()=new ConstExp();
                            yylhs.value.as < ConstExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
                        }
#line 2435 "parser.cc"
                            break;


#line 2439 "parser.cc"

                        default:
                            break;
                    }
                }
#if YY_EXCEPTIONS
                catch (const syntax_error& yyexc)
                {
                    YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
                    error (yyexc);
                    YYERROR;
                }
#endif // YY_EXCEPTIONS
                YY_SYMBOL_PRINT ("-> $$ =", yylhs);
                yypop_ (yylen);
                yylen = 0;
                YY_STACK_PRINT ();

                // Shift the result of the reduction.
                yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
            }
            goto yynewstate;


            /*--------------------------------------.
            | yyerrlab -- here on detecting error.  |
            `--------------------------------------*/
            yyerrlab:
            // If not already recovering from an error, report this error.
            if (!yyerrstatus_)
            {
                ++yynerrs_;
                error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
            }


            yyerror_range[1].location = yyla.location;
            if (yyerrstatus_ == 3)
            {
                /* If just tried and failed to reuse lookahead token after an
                   error, discard it.  */

                // Return failure if at end of input.
                if (yyla.type_get () == yyeof_)
                    YYABORT;
                else if (!yyla.empty ())
                {
                    yy_destroy_ ("Error: discarding", yyla);
                    yyla.clear ();
                }
            }

            // Else will try to reuse lookahead token after shifting the error token.
            goto yyerrlab1;


            /*---------------------------------------------------.
            | yyerrorlab -- error raised explicitly by YYERROR.  |
            `---------------------------------------------------*/
            yyerrorlab:
            /* Pacify compilers when the user code never invokes YYERROR and
               the label yyerrorlab therefore never appears in user code.  */
            if (false)
                YYERROR;

            /* Do not reclaim the symbols of the rule whose action triggered
               this YYERROR.  */
            yypop_ (yylen);
            yylen = 0;
            goto yyerrlab1;


            /*-------------------------------------------------------------.
            | yyerrlab1 -- common code for both syntax error and YYERROR.  |
            `-------------------------------------------------------------*/
            yyerrlab1:
            yyerrstatus_ = 3;   // Each real token shifted decrements this.
            {
                stack_symbol_type error_token;
                for (;;)
                {
                    yyn = yypact_[+yystack_[0].state];
                    if (!yy_pact_value_is_default_ (yyn))
                    {
                        yyn += yy_error_token_;
                        if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                        {
                            yyn = yytable_[yyn];
                            if (0 < yyn)
                                break;
                        }
                    }

                    // Pop the current state because it cannot handle the error token.
                    if (yystack_.size () == 1)
                        YYABORT;

                    yyerror_range[1].location = yystack_[0].location;
                    yy_destroy_ ("Error: popping", yystack_[0]);
                    yypop_ ();
                    YY_STACK_PRINT ();
                }

                yyerror_range[2].location = yyla.location;
                YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

                // Shift the error token.
                error_token.state = state_type (yyn);
                yypush_ ("Shifting", YY_MOVE (error_token));
            }
            goto yynewstate;


            /*-------------------------------------.
            | yyacceptlab -- YYACCEPT comes here.  |
            `-------------------------------------*/
            yyacceptlab:
            yyresult = 0;
            goto yyreturn;


            /*-----------------------------------.
            | yyabortlab -- YYABORT comes here.  |
            `-----------------------------------*/
            yyabortlab:
            yyresult = 1;
            goto yyreturn;


            /*-----------------------------------------------------.
            | yyreturn -- parsing is finished, return the result.  |
            `-----------------------------------------------------*/
            yyreturn:
            if (!yyla.empty ())
                yy_destroy_ ("Cleanup: discarding lookahead", yyla);

            /* Do not reclaim the symbols of the rule whose action triggered
               this YYABORT or YYACCEPT.  */
            yypop_ (yylen);
            while (1 < yystack_.size ())
            {
                yy_destroy_ ("Cleanup: popping", yystack_[0]);
                yypop_ ();
            }

            return yyresult;
        }
#if YY_EXCEPTIONS
        catch (...)
        {
            YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
            // Do not try to display the values of the reclaimed symbols,
            // as their printers might throw an exception.
            if (!yyla.empty ())
                yy_destroy_ (YY_NULLPTR, yyla);

            while (1 < yystack_.size ())
            {
                yy_destroy_ (YY_NULLPTR, yystack_[0]);
                yypop_ ();
            }
            throw;
        }
#endif // YY_EXCEPTIONS
    }

    void
    parser::error (const syntax_error& yyexc)
    {
        error (yyexc.location, yyexc.what ());
    }

    // Generate an error message.
    std::string
    parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
    {
        // Number of reported tokens (one for the "unexpected", one per
        // "expected").
        std::ptrdiff_t yycount = 0;
        // Its maximum.
        enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
        // Arguments of yyformat.
        char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

        /* There are many possibilities here to consider:
           - If this state is a consistent state with a default action, then
             the only way this function was invoked is if the default action
             is an error action.  In that case, don't check for expected
             tokens because there are none.
           - The only way there can be no lookahead present (in yyla) is
             if this state is a consistent state with a default action.
             Thus, detecting the absence of a lookahead is sufficient to
             determine that there is no unexpected or expected token to
             report.  In that case, just report a simple "syntax error".
           - Don't assume there isn't a lookahead just because this state is
             a consistent state with a default action.  There might have
             been a previous inconsistent state, consistent state with a
             non-default action, or user semantic action that manipulated
             yyla.  (However, yyla is currently not documented for users.)
           - Of course, the expected token list depends on states to have
             correct lookahead information, and it depends on the parser not
             to perform extra reductions after fetching a lookahead from the
             scanner and before detecting a syntax error.  Thus, state merging
             (from LALR or IELR) and default reductions corrupt the expected
             token list.  However, the list is correct for canonical LR with
             one exception: it will still contain any token that will not be
             accepted due to an error action in a later state.
        */
        if (!yyla.empty ())
        {
            symbol_number_type yytoken = yyla.type_get ();
            yyarg[yycount++] = yytname_[yytoken];

            int yyn = yypact_[+yystate];
            if (!yy_pact_value_is_default_ (yyn))
            {
                /* Start YYX at -YYN if negative to avoid negative indexes in
                   YYCHECK.  In other words, skip the first -YYN actions for
                   this state because they are default actions.  */
                int yyxbegin = yyn < 0 ? -yyn : 0;
                // Stay within bounds of both yycheck and yytname.
                int yychecklim = yylast_ - yyn + 1;
                int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
                for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
                    if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                        && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                    {
                        if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                        {
                            yycount = 1;
                            break;
                        }
                        else
                            yyarg[yycount++] = yytname_[yyx];
                    }
            }
        }

        char const* yyformat = YY_NULLPTR;
        switch (yycount)
        {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
            default: // Avoid compiler warnings.
            YYCASE_ (0, YY_("syntax error"));
            YYCASE_ (1, YY_("syntax error, unexpected %s"));
            YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
            YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
            YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
            YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
        }

        std::string yyres;
        // Argument number.
        std::ptrdiff_t yyi = 0;
        for (char const* yyp = yyformat; *yyp; ++yyp)
            if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
            {
                yyres += yytnamerr_ (yyarg[yyi++]);
                ++yyp;
            }
            else
                yyres += *yyp;
        return yyres;
    }


    const signed char parser::yypact_ninf_ = -101;

    const signed char parser::yytable_ninf_ = -1;

    const short
            parser::yypact_[] =
            {
                    101,  -101,  -101,  -101,    93,    18,     4,  -101,  -101,  -101,
                    -101,    10,    25,  -101,  -101,  -101,    12,    49,  -101,  -101,
                    107,  -101,     9,   -12,  -101,    35,    27,  -101,    25,    19,
                    40,    41,  -101,   150,   223,  -101,  -101,   171,  -101,  -101,
                    -101,    24,    93,    19,  -101,    39,  -101,  -101,  -101,  -101,
                    223,    61,  -101,  -101,  -101,  -101,  -101,  -101,  -101,   223,
                    86,    -9,    -9,    52,   137,  -101,  -101,    22,    57,  -101,
                    -101,   184,    67,    92,  -101,  -101,   -13,  -101,   223,   223,
                    223,   223,   223,  -101,  -101,  -101,    50,   111,   115,   105,
                    119,   204,  -101,  -101,  -101,  -101,    35,  -101,  -101,  -101,
                    -101,  -101,  -101,  -101,  -101,  -101,   125,   135,  -101,  -101,
                    -101,   103,   223,  -101,   150,  -101,  -101,  -101,  -101,    86,
                    86,   171,  -101,   223,   223,  -101,  -101,  -101,   130,  -101,
                    223,    67,   223,  -101,   124,  -101,  -101,   140,    -9,    91,
                    117,   132,   129,   141,  -101,   148,  -101,  -101,   116,   223,
                    223,   223,   223,   223,   223,   223,   223,   116,  -101,   170,
                    -9,    -9,    -9,    -9,    91,    91,   117,   132,  -101,   116,
                    -101
            };

    const signed char
            parser::yydefact_[] =
            {
                    0,    31,    32,    33,     0,     0,     0,     4,     5,     6,
                    7,     0,     0,     1,     2,     3,    13,     0,    21,    13,
                    0,    10,     0,    22,    19,     0,     0,     8,     0,     0,
                    0,     0,    35,     0,     0,    13,    20,     0,     9,    42,
                    29,    37,     0,     0,    75,    39,    69,    70,    76,    77,
                    0,     0,    78,    23,    24,    67,    71,    68,    81,     0,
                    85,    63,   100,     0,     0,    11,    14,     0,     0,    34,
                    30,     0,    65,     0,    25,    28,     0,    74,     0,     0,
                    0,     0,     0,    12,    16,    18,     0,     0,     0,     0,
                    0,     0,    48,    40,    43,    44,     0,    49,    41,    45,
                    46,    50,    51,    52,    53,    54,     0,    67,    39,    73,
                    80,     0,     0,    66,     0,    26,    82,    83,    84,    86,
                    87,     0,    15,     0,     0,    59,    60,    61,     0,    47,
                    0,    36,     0,    72,     0,    27,    17,     0,    88,    93,
                    96,    98,    64,     0,    62,     0,    79,    38,     0,     0,
                    0,     0,     0,     0,     0,     0,     0,     0,    55,    56,
                    91,    89,    92,    90,    94,    95,    97,    99,    58,     0,
                    57
            };

    const short
            parser::yypgoto_[] =
            {
                    -101,  -101,  -101,   173,   113,  -101,   154,   169,   -58,  -101,
                    123,  -101,   166,   -46,  -101,  -101,     0,  -101,   151,    84,
                    29,  -101,  -101,  -100,  -101,  -101,  -101,  -101,  -101,  -101,
                    -31,    70,   -66,  -101,  -101,   -14,  -101,  -101,    62,   -34,
                    3,    46,    47,  -101,   172
            };

    const short
            parser::yydefgoto_[] =
            {
                    -1,     5,     6,     7,     8,    20,    21,    23,    65,    86,
                    9,    17,    18,    53,    76,    10,    11,    31,    32,    72,
                    97,    67,    98,    99,   100,   101,   102,   103,   104,   105,
                    106,   137,    55,    56,    57,    58,    59,   111,    60,    61,
                    139,   140,   141,   142,    66
            };

    const unsigned char
            parser::yytable_[] =
            {
                    62,   107,    54,    62,    12,    75,    85,     1,     2,     3,
                    4,    33,     1,     2,     3,    81,    82,   114,    13,    73,
                    54,   115,    30,    34,    16,     1,     2,     3,     4,    87,
                    62,    88,    89,    90,    91,    44,    45,    46,    47,    19,
                    110,    29,    30,    22,    14,    77,    48,    49,   159,    35,
                    37,    92,    39,    50,    41,    39,    93,   168,    40,    68,
                    128,    52,    34,   136,   116,   117,   118,    96,   135,   170,
                    71,    42,    70,    43,    44,    45,    46,    47,    24,    25,
                    121,   134,   107,    54,   122,    48,    49,    62,    83,   138,
                    138,   107,    50,   108,    51,    74,     1,     2,     3,   145,
                    52,   146,   112,   107,     1,     2,     3,     4,   149,   150,
                    151,   152,    78,    79,    80,   160,   161,   162,   163,   138,
                    138,   138,   138,    87,   113,    88,    89,    90,    91,    44,
                    45,    46,    47,   132,   125,   133,    27,    28,   153,   154,
                    48,    49,   123,   119,   120,    92,   124,    50,   126,    39,
                    44,    45,    46,    47,   129,    52,   164,   165,   130,   144,
                    147,    48,    49,    44,    45,    46,    47,   156,    50,   155,
                    64,    84,   148,   157,    48,    49,    52,   158,   169,    15,
                    94,    50,    38,    51,    44,    45,    46,    47,    26,    52,
                    95,    36,   131,    69,   143,    48,    49,    44,    45,    46,
                    47,   166,    50,   167,    64,     0,    63,     0,    48,    49,
                    52,     0,     0,     0,     0,    50,   109,    44,    45,    46,
                    47,     0,     0,    52,     0,     0,     0,     0,    48,    49,
                    0,     0,     0,   127,     0,    50,    44,    45,    46,    47,
                    0,     0,     0,    52,     0,     0,     0,    48,    49,     0,
                    0,     0,     0,     0,    50,     0,     0,     0,     0,     0,
                    0,     0,    52
            };

    const short
            parser::yycheck_[] =
            {
                    34,    67,    33,    37,     4,    51,    64,     3,     4,     5,
                    6,    23,     3,     4,     5,    24,    25,    30,     0,    50,
                    51,    34,    22,    35,    14,     3,     4,     5,     6,     7,
                    64,     9,    10,    11,    12,    13,    14,    15,    16,    14,
                    71,    32,    42,    31,    40,    59,    24,    25,   148,    14,
                    23,    29,    33,    31,    14,    33,    34,   157,    29,    35,
                    91,    39,    35,   121,    78,    79,    80,    67,   114,   169,
                    31,    30,    43,    32,    13,    14,    15,    16,    29,    30,
                    30,   112,   148,   114,    34,    24,    25,   121,    36,   123,
                    124,   157,    31,    36,    33,    34,     3,     4,     5,   130,
                    39,   132,    35,   169,     3,     4,     5,     6,    17,    18,
                    19,    20,    26,    27,    28,   149,   150,   151,   152,   153,
                    154,   155,   156,     7,    32,     9,    10,    11,    12,    13,
                    14,    15,    16,    30,    29,    32,    29,    30,    21,    22,
                    24,    25,    31,    81,    82,    29,    31,    31,    29,    33,
                    13,    14,    15,    16,    29,    39,   153,   154,    23,    29,
                    36,    24,    25,    13,    14,    15,    16,    38,    31,    37,
                    33,    34,    32,    32,    24,    25,    39,    29,     8,     6,
                    67,    31,    28,    33,    13,    14,    15,    16,    19,    39,
                    67,    25,   108,    42,   124,    24,    25,    13,    14,    15,
                    16,   155,    31,   156,    33,    -1,    34,    -1,    24,    25,
                    39,    -1,    -1,    -1,    -1,    31,    32,    13,    14,    15,
                    16,    -1,    -1,    39,    -1,    -1,    -1,    -1,    24,    25,
                    -1,    -1,    -1,    29,    -1,    31,    13,    14,    15,    16,
                    -1,    -1,    -1,    39,    -1,    -1,    -1,    24,    25,    -1,
                    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
                    -1,    -1,    39
            };

    const signed char
            parser::yystos_[] =
            {
                    0,     3,     4,     5,     6,    42,    43,    44,    45,    51,
                    56,    57,    57,     0,    40,    44,    14,    52,    53,    14,
                    46,    47,    31,    48,    29,    30,    48,    29,    30,    32,
                    57,    58,    59,    23,    35,    14,    53,    23,    47,    33,
                    61,    14,    30,    32,    13,    14,    15,    16,    24,    25,
                    31,    33,    39,    54,    71,    73,    74,    75,    76,    77,
                    79,    80,    80,    85,    33,    49,    85,    62,    35,    59,
                    61,    31,    60,    71,    34,    54,    55,    76,    26,    27,
                    28,    24,    25,    36,    34,    49,    50,     7,     9,    10,
                    11,    12,    29,    34,    45,    51,    57,    61,    63,    64,
                    65,    66,    67,    68,    69,    70,    71,    73,    36,    32,
                    71,    78,    35,    32,    30,    34,    76,    76,    76,    79,
                    79,    30,    34,    31,    31,    29,    29,    29,    71,    29,
                    23,    60,    30,    32,    71,    54,    49,    72,    80,    81,
                    82,    83,    84,    72,    29,    71,    71,    36,    32,    17,
                    18,    19,    20,    21,    22,    37,    38,    32,    29,    64,
                    80,    80,    80,    80,    81,    81,    82,    83,    64,     8,
                    64
            };

    const signed char
            parser::yyr1_[] =
            {
                    0,    41,    42,    43,    43,    44,    44,    44,    45,    46,
                    46,    47,    48,    48,    49,    49,    49,    50,    50,    51,
                    52,    52,    53,    53,    54,    54,    54,    55,    55,    56,
                    56,    57,    57,    57,    58,    58,    59,    59,    60,    60,
                    61,    62,    62,    63,    63,    63,    64,    64,    64,    64,
                    64,    64,    64,    64,    64,    65,    66,    66,    67,    68,
                    69,    70,    70,    71,    72,    73,    74,    74,    74,    75,
                    75,    76,    76,    76,    76,    76,    77,    77,    77,    78,
                    78,    79,    79,    79,    79,    80,    80,    80,    81,    81,
                    81,    81,    81,    82,    82,    82,    83,    83,    84,    84,
                    85
            };

    const signed char
            parser::yyr2_[] =
            {
                    0,     2,     2,     2,     1,     1,     1,     1,     4,     3,
                    1,     4,     4,     0,     1,     3,     2,     3,     1,     3,
                    3,     1,     2,     4,     1,     2,     3,     3,     1,     5,
                    6,     1,     1,     1,     3,     1,     5,     2,     4,     0,
                    3,     2,     0,     1,     1,     1,     1,     2,     1,     1,
                    1,     1,     1,     1,     1,     4,     5,     7,     5,     2,
                    2,     2,     3,     1,     1,     2,     3,     1,     1,     1,
                    1,     1,     4,     3,     2,     1,     1,     1,     1,     3,
                    1,     1,     3,     3,     3,     1,     3,     3,     1,     3,
                    3,     3,     3,     1,     3,     3,     1,     3,     1,     3,
                    1
            };



    // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
    // First, the terminals, then, starting at \a yyntokens_, nonterminals.
    const char*
            const parser::yytname_[] =
            {
                    "$end", "error", "$undefined", "VOID", "INT", "FLOAT", "CONST", "IF",
                    "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN", "STRING", "IDENTIFIER",
                    "INTCONST", "FLOATCONST", "LE", "LT", "GE", "GT", "EQU", "NE", "ASSIGN",
                    "ADD", "SUB", "MUL", "DIV", "MOD", "SEMICOLON", "COMMA", "LB", "RB",
                    "BLB", "BRB", "MLB", "MRB", "AND", "OR", "NOT", "END", "$accept",
                    "Begin", "CompUnit", "DeclDef", "ConstDecl", "ConstDefList", "ConstDef",
                    "ConstExpList", "ConstInitVal", "ConstInitValList", "VarDecl",
                    "VarDefList", "VarDef", "InitVal", "InitValList", "FuncDef", "DefType",
                    "FuncFParams", "FuncFParam", "ParamArrayExpList", "Block",
                    "BlockItemList", "BlockItem", "Stmt", "AssignStmt", "SelectStmt",
                    "IterationStmt", "BreakStmt", "ContinueStmt", "ReturnStmt", "Exp",
                    "Cond", "LVal", "PrimaryExp", "Number", "UnaryExp", "UnaryOp",
                    "FuncRParams", "MulExp", "AddExp", "RelExp", "EqExp", "LAndExp",
                    "LOrExp", "ConstExp", YY_NULLPTR
            };

#if YYDEBUG
    const short
            parser::yyrline_[] =
            {
                    0,   101,   101,   106,   110,   115,   119,   123,   128,   134,
                    138,   144,   151,   155,   160,   164,   168,   172,   176,   182,
                    189,   193,   199,   204,   211,   215,   218,   223,   227,   233,
                    239,   247,   251,   255,   260,   264,   270,   277,   285,   289,
                    294,   300,   304,   309,   313,   317,   323,   327,   331,   334,
                    338,   342,   346,   350,   354,   359,   365,   370,   377,   383,
                    387,   391,   394,   399,   405,   410,   417,   421,   425,   430,
                    435,   442,   446,   451,   455,   460,   465,   469,   473,   478,
                    482,   488,   492,   498,   504,   512,   516,   522,   530,   534,
                    540,   546,   552,   559,   563,   569,   576,   580,   586,   590,
                    596
            };

    // Print the state stack on the debug stream.
    void
    parser::yystack_print_ ()
    {
        *yycdebug_ << "Stack now";
        for (stack_type::const_iterator
                     i = yystack_.begin (),
                     i_end = yystack_.end ();
             i != i_end; ++i)
            *yycdebug_ << ' ' << int (i->state);
        *yycdebug_ << '\n';
    }

    // Report on the debug stream that the rule \a yyrule is going to be reduced.
    void
    parser::yy_reduce_print_ (int yyrule)
    {
        int yylno = yyrline_[yyrule];
        int yynrhs = yyr2_[yyrule];
        // Print the symbols being reduced, and their result.
        *yycdebug_ << "Reducing stack by rule " << yyrule - 1
                   << " (line " << yylno << "):\n";
        // The symbols being reduced.
        for (int yyi = 0; yyi < yynrhs; yyi++)
            YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                             yystack_[(yynrhs) - (yyi + 1)]);
    }
#endif // YYDEBUG


} // yy
#line 2970 "parser.cc"

#line 601 "parser.yy"

/*Parser实现错误处理接口*/
void yy::parser::error (const location_type& l,
                        const std::string& m)
{
    ddriver.error(l, m);
}
