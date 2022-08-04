// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file parser.hh
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

#ifndef YY_YY_PARSER_HH_INCLUDED
# define YY_YY_PARSER_HH_INCLUDED
// "%code requires" blocks.
#line 14 "parser.yy"

#include <string>
#include "syntax_tree.hh"
class driver;

#line 54 "parser.hh"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

namespace yy {
#line 188 "parser.hh"




    /// A Bison parser.
    class parser
    {
    public:
#ifndef YYSTYPE
        /// A buffer to store and retrieve objects.
        ///
        /// Sort of a variant, but does not keep track of the nature
        /// of the stored data, since that knowledge is available
        /// via the current parser state.
        class semantic_type
        {
        public:
            /// Type of *this.
            typedef semantic_type self_type;

            /// Empty construction.
            semantic_type () YY_NOEXCEPT
                    : yybuffer_ ()
                    , yytypeid_ (YY_NULLPTR)
            {}

            /// Construct and fill.
            template <typename T>
            semantic_type (YY_RVREF (T) t)
                    : yytypeid_ (&typeid (T))
            {
                        YY_ASSERT (sizeof (T) <= size);
                new (yyas_<T> ()) T (YY_MOVE (t));
            }

            /// Destruction, allowed only if empty.
            ~semantic_type () YY_NOEXCEPT
            {
                        YY_ASSERT (!yytypeid_);
            }

# if 201103L <= YY_CPLUSPLUS
            /// Instantiate a \a T in here from \a t.
            template <typename T, typename... U>
            T&
            emplace (U&&... u)
            {
                        YY_ASSERT (!yytypeid_);
                        YY_ASSERT (sizeof (T) <= size);
                yytypeid_ = & typeid (T);
                return *new (yyas_<T> ()) T (std::forward <U>(u)...);
            }
# else
            /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

            /// Instantiate an empty \a T in here.
            /// Obsolete, use emplace.
            template <typename T>
            T&
            build ()
            {
                return emplace<T> ();
            }

            /// Instantiate a \a T in here from \a t.
            /// Obsolete, use emplace.
            template <typename T>
            T&
            build (const T& t)
            {
                return emplace<T> (t);
            }

            /// Accessor to a built \a T.
            template <typename T>
            T&
            as () YY_NOEXCEPT
            {
                        YY_ASSERT (yytypeid_);
                        YY_ASSERT (*yytypeid_ == typeid (T));
                        YY_ASSERT (sizeof (T) <= size);
                return *yyas_<T> ();
            }

            /// Const accessor to a built \a T (for %printer).
            template <typename T>
            const T&
            as () const YY_NOEXCEPT
            {
                        YY_ASSERT (yytypeid_);
                        YY_ASSERT (*yytypeid_ == typeid (T));
                        YY_ASSERT (sizeof (T) <= size);
                return *yyas_<T> ();
            }

            /// Swap the content with \a that, of same type.
            ///
            /// Both variants must be built beforehand, because swapping the actual
            /// data requires reading it (with as()), and this is not possible on
            /// unconstructed variants: it would require some dynamic testing, which
            /// should not be the variant's responsibility.
            /// Swapping between built and (possibly) non-built is done with
            /// self_type::move ().
            template <typename T>
            void
            swap (self_type& that) YY_NOEXCEPT
            {
                        YY_ASSERT (yytypeid_);
                        YY_ASSERT (*yytypeid_ == *that.yytypeid_);
                std::swap (as<T> (), that.as<T> ());
            }

            /// Move the content of \a that to this.
            ///
            /// Destroys \a that.
            template <typename T>
            void
            move (self_type& that)
            {
# if 201103L <= YY_CPLUSPLUS
                emplace<T> (std::move (that.as<T> ()));
# else
                emplace<T> ();
      swap<T> (that);
# endif
                that.destroy<T> ();
            }

# if 201103L <= YY_CPLUSPLUS
            /// Move the content of \a that to this.
            template <typename T>
            void
            move (self_type&& that)
            {
                emplace<T> (std::move (that.as<T> ()));
                that.destroy<T> ();
            }
#endif

            /// Copy the content of \a that to this.
            template <typename T>
            void
            copy (const self_type& that)
            {
                emplace<T> (that.as<T> ());
            }

            /// Destroy the stored \a T.
            template <typename T>
            void
            destroy ()
            {
                as<T> ().~T ();
                yytypeid_ = YY_NULLPTR;
            }

        private:
            /// Prohibit blind copies.
            self_type& operator= (const self_type&);
            semantic_type (const self_type&);

            /// Accessor to raw memory as \a T.
            template <typename T>
            T*
            yyas_ () YY_NOEXCEPT
            {
                void *yyp = yybuffer_.yyraw;
                return static_cast<T*> (yyp);
            }

            /// Const accessor to raw memory as \a T.
            template <typename T>
            const T*
            yyas_ () const YY_NOEXCEPT
            {
                const void *yyp = yybuffer_.yyraw;
                return static_cast<const T*> (yyp);
            }

            /// An auxiliary type to compute the largest semantic type.
            union union_type
            {
                // AddExp
                char dummy1[sizeof (AddExp*)];

                // AssignStmt
                char dummy2[sizeof (AssignStmt*)];

                // Block
                char dummy3[sizeof (Block*)];

                // BlockItem
                char dummy4[sizeof (BlockItem*)];

                // BlockItemList
                char dummy5[sizeof (BlockItemList*)];

                // BreakStmt
                char dummy6[sizeof (BreakStmt*)];

                // Begin
                // CompUnit
                char dummy7[sizeof (CompUnit*)];

                // Cond
                char dummy8[sizeof (Cond*)];

                // ConstDecl
                char dummy9[sizeof (ConstDecl*)];

                // ConstDef
                char dummy10[sizeof (ConstDef*)];

                // ConstDefList
                char dummy11[sizeof (ConstDefList*)];

                // ConstExp
                char dummy12[sizeof (ConstExp*)];

                // ConstExpList
                char dummy13[sizeof (ConstExpList*)];

                // ConstInitVal
                char dummy14[sizeof (ConstInitVal*)];

                // ConstInitValList
                char dummy15[sizeof (ConstInitValList*)];

                // ContinueStmt
                char dummy16[sizeof (ContinueStmt*)];

                // DeclDef
                char dummy17[sizeof (DeclDef*)];

                // DefType
                char dummy18[sizeof (DefType*)];

                // EqExp
                char dummy19[sizeof (EqExp*)];

                // Exp
                char dummy20[sizeof (Exp*)];

                // FuncDef
                char dummy21[sizeof (FuncDef*)];

                // FuncFParam
                char dummy22[sizeof (FuncFParam*)];

                // FuncFParams
                char dummy23[sizeof (FuncFParams*)];

                // FuncRParams
                char dummy24[sizeof (FuncRParams*)];

                // InitVal
                char dummy25[sizeof (InitVal*)];

                // InitValList
                char dummy26[sizeof (InitValList*)];

                // IterationStmt
                char dummy27[sizeof (IterationStmt*)];

                // LAndExp
                char dummy28[sizeof (LAndExp*)];

