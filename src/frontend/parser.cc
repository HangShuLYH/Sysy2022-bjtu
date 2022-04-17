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
      case 73: // AddExp
        value.YY_MOVE_OR_COPY< AddExp* > (YY_MOVE (that.value));
        break;

      case 60: // Block
        value.YY_MOVE_OR_COPY< Block* > (YY_MOVE (that.value));
        break;

      case 62: // BlockItem
        value.YY_MOVE_OR_COPY< BlockItem* > (YY_MOVE (that.value));
        break;

      case 61: // BlockItemList
        value.YY_MOVE_OR_COPY< BlockItemList* > (YY_MOVE (that.value));
        break;

      case 41: // Begin
      case 42: // CompUnit
        value.YY_MOVE_OR_COPY< CompUnit* > (YY_MOVE (that.value));
        break;

      case 65: // Cond
        value.YY_MOVE_OR_COPY< Cond* > (YY_MOVE (that.value));
        break;

      case 44: // ConstDecl
        value.YY_MOVE_OR_COPY< ConstDecl* > (YY_MOVE (that.value));
        break;

      case 46: // ConstDef
        value.YY_MOVE_OR_COPY< ConstDef* > (YY_MOVE (that.value));
        break;

      case 45: // ConstDefList
        value.YY_MOVE_OR_COPY< ConstDefList* > (YY_MOVE (that.value));
        break;

      case 78: // ConstExp
        value.YY_MOVE_OR_COPY< ConstExp* > (YY_MOVE (that.value));
        break;

      case 47: // ConstExpList
        value.YY_MOVE_OR_COPY< ConstExpList* > (YY_MOVE (that.value));
        break;

      case 48: // ConstInitVal
        value.YY_MOVE_OR_COPY< ConstInitVal* > (YY_MOVE (that.value));
        break;

      case 49: // ConstInitValList
        value.YY_MOVE_OR_COPY< ConstInitValList* > (YY_MOVE (that.value));
        break;

      case 43: // DeclDef
        value.YY_MOVE_OR_COPY< DeclDef* > (YY_MOVE (that.value));
        break;

      case 56: // DefType
        value.YY_MOVE_OR_COPY< DefType* > (YY_MOVE (that.value));
        break;

      case 75: // EqExp
        value.YY_MOVE_OR_COPY< EqExp* > (YY_MOVE (that.value));
        break;

      case 64: // Exp
        value.YY_MOVE_OR_COPY< Exp* > (YY_MOVE (that.value));
        break;

      case 55: // FuncDef
        value.YY_MOVE_OR_COPY< FuncDef* > (YY_MOVE (that.value));
        break;

      case 58: // FuncFParam
        value.YY_MOVE_OR_COPY< FuncFParam* > (YY_MOVE (that.value));
        break;

      case 57: // FuncFParams
        value.YY_MOVE_OR_COPY< FuncFParams* > (YY_MOVE (that.value));
        break;

      case 71: // FuncRParams
        value.YY_MOVE_OR_COPY< FuncRParams* > (YY_MOVE (that.value));
        break;

      case 53: // InitVal
        value.YY_MOVE_OR_COPY< InitVal* > (YY_MOVE (that.value));
        break;

      case 54: // InitValList
        value.YY_MOVE_OR_COPY< InitValList* > (YY_MOVE (that.value));
        break;

      case 76: // LAndExp
        value.YY_MOVE_OR_COPY< LAndExp* > (YY_MOVE (that.value));
        break;

      case 77: // LOrExp
        value.YY_MOVE_OR_COPY< LOrExp* > (YY_MOVE (that.value));
        break;

      case 66: // LVal
        value.YY_MOVE_OR_COPY< LVal* > (YY_MOVE (that.value));
        break;

      case 72: // MulExp
        value.YY_MOVE_OR_COPY< MulExp* > (YY_MOVE (that.value));
        break;

      case 68: // Number
        value.YY_MOVE_OR_COPY< Number* > (YY_MOVE (that.value));
        break;

      case 59: // ParamArrayExpList
        value.YY_MOVE_OR_COPY< ParamArrayExpList* > (YY_MOVE (that.value));
        break;

      case 67: // PrimaryExp
        value.YY_MOVE_OR_COPY< PrimaryExp* > (YY_MOVE (that.value));
        break;

      case 74: // RelExp
        value.YY_MOVE_OR_COPY< RelExp* > (YY_MOVE (that.value));
        break;

      case 63: // Stmt
        value.YY_MOVE_OR_COPY< Stmt* > (YY_MOVE (that.value));
        break;

      case 69: // UnaryExp
        value.YY_MOVE_OR_COPY< UnaryExp* > (YY_MOVE (that.value));
        break;

      case 70: // UnaryOp
        value.YY_MOVE_OR_COPY< UnaryOp* > (YY_MOVE (that.value));
        break;

      case 50: // VarDecl
        value.YY_MOVE_OR_COPY< VarDecl* > (YY_MOVE (that.value));
        break;

      case 52: // VarDef
        value.YY_MOVE_OR_COPY< VarDef* > (YY_MOVE (that.value));
        break;

      case 51: // VarDefList
        value.YY_MOVE_OR_COPY< VarDefList* > (YY_MOVE (that.value));
        break;

      case 15: // FLOATCONST
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
        break;

      case 14: // INTCONST
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 13: // IDENTIFIER
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
      case 73: // AddExp
        value.move< AddExp* > (YY_MOVE (that.value));
        break;

      case 60: // Block
        value.move< Block* > (YY_MOVE (that.value));
        break;

      case 62: // BlockItem
        value.move< BlockItem* > (YY_MOVE (that.value));
        break;

      case 61: // BlockItemList
        value.move< BlockItemList* > (YY_MOVE (that.value));
        break;

      case 41: // Begin
      case 42: // CompUnit
        value.move< CompUnit* > (YY_MOVE (that.value));
        break;

      case 65: // Cond
        value.move< Cond* > (YY_MOVE (that.value));
        break;

      case 44: // ConstDecl
        value.move< ConstDecl* > (YY_MOVE (that.value));
        break;

      case 46: // ConstDef
        value.move< ConstDef* > (YY_MOVE (that.value));
        break;

      case 45: // ConstDefList
        value.move< ConstDefList* > (YY_MOVE (that.value));
        break;

      case 78: // ConstExp
        value.move< ConstExp* > (YY_MOVE (that.value));
        break;

      case 47: // ConstExpList
        value.move< ConstExpList* > (YY_MOVE (that.value));
        break;

      case 48: // ConstInitVal
        value.move< ConstInitVal* > (YY_MOVE (that.value));
        break;

      case 49: // ConstInitValList
        value.move< ConstInitValList* > (YY_MOVE (that.value));
        break;

      case 43: // DeclDef
        value.move< DeclDef* > (YY_MOVE (that.value));
        break;

      case 56: // DefType
        value.move< DefType* > (YY_MOVE (that.value));
        break;

      case 75: // EqExp
        value.move< EqExp* > (YY_MOVE (that.value));
        break;

      case 64: // Exp
        value.move< Exp* > (YY_MOVE (that.value));
        break;

      case 55: // FuncDef
        value.move< FuncDef* > (YY_MOVE (that.value));
        break;

      case 58: // FuncFParam
        value.move< FuncFParam* > (YY_MOVE (that.value));
        break;

      case 57: // FuncFParams
        value.move< FuncFParams* > (YY_MOVE (that.value));
        break;

      case 71: // FuncRParams
        value.move< FuncRParams* > (YY_MOVE (that.value));
        break;

      case 53: // InitVal
        value.move< InitVal* > (YY_MOVE (that.value));
        break;

      case 54: // InitValList
        value.move< InitValList* > (YY_MOVE (that.value));
        break;

      case 76: // LAndExp
        value.move< LAndExp* > (YY_MOVE (that.value));
        break;

      case 77: // LOrExp
        value.move< LOrExp* > (YY_MOVE (that.value));
        break;

      case 66: // LVal
        value.move< LVal* > (YY_MOVE (that.value));
        break;

      case 72: // MulExp
        value.move< MulExp* > (YY_MOVE (that.value));
        break;

      case 68: // Number
        value.move< Number* > (YY_MOVE (that.value));
        break;

      case 59: // ParamArrayExpList
        value.move< ParamArrayExpList* > (YY_MOVE (that.value));
        break;

      case 67: // PrimaryExp
        value.move< PrimaryExp* > (YY_MOVE (that.value));
        break;

      case 74: // RelExp
        value.move< RelExp* > (YY_MOVE (that.value));
        break;

      case 63: // Stmt
        value.move< Stmt* > (YY_MOVE (that.value));
        break;

      case 69: // UnaryExp
        value.move< UnaryExp* > (YY_MOVE (that.value));
        break;

      case 70: // UnaryOp
        value.move< UnaryOp* > (YY_MOVE (that.value));
        break;

      case 50: // VarDecl
        value.move< VarDecl* > (YY_MOVE (that.value));
        break;

      case 52: // VarDef
        value.move< VarDef* > (YY_MOVE (that.value));
        break;

      case 51: // VarDefList
        value.move< VarDefList* > (YY_MOVE (that.value));
        break;

      case 15: // FLOATCONST
        value.move< float > (YY_MOVE (that.value));
        break;

      case 14: // INTCONST
        value.move< int > (YY_MOVE (that.value));
        break;

      case 13: // IDENTIFIER
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
      case 73: // AddExp
        value.copy< AddExp* > (that.value);
        break;

      case 60: // Block
        value.copy< Block* > (that.value);
        break;

      case 62: // BlockItem
        value.copy< BlockItem* > (that.value);
        break;

      case 61: // BlockItemList
        value.copy< BlockItemList* > (that.value);
        break;

      case 41: // Begin
      case 42: // CompUnit
        value.copy< CompUnit* > (that.value);
        break;

      case 65: // Cond
        value.copy< Cond* > (that.value);
        break;

      case 44: // ConstDecl
        value.copy< ConstDecl* > (that.value);
        break;

      case 46: // ConstDef
        value.copy< ConstDef* > (that.value);
        break;

      case 45: // ConstDefList
        value.copy< ConstDefList* > (that.value);
        break;

      case 78: // ConstExp
        value.copy< ConstExp* > (that.value);
        break;

      case 47: // ConstExpList
        value.copy< ConstExpList* > (that.value);
        break;

      case 48: // ConstInitVal
        value.copy< ConstInitVal* > (that.value);
        break;

      case 49: // ConstInitValList
        value.copy< ConstInitValList* > (that.value);
        break;

      case 43: // DeclDef
        value.copy< DeclDef* > (that.value);
        break;

      case 56: // DefType
        value.copy< DefType* > (that.value);
        break;

      case 75: // EqExp
        value.copy< EqExp* > (that.value);
        break;

      case 64: // Exp
        value.copy< Exp* > (that.value);
        break;

      case 55: // FuncDef
        value.copy< FuncDef* > (that.value);
        break;

      case 58: // FuncFParam
        value.copy< FuncFParam* > (that.value);
        break;

      case 57: // FuncFParams
        value.copy< FuncFParams* > (that.value);
        break;

      case 71: // FuncRParams
        value.copy< FuncRParams* > (that.value);
        break;

      case 53: // InitVal
        value.copy< InitVal* > (that.value);
        break;

      case 54: // InitValList
        value.copy< InitValList* > (that.value);
        break;

      case 76: // LAndExp
        value.copy< LAndExp* > (that.value);
        break;

      case 77: // LOrExp
        value.copy< LOrExp* > (that.value);
        break;

      case 66: // LVal
        value.copy< LVal* > (that.value);
        break;

      case 72: // MulExp
        value.copy< MulExp* > (that.value);
        break;

      case 68: // Number
        value.copy< Number* > (that.value);
        break;

      case 59: // ParamArrayExpList
        value.copy< ParamArrayExpList* > (that.value);
        break;

      case 67: // PrimaryExp
        value.copy< PrimaryExp* > (that.value);
        break;

      case 74: // RelExp
        value.copy< RelExp* > (that.value);
        break;

      case 63: // Stmt
        value.copy< Stmt* > (that.value);
        break;

      case 69: // UnaryExp
        value.copy< UnaryExp* > (that.value);
        break;

      case 70: // UnaryOp
        value.copy< UnaryOp* > (that.value);
        break;

      case 50: // VarDecl
        value.copy< VarDecl* > (that.value);
        break;

      case 52: // VarDef
        value.copy< VarDef* > (that.value);
        break;

      case 51: // VarDefList
        value.copy< VarDefList* > (that.value);
        break;

      case 15: // FLOATCONST
        value.copy< float > (that.value);
        break;

      case 14: // INTCONST
        value.copy< int > (that.value);
        break;

      case 13: // IDENTIFIER
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
      case 73: // AddExp
        value.move< AddExp* > (that.value);
        break;

      case 60: // Block
        value.move< Block* > (that.value);
        break;

      case 62: // BlockItem
        value.move< BlockItem* > (that.value);
        break;

      case 61: // BlockItemList
        value.move< BlockItemList* > (that.value);
        break;

      case 41: // Begin
      case 42: // CompUnit
        value.move< CompUnit* > (that.value);
        break;

      case 65: // Cond
        value.move< Cond* > (that.value);
        break;

      case 44: // ConstDecl
        value.move< ConstDecl* > (that.value);
        break;

      case 46: // ConstDef
        value.move< ConstDef* > (that.value);
        break;

      case 45: // ConstDefList
        value.move< ConstDefList* > (that.value);
        break;

      case 78: // ConstExp
        value.move< ConstExp* > (that.value);
        break;

      case 47: // ConstExpList
        value.move< ConstExpList* > (that.value);
        break;

      case 48: // ConstInitVal
        value.move< ConstInitVal* > (that.value);
        break;

      case 49: // ConstInitValList
        value.move< ConstInitValList* > (that.value);
        break;

      case 43: // DeclDef
        value.move< DeclDef* > (that.value);
        break;

      case 56: // DefType
        value.move< DefType* > (that.value);
        break;

      case 75: // EqExp
        value.move< EqExp* > (that.value);
        break;

      case 64: // Exp
        value.move< Exp* > (that.value);
        break;

      case 55: // FuncDef
        value.move< FuncDef* > (that.value);
        break;

      case 58: // FuncFParam
        value.move< FuncFParam* > (that.value);
        break;

      case 57: // FuncFParams
        value.move< FuncFParams* > (that.value);
        break;

      case 71: // FuncRParams
        value.move< FuncRParams* > (that.value);
        break;

      case 53: // InitVal
        value.move< InitVal* > (that.value);
        break;

      case 54: // InitValList
        value.move< InitValList* > (that.value);
        break;

      case 76: // LAndExp
        value.move< LAndExp* > (that.value);
        break;

      case 77: // LOrExp
        value.move< LOrExp* > (that.value);
        break;

      case 66: // LVal
        value.move< LVal* > (that.value);
        break;

      case 72: // MulExp
        value.move< MulExp* > (that.value);
        break;

      case 68: // Number
        value.move< Number* > (that.value);
        break;

      case 59: // ParamArrayExpList
        value.move< ParamArrayExpList* > (that.value);
        break;

      case 67: // PrimaryExp
        value.move< PrimaryExp* > (that.value);
        break;

      case 74: // RelExp
        value.move< RelExp* > (that.value);
        break;

      case 63: // Stmt
        value.move< Stmt* > (that.value);
        break;

      case 69: // UnaryExp
        value.move< UnaryExp* > (that.value);
        break;

      case 70: // UnaryOp
        value.move< UnaryOp* > (that.value);
        break;

      case 50: // VarDecl
        value.move< VarDecl* > (that.value);
        break;

      case 52: // VarDef
        value.move< VarDef* > (that.value);
        break;

      case 51: // VarDefList
        value.move< VarDefList* > (that.value);
        break;

      case 15: // FLOATCONST
        value.move< float > (that.value);
        break;

      case 14: // INTCONST
        value.move< int > (that.value);
        break;

      case 13: // IDENTIFIER
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

#line 1095 "parser.cc"


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
      case 73: // AddExp
        yylhs.value.emplace< AddExp* > ();
        break;

      case 60: // Block
        yylhs.value.emplace< Block* > ();
        break;

      case 62: // BlockItem
        yylhs.value.emplace< BlockItem* > ();
        break;

      case 61: // BlockItemList
        yylhs.value.emplace< BlockItemList* > ();
        break;

      case 41: // Begin
      case 42: // CompUnit
        yylhs.value.emplace< CompUnit* > ();
        break;

      case 65: // Cond
        yylhs.value.emplace< Cond* > ();
        break;

      case 44: // ConstDecl
        yylhs.value.emplace< ConstDecl* > ();
        break;

      case 46: // ConstDef
        yylhs.value.emplace< ConstDef* > ();
        break;

      case 45: // ConstDefList
        yylhs.value.emplace< ConstDefList* > ();
        break;

      case 78: // ConstExp
        yylhs.value.emplace< ConstExp* > ();
        break;

      case 47: // ConstExpList
        yylhs.value.emplace< ConstExpList* > ();
        break;

      case 48: // ConstInitVal
        yylhs.value.emplace< ConstInitVal* > ();
        break;

      case 49: // ConstInitValList
        yylhs.value.emplace< ConstInitValList* > ();
        break;

      case 43: // DeclDef
        yylhs.value.emplace< DeclDef* > ();
        break;

      case 56: // DefType
        yylhs.value.emplace< DefType* > ();
        break;

      case 75: // EqExp
        yylhs.value.emplace< EqExp* > ();
        break;

      case 64: // Exp
        yylhs.value.emplace< Exp* > ();
        break;

      case 55: // FuncDef
        yylhs.value.emplace< FuncDef* > ();
        break;

      case 58: // FuncFParam
        yylhs.value.emplace< FuncFParam* > ();
        break;

      case 57: // FuncFParams
        yylhs.value.emplace< FuncFParams* > ();
        break;

      case 71: // FuncRParams
        yylhs.value.emplace< FuncRParams* > ();
        break;

      case 53: // InitVal
        yylhs.value.emplace< InitVal* > ();
        break;

      case 54: // InitValList
        yylhs.value.emplace< InitValList* > ();
        break;

      case 76: // LAndExp
        yylhs.value.emplace< LAndExp* > ();
        break;

      case 77: // LOrExp
        yylhs.value.emplace< LOrExp* > ();
        break;

      case 66: // LVal
        yylhs.value.emplace< LVal* > ();
        break;

      case 72: // MulExp
        yylhs.value.emplace< MulExp* > ();
        break;

      case 68: // Number
        yylhs.value.emplace< Number* > ();
        break;

      case 59: // ParamArrayExpList
        yylhs.value.emplace< ParamArrayExpList* > ();
        break;

      case 67: // PrimaryExp
        yylhs.value.emplace< PrimaryExp* > ();
        break;

      case 74: // RelExp
        yylhs.value.emplace< RelExp* > ();
        break;

      case 63: // Stmt
        yylhs.value.emplace< Stmt* > ();
        break;

      case 69: // UnaryExp
        yylhs.value.emplace< UnaryExp* > ();
        break;

      case 70: // UnaryOp
        yylhs.value.emplace< UnaryOp* > ();
        break;

      case 50: // VarDecl
        yylhs.value.emplace< VarDecl* > ();
        break;

      case 52: // VarDef
        yylhs.value.emplace< VarDef* > ();
        break;

      case 51: // VarDefList
        yylhs.value.emplace< VarDefList* > ();
        break;

      case 15: // FLOATCONST
        yylhs.value.emplace< float > ();
        break;

      case 14: // INTCONST
        yylhs.value.emplace< int > ();
        break;

      case 13: // IDENTIFIER
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
#line 94 "parser.yy"
                    {
        ddriver.root = yystack_[1].value.as < CompUnit* > ();
        return 0;
    }