                // LOrExp
                char dummy29[sizeof (LOrExp*)];

                // LVal
                char dummy30[sizeof (LVal*)];

                // MulExp
                char dummy31[sizeof (MulExp*)];

                // Number
                char dummy32[sizeof (Number*)];

                // ParamArrayExpList
                char dummy33[sizeof (ParamArrayExpList*)];

                // PrimaryExp
                char dummy34[sizeof (PrimaryExp*)];

                // RelExp
                char dummy35[sizeof (RelExp*)];

                // ReturnStmt
                char dummy36[sizeof (ReturnStmt*)];

                // SelectStmt
                char dummy37[sizeof (SelectStmt*)];

                // Stmt
                char dummy38[sizeof (Stmt*)];

                // UnaryExp
                char dummy39[sizeof (UnaryExp*)];

                // UnaryOp
                char dummy40[sizeof (UnaryOp*)];

                // VarDecl
                char dummy41[sizeof (VarDecl*)];

                // VarDef
                char dummy42[sizeof (VarDef*)];

                // VarDefList
                char dummy43[sizeof (VarDefList*)];

                // FLOATCONST
                char dummy44[sizeof (float)];

                // INTCONST
                char dummy45[sizeof (int)];

                // STRING
                // IDENTIFIER
                char dummy46[sizeof (std::string)];
            };

            /// The size of the largest semantic type.
            enum { size = sizeof (union_type) };

            /// A buffer to store semantic values.
            union
            {
                /// Strongest alignment constraints.
                long double yyalign_me;
                /// A buffer large enough to store any of the semantic values.
                char yyraw[size];
            } yybuffer_;

            /// Whether the content is built: if defined, the name of the stored type.
            const std::type_info *yytypeid_;
        };

#else
        typedef YYSTYPE semantic_type;
#endif
        /// Symbol locations.
        typedef location location_type;

        /// Syntax errors thrown from user actions.
        struct syntax_error : std::runtime_error
        {
            syntax_error (const location_type& l, const std::string& m)
                    : std::runtime_error (m)
                    , location (l)
            {}

            syntax_error (const syntax_error& s)
                    : std::runtime_error (s.what ())
                    , location (s.location)
            {}

            ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

            location_type location;
        };

        /// Tokens.
        struct token
        {
            enum yytokentype
            {
                TOK_VOID = 258,
                TOK_INT = 259,
                TOK_FLOAT = 260,
                TOK_CONST = 261,
                TOK_IF = 262,
                TOK_ELSE = 263,
                TOK_WHILE = 264,
                TOK_BREAK = 265,
                TOK_CONTINUE = 266,
                TOK_RETURN = 267,
                TOK_STRING = 268,
                TOK_IDENTIFIER = 269,
                TOK_INTCONST = 270,
                TOK_FLOATCONST = 271,
                TOK_LE = 272,
                TOK_LT = 273,
                TOK_GE = 274,
                TOK_GT = 275,
                TOK_EQU = 276,
                TOK_NE = 277,
                TOK_ASSIGN = 278,
                TOK_ADD = 279,
                TOK_SUB = 280,
                TOK_MUL = 281,
                TOK_DIV = 282,
                TOK_MOD = 283,
                TOK_SEMICOLON = 284,
                TOK_COMMA = 285,
                TOK_LB = 286,
                TOK_RB = 287,
                TOK_BLB = 288,
                TOK_BRB = 289,
                TOK_MLB = 290,
                TOK_MRB = 291,
                TOK_AND = 292,
                TOK_OR = 293,
                TOK_NOT = 294,
                TOK_END = 295
            };
        };

        /// (External) token type, as returned by yylex.
        typedef token::yytokentype token_type;

        /// Symbol type: an internal symbol number.
        typedef int symbol_number_type;

        /// The symbol type number to denote an empty symbol.
        enum { empty_symbol = -2 };

        /// Internal symbol number for tokens (subsumed by symbol_number_type).
        typedef signed char token_number_type;

        /// A complete symbol.
        ///
        /// Expects its Base type to provide access to the symbol type
        /// via type_get ().
        ///
        /// Provide access to semantic value and location.
        template <typename Base>
        struct basic_symbol : Base
        {
            /// Alias to Base.
            typedef Base super_type;

            /// Default constructor.
            basic_symbol ()
                    : value ()
                    , location ()
            {}

#if 201103L <= YY_CPLUSPLUS
            /// Move constructor.
            basic_symbol (basic_symbol&& that);
#endif

            /// Copy constructor.
            basic_symbol (const basic_symbol& that);

            /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, location_type&& l)
                    : Base (t)
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, AddExp*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const AddExp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, AssignStmt*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const AssignStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, Block*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const Block*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, BlockItem*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const BlockItem*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, BlockItemList*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const BlockItemList*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, BreakStmt*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const BreakStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, CompUnit*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const CompUnit*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, Cond*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const Cond*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, ConstDecl*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const ConstDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, ConstDef*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const ConstDef*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, ConstDefList*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const ConstDefList*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, ConstExp*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const ConstExp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, ConstExpList*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const ConstExpList*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, ConstInitVal*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const ConstInitVal*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, ConstInitValList*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const ConstInitValList*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, ContinueStmt*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const ContinueStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, DeclDef*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const DeclDef*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, DefType*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const DefType*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, EqExp*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const EqExp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, Exp*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const Exp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, FuncDef*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const FuncDef*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, FuncFParam*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const FuncFParam*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, FuncFParams*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const FuncFParams*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, FuncRParams*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const FuncRParams*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, InitVal*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const InitVal*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, InitValList*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const InitValList*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, IterationStmt*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const IterationStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, LAndExp*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const LAndExp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, LOrExp*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const LOrExp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, LVal*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const LVal*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, MulExp*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const MulExp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, Number*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const Number*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, ParamArrayExpList*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const ParamArrayExpList*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, PrimaryExp*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const PrimaryExp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, RelExp*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const RelExp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, ReturnStmt*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const ReturnStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, SelectStmt*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const SelectStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, Stmt*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const Stmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, UnaryExp*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const UnaryExp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, UnaryOp*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const UnaryOp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, VarDecl*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const VarDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, VarDef*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const VarDef*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, VarDefList*&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const VarDefList*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, float&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const float& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, int&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
            basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
                    : Base (t)
                    , value (std::move (v))
                    , location (std::move (l))
            {}
#else
            basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

            /// Destroy the symbol.
            ~basic_symbol ()
            {
                clear ();
            }