#line 1386 "parser.cc"
    break;

  case 3:
#line 99 "parser.yy"
                           {
        yystack_[1].value.as < CompUnit* > ()->declDefList.push_back(std::shared_ptr<DeclDef>(yystack_[0].value.as < DeclDef* > ()));
        yylhs.value.as < CompUnit* > ()=yystack_[1].value.as < CompUnit* > ();
    }
#line 1395 "parser.cc"
    break;

  case 4:
#line 103 "parser.yy"
             {
        yylhs.value.as < CompUnit* > ()=new CompUnit();
        yylhs.value.as < CompUnit* > ()->declDefList.push_back(std::shared_ptr<DeclDef>(yystack_[0].value.as < DeclDef* > ()));
    }
#line 1404 "parser.cc"
    break;

  case 5:
#line 108 "parser.yy"
                  {
        yylhs.value.as < DeclDef* > ()=new DeclDef();
        yylhs.value.as < DeclDef* > ()->constDecl=std::shared_ptr<ConstDecl>(yystack_[0].value.as < ConstDecl* > ());
    }
#line 1413 "parser.cc"
    break;

  case 6:
#line 112 "parser.yy"
             {
        yylhs.value.as < DeclDef* > ()=new DeclDef();
        yylhs.value.as < DeclDef* > ()->varDecl=std::shared_ptr<VarDecl>(yystack_[0].value.as < VarDecl* > ());
    }
#line 1422 "parser.cc"
    break;

  case 7:
#line 116 "parser.yy"
             {
        yylhs.value.as < DeclDef* > ()=new DeclDef();
        yylhs.value.as < DeclDef* > ()->funcDef=std::shared_ptr<FuncDef>(yystack_[0].value.as < FuncDef* > ());
    }
#line 1431 "parser.cc"
    break;

  case 8:
#line 121 "parser.yy"
                                               {
        yylhs.value.as < ConstDecl* > ()=new ConstDecl();
        yylhs.value.as < ConstDecl* > ()->constDefList.swap(yystack_[1].value.as < ConstDefList* > ()->constDefList);
        yylhs.value.as < ConstDecl* > ()->defType=std::shared_ptr<DefType>(yystack_[2].value.as < DefType* > ());
    }
#line 1441 "parser.cc"
    break;

  case 9:
#line 127 "parser.yy"
                                         {
    yystack_[2].value.as < ConstDefList* > ()->constDefList.push_back(std::shared_ptr<ConstDef>(yystack_[0].value.as < ConstDef* > ()));
    yylhs.value.as < ConstDefList* > ()=yystack_[2].value.as < ConstDefList* > ();
}
#line 1450 "parser.cc"
    break;

  case 10:
#line 131 "parser.yy"
                  {
    yylhs.value.as < ConstDefList* > ()=new ConstDefList();
    yylhs.value.as < ConstDefList* > ()->constDefList.push_back(std::shared_ptr<ConstDef>(yystack_[0].value.as < ConstDef* > ()));
  }
#line 1459 "parser.cc"
    break;

  case 11:
#line 137 "parser.yy"
                                                     {
        yylhs.value.as < ConstDef* > ()=new ConstDef();
        yylhs.value.as < ConstDef* > ()->identifier=yystack_[3].value.as < std::string > ();
        yylhs.value.as < ConstDef* > ()->constExpList.swap(yystack_[2].value.as < ConstExpList* > ()->constExpList);
        yylhs.value.as < ConstDef* > ()->constInitVal=std::shared_ptr<ConstInitVal>(yystack_[0].value.as < ConstInitVal* > ());
    }
#line 1470 "parser.cc"
    break;

  case 12:
#line 144 "parser.yy"
                                           {
        yystack_[3].value.as < ConstExpList* > ()->constExpList.push_back(std::shared_ptr<ConstExp>(yystack_[1].value.as < ConstExp* > ()));
        yylhs.value.as < ConstExpList* > ()=yystack_[3].value.as < ConstExpList* > ();
    }
#line 1479 "parser.cc"
    break;

  case 13:
#line 148 "parser.yy"
            {
        yylhs.value.as < ConstExpList* > ()=new ConstExpList();
    }
#line 1487 "parser.cc"
    break;

  case 14:
#line 153 "parser.yy"
                     {
    yylhs.value.as < ConstInitVal* > ()=new ConstInitVal();
    yylhs.value.as < ConstInitVal* > ()->constExp=std::shared_ptr<ConstExp>(yystack_[0].value.as < ConstExp* > ());
}
#line 1496 "parser.cc"
    break;

  case 15:
#line 157 "parser.yy"
                                  {
    yylhs.value.as < ConstInitVal* > ()=new ConstInitVal();
    yylhs.value.as < ConstInitVal* > ()->constInitValList.swap(yystack_[1].value.as < ConstInitValList* > ()->constInitValList);
  }
#line 1505 "parser.cc"
    break;

  case 16:
#line 161 "parser.yy"
                 {
    yylhs.value.as < ConstInitVal* > ()=new ConstInitVal();
  }
#line 1513 "parser.cc"
    break;

  case 17:
#line 165 "parser.yy"
                                                    {
    yystack_[2].value.as < ConstInitValList* > ()->constInitValList.push_back(std::shared_ptr<ConstInitVal>(yystack_[0].value.as < ConstInitVal* > ()));
    yylhs.value.as < ConstInitValList* > ()=yystack_[2].value.as < ConstInitValList* > ();
}
#line 1522 "parser.cc"
    break;

  case 18:
#line 169 "parser.yy"
                      {
    yylhs.value.as < ConstInitValList* > ()=new ConstInitValList();
    yylhs.value.as < ConstInitValList* > ()->constInitValList.push_back(std::shared_ptr<ConstInitVal>(yystack_[0].value.as < ConstInitVal* > ()));
  }
#line 1531 "parser.cc"
    break;

  case 19:
#line 175 "parser.yy"
                                    {
    yylhs.value.as < VarDecl* > ()=new VarDecl();
    yylhs.value.as < VarDecl* > ()->varDefList.swap(yystack_[1].value.as < VarDefList* > ()->varDefList);
    yylhs.value.as < VarDecl* > ()->defType=std::shared_ptr<DefType>(yystack_[2].value.as < DefType* > ());
}
#line 1541 "parser.cc"
    break;

  case 20:
#line 182 "parser.yy"
                                  {
    yystack_[2].value.as < VarDefList* > ()->varDefList.push_back(std::shared_ptr<VarDef>(yystack_[0].value.as < VarDef* > ()));
    yylhs.value.as < VarDefList* > ()=yystack_[2].value.as < VarDefList* > ();
}
#line 1550 "parser.cc"
    break;

  case 21:
#line 186 "parser.yy"
                {
    yylhs.value.as < VarDefList* > ()=new VarDefList();
    yylhs.value.as < VarDefList* > ()->varDefList.push_back(std::shared_ptr<VarDef>(yystack_[0].value.as < VarDef* > ()));
  }
#line 1559 "parser.cc"
    break;

  case 22:
#line 192 "parser.yy"
                              {
    yylhs.value.as < VarDef* > ()=new VarDef();
    yylhs.value.as < VarDef* > ()->identifier=yystack_[1].value.as < std::string > ();
    yylhs.value.as < VarDef* > ()->constExpList.swap(yystack_[0].value.as < ConstExpList* > ()->constExpList);
}
#line 1569 "parser.cc"
    break;

  case 23:
#line 197 "parser.yy"
                                                {
    yylhs.value.as < VarDef* > ()=new VarDef();
    yylhs.value.as < VarDef* > ()->identifier=yystack_[3].value.as < std::string > ();
    yylhs.value.as < VarDef* > ()->constExpList.swap(yystack_[2].value.as < ConstExpList* > ()->constExpList);
    yylhs.value.as < VarDef* > ()->initVal=std::shared_ptr<InitVal>(yystack_[0].value.as < InitVal* > ());
  }
#line 1580 "parser.cc"
    break;

  case 24:
#line 204 "parser.yy"
           {
    yylhs.value.as < InitVal* > ()=new InitVal();
    yylhs.value.as < InitVal* > ()->exp=std::shared_ptr<Exp>(yystack_[0].value.as < Exp* > ());
}
#line 1589 "parser.cc"
    break;

  case 25:
#line 208 "parser.yy"
                 {
    yylhs.value.as < InitVal* > ()=new InitVal();
  }
#line 1597 "parser.cc"
    break;

  case 26:
#line 211 "parser.yy"
                             {
    yylhs.value.as < InitVal* > ()=new InitVal();
    yylhs.value.as < InitVal* > ()->initValList.swap(yystack_[1].value.as < InitValList* > ()->initValList);
  }
#line 1606 "parser.cc"
    break;

  case 27:
#line 216 "parser.yy"
                                     {
    yystack_[2].value.as < InitValList* > ()->initValList.push_back(std::shared_ptr<InitVal>(yystack_[0].value.as < InitVal* > ()));
    yylhs.value.as < InitValList* > ()=yystack_[2].value.as < InitValList* > ();
  }
#line 1615 "parser.cc"
    break;

  case 28:
#line 220 "parser.yy"
           {
    yylhs.value.as < InitValList* > ()=new InitValList();
    yylhs.value.as < InitValList* > ()->initValList.push_back(std::shared_ptr<InitVal>(yystack_[0].value.as < InitVal* > ()));
  }
#line 1624 "parser.cc"
    break;

  case 29:
#line 226 "parser.yy"
                                      {
    yylhs.value.as < FuncDef* > ()=new FuncDef();
    yylhs.value.as < FuncDef* > ()->defType=std::shared_ptr<DefType>(yystack_[4].value.as < DefType* > ());
    yylhs.value.as < FuncDef* > ()->identifier=yystack_[3].value.as < std::string > ();
    yylhs.value.as < FuncDef* > ()->block=std::shared_ptr<Block>(yystack_[0].value.as < Block* > ());
}
#line 1635 "parser.cc"
    break;

  case 30:
#line 232 "parser.yy"
                                                    {
    yylhs.value.as < FuncDef* > ()=new FuncDef();
    yylhs.value.as < FuncDef* > ()->defType=std::shared_ptr<DefType>(yystack_[5].value.as < DefType* > ());
    yylhs.value.as < FuncDef* > ()->identifier=yystack_[4].value.as < std::string > ();
    yylhs.value.as < FuncDef* > ()->funcFParams=std::shared_ptr<FuncFParams>(yystack_[2].value.as < FuncFParams* > ());
    yylhs.value.as < FuncDef* > ()->block=std::shared_ptr<Block>(yystack_[0].value.as < Block* > ());
  }
#line 1647 "parser.cc"
    break;

  case 31:
#line 240 "parser.yy"
             {
        yylhs.value.as < DefType* > ()=new DefType();
        yylhs.value.as < DefType* > ()->type=type_specifier::TYPE_VOID;
    }
#line 1656 "parser.cc"
    break;

  case 32:
#line 244 "parser.yy"
         {
        yylhs.value.as < DefType* > ()=new DefType();
        yylhs.value.as < DefType* > ()->type=type_specifier::TYPE_INT;
    }
#line 1665 "parser.cc"
    break;

  case 33:
#line 248 "parser.yy"
           {
        yylhs.value.as < DefType* > ()=new DefType();
        yylhs.value.as < DefType* > ()->type=type_specifier::TYPE_FLOAT;
    }
#line 1674 "parser.cc"
    break;

  case 34:
#line 253 "parser.yy"
                                        {
    yystack_[2].value.as < FuncFParams* > ()->funcFParamList.push_back(std::shared_ptr<FuncFParam>(yystack_[0].value.as < FuncFParam* > ()));
    yylhs.value.as < FuncFParams* > ()=yystack_[2].value.as < FuncFParams* > ();
}
#line 1683 "parser.cc"
    break;

  case 35:
#line 257 "parser.yy"
                    {
    yylhs.value.as < FuncFParams* > ()=new FuncFParams();
    yylhs.value.as < FuncFParams* > ()->funcFParamList.push_back(std::shared_ptr<FuncFParam>(yystack_[0].value.as < FuncFParam* > ()));
  }
#line 1692 "parser.cc"
    break;

  case 36:
#line 263 "parser.yy"
                                                       {
    yylhs.value.as < FuncFParam* > ()=new FuncFParam();
    yylhs.value.as < FuncFParam* > ()->defType=std::shared_ptr<DefType>(yystack_[4].value.as < DefType* > ());
    yylhs.value.as < FuncFParam* > ()->identifier=yystack_[3].value.as < std::string > ();
    yylhs.value.as < FuncFParam* > ()->expList.swap(yystack_[0].value.as < ParamArrayExpList* > ()->expList);
}
#line 1703 "parser.cc"
    break;

  case 37:
#line 269 "parser.yy"
                            {
    yylhs.value.as < FuncFParam* > ()=new FuncFParam();
    yylhs.value.as < FuncFParam* > ()->defType=std::shared_ptr<DefType>(yystack_[1].value.as < DefType* > ());
    yylhs.value.as < FuncFParam* > ()->identifier=yystack_[0].value.as < std::string > ();
  }
#line 1713 "parser.cc"
    break;

  case 38:
#line 276 "parser.yy"
                                                {
        yystack_[3].value.as < ParamArrayExpList* > ()->expList.push_back(std::shared_ptr<Exp>(yystack_[1].value.as < Exp* > ()));
        yylhs.value.as < ParamArrayExpList* > ()=yystack_[3].value.as < ParamArrayExpList* > ();
    }
#line 1722 "parser.cc"
    break;

  case 39:
#line 280 "parser.yy"
            {
        yylhs.value.as < ParamArrayExpList* > ()=new ParamArrayExpList();
    }
#line 1730 "parser.cc"
    break;

  case 40:
#line 285 "parser.yy"
                           {
    yylhs.value.as < Block* > ()=new Block();
    yylhs.value.as < Block* > ()->blockItemList.swap(yystack_[1].value.as < BlockItemList* > ()->blockItemList);
}
#line 1739 "parser.cc"
    break;

  case 41:
#line 291 "parser.yy"
                                     {
    yystack_[1].value.as < BlockItemList* > ()->blockItemList.push_back(std::shared_ptr<BlockItem>(yystack_[0].value.as < BlockItem* > ()));
    yylhs.value.as < BlockItemList* > ()=yystack_[1].value.as < BlockItemList* > ();
}
#line 1748 "parser.cc"
    break;

  case 42:
#line 295 "parser.yy"
                {
    yylhs.value.as < BlockItemList* > ()=new BlockItemList();
  }
#line 1756 "parser.cc"
    break;

  case 43:
#line 300 "parser.yy"
                   {
    yylhs.value.as < BlockItem* > ()=new BlockItem();
    yylhs.value.as < BlockItem* > ()->constDecl=std::shared_ptr<ConstDecl>(yystack_[0].value.as < ConstDecl* > ());
}
#line 1765 "parser.cc"
    break;

  case 44:
#line 304 "parser.yy"
                 {
    yylhs.value.as < BlockItem* > ()=new BlockItem();
    yylhs.value.as < BlockItem* > ()->varDecl=std::shared_ptr<VarDecl>(yystack_[0].value.as < VarDecl* > ());
  }
#line 1774 "parser.cc"
    break;

  case 45:
#line 308 "parser.yy"
              {
    yylhs.value.as < BlockItem* > ()=new BlockItem();
    yylhs.value.as < BlockItem* > ()->stmt=std::shared_ptr<Stmt>(yystack_[0].value.as < Stmt* > ());
  }
#line 1783 "parser.cc"
    break;

  case 46:
#line 314 "parser.yy"
                               {
        yylhs.value.as < Stmt* > ()=new Stmt();
        yylhs.value.as < Stmt* > ()->lVal=std::shared_ptr<LVal>(yystack_[3].value.as < LVal* > ());
        yylhs.value.as < Stmt* > ()->exp=std::shared_ptr<Exp>(yystack_[1].value.as < Exp* > ());
    }
#line 1793 "parser.cc"
    break;

  case 47:
#line 319 "parser.yy"
                  {
        yylhs.value.as < Stmt* > ()=new Stmt();
        yylhs.value.as < Stmt* > ()->exp=std::shared_ptr<Exp>(yystack_[1].value.as < Exp* > ());
    }
#line 1802 "parser.cc"
    break;

  case 48:
#line 323 "parser.yy"
              {
        yylhs.value.as < Stmt* > ()=new Stmt();
    }
#line 1810 "parser.cc"
    break;

  case 49:
#line 326 "parser.yy"
          {
        yylhs.value.as < Stmt* > ()=new Stmt();
        yylhs.value.as < Stmt* > ()->block=std::shared_ptr<Block>(yystack_[0].value.as < Block* > ());
    }
#line 1819 "parser.cc"
    break;

  case 50:
#line 330 "parser.yy"
                       {
        yylhs.value.as < Stmt* > ()=new Stmt();
        yylhs.value.as < Stmt* > ()->cond=std::shared_ptr<Cond>(yystack_[2].value.as < Cond* > ());
        yylhs.value.as < Stmt* > ()->stmt1=std::shared_ptr<Stmt>(yystack_[0].value.as < Stmt* > ());
        yylhs.value.as < Stmt* > ()->isSelect=true;
    }
#line 1830 "parser.cc"
    break;

  case 51:
#line 336 "parser.yy"
                                 {
        yylhs.value.as < Stmt* > ()=new Stmt();
        yylhs.value.as < Stmt* > ()->cond=std::shared_ptr<Cond>(yystack_[4].value.as < Cond* > ());
        yylhs.value.as < Stmt* > ()->stmt1=std::shared_ptr<Stmt>(yystack_[2].value.as < Stmt* > ());
        yylhs.value.as < Stmt* > ()->stmt2=std::shared_ptr<Stmt>(yystack_[0].value.as < Stmt* > ());
        yylhs.value.as < Stmt* > ()->isSelect=true;
    }
#line 1842 "parser.cc"
    break;

  case 52:
#line 343 "parser.yy"
                          {
        yylhs.value.as < Stmt* > ()=new Stmt();
        yylhs.value.as < Stmt* > ()->cond=std::shared_ptr<Cond>(yystack_[2].value.as < Cond* > ());
        yylhs.value.as < Stmt* > ()->stmt1=std::shared_ptr<Stmt>(yystack_[0].value.as < Stmt* > ());
        yylhs.value.as < Stmt* > ()->isIteration=true;
    }
#line 1853 "parser.cc"
    break;

  case 53:
#line 349 "parser.yy"
                    {
        yylhs.value.as < Stmt* > ()=new Stmt();
        yylhs.value.as < Stmt* > ()->isBreak=true;
    }
#line 1862 "parser.cc"
    break;

  case 54:
#line 353 "parser.yy"
                       {
        yylhs.value.as < Stmt* > ()=new Stmt();
        yylhs.value.as < Stmt* > ()->isContinue=true;
    }
#line 1871 "parser.cc"
    break;

  case 55:
#line 357 "parser.yy"
                     {
        yylhs.value.as < Stmt* > ()=new Stmt();
        yylhs.value.as < Stmt* > ()->isReturn=true;
    }
#line 1880 "parser.cc"
    break;

  case 56:
#line 361 "parser.yy"
                         {
        yylhs.value.as < Stmt* > ()=new Stmt();
        yylhs.value.as < Stmt* > ()->exp=std::shared_ptr<Exp>(yystack_[1].value.as < Exp* > ());
        yylhs.value.as < Stmt* > ()->isReturn=true;
    }
#line 1890 "parser.cc"
    break;

  case 57:
#line 368 "parser.yy"
          {
    yylhs.value.as < Exp* > ()=new Exp();
    yylhs.value.as < Exp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
}
#line 1899 "parser.cc"
    break;

  case 58:
#line 374 "parser.yy"
           {
    yylhs.value.as < Cond* > ()=new Cond();
    yylhs.value.as < Cond* > ()->lOrExp=std::shared_ptr<LOrExp>(yystack_[0].value.as < LOrExp* > ());
}
#line 1908 "parser.cc"
    break;

  case 59:
#line 379 "parser.yy"
                                 {
    yylhs.value.as < LVal* > ()=new LVal();
    yylhs.value.as < LVal* > ()->identifier=yystack_[1].value.as < std::string > ();
    yylhs.value.as < LVal* > ()->expList.swap(yystack_[0].value.as < ParamArrayExpList* > ()->expList);
}
#line 1919 "parser.cc"
    break;

  case 60:
#line 387 "parser.yy"
                    {
    yylhs.value.as < PrimaryExp* > ()=new PrimaryExp();
    yylhs.value.as < PrimaryExp* > ()->exp=std::shared_ptr<Exp>(yystack_[1].value.as < Exp* > ());
}
#line 1928 "parser.cc"
    break;

  case 61:
#line 391 "parser.yy"
              {
    yylhs.value.as < PrimaryExp* > ()=new PrimaryExp();
    yylhs.value.as < PrimaryExp* > ()->lVal=std::shared_ptr<LVal>(yystack_[0].value.as < LVal* > ());
  }
#line 1937 "parser.cc"
    break;

  case 62:
#line 395 "parser.yy"
                {
    yylhs.value.as < PrimaryExp* > ()=new PrimaryExp();
    yylhs.value.as < PrimaryExp* > ()->number=std::shared_ptr<Number>(yystack_[0].value.as < Number* > ());
  }
#line 1946 "parser.cc"
    break;

  case 63:
#line 400 "parser.yy"
               {
    yylhs.value.as < Number* > ()=new Number();
    yylhs.value.as < Number* > ()->type=type_specifier::TYPE_INT;
    yylhs.value.as < Number* > ()->intNum=yystack_[0].value.as < int > ();
    }
#line 1956 "parser.cc"
    break;

  case 64:
#line 405 "parser.yy"
               {
    yylhs.value.as < Number* > ()=new Number();
    yylhs.value.as < Number* > ()->type=type_specifier::TYPE_FLOAT;
    yylhs.value.as < Number* > ()->floatNum=yystack_[0].value.as < float > ();
    }
#line 1966 "parser.cc"
    break;

  case 65:
#line 412 "parser.yy"
                   {
    yylhs.value.as < UnaryExp* > ()=new UnaryExp();
    yylhs.value.as < UnaryExp* > ()->primaryExp=std::shared_ptr<PrimaryExp>(yystack_[0].value.as < PrimaryExp* > ());
}
#line 1975 "parser.cc"
    break;

  case 66:
#line 416 "parser.yy"
                                      {
    yylhs.value.as < UnaryExp* > ()=new UnaryExp();
    yylhs.value.as < UnaryExp* > ()->identifier=yystack_[3].value.as < std::string > ();
    yylhs.value.as < UnaryExp* > ()->funcRParams=std::shared_ptr<FuncRParams>(yystack_[1].value.as < FuncRParams* > ());
  }
#line 1985 "parser.cc"
    break;

  case 67:
#line 421 "parser.yy"
                      {
    yylhs.value.as < UnaryExp* > ()=new UnaryExp();
    yylhs.value.as < UnaryExp* > ()->identifier=yystack_[2].value.as < std::string > ();
    }
#line 1994 "parser.cc"
    break;

  case 68:
#line 425 "parser.yy"
                          {
    yylhs.value.as < UnaryExp* > ()=new UnaryExp();
    yylhs.value.as < UnaryExp* > ()->unaryOp=std::shared_ptr<UnaryOp>(yystack_[1].value.as < UnaryOp* > ());
    yylhs.value.as < UnaryExp* > ()->unaryExp=std::shared_ptr<UnaryExp>(yystack_[0].value.as < UnaryExp* > ());
  }
#line 2004 "parser.cc"
    break;

  case 69:
#line 431 "parser.yy"
            {
    yylhs.value.as < UnaryOp* > ()=new UnaryOp();
    yylhs.value.as < UnaryOp* > ()->op=unaryop::OP_POS;
}
#line 2013 "parser.cc"
    break;

  case 70:
#line 435 "parser.yy"
             {
	yylhs.value.as < UnaryOp* > ()=new UnaryOp();
    yylhs.value.as < UnaryOp* > ()->op=unaryop::OP_NEG;
    }
#line 2022 "parser.cc"
    break;

  case 71:
#line 439 "parser.yy"
             {
	yylhs.value.as < UnaryOp* > ()=new UnaryOp();
	yylhs.value.as < UnaryOp* > ()->op=unaryop::OP_NOT;
	}
#line 2031 "parser.cc"
    break;

  case 72:
#line 444 "parser.yy"
                                 {
    yystack_[2].value.as < FuncRParams* > ()->expList.push_back(std::shared_ptr<Exp>(yystack_[0].value.as < Exp* > ()));
    yylhs.value.as < FuncRParams* > ()=yystack_[2].value.as < FuncRParams* > ();
    }
#line 2040 "parser.cc"
    break;

  case 73:
#line 448 "parser.yy"
        {
        yylhs.value.as < FuncRParams* > ()=new FuncRParams();
        yylhs.value.as < FuncRParams* > ()->expList.push_back(std::shared_ptr<Exp>(yystack_[0].value.as < Exp* > ()));
    }
#line 2049 "parser.cc"
    break;

  case 74:
#line 454 "parser.yy"
               {
    yylhs.value.as < MulExp* > ()=new MulExp();
    yylhs.value.as < MulExp* > ()->unaryExp=std::shared_ptr<UnaryExp>(yystack_[0].value.as < UnaryExp* > ());
}
#line 2058 "parser.cc"
    break;

  case 75:
#line 458 "parser.yy"
                             {
    yylhs.value.as < MulExp* > ()=new MulExp();
    yylhs.value.as < MulExp* > ()->mulExp=std::shared_ptr<MulExp>(yystack_[2].value.as < MulExp* > ());
    yylhs.value.as < MulExp* > ()->unaryExp=std::shared_ptr<UnaryExp>(yystack_[0].value.as < UnaryExp* > ());
    yylhs.value.as < MulExp* > ()->op=mulop::OP_MUL;
  }
#line 2069 "parser.cc"
    break;

  case 76:
#line 464 "parser.yy"
                             {
    yylhs.value.as < MulExp* > ()=new MulExp();
    yylhs.value.as < MulExp* > ()->mulExp=std::shared_ptr<MulExp>(yystack_[2].value.as < MulExp* > ());
    yylhs.value.as < MulExp* > ()->unaryExp=std::shared_ptr<UnaryExp>(yystack_[0].value.as < UnaryExp* > ());
    yylhs.value.as < MulExp* > ()->op=mulop::OP_DIV;
  }
#line 2080 "parser.cc"
    break;

  case 77:
#line 470 "parser.yy"
                             {
    yylhs.value.as < MulExp* > ()=new MulExp();
    yylhs.value.as < MulExp* > ()->mulExp=std::shared_ptr<MulExp>(yystack_[2].value.as < MulExp* > ());
    yylhs.value.as < MulExp* > ()->unaryExp=std::shared_ptr<UnaryExp>(yystack_[0].value.as < UnaryExp* > ());
    yylhs.value.as < MulExp* > ()->op=mulop::OP_MOD;
  }
#line 2091 "parser.cc"
    break;

  case 78:
#line 478 "parser.yy"
             {
    yylhs.value.as < AddExp* > ()=new AddExp();
    yylhs.value.as < AddExp* > ()->mulExp=std::shared_ptr<MulExp>(yystack_[0].value.as < MulExp* > ());
}
#line 2100 "parser.cc"
    break;

  case 79:
#line 482 "parser.yy"
                           {
    yylhs.value.as < AddExp* > ()=new AddExp();
    yylhs.value.as < AddExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[2].value.as < AddExp* > ());
    yylhs.value.as < AddExp* > ()->mulExp=std::shared_ptr<MulExp>(yystack_[0].value.as < MulExp* > ());
    yylhs.value.as < AddExp* > ()->op=addop::OP_ADD;
  }
#line 2111 "parser.cc"
    break;

  case 80:
#line 488 "parser.yy"
                           {
    yylhs.value.as < AddExp* > ()=new AddExp();
    yylhs.value.as < AddExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[2].value.as < AddExp* > ());
    yylhs.value.as < AddExp* > ()->mulExp=std::shared_ptr<MulExp>(yystack_[0].value.as < MulExp* > ());
    yylhs.value.as < AddExp* > ()->op=addop::OP_SUB;
  }
#line 2122 "parser.cc"
    break;

  case 81:
#line 496 "parser.yy"
             {
    yylhs.value.as < RelExp* > ()=new RelExp();
    yylhs.value.as < RelExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
}
#line 2131 "parser.cc"
    break;

  case 82:
#line 500 "parser.yy"
                          {
    yylhs.value.as < RelExp* > ()=new RelExp();
    yylhs.value.as < RelExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[2].value.as < RelExp* > ());
    yylhs.value.as < RelExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
    yylhs.value.as < RelExp* > ()->op=relop::OP_LT;
  }