            /// Destroy contents, and record that is empty.
            void clear ()
            {
                // User destructor.
                symbol_number_type yytype = this->type_get ();
                basic_symbol<Base>& yysym = *this;
                (void) yysym;
                switch (yytype)
                {
                    default:
                        break;
                }

                // Type destructor.
                switch (yytype)
                {
                    case 80: // AddExp
                        value.template destroy< AddExp* > ();
                        break;

                    case 65: // AssignStmt
                        value.template destroy< AssignStmt* > ();
                        break;

                    case 61: // Block
                        value.template destroy< Block* > ();
                        break;

                    case 63: // BlockItem
                        value.template destroy< BlockItem* > ();
                        break;

                    case 62: // BlockItemList
                        value.template destroy< BlockItemList* > ();
                        break;

                    case 68: // BreakStmt
                        value.template destroy< BreakStmt* > ();
                        break;

                    case 42: // Begin
                    case 43: // CompUnit
                        value.template destroy< CompUnit* > ();
                        break;

                    case 72: // Cond
                        value.template destroy< Cond* > ();
                        break;

                    case 45: // ConstDecl
                        value.template destroy< ConstDecl* > ();
                        break;

                    case 47: // ConstDef
                        value.template destroy< ConstDef* > ();
                        break;

                    case 46: // ConstDefList
                        value.template destroy< ConstDefList* > ();
                        break;

                    case 85: // ConstExp
                        value.template destroy< ConstExp* > ();
                        break;

                    case 48: // ConstExpList
                        value.template destroy< ConstExpList* > ();
                        break;

                    case 49: // ConstInitVal
                        value.template destroy< ConstInitVal* > ();
                        break;

                    case 50: // ConstInitValList
                        value.template destroy< ConstInitValList* > ();
                        break;

                    case 69: // ContinueStmt
                        value.template destroy< ContinueStmt* > ();
                        break;

                    case 44: // DeclDef
                        value.template destroy< DeclDef* > ();
                        break;

                    case 57: // DefType
                        value.template destroy< DefType* > ();
                        break;

                    case 82: // EqExp
                        value.template destroy< EqExp* > ();
                        break;

                    case 71: // Exp
                        value.template destroy< Exp* > ();
                        break;

                    case 56: // FuncDef
                        value.template destroy< FuncDef* > ();
                        break;

                    case 59: // FuncFParam
                        value.template destroy< FuncFParam* > ();
                        break;

                    case 58: // FuncFParams
                        value.template destroy< FuncFParams* > ();
                        break;

                    case 78: // FuncRParams
                        value.template destroy< FuncRParams* > ();
                        break;

                    case 54: // InitVal
                        value.template destroy< InitVal* > ();
                        break;

                    case 55: // InitValList
                        value.template destroy< InitValList* > ();
                        break;

                    case 67: // IterationStmt
                        value.template destroy< IterationStmt* > ();
                        break;

                    case 83: // LAndExp
                        value.template destroy< LAndExp* > ();
                        break;

                    case 84: // LOrExp
                        value.template destroy< LOrExp* > ();
                        break;

                    case 73: // LVal
                        value.template destroy< LVal* > ();
                        break;

                    case 79: // MulExp
                        value.template destroy< MulExp* > ();
                        break;

                    case 75: // Number
                        value.template destroy< Number* > ();
                        break;

                    case 60: // ParamArrayExpList
                        value.template destroy< ParamArrayExpList* > ();
                        break;

                    case 74: // PrimaryExp
                        value.template destroy< PrimaryExp* > ();
                        break;

                    case 81: // RelExp
                        value.template destroy< RelExp* > ();
                        break;

                    case 70: // ReturnStmt
                        value.template destroy< ReturnStmt* > ();
                        break;

                    case 66: // SelectStmt
                        value.template destroy< SelectStmt* > ();
                        break;

                    case 64: // Stmt
                        value.template destroy< Stmt* > ();
                        break;

                    case 76: // UnaryExp
                        value.template destroy< UnaryExp* > ();
                        break;

                    case 77: // UnaryOp
                        value.template destroy< UnaryOp* > ();
                        break;

                    case 51: // VarDecl
                        value.template destroy< VarDecl* > ();
                        break;

                    case 53: // VarDef
                        value.template destroy< VarDef* > ();
                        break;

                    case 52: // VarDefList
                        value.template destroy< VarDefList* > ();
                        break;

                    case 16: // FLOATCONST
                        value.template destroy< float > ();
                        break;

                    case 15: // INTCONST
                        value.template destroy< int > ();
                        break;

                    case 13: // STRING
                    case 14: // IDENTIFIER
                        value.template destroy< std::string > ();
                        break;

                    default:
                        break;
                }

                Base::clear ();
            }

            /// Whether empty.
            bool empty () const YY_NOEXCEPT;

            /// Destructive move, \a s is emptied into this.
            void move (basic_symbol& s);

            /// The semantic value.
            semantic_type value;

            /// The location.
            location_type location;

        private:
#if YY_CPLUSPLUS < 201103L
            /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
        };

        /// Type access provider for token (enum) based symbols.
        struct by_type
        {
            /// Default constructor.
            by_type ();

#if 201103L <= YY_CPLUSPLUS
            /// Move constructor.
            by_type (by_type&& that);
#endif

            /// Copy constructor.
            by_type (const by_type& that);

            /// The symbol type as needed by the constructor.
            typedef token_type kind_type;

            /// Constructor from (external) token numbers.
            by_type (kind_type t);

            /// Record that this symbol is empty.
            void clear ();

            /// Steal the symbol type from \a that.
            void move (by_type& that);

            /// The (internal) type number (corresponding to \a type).
            /// \a empty when empty.
            symbol_number_type type_get () const YY_NOEXCEPT;

            /// The symbol type.
            /// \a empty_symbol when empty.
            /// An int, not token_number_type, to be able to store empty_symbol.
            int type;
        };

        /// "External" symbols: returned by the scanner.
        struct symbol_type : basic_symbol<by_type>
        {
            /// Superclass.
            typedef basic_symbol<by_type> super_type;

            /// Empty symbol.
            symbol_type () {}

            /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
            symbol_type (int tok, location_type l)
                    : super_type(token_type (tok), std::move (l))
            {
                        YY_ASSERT (tok == 0 || tok == token::TOK_VOID || tok == token::TOK_INT || tok == token::TOK_FLOAT || tok == token::TOK_CONST || tok == token::TOK_IF || tok == token::TOK_ELSE || tok == token::TOK_WHILE || tok == token::TOK_BREAK || tok == token::TOK_CONTINUE || tok == token::TOK_RETURN || tok == token::TOK_LE || tok == token::TOK_LT || tok == token::TOK_GE || tok == token::TOK_GT || tok == token::TOK_EQU || tok == token::TOK_NE || tok == token::TOK_ASSIGN || tok == token::TOK_ADD || tok == token::TOK_SUB || tok == token::TOK_MUL || tok == token::TOK_DIV || tok == token::TOK_MOD || tok == token::TOK_SEMICOLON || tok == token::TOK_COMMA || tok == token::TOK_LB || tok == token::TOK_RB || tok == token::TOK_BLB || tok == token::TOK_BRB || tok == token::TOK_MLB || tok == token::TOK_MRB || tok == token::TOK_AND || tok == token::TOK_OR || tok == token::TOK_NOT || tok == token::TOK_END);
            }
#else
            symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YY_ASSERT (tok == 0 || tok == token::TOK_VOID || tok == token::TOK_INT || tok == token::TOK_FLOAT || tok == token::TOK_CONST || tok == token::TOK_IF || tok == token::TOK_ELSE || tok == token::TOK_WHILE || tok == token::TOK_BREAK || tok == token::TOK_CONTINUE || tok == token::TOK_RETURN || tok == token::TOK_LE || tok == token::TOK_LT || tok == token::TOK_GE || tok == token::TOK_GT || tok == token::TOK_EQU || tok == token::TOK_NE || tok == token::TOK_ASSIGN || tok == token::TOK_ADD || tok == token::TOK_SUB || tok == token::TOK_MUL || tok == token::TOK_DIV || tok == token::TOK_MOD || tok == token::TOK_SEMICOLON || tok == token::TOK_COMMA || tok == token::TOK_LB || tok == token::TOK_RB || tok == token::TOK_BLB || tok == token::TOK_BRB || tok == token::TOK_MLB || tok == token::TOK_MRB || tok == token::TOK_AND || tok == token::TOK_OR || tok == token::TOK_NOT || tok == token::TOK_END);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
            symbol_type (int tok, float v, location_type l)
                    : super_type(token_type (tok), std::move (v), std::move (l))
            {
                        YY_ASSERT (tok == token::TOK_FLOATCONST);
            }
#else
            symbol_type (int tok, const float& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::TOK_FLOATCONST);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
            symbol_type (int tok, int v, location_type l)
                    : super_type(token_type (tok), std::move (v), std::move (l))
            {
                        YY_ASSERT (tok == token::TOK_INTCONST);
            }
#else
            symbol_type (int tok, const int& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::TOK_INTCONST);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
            symbol_type (int tok, std::string v, location_type l)
                    : super_type(token_type (tok), std::move (v), std::move (l))
            {
                        YY_ASSERT (tok == token::TOK_STRING || tok == token::TOK_IDENTIFIER);
            }
#else
            symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::TOK_STRING || tok == token::TOK_IDENTIFIER);
      }
#endif
        };

        /// Build a parser object.
        parser (driver& ddriver_yyarg);
        virtual ~parser ();

        /// Parse.  An alias for parse ().
        /// \returns  0 iff parsing succeeded.
        int operator() ();

        /// Parse.
        /// \returns  0 iff parsing succeeded.
        virtual int parse ();

#if YYDEBUG
        /// The current debugging stream.
        std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
        /// Set the current debugging stream.
        void set_debug_stream (std::ostream &);

        /// Type for debugging levels.
        typedef int debug_level_type;
        /// The current debugging level.
        debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
        /// Set the current debugging level.
        void set_debug_level (debug_level_type l);
#endif

        /// Report a syntax error.
        /// \param loc    where the syntax error is found.
        /// \param msg    a description of the syntax error.
        virtual void error (const location_type& loc, const std::string& msg);

        /// Report a syntax error.
        void error (const syntax_error& err);

        // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_VOID (location_type l)
        {
            return symbol_type (token::TOK_VOID, std::move (l));
        }