#line 2142 "parser.cc"
    break;

  case 83:
#line 506 "parser.yy"
                          {
    yylhs.value.as < RelExp* > ()=new RelExp();
    yylhs.value.as < RelExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[2].value.as < RelExp* > ());
    yylhs.value.as < RelExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
    yylhs.value.as < RelExp* > ()->op=relop::OP_GT;
  }
#line 2153 "parser.cc"
    break;

  case 84:
#line 512 "parser.yy"
                          {
    yylhs.value.as < RelExp* > ()=new RelExp();
    yylhs.value.as < RelExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[2].value.as < RelExp* > ());
    yylhs.value.as < RelExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
    yylhs.value.as < RelExp* > ()->op=relop::OP_LE;
  }
#line 2164 "parser.cc"
    break;

  case 85:
#line 518 "parser.yy"
                          {
    yylhs.value.as < RelExp* > ()=new RelExp();
    yylhs.value.as < RelExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[2].value.as < RelExp* > ());
    yylhs.value.as < RelExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
    yylhs.value.as < RelExp* > ()->op=relop::OP_GE;
  }
#line 2175 "parser.cc"
    break;

  case 86:
#line 525 "parser.yy"
            {
    yylhs.value.as < EqExp* > ()=new EqExp();
    yylhs.value.as < EqExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[0].value.as < RelExp* > ());
  }
#line 2184 "parser.cc"
    break;

  case 87:
#line 529 "parser.yy"
                          {
    yylhs.value.as < EqExp* > ()=new EqExp();
    yylhs.value.as < EqExp* > ()->eqExp=std::shared_ptr<EqExp>(yystack_[2].value.as < EqExp* > ());
    yylhs.value.as < EqExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[0].value.as < RelExp* > ());
    yylhs.value.as < EqExp* > ()->op=relop::OP_EQU;
  }
#line 2195 "parser.cc"
    break;

  case 88:
#line 535 "parser.yy"
                         {
    yylhs.value.as < EqExp* > ()=new EqExp();
    yylhs.value.as < EqExp* > ()->eqExp=std::shared_ptr<EqExp>(yystack_[2].value.as < EqExp* > ());
    yylhs.value.as < EqExp* > ()->relExp=std::shared_ptr<RelExp>(yystack_[0].value.as < RelExp* > ());
    yylhs.value.as < EqExp* > ()->op=relop::OP_NE;
  }
#line 2206 "parser.cc"
    break;

  case 89:
#line 542 "parser.yy"
              {
    yylhs.value.as < LAndExp* > ()=new LAndExp();
    yylhs.value.as < LAndExp* > ()->eqExp=std::shared_ptr<EqExp>(yystack_[0].value.as < EqExp* > ());
  }
#line 2215 "parser.cc"
    break;

  case 90:
#line 546 "parser.yy"
                           {
    yylhs.value.as < LAndExp* > ()=new LAndExp();
    yylhs.value.as < LAndExp* > ()->lAndExp=std::shared_ptr<LAndExp>(yystack_[2].value.as < LAndExp* > ());
    yylhs.value.as < LAndExp* > ()->eqExp=std::shared_ptr<EqExp>(yystack_[0].value.as < EqExp* > ());
  }
#line 2225 "parser.cc"
    break;

  case 91:
#line 552 "parser.yy"
              {
    yylhs.value.as < LOrExp* > ()=new LOrExp();
    yylhs.value.as < LOrExp* > ()->lAndExp=std::shared_ptr<LAndExp>(yystack_[0].value.as < LAndExp* > ());
  }
#line 2234 "parser.cc"
    break;

  case 92:
#line 556 "parser.yy"
                           {
    yylhs.value.as < LOrExp* > ()=new LOrExp();
    yylhs.value.as < LOrExp* > ()->lOrExp=std::shared_ptr<LOrExp>(yystack_[2].value.as < LOrExp* > ());
    yylhs.value.as < LOrExp* > ()->lAndExp=std::shared_ptr<LAndExp>(yystack_[0].value.as < LAndExp* > ());
  }
#line 2244 "parser.cc"
    break;

  case 93:
#line 562 "parser.yy"
               {
    yylhs.value.as < ConstExp* > ()=new ConstExp();
    yylhs.value.as < ConstExp* > ()->addExp=std::shared_ptr<AddExp>(yystack_[0].value.as < AddExp* > ());
  }
#line 2253 "parser.cc"
    break;