#else
        static
      symbol_type
      make_VOID (const location_type& l)
      {
        return symbol_type (token::TOK_VOID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_INT (location_type l)
        {
            return symbol_type (token::TOK_INT, std::move (l));
        }
#else
        static
      symbol_type
      make_INT (const location_type& l)
      {
        return symbol_type (token::TOK_INT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_FLOAT (location_type l)
        {
            return symbol_type (token::TOK_FLOAT, std::move (l));
        }
#else
        static
      symbol_type
      make_FLOAT (const location_type& l)
      {
        return symbol_type (token::TOK_FLOAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_CONST (location_type l)
        {
            return symbol_type (token::TOK_CONST, std::move (l));
        }
#else
        static
      symbol_type
      make_CONST (const location_type& l)
      {
        return symbol_type (token::TOK_CONST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_IF (location_type l)
        {
            return symbol_type (token::TOK_IF, std::move (l));
        }
#else
        static
      symbol_type
      make_IF (const location_type& l)
      {
        return symbol_type (token::TOK_IF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_ELSE (location_type l)
        {
            return symbol_type (token::TOK_ELSE, std::move (l));
        }
#else
        static
      symbol_type
      make_ELSE (const location_type& l)
      {
        return symbol_type (token::TOK_ELSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_WHILE (location_type l)
        {
            return symbol_type (token::TOK_WHILE, std::move (l));
        }
#else
        static
      symbol_type
      make_WHILE (const location_type& l)
      {
        return symbol_type (token::TOK_WHILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_BREAK (location_type l)
        {
            return symbol_type (token::TOK_BREAK, std::move (l));
        }
#else
        static
      symbol_type
      make_BREAK (const location_type& l)
      {
        return symbol_type (token::TOK_BREAK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_CONTINUE (location_type l)
        {
            return symbol_type (token::TOK_CONTINUE, std::move (l));
        }
#else
        static
      symbol_type
      make_CONTINUE (const location_type& l)
      {
        return symbol_type (token::TOK_CONTINUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_RETURN (location_type l)
        {
            return symbol_type (token::TOK_RETURN, std::move (l));
        }
#else
        static
      symbol_type
      make_RETURN (const location_type& l)
      {
        return symbol_type (token::TOK_RETURN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_STRING (std::string v, location_type l)
        {
            return symbol_type (token::TOK_STRING, std::move (v), std::move (l));
        }
#else
        static
      symbol_type
      make_STRING (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_STRING, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_IDENTIFIER (std::string v, location_type l)
        {
            return symbol_type (token::TOK_IDENTIFIER, std::move (v), std::move (l));
        }
#else
        static
      symbol_type
      make_IDENTIFIER (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_INTCONST (int v, location_type l)
        {
            return symbol_type (token::TOK_INTCONST, std::move (v), std::move (l));
        }
#else
        static
      symbol_type
      make_INTCONST (const int& v, const location_type& l)
      {
        return symbol_type (token::TOK_INTCONST, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_FLOATCONST (float v, location_type l)
        {
            return symbol_type (token::TOK_FLOATCONST, std::move (v), std::move (l));
        }
#else
        static
      symbol_type
      make_FLOATCONST (const float& v, const location_type& l)
      {
        return symbol_type (token::TOK_FLOATCONST, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_LE (location_type l)
        {
            return symbol_type (token::TOK_LE, std::move (l));
        }
#else
        static
      symbol_type
      make_LE (const location_type& l)
      {
        return symbol_type (token::TOK_LE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_LT (location_type l)
        {
            return symbol_type (token::TOK_LT, std::move (l));
        }
#else
        static
      symbol_type
      make_LT (const location_type& l)
      {
        return symbol_type (token::TOK_LT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_GE (location_type l)
        {
            return symbol_type (token::TOK_GE, std::move (l));
        }
#else
        static
      symbol_type
      make_GE (const location_type& l)
      {
        return symbol_type (token::TOK_GE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_GT (location_type l)
        {
            return symbol_type (token::TOK_GT, std::move (l));
        }
#else
        static
      symbol_type
      make_GT (const location_type& l)
      {
        return symbol_type (token::TOK_GT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_EQU (location_type l)
        {
            return symbol_type (token::TOK_EQU, std::move (l));
        }
#else
        static
      symbol_type
      make_EQU (const location_type& l)
      {
        return symbol_type (token::TOK_EQU, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_NE (location_type l)
        {
            return symbol_type (token::TOK_NE, std::move (l));
        }
#else
        static
      symbol_type
      make_NE (const location_type& l)
      {
        return symbol_type (token::TOK_NE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_ASSIGN (location_type l)
        {
            return symbol_type (token::TOK_ASSIGN, std::move (l));
        }
#else
        static
      symbol_type
      make_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOK_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_ADD (location_type l)
        {
            return symbol_type (token::TOK_ADD, std::move (l));
        }
#else
        static
      symbol_type
      make_ADD (const location_type& l)
      {
        return symbol_type (token::TOK_ADD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_SUB (location_type l)
        {
            return symbol_type (token::TOK_SUB, std::move (l));
        }
#else
        static
      symbol_type
      make_SUB (const location_type& l)
      {
        return symbol_type (token::TOK_SUB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_MUL (location_type l)
        {
            return symbol_type (token::TOK_MUL, std::move (l));
        }
#else
        static
      symbol_type
      make_MUL (const location_type& l)
      {
        return symbol_type (token::TOK_MUL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_DIV (location_type l)
        {
            return symbol_type (token::TOK_DIV, std::move (l));
        }
#else
        static
      symbol_type
      make_DIV (const location_type& l)
      {
        return symbol_type (token::TOK_DIV, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_MOD (location_type l)
        {
            return symbol_type (token::TOK_MOD, std::move (l));
        }
#else
        static
      symbol_type
      make_MOD (const location_type& l)
      {
        return symbol_type (token::TOK_MOD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_SEMICOLON (location_type l)
        {
            return symbol_type (token::TOK_SEMICOLON, std::move (l));
        }
#else
        static
      symbol_type
      make_SEMICOLON (const location_type& l)
      {
        return symbol_type (token::TOK_SEMICOLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_COMMA (location_type l)
        {
            return symbol_type (token::TOK_COMMA, std::move (l));
        }
#else
        static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::TOK_COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_LB (location_type l)
        {
            return symbol_type (token::TOK_LB, std::move (l));
        }
#else
        static
      symbol_type
      make_LB (const location_type& l)
      {
        return symbol_type (token::TOK_LB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_RB (location_type l)
        {
            return symbol_type (token::TOK_RB, std::move (l));
        }
#else
        static
      symbol_type
      make_RB (const location_type& l)
      {
        return symbol_type (token::TOK_RB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_BLB (location_type l)
        {
            return symbol_type (token::TOK_BLB, std::move (l));
        }
#else
        static
      symbol_type
      make_BLB (const location_type& l)
      {
        return symbol_type (token::TOK_BLB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_BRB (location_type l)
        {
            return symbol_type (token::TOK_BRB, std::move (l));
        }
#else
        static
      symbol_type
      make_BRB (const location_type& l)
      {
        return symbol_type (token::TOK_BRB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_MLB (location_type l)
        {
            return symbol_type (token::TOK_MLB, std::move (l));
        }
#else
        static
      symbol_type
      make_MLB (const location_type& l)
      {
        return symbol_type (token::TOK_MLB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_MRB (location_type l)
        {
            return symbol_type (token::TOK_MRB, std::move (l));
        }
#else
        static
      symbol_type
      make_MRB (const location_type& l)
      {
        return symbol_type (token::TOK_MRB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_AND (location_type l)
        {
            return symbol_type (token::TOK_AND, std::move (l));
        }
#else
        static
      symbol_type
      make_AND (const location_type& l)
      {
        return symbol_type (token::TOK_AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_OR (location_type l)
        {
            return symbol_type (token::TOK_OR, std::move (l));
        }
#else
        static
      symbol_type
      make_OR (const location_type& l)
      {
        return symbol_type (token::TOK_OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_NOT (location_type l)
        {
            return symbol_type (token::TOK_NOT, std::move (l));
        }
#else
        static
      symbol_type
      make_NOT (const location_type& l)
      {
        return symbol_type (token::TOK_NOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
        static
        symbol_type
        make_END (location_type l)
        {
            return symbol_type (token::TOK_END, std::move (l));
        }
#else
        static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::TOK_END, l);
      }
#endif


    private:
        /// This class is not copyable.
        parser (const parser&);
        parser& operator= (const parser&);

        /// Stored state numbers (used for stacks).
        typedef unsigned char state_type;

        /// Generate an error message.
        /// \param yystate   the state where the error occurred.
        /// \param yyla      the lookahead token.
        virtual std::string yysyntax_error_ (state_type yystate,
                                             const symbol_type& yyla) const;

        /// Compute post-reduction state.
        /// \param yystate   the current state
        /// \param yysym     the nonterminal to push on the stack
        static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

        /// Whether the given \c yypact_ value indicates a defaulted state.
        /// \param yyvalue   the value to check
        static bool yy_pact_value_is_default_ (int yyvalue);

        /// Whether the given \c yytable_ value indicates a syntax error.
        /// \param yyvalue   the value to check
        static bool yy_table_value_is_error_ (int yyvalue);

        static const signed char yypact_ninf_;
        static const signed char yytable_ninf_;

        /// Convert a scanner token number \a t to a symbol number.
        /// In theory \a t should be a token_type, but character literals
        /// are valid, yet not members of the token_type enum.
        static token_number_type yytranslate_ (int t);

        // Tables.
        // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
        // STATE-NUM.
        static const short yypact_[];

        // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
        // Performed when YYTABLE does not specify something else to do.  Zero
        // means the default is an error.
        static const signed char yydefact_[];

        // YYPGOTO[NTERM-NUM].
        static const short yypgoto_[];

        // YYDEFGOTO[NTERM-NUM].
        static const short yydefgoto_[];

        // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
        // positive, shift that token.  If negative, reduce the rule whose
        // number is the opposite.  If YYTABLE_NINF, syntax error.
        static const unsigned char yytable_[];

        static const short yycheck_[];

        // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
        // symbol of state STATE-NUM.
        static const signed char yystos_[];

        // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
        static const signed char yyr1_[];

        // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
        static const signed char yyr2_[];


        /// Convert the symbol name \a n to a form suitable for a diagnostic.
        static std::string yytnamerr_ (const char *n);


        /// For a symbol, its name in clear.
        static const char* const yytname_[];
#if YYDEBUG
        // YYRLINE[YYN] -- Source line where rule number YYN was defined.
        static const short yyrline_[];
        /// Report on the debug stream that the rule \a r is going to be reduced.
        virtual void yy_reduce_print_ (int r);
        /// Print the state stack on the debug stream.
        virtual void yystack_print_ ();

        /// Debugging level.
        int yydebug_;
        /// Debug stream.
        std::ostream* yycdebug_;

        /// \brief Display a symbol type, value and location.
        /// \param yyo    The output stream.
        /// \param yysym  The symbol.
        template <typename Base>
        void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

        /// \brief Reclaim the memory associated to a symbol.
        /// \param yymsg     Why this token is reclaimed.
        ///                  If null, print nothing.
        /// \param yysym     The symbol.
        template <typename Base>
        void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

    private:
        /// Type access provider for state based symbols.
        struct by_state
        {
            /// Default constructor.
            by_state () YY_NOEXCEPT;

            /// The symbol type as needed by the constructor.
            typedef state_type kind_type;

            /// Constructor.
            by_state (kind_type s) YY_NOEXCEPT;

            /// Copy constructor.
            by_state (const by_state& that) YY_NOEXCEPT;

            /// Record that this symbol is empty.
            void clear () YY_NOEXCEPT;

            /// Steal the symbol type from \a that.
            void move (by_state& that);

            /// The (internal) type number (corresponding to \a state).
            /// \a empty_symbol when empty.
            symbol_number_type type_get () const YY_NOEXCEPT;

            /// The state number used to denote an empty symbol.
            /// We use the initial state, as it does not have a value.
            enum { empty_state = 0 };

            /// The state.
            /// \a empty when empty.
            state_type state;
        };

        /// "Internal" symbol: element of the stack.
        struct stack_symbol_type : basic_symbol<by_state>
        {
            /// Superclass.
            typedef basic_symbol<by_state> super_type;
            /// Construct an empty symbol.
            stack_symbol_type ();
            /// Move or copy construction.
            stack_symbol_type (YY_RVREF (stack_symbol_type) that);
            /// Steal the contents from \a sym to build this.
            stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
            /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
        };

        /// A stack with random access from its top.
        template <typename T, typename S = std::vector<T> >
        class stack
        {
        public:
            // Hide our reversed order.
            typedef typename S::reverse_iterator iterator;
            typedef typename S::const_reverse_iterator const_iterator;
            typedef typename S::size_type size_type;
            typedef typename std::ptrdiff_t index_type;

            stack (size_type n = 200)
                    : seq_ (n)
            {}

            /// Random access.
            ///
            /// Index 0 returns the topmost element.
            const T&
            operator[] (index_type i) const
            {
                return seq_[size_type (size () - 1 - i)];
            }

            /// Random access.
            ///
            /// Index 0 returns the topmost element.
            T&
            operator[] (index_type i)
            {
                return seq_[size_type (size () - 1 - i)];
            }

            /// Steal the contents of \a t.
            ///
            /// Close to move-semantics.
            void
            push (YY_MOVE_REF (T) t)
            {
                seq_.push_back (T ());
                operator[] (0).move (t);
            }

            /// Pop elements from the stack.
            void
            pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
            {
                for (; 0 < n; --n)
                    seq_.pop_back ();
            }

            /// Pop all elements from the stack.
            void
            clear () YY_NOEXCEPT
            {
                seq_.clear ();
            }

            /// Number of elements on the stack.
            index_type
            size () const YY_NOEXCEPT
            {
                return index_type (seq_.size ());
            }

            std::ptrdiff_t
            ssize () const YY_NOEXCEPT
            {
                return std::ptrdiff_t (size ());
            }

            /// Iterator on top of the stack (going downwards).
            const_iterator
            begin () const YY_NOEXCEPT
            {
                return seq_.rbegin ();
            }

            /// Bottom of the stack.
            const_iterator
            end () const YY_NOEXCEPT
            {
                return seq_.rend ();
            }

            /// Present a slice of the top of a stack.
            class slice
            {
            public:
                slice (const stack& stack, index_type range)
                        : stack_ (stack)
                        , range_ (range)
                {}

                const T&
                operator[] (index_type i) const
                {
                    return stack_[range_ - i];
                }

            private:
                const stack& stack_;
                index_type range_;
            };

        private:
            stack (const stack&);
            stack& operator= (const stack&);
            /// The wrapped container.
            S seq_;
        };


        /// Stack type.
        typedef stack<stack_symbol_type> stack_type;

        /// The stack.
        stack_type yystack_;

        /// Push a new state on the stack.
        /// \param m    a debug message to display
        ///             if null, no trace is output.
        /// \param sym  the symbol
        /// \warning the contents of \a s.value is stolen.
        void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

        /// Push a new look ahead token on the state on the stack.
        /// \param m    a debug message to display
        ///             if null, no trace is output.
        /// \param s    the state
        /// \param sym  the symbol (for its value and location).
        /// \warning the contents of \a sym.value is stolen.
        void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

        /// Pop \a n symbols from the stack.
        void yypop_ (int n = 1);

        /// Some specific tokens.
        static const token_number_type yy_error_token_ = 1;
        static const token_number_type yy_undef_token_ = 2;

        /// Constants.
        enum
        {
            yyeof_ = 0,
            yylast_ = 262,     ///< Last index in yytable_.
            yynnts_ = 45,  ///< Number of nonterminal symbols.
            yyfinal_ = 13, ///< Termination state number.
            yyntokens_ = 41  ///< Number of tokens.
        };


        // User arguments.
        driver& ddriver;
    };

    inline
    parser::token_number_type
    parser::yytranslate_ (int t)
    {
        // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
        // TOKEN-NUM as returned by yylex.
        static
        const token_number_type
                translate_table[] =
                {
                        0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                        2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
                        5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
                        15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
                        25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
                        35,    36,    37,    38,    39,    40
                };
        const int user_token_number_max_ = 295;

        if (t <= 0)
            return yyeof_;
        else if (t <= user_token_number_max_)
            return translate_table[t];
        else
            return yy_undef_token_;
    }

    // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
    template <typename Base>
    parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
            : Base (std::move (that))
            , value ()
            , location (std::move (that.location))
    {
        switch (this->type_get ())
        {
            case 80: // AddExp
                value.move< AddExp* > (std::move (that.value));
                break;

            case 65: // AssignStmt
                value.move< AssignStmt* > (std::move (that.value));
                break;

            case 61: // Block
                value.move< Block* > (std::move (that.value));
                break;

            case 63: // BlockItem
                value.move< BlockItem* > (std::move (that.value));
                break;

            case 62: // BlockItemList
                value.move< BlockItemList* > (std::move (that.value));
                break;

            case 68: // BreakStmt
                value.move< BreakStmt* > (std::move (that.value));
                break;

            case 42: // Begin
            case 43: // CompUnit
                value.move< CompUnit* > (std::move (that.value));
                break;

            case 72: // Cond
                value.move< Cond* > (std::move (that.value));
                break;

            case 45: // ConstDecl
                value.move< ConstDecl* > (std::move (that.value));
                break;

            case 47: // ConstDef
                value.move< ConstDef* > (std::move (that.value));
                break;

            case 46: // ConstDefList
                value.move< ConstDefList* > (std::move (that.value));
                break;

            case 85: // ConstExp
                value.move< ConstExp* > (std::move (that.value));
                break;

            case 48: // ConstExpList
                value.move< ConstExpList* > (std::move (that.value));
                break;

            case 49: // ConstInitVal
                value.move< ConstInitVal* > (std::move (that.value));
                break;

            case 50: // ConstInitValList
                value.move< ConstInitValList* > (std::move (that.value));
                break;

            case 69: // ContinueStmt
                value.move< ContinueStmt* > (std::move (that.value));
                break;

            case 44: // DeclDef
                value.move< DeclDef* > (std::move (that.value));
                break;

            case 57: // DefType
                value.move< DefType* > (std::move (that.value));
                break;

            case 82: // EqExp
                value.move< EqExp* > (std::move (that.value));
                break;

            case 71: // Exp
                value.move< Exp* > (std::move (that.value));
                break;

            case 56: // FuncDef
                value.move< FuncDef* > (std::move (that.value));
                break;

            case 59: // FuncFParam
                value.move< FuncFParam* > (std::move (that.value));
                break;

            case 58: // FuncFParams
                value.move< FuncFParams* > (std::move (that.value));
                break;

            case 78: // FuncRParams
                value.move< FuncRParams* > (std::move (that.value));
                break;

            case 54: // InitVal
                value.move< InitVal* > (std::move (that.value));
                break;

            case 55: // InitValList
                value.move< InitValList* > (std::move (that.value));
                break;

            case 67: // IterationStmt
                value.move< IterationStmt* > (std::move (that.value));
                break;

            case 83: // LAndExp
                value.move< LAndExp* > (std::move (that.value));
                break;

            case 84: // LOrExp
                value.move< LOrExp* > (std::move (that.value));
                break;

            case 73: // LVal
                value.move< LVal* > (std::move (that.value));
                break;

            case 79: // MulExp
                value.move< MulExp* > (std::move (that.value));
                break;

            case 75: // Number
                value.move< Number* > (std::move (that.value));
                break;

            case 60: // ParamArrayExpList
                value.move< ParamArrayExpList* > (std::move (that.value));
                break;

            case 74: // PrimaryExp
                value.move< PrimaryExp* > (std::move (that.value));
                break;

            case 81: // RelExp
                value.move< RelExp* > (std::move (that.value));
                break;

            case 70: // ReturnStmt
                value.move< ReturnStmt* > (std::move (that.value));
                break;

            case 66: // SelectStmt
                value.move< SelectStmt* > (std::move (that.value));
                break;

            case 64: // Stmt
                value.move< Stmt* > (std::move (that.value));
                break;

            case 76: // UnaryExp
                value.move< UnaryExp* > (std::move (that.value));
                break;

            case 77: // UnaryOp
                value.move< UnaryOp* > (std::move (that.value));
                break;

            case 51: // VarDecl
                value.move< VarDecl* > (std::move (that.value));
                break;

            case 53: // VarDef
                value.move< VarDef* > (std::move (that.value));
                break;

            case 52: // VarDefList
                value.move< VarDefList* > (std::move (that.value));
                break;

            case 16: // FLOATCONST
                value.move< float > (std::move (that.value));
                break;

            case 15: // INTCONST
                value.move< int > (std::move (that.value));
                break;

            case 13: // STRING
            case 14: // IDENTIFIER
                value.move< std::string > (std::move (that.value));
                break;

            default:
                break;
        }

    }
#endif

    template <typename Base>
    parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
            : Base (that)
            , value ()
            , location (that.location)
    {
        switch (this->type_get ())
        {
            case 80: // AddExp
                value.copy< AddExp* > (YY_MOVE (that.value));
                break;

            case 65: // AssignStmt
                value.copy< AssignStmt* > (YY_MOVE (that.value));
                break;

            case 61: // Block
                value.copy< Block* > (YY_MOVE (that.value));
                break;

            case 63: // BlockItem
                value.copy< BlockItem* > (YY_MOVE (that.value));
                break;

            case 62: // BlockItemList
                value.copy< BlockItemList* > (YY_MOVE (that.value));
                break;

            case 68: // BreakStmt
                value.copy< BreakStmt* > (YY_MOVE (that.value));
                break;

            case 42: // Begin
            case 43: // CompUnit
                value.copy< CompUnit* > (YY_MOVE (that.value));
                break;

            case 72: // Cond
                value.copy< Cond* > (YY_MOVE (that.value));
                break;

            case 45: // ConstDecl
                value.copy< ConstDecl* > (YY_MOVE (that.value));
                break;

            case 47: // ConstDef
                value.copy< ConstDef* > (YY_MOVE (that.value));
                break;

            case 46: // ConstDefList
                value.copy< ConstDefList* > (YY_MOVE (that.value));
                break;

            case 85: // ConstExp
                value.copy< ConstExp* > (YY_MOVE (that.value));
                break;

            case 48: // ConstExpList
                value.copy< ConstExpList* > (YY_MOVE (that.value));
                break;

            case 49: // ConstInitVal
                value.copy< ConstInitVal* > (YY_MOVE (that.value));
                break;

            case 50: // ConstInitValList
                value.copy< ConstInitValList* > (YY_MOVE (that.value));
                break;

            case 69: // ContinueStmt
                value.copy< ContinueStmt* > (YY_MOVE (that.value));
                break;

            case 44: // DeclDef
                value.copy< DeclDef* > (YY_MOVE (that.value));
                break;

            case 57: // DefType
                value.copy< DefType* > (YY_MOVE (that.value));
                break;

            case 82: // EqExp
                value.copy< EqExp* > (YY_MOVE (that.value));
                break;

            case 71: // Exp
                value.copy< Exp* > (YY_MOVE (that.value));
                break;

            case 56: // FuncDef
                value.copy< FuncDef* > (YY_MOVE (that.value));
                break;

            case 59: // FuncFParam
                value.copy< FuncFParam* > (YY_MOVE (that.value));
                break;

            case 58: // FuncFParams
                value.copy< FuncFParams* > (YY_MOVE (that.value));
                break;

            case 78: // FuncRParams
                value.copy< FuncRParams* > (YY_MOVE (that.value));
                break;

            case 54: // InitVal
                value.copy< InitVal* > (YY_MOVE (that.value));
                break;

            case 55: // InitValList
                value.copy< InitValList* > (YY_MOVE (that.value));
                break;

            case 67: // IterationStmt
                value.copy< IterationStmt* > (YY_MOVE (that.value));
                break;

            case 83: // LAndExp
                value.copy< LAndExp* > (YY_MOVE (that.value));
                break;

            case 84: // LOrExp
                value.copy< LOrExp* > (YY_MOVE (that.value));
                break;

            case 73: // LVal
                value.copy< LVal* > (YY_MOVE (that.value));
                break;

            case 79: // MulExp
                value.copy< MulExp* > (YY_MOVE (that.value));
                break;

            case 75: // Number
                value.copy< Number* > (YY_MOVE (that.value));
                break;

            case 60: // ParamArrayExpList
                value.copy< ParamArrayExpList* > (YY_MOVE (that.value));
                break;

            case 74: // PrimaryExp
                value.copy< PrimaryExp* > (YY_MOVE (that.value));
                break;

            case 81: // RelExp
                value.copy< RelExp* > (YY_MOVE (that.value));
                break;

            case 70: // ReturnStmt
                value.copy< ReturnStmt* > (YY_MOVE (that.value));
                break;

            case 66: // SelectStmt
                value.copy< SelectStmt* > (YY_MOVE (that.value));
                break;

            case 64: // Stmt
                value.copy< Stmt* > (YY_MOVE (that.value));
                break;

            case 76: // UnaryExp
                value.copy< UnaryExp* > (YY_MOVE (that.value));
                break;

            case 77: // UnaryOp
                value.copy< UnaryOp* > (YY_MOVE (that.value));
                break;

            case 51: // VarDecl
                value.copy< VarDecl* > (YY_MOVE (that.value));
                break;

            case 53: // VarDef
                value.copy< VarDef* > (YY_MOVE (that.value));
                break;

            case 52: // VarDefList
                value.copy< VarDefList* > (YY_MOVE (that.value));
                break;

            case 16: // FLOATCONST
                value.copy< float > (YY_MOVE (that.value));
                break;

            case 15: // INTCONST
                value.copy< int > (YY_MOVE (that.value));
                break;

            case 13: // STRING
            case 14: // IDENTIFIER
                value.copy< std::string > (YY_MOVE (that.value));
                break;

            default:
                break;
        }

    }



    template <typename Base>
    bool
    parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
    {
        return Base::type_get () == empty_symbol;
    }

    template <typename Base>
    void
    parser::basic_symbol<Base>::move (basic_symbol& s)
    {
        super_type::move (s);
        switch (this->type_get ())
        {
            case 80: // AddExp
                value.move< AddExp* > (YY_MOVE (s.value));
                break;

            case 65: // AssignStmt
                value.move< AssignStmt* > (YY_MOVE (s.value));
                break;

            case 61: // Block
                value.move< Block* > (YY_MOVE (s.value));
                break;

            case 63: // BlockItem
                value.move< BlockItem* > (YY_MOVE (s.value));
                break;

            case 62: // BlockItemList
                value.move< BlockItemList* > (YY_MOVE (s.value));
                break;

            case 68: // BreakStmt
                value.move< BreakStmt* > (YY_MOVE (s.value));
                break;

            case 42: // Begin
            case 43: // CompUnit
                value.move< CompUnit* > (YY_MOVE (s.value));
                break;

            case 72: // Cond
                value.move< Cond* > (YY_MOVE (s.value));
                break;

            case 45: // ConstDecl
                value.move< ConstDecl* > (YY_MOVE (s.value));
                break;

            case 47: // ConstDef
                value.move< ConstDef* > (YY_MOVE (s.value));
                break;

            case 46: // ConstDefList
                value.move< ConstDefList* > (YY_MOVE (s.value));
                break;

            case 85: // ConstExp
                value.move< ConstExp* > (YY_MOVE (s.value));
                break;

            case 48: // ConstExpList
                value.move< ConstExpList* > (YY_MOVE (s.value));
                break;

            case 49: // ConstInitVal
                value.move< ConstInitVal* > (YY_MOVE (s.value));
                break;

            case 50: // ConstInitValList
                value.move< ConstInitValList* > (YY_MOVE (s.value));
                break;

            case 69: // ContinueStmt
                value.move< ContinueStmt* > (YY_MOVE (s.value));
                break;

            case 44: // DeclDef
                value.move< DeclDef* > (YY_MOVE (s.value));
                break;

            case 57: // DefType
                value.move< DefType* > (YY_MOVE (s.value));
                break;

            case 82: // EqExp
                value.move< EqExp* > (YY_MOVE (s.value));
                break;

            case 71: // Exp
                value.move< Exp* > (YY_MOVE (s.value));
                break;

            case 56: // FuncDef
                value.move< FuncDef* > (YY_MOVE (s.value));
                break;

            case 59: // FuncFParam
                value.move< FuncFParam* > (YY_MOVE (s.value));
                break;

            case 58: // FuncFParams
                value.move< FuncFParams* > (YY_MOVE (s.value));
                break;

            case 78: // FuncRParams
                value.move< FuncRParams* > (YY_MOVE (s.value));
                break;

            case 54: // InitVal
                value.move< InitVal* > (YY_MOVE (s.value));
                break;

            case 55: // InitValList
                value.move< InitValList* > (YY_MOVE (s.value));
                break;

            case 67: // IterationStmt
                value.move< IterationStmt* > (YY_MOVE (s.value));
                break;

            case 83: // LAndExp
                value.move< LAndExp* > (YY_MOVE (s.value));
                break;

            case 84: // LOrExp
                value.move< LOrExp* > (YY_MOVE (s.value));
                break;

            case 73: // LVal
                value.move< LVal* > (YY_MOVE (s.value));
                break;

            case 79: // MulExp
                value.move< MulExp* > (YY_MOVE (s.value));
                break;

            case 75: // Number
                value.move< Number* > (YY_MOVE (s.value));
                break;

            case 60: // ParamArrayExpList
                value.move< ParamArrayExpList* > (YY_MOVE (s.value));
                break;

            case 74: // PrimaryExp
                value.move< PrimaryExp* > (YY_MOVE (s.value));
                break;

            case 81: // RelExp
                value.move< RelExp* > (YY_MOVE (s.value));
                break;

            case 70: // ReturnStmt
                value.move< ReturnStmt* > (YY_MOVE (s.value));
                break;

            case 66: // SelectStmt
                value.move< SelectStmt* > (YY_MOVE (s.value));
                break;

            case 64: // Stmt
                value.move< Stmt* > (YY_MOVE (s.value));
                break;

            case 76: // UnaryExp
                value.move< UnaryExp* > (YY_MOVE (s.value));
                break;

            case 77: // UnaryOp
                value.move< UnaryOp* > (YY_MOVE (s.value));
                break;

            case 51: // VarDecl
                value.move< VarDecl* > (YY_MOVE (s.value));
                break;

            case 53: // VarDef
                value.move< VarDef* > (YY_MOVE (s.value));
                break;

            case 52: // VarDefList
                value.move< VarDefList* > (YY_MOVE (s.value));
                break;

            case 16: // FLOATCONST
                value.move< float > (YY_MOVE (s.value));
                break;

            case 15: // INTCONST
                value.move< int > (YY_MOVE (s.value));
                break;

            case 13: // STRING
            case 14: // IDENTIFIER
                value.move< std::string > (YY_MOVE (s.value));
                break;

            default:
                break;
        }

        location = YY_MOVE (s.location);
    }

    // by_type.
    inline
    parser::by_type::by_type ()
            : type (empty_symbol)
    {}

#if 201103L <= YY_CPLUSPLUS
    inline
    parser::by_type::by_type (by_type&& that)
            : type (that.type)
    {
        that.clear ();
    }
#endif

    inline
    parser::by_type::by_type (const by_type& that)
            : type (that.type)
    {}

    inline
    parser::by_type::by_type (token_type t)
            : type (yytranslate_ (t))
    {}

    inline
    void
    parser::by_type::clear ()
    {
        type = empty_symbol;
    }

    inline
    void
    parser::by_type::move (by_type& that)
    {
        type = that.type;
        that.clear ();
    }

    inline
    int
    parser::by_type::type_get () const YY_NOEXCEPT
    {
        return type;
    }

} // yy
#line 3235 "parser.hh"





#endif // !YY_YY_PARSER_HH_INCLUDED