#line 2257 "parser.cc"

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


  const signed char parser::yypact_ninf_ = -106;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      62,  -106,  -106,  -106,    86,    16,     3,  -106,  -106,  -106,
    -106,     9,    15,  -106,  -106,  -106,    25,    30,  -106,  -106,
      70,  -106,     7,    -9,  -106,    20,    28,  -106,    15,    46,
      71,     8,  -106,   172,   204,  -106,  -106,   175,  -106,  -106,
    -106,    53,    86,    46,    75,  -106,  -106,  -106,  -106,   204,
      11,  -106,  -106,  -106,  -106,  -106,  -106,  -106,   204,    67,
      72,    72,    74,   146,  -106,  -106,   113,    96,  -106,  -106,
      39,    87,   101,  -106,  -106,   -14,  -106,   204,   204,   204,
     204,   204,  -106,  -106,  -106,   -12,   103,   104,   107,   110,
     201,  -106,  -106,  -106,  -106,    20,  -106,  -106,  -106,   111,
     118,  -106,  -106,  -106,    50,   204,  -106,   172,  -106,  -106,
    -106,  -106,    67,    67,   175,  -106,   204,   204,  -106,  -106,
    -106,   114,  -106,   204,    87,   204,  -106,   109,  -106,  -106,
     116,    72,    56,    80,   112,   125,   132,  -106,   121,  -106,
    -106,   143,   204,   204,   204,   204,   204,   204,   204,   204,
     143,  -106,   156,    72,    72,    72,    72,    56,    56,    80,
     112,  -106,   143,  -106
  };

  const signed char
  parser::yydefact_[] =
  {
       0,    31,    32,    33,     0,     0,     0,     4,     5,     6,
       7,     0,     0,     1,     2,     3,    13,     0,    21,    13,
       0,    10,     0,    22,    19,     0,     0,     8,     0,     0,
       0,     0,    35,     0,     0,    13,    20,     0,     9,    42,
      29,    37,     0,     0,    39,    63,    64,    69,    70,     0,
       0,    71,    23,    24,    61,    65,    62,    74,     0,    78,
      57,    93,     0,     0,    11,    14,     0,     0,    34,    30,
       0,    59,     0,    25,    28,     0,    68,     0,     0,     0,
       0,     0,    12,    16,    18,     0,     0,     0,     0,     0,
       0,    48,    40,    43,    44,     0,    49,    41,    45,     0,
      61,    39,    67,    73,     0,     0,    60,     0,    26,    75,
      76,    77,    79,    80,     0,    15,     0,     0,    53,    54,
      55,     0,    47,     0,    36,     0,    66,     0,    27,    17,
       0,    81,    86,    89,    91,    58,     0,    56,     0,    72,
      38,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    46,    50,    84,    82,    85,    83,    87,    88,    90,
      92,    52,     0,    51
  };

  const short
  parser::yypgoto_[] =
  {
    -106,  -106,  -106,   159,   102,  -106,   144,   155,   -58,  -106,
     117,  -106,   152,   -46,  -106,  -106,    -2,  -106,   138,    81,
     -11,  -106,  -106,  -105,   -19,    76,   -65,  -106,  -106,   -31,
    -106,  -106,    22,   -34,   -17,    43,    45,  -106,   158
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     5,     6,     7,     8,    20,    21,    23,    64,    85,
       9,    17,    18,    52,    75,    10,    11,    31,    32,    71,
      96,    66,    97,    98,    99,   130,    54,    55,    56,    57,
      58,   104,    59,    60,   132,   133,   134,   135,    65
  };

  const unsigned char
  parser::yytable_[] =
  {
      61,   100,    12,    61,    74,    84,     1,     2,     3,     4,
       1,     2,     3,    33,    53,   107,    13,   114,    40,   108,
      30,   115,    16,    34,    44,    45,    46,    76,    19,    61,
      72,    53,    69,    35,    47,    48,   152,    42,    29,    43,
      30,    49,    14,    50,    73,   161,   109,   110,   111,    51,
      37,   103,    44,    45,    46,    22,   129,   163,    24,    25,
      34,   128,    47,    48,    95,     1,     2,     3,     4,    49,
     102,   121,   142,   143,   144,   145,   100,    51,    39,   125,
      61,   126,   131,   131,    41,   100,   127,    67,    53,     1,
       2,     3,    77,    78,    79,    80,    81,   100,    27,    28,
     146,   147,   112,   113,   138,    70,   139,    82,   153,   154,
     155,   156,   131,   131,   131,   131,     1,     2,     3,     4,
      86,   105,    87,    88,    89,    90,    44,    45,    46,   157,
     158,   101,   106,   116,   117,   118,    47,    48,   119,   122,
     123,    91,   137,    49,   140,    39,    92,   141,   148,   151,
      86,    51,    87,    88,    89,    90,    44,    45,    46,    44,
      45,    46,   149,   150,   162,    15,    47,    48,    93,    47,
      48,    91,    38,    49,    26,    39,    49,    36,    63,    83,
      68,    51,   124,    94,    51,    44,    45,    46,    44,    45,
      46,   159,    62,   136,   160,    47,    48,     0,    47,    48,
       0,     0,    49,     0,    50,    49,     0,    63,     0,     0,
      51,     0,     0,    51,    44,    45,    46,    44,    45,    46,
       0,     0,     0,     0,    47,    48,     0,    47,    48,   120,
       0,    49,     0,     0,    49,     0,     0,     0,     0,    51,
       0,     0,    51
  };

  const short
  parser::yycheck_[] =
  {
      34,    66,     4,    37,    50,    63,     3,     4,     5,     6,
       3,     4,     5,    22,    33,    29,     0,    29,    29,    33,
      22,    33,    13,    32,    13,    14,    15,    58,    13,    63,
      49,    50,    43,    13,    23,    24,   141,    29,    31,    31,
      42,    30,    39,    32,    33,   150,    77,    78,    79,    38,
      22,    70,    13,    14,    15,    30,   114,   162,    28,    29,
      32,   107,    23,    24,    66,     3,     4,     5,     6,    30,
      31,    90,    16,    17,    18,    19,   141,    38,    32,    29,
     114,    31,   116,   117,    13,   150,   105,    34,   107,     3,
       4,     5,    25,    26,    27,    23,    24,   162,    28,    29,
      20,    21,    80,    81,   123,    30,   125,    33,   142,   143,
     144,   145,   146,   147,   148,   149,     3,     4,     5,     6,
       7,    34,     9,    10,    11,    12,    13,    14,    15,   146,
     147,    35,    31,    30,    30,    28,    23,    24,    28,    28,
      22,    28,    28,    30,    35,    32,    33,    31,    36,    28,
       7,    38,     9,    10,    11,    12,    13,    14,    15,    13,
      14,    15,    37,    31,     8,     6,    23,    24,    66,    23,
      24,    28,    28,    30,    19,    32,    30,    25,    32,    33,
      42,    38,   101,    66,    38,    13,    14,    15,    13,    14,
      15,   148,    34,   117,   149,    23,    24,    -1,    23,    24,
      -1,    -1,    30,    -1,    32,    30,    -1,    32,    -1,    -1,
      38,    -1,    -1,    38,    13,    14,    15,    13,    14,    15,
      -1,    -1,    -1,    -1,    23,    24,    -1,    23,    24,    28,
      -1,    30,    -1,    -1,    30,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    38
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,    41,    42,    43,    44,    50,
      55,    56,    56,     0,    39,    43,    13,    51,    52,    13,
      45,    46,    30,    47,    28,    29,    47,    28,    29,    31,
      56,    57,    58,    22,    32,    13,    52,    22,    46,    32,
      60,    13,    29,    31,    13,    14,    15,    23,    24,    30,
      32,    38,    53,    64,    66,    67,    68,    69,    70,    72,
      73,    73,    78,    32,    48,    78,    61,    34,    58,    60,
      30,    59,    64,    33,    53,    54,    69,    25,    26,    27,
      23,    24,    33,    33,    48,    49,     7,     9,    10,    11,
      12,    28,    33,    44,    50,    56,    60,    62,    63,    64,
      66,    35,    31,    64,    71,    34,    31,    29,    33,    69,
      69,    69,    72,    72,    29,    33,    30,    30,    28,    28,
      28,    64,    28,    22,    59,    29,    31,    64,    53,    48,
      65,    73,    74,    75,    76,    77,    65,    28,    64,    64,
      35,    31,    16,    17,    18,    19,    20,    21,    36,    37,
      31,    28,    63,    73,    73,    73,    73,    74,    74,    75,
      76,    63,     8,    63
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    40,    41,    42,    42,    43,    43,    43,    44,    45,
      45,    46,    47,    47,    48,    48,    48,    49,    49,    50,
      51,    51,    52,    52,    53,    53,    53,    54,    54,    55,
      55,    56,    56,    56,    57,    57,    58,    58,    59,    59,
      60,    61,    61,    62,    62,    62,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    64,    65,    66,
      67,    67,    67,    68,    68,    69,    69,    69,    69,    70,
      70,    70,    71,    71,    72,    72,    72,    72,    73,    73,
      73,    74,    74,    74,    74,    74,    75,    75,    75,    76,
      76,    77,    77,    78
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     1,     1,     1,     4,     3,
       1,     4,     4,     0,     1,     3,     2,     3,     1,     3,
       3,     1,     2,     4,     1,     2,     3,     3,     1,     5,
       6,     1,     1,     1,     3,     1,     5,     2,     4,     0,
       3,     2,     0,     1,     1,     1,     4,     2,     1,     1,
       5,     7,     5,     2,     2,     2,     3,     1,     1,     2,
       3,     1,     1,     1,     1,     1,     4,     3,     2,     1,
       1,     1,     3,     1,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "VOID", "INT", "FLOAT", "CONST", "IF",
  "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN", "IDENTIFIER", "INTCONST",
  "FLOATCONST", "LE", "LT", "GE", "GT", "EQU", "NE", "ASSIGN", "ADD",
  "SUB", "MUL", "DIV", "MOD", "SEMICOLON", "COMMA", "LB", "RB", "BLB",
  "BRB", "MLB", "MRB", "AND", "OR", "NOT", "END", "$accept", "Begin",
  "CompUnit", "DeclDef", "ConstDecl", "ConstDefList", "ConstDef",
  "ConstExpList", "ConstInitVal", "ConstInitValList", "VarDecl",
  "VarDefList", "VarDef", "InitVal", "InitValList", "FuncDef", "DefType",
  "FuncFParams", "FuncFParam", "ParamArrayExpList", "Block",
  "BlockItemList", "BlockItem", "Stmt", "Exp", "Cond", "LVal",
  "PrimaryExp", "Number", "UnaryExp", "UnaryOp", "FuncRParams", "MulExp",
  "AddExp", "RelExp", "EqExp", "LAndExp", "LOrExp", "ConstExp", YY_NULLPTR
  };

#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    94,    94,    99,   103,   108,   112,   116,   121,   127,
     131,   137,   144,   148,   153,   157,   161,   165,   169,   175,
     182,   186,   192,   197,   204,   208,   211,   216,   220,   226,
     232,   240,   244,   248,   253,   257,   263,   269,   276,   280,
     285,   291,   295,   300,   304,   308,   314,   319,   323,   326,
     330,   336,   343,   349,   353,   357,   361,   368,   374,   379,
     387,   391,   395,   400,   405,   412,   416,   421,   425,   431,
     435,   439,   444,   448,   454,   458,   464,   470,   478,   482,
     488,   496,   500,   506,   512,   518,   525,   529,   535,   542,
     546,   552,   556,   562
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
#line 2774 "parser.cc"

#line 567 "parser.yy"

/*Parser实现错误处理接口*/
void yy::parser::error (const location_type& l,
                          const std::string& m)
{
    ddriver.error(l, m);
}
