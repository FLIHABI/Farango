//%
/* This file is part of Farango.
 *
 * Copyright (c) 2015 FLIHABI.
 *
 * Farango is licensed under the FLIHABI License Version 1.
 *
 * Farango is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * In addition, 180 days after any changes are published, you can use the
 * software, incorporating those changes, under the terms of the MIT license,
 * as described in the FLIHABI License Version 1.
 *
 * Farango is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License,
 * the MIT license and the FLIHABI License Version 1 along with this program.
 * If not, see <http://www.gnu.org/licenses/> for the GNU Lesser General Public
 * License and see <http://goo.gl/t8dfl6> for the full license, including
 * the MIT license.
 */
%require "3.0.2"
%skeleton "lalr1.cc"
%expect 0
%error-verbose
%defines
%locations

%define api.token.prefix {TOK_}
%define api.token.constructor
%define api.value.type variant

%param { parse::FgcParser& fp}

%code requires
{
    #include <iostream>
    #include <cstdio>
    #include <cstdlib>
    #include <memory>

    #include "parse/fgc_parser.hh"
    #include "lib/symbol.hh"
    #include "ast/all.hh"
    #include "ast/default_visitor.hh"
    #include "ast/pretty_print.hh"
    #include "lib/symbol.hh"
}

%code provides
{
    yy::parser::symbol_type yylex(parse::FgcParser& fp);
    extern FILE* yyin;
}

%token <std::string>    STRING       "string"
%token <misc::symbol>   USER_OP      "user_op"
%token <int>            INTEGER      "integer"
%token <misc::symbol>   IDENTIFIER   "ID"

/************************************************
 *                    TOKENS                    *
 ************************************************/

%token NEWLINE      "\n"
 IF           "if"
 ELSE         "else"
 WHILE        "while"
 FOR          "for"
 DO           "do"
 IN           "in"
 BREAK        "break"
 CONTINUE     "continue"
 NEW          "new"
 ARRAY        "array"
 FUNCTION     "fun"
 VAR          "var"
 TYPE         "type"
 IMPORT       "import"
 MODULE       "module"
 OFFER        "offer"
 GET          "get"
 COMMA        ","
 COLON        ":"
 DCOLON       "::<"
 SEMICOLON    ";"
 LPAREN       "("
 RPAREN       ")"
 LSQUARE      "["
 RSQUARE      "]"
 LBRACE       "{"
 RBRACE       "}"
 DOT          "."
 PLUS         "+"
 MINUS        "-"
 MUL          "*"
 DIV          "/"
 MODULO       "%"
 EQUAL        "=="
 NEQUAL       "!="
 LESS         "<"
 LESS_EQ      "<="
 GREATER      ">"
 GREATER_EQ   ">="
 AND          "&"
 OR           "|"
 XOR          "^"
 LOR          "||"
 LAND         "&&"
 BANG         "!"
 TILDE        "~"
 LSHIFT       "<<"
 RSHIFT       ">>"
 ASSIGN       "="
 DOUBLE       "DOUBLE"
 END_OF_FILE 0 "<EOF>"

%type <std::shared_ptr<ast::Exp>> expression
%type <std::shared_ptr<ast::Literal>> literal
%type <std::shared_ptr<ast::Number>> number
%type <std::shared_ptr<ast::Value>> value binop
%type <std::shared_ptr<ast::Value>> lvalue member_access array_access
//%type <ast::Operator> operator
%type <std::shared_ptr<ast::Id>> identifier func_identifier
%type <std::shared_ptr<ast::ExpList>> expression_list expression_list_rec parameter_list parameter_list_rec
%type <std::shared_ptr<ast::FunCall>> function_call
%type <std::shared_ptr<ast::IfExp>> if_expr
%type <std::shared_ptr<ast::DoExp>> do_expr
%type <std::shared_ptr<ast::WhileExp>> while_expr
%type <std::shared_ptr<ast::ForExp>> for_expr
%type <std::shared_ptr<ast::Declaration>> declaration
%type <std::shared_ptr<ast::TypePrototype>> type_decl
%type <std::shared_ptr<ast::VarDec>> var_decl typed_var
%type <std::shared_ptr<ast::FunctionPrototype>> func_decl func_prototype
%type <std::shared_ptr<ast::TypeIdentifierUse>> type_identifier_use type_allocation aux_use
%type <std::shared_ptr<ast::TypeArrayIdentifier>> array_identifier array_identifier_allocation
%type <std::shared_ptr<ast::TypeIdentifierDec>> type_identifier_dec
%type <std::vector<std::shared_ptr<ast::TypeIdentifierUse>>> function_use_generics_list generics_list_use generics_list_inner_use
%type <std::vector<std::shared_ptr<ast::Declaration>>> generics_list_dec generics_list_inner_dec function_def_generics_list
%type <std::vector<ast::VarDec>> member_list proto_parameter_list proto_parameter_list_rec
%type <std::vector<ast::TypeIdentifierUse>> type_union
/************************************************
 *                  PRECEDENCE                  *
 ************************************************/

%nonassoc THEN
%nonassoc ELSE
%precedence WHILER FORR

%left ASSIGN

%left LOR
%left LAND
%nonassoc GREATER_EQ LESS_EQ EQUAL NEQUAL XOR GREATER LESS

%left PLUS MINUS
%left OR
%left AND
%left MUL DIV
%left LSHIFT RSHIFT
%left USER_OP
%left UMINUS UPLUS ULNOT UNOT UUSER_OP

%start program

/************************************************
 *                    GRAMMAR                   *
 ************************************************/

%%

program
    : MODULE module_identifier SEMICOLON expression_list {fp.ast_ = $4;}
    | expression_list {fp.ast_ = $1;}
    ;

/* FIXME
import_identifier
    : dot_sequence module_identifier
    | module_identifier
    ;

dot_sequence
    : DOT
    | DOT dot_sequence
    ;
*/

module_identifier
    : identifier
    | identifier DOT module_identifier
    ;

expression_list /* ast exist */
    : %empty {$$ = std::make_shared<ast::ExpList>();}
    | expression_list_rec {$$ = $1;}
    ;

expression_list_rec /* ast exist */
    : expression SEMICOLON { $$ = std::make_shared<ast::ExpList>(); $$->push($1); }
    | expression_list_rec expression SEMICOLON { $$ = $1; $$->push($2); }
    ;

identifier
    : IDENTIFIER { $$ = std::make_shared<ast::Id>($1);} /* ast exist */
    ;

literal /* ast exist */
    : number { $$ = $1; }
    | STRING { $$ = std::make_shared<ast::String>($1); }
    ;

number /* ast exist */
    : INTEGER { $$ = std::make_shared<ast::Int>($1); }
    | DOUBLE { $$ = std::make_shared<ast::Int>(-1); } /* FIXME */
    ;

/* */
type_identifier_dec /* ast exist */
    : identifier generics_list_dec { $$ = std::make_shared<ast::TypeIdentifierDec>($1, $2);}
    ;

generics_list_dec /* ast exist */
    : %empty {$$ = std::vector<std::shared_ptr<ast::Declaration>>();}
    | identifier {$$ = std::vector<std::shared_ptr<ast::Declaration>>(); $$.push_back(std::make_shared<ast::Declaration>($1)); }
    | LPAREN generics_list_inner_dec RPAREN { $$ = $2; }
    ;

generics_list_inner_dec /* ast exist */
    : identifier {$$ = std::vector<std::shared_ptr<ast::Declaration>>(); $$.push_back(std::make_shared<ast::Declaration>($1)); }
    | generics_list_inner_dec COMMA identifier {$$ = $1; $$.push_back(std::make_shared<ast::Declaration>($3)); }
    ;
/* */

aux_use
    : identifier generics_list_use { $$ = std::make_shared<ast::TypeIdentifierUse>($1, $2); }
    ;

array_identifier
    : identifier generics_list_use LSQUARE RSQUARE {$$ = std::make_shared<ast::TypeArrayIdentifier>(*std::make_shared<ast::TypeIdentifierUse>($1, $2)); }
    | array_identifier LSQUARE RSQUARE {$$ = $1; $$->depth_set($$->depth_get() + 1); }
    ;

/* */
type_identifier_use /* ast exist */
    : aux_use { $$ = $1;}
    | array_identifier { $$ = $1; }
    ;

generics_list_use /* ast exist */
    : %empty {$$ = std::vector<std::shared_ptr<ast::TypeIdentifierUse>>();}
/*
    | type_identifier_use
    {
        $$ = std::vector<std::shared_ptr<ast::TypeIdentifierUse>>();
        $$.push_back($1);
    }
*/
    | LPAREN generics_list_inner_use RPAREN { $$ = $2; }
    ;

generics_list_inner_use /* ast exist */
    : type_identifier_use
    {
        $$ = std::vector<std::shared_ptr<ast::TypeIdentifierUse>>();
        $$.push_back($1);
    }
    | generics_list_inner_use COMMA type_identifier_use
    {
        $$ = $1;
        $$.push_back($3);
    }
    ;

type_decl
    : TYPE type_identifier_dec ASSIGN LBRACE member_list RBRACE {$$ = std::make_shared<ast::TypeStruct>($2, $5); }
    | TYPE type_identifier_dec ASSIGN LBRACE RBRACE {$$ = std::make_shared<ast::TypeStruct>($2, std::vector<ast::VarDec>()); }
    | TYPE type_identifier_dec ASSIGN type_union {$$ = std::make_shared<ast::TypeUnion>($2, $4); }
    | TYPE type_identifier_dec {$$ = std::make_shared<ast::TypePrototype>($2); }
    ;

/* FIXME: refactor in : identifier type_identifier_use  */
type_union
    : type_identifier_use { $$ = std::vector<ast::TypeIdentifierUse>(), $$.push_back(*$1); }
    | type_union OR type_identifier_use { $$ = $1, $$.push_back(*$3); }
    ;

typed_var /* ast exist */
    : identifier COLON type_identifier_use { $$ = std::make_shared<ast::VarDec>($1, $3); }
    | identifier
    {
        std::shared_ptr<ast::TypeIdentifierUse> tiu = std::make_shared<ast::AutoTypeIdentifier>();
        $$ = std::make_shared<ast::VarDec>($1, tiu);
    }
    ;

var_decl /* ast exist */
    : VAR typed_var { $$ = $2; $$->decl_set(true);}
    | VAR typed_var ASSIGN expression { $$ = std::make_shared<ast::VarAssign>($2, $4);}
    ;

member_list /* ast exist */
    : typed_var SEMICOLON { $$ = std::vector<ast::VarDec>(), $$.push_back(*$1); }
    | member_list typed_var SEMICOLON {$$ = $1; $$.push_back(*$2); }
    ;

value /* ast exist */
    : lvalue { $$ = $1;}
    | type_allocation { $$ = std::make_shared<ast::NewExp>($1); }
    | literal { $$ = $1;}
    | function_call { $$ = $1; }
    | LPAREN expression RPAREN { $$ = std::make_shared<ast::InnerExp>($2); }
    | LBRACE expression_list RBRACE {$$ = std::make_shared<ast::ExpListInner>(*$2); }
    | OFFER LPAREN function_call RPAREN { $$ = std::make_shared<ast::OfferExp>($3); }
    | GET LPAREN value RPAREN { $$ = std::make_shared<ast::GetExp>($3); }
    ;
/*
   | LPAREN operator RPAREN //FIXME: Not in ast
*/
array_identifier_allocation
    : identifier generics_list_use LSQUARE expression RSQUARE {$$ = std::make_shared<ast::TypeArrayIdentifier>(*std::make_shared<ast::TypeIdentifierUse>($1, $2)); $$->size_set($4); }
    | array_identifier_allocation LSQUARE RSQUARE {$$ = $1; $$->depth_set($$->depth_get() + 1); }
    ;

type_allocation
    : NEW LPAREN aux_use RPAREN { $$ = $3;}
    | NEW LPAREN array_identifier_allocation RPAREN{ $$ = $3; }
    ;

member_access /* ast exist */
    : value DOT identifier  {$$ = std::make_shared<ast::MemberAccess>($1, $3); }
    ;

array_access
    : value LSQUARE expression RSQUARE { $$ = std::make_shared<ast::ArrayAccess>($1, $3);}
    ;

function_use_generics_list
    : %empty {}
    | DCOLON generics_list_inner_use GREATER { $$ = $2; }
    ;

function_call /* ast exist */
    : value function_use_generics_list LPAREN parameter_list RPAREN { $$ = std::make_shared<ast::FunCall>($1, $2, std::make_shared<ast::ExpListFunction>(*$4));}
    ;

/*
operator
    : PLUS { $$ = ast::Operator::PLUS; }
    | MINUS { $$ = ast::Operator::MINUS; }
    | MUL { $$ = ast::Operator::MUL; }
    | DIV  { $$ = ast::Operator::DIV; }
    | EQUAL { $$ = ast::Operator::EQUAL; }
    | NEQUAL { $$ = ast::Operator::NEQUAL; }
    | AND { $$ = ast::Operator::AND; }
    | OR { $$ = ast::Operator::OR; }
    | XOR { $$ = ast::Operator::XOR; }
    | LAND { $$ = ast::Operator::LAND; }
    | LOR { $$ = ast::Operator::LOR; }
    | GREATER { $$ = ast::Operator::GREATER; }
    | GREATER_EQ { $$ = ast::Operator::GREATER_EQ; }
    | LESS { $$ = ast::Operator::LESS; }
    | LESS_EQ { $$ = ast::Operator::LESS_EQ; }
    | BANG { $$ = ast::Operator::BANG; }
    | TILDE { $$ = ast::Operator::TILDE; }
    | LSHIFT { $$ = ast::Operator::LSHIFT; }
    | RSHIFT { $$ = ast::Operator::RSHIFT; }
    ;
*/

binop
    : expression PLUS expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::PLUS, $3); }
    | expression MINUS expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::MINUS, $3); }
    | expression MUL expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::MUL, $3); }
    | expression DIV expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::DIV, $3); }
    | expression EQUAL expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::EQUAL, $3); }
    | expression NEQUAL expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::NEQUAL, $3); }
    | expression AND expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::AND, $3); }
    | expression OR expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::OR, $3); }
    | expression XOR expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::XOR, $3); }
    | expression LAND expression
    {
        std::shared_ptr<ast::ExpListInner> el = std::make_shared<ast::ExpListInner>();
        std::shared_ptr<ast::Exp> body = std::make_shared<ast::Int>(0);
        std::shared_ptr<ast::IfExp> if_ = std::make_shared<ast::IfExp>($1, $3, body);
        el->push(if_);
        $$ = el;
    }
    | expression LOR expression
    {
        std::shared_ptr<ast::ExpListInner> el = std::make_shared<ast::ExpListInner>();
        std::shared_ptr<ast::Exp> body = std::make_shared<ast::Int>(1);
        std::shared_ptr<ast::IfExp> if_ = std::make_shared<ast::IfExp>($1, body, $3);
        el->push(if_);
        $$ = el;
    }
    | expression GREATER expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::GREATER, $3); }
    | expression GREATER_EQ expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::GREATER_EQ, $3); }
    | expression LESS expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::LESS, $3); }
    | expression LESS_EQ expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::LESS_EQ, $3); }
    | expression LSHIFT expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::LSHIFT, $3); }
    | expression RSHIFT expression { $$ = std::make_shared<ast::BinaryExp>($1, ast::Operator::RSHIFT, $3); }
    | expression USER_OP expression
    {
        std::shared_ptr<ast::Value> op = std::make_shared<ast::Lvalue>($2);
        std::vector<std::shared_ptr<ast::TypeIdentifierUse>> empty;
        std::shared_ptr<ast::ExpListFunction> params = std::make_shared<ast::ExpListFunction>();
        params->push($1);
        params->push($3);
        $$ = std::make_shared<ast::FunCall>(op, empty, params);
    }
    ;

lvalue /* ast exist */
    : member_access { $$ = $1; }
    | func_identifier { $$ = std::make_shared<ast::Lvalue>($1); }
    | identifier identifier { $$ = std::make_shared<ast::Lvalue>($1); }
    | array_access { $$ = $1; }
    ;

expression
    : value { $$ = $1; }
    | lvalue ASSIGN expression { $$ = std::make_shared<ast::AssignExp>($1, $3); }
    | declaration { $$ = $1; }
    | BREAK { $$ = std::make_shared<ast::BreakExp>(); }
    | CONTINUE { $$ = std::make_shared<ast::ContinueExp>(); }
    | binop { $$ = $1; }
    | BANG expression %prec ULNOT { $$ = std::make_shared<ast::UnaryExp>(ast::Operator::BANG, $2); }
    | TILDE expression %prec UNOT { $$ = std::make_shared<ast::UnaryExp>(ast::Operator::TILDE, $2); }
    | MINUS expression %prec UMINUS { $$ = std::make_shared<ast::UnaryExp>(ast::Operator::MINUS, $2); }
    | PLUS expression %prec UPLUS { $$ = std::make_shared<ast::UnaryExp>(ast::Operator::PLUS, $2); }
    | USER_OP expression %prec UUSER_OP
    {
        std::shared_ptr<ast::Value> op = std::make_shared<ast::Lvalue>($1);
        std::vector<std::shared_ptr<ast::TypeIdentifierUse>> empty;
        std::shared_ptr<ast::ExpListFunction> params = std::make_shared<ast::ExpListFunction>();
        params->push($2);
        $$ = std::make_shared<ast::FunCall>(op, empty, params);
    }
/*  FIXME
    | IMPORT import_identifier
*/
    | if_expr { $$ = $1; }
    | while_expr { $$ = $1; }
    | do_expr { $$ = $1; }
    | for_expr { $$ = $1; }
    ;

/*
r_exp
    : %empty | operator expression
    ;
*/

parameter_list /* ast exist */
    : %empty {$$ = std::make_shared<ast::ExpListFunction>();}
    | parameter_list_rec {$$ = $1;}
    ;

parameter_list_rec /* ast exist */
    : expression {$$ = std::make_shared<ast::ExpListFunction>(); $$->push($1); }
    | parameter_list_rec COMMA expression {$$ = $1; $$->push($3); }
    ;

proto_parameter_list /* ast exist */
    : %empty { $$ = std::vector<ast::VarDec>(); }
    | proto_parameter_list_rec {$$ = $1; }
    ;

proto_parameter_list_rec /* ast exist */
    : typed_var { $$ = std::vector<ast::VarDec>(); $$.push_back(*$1);}
    | proto_parameter_list_rec COMMA typed_var  { $$ = $1; $$.push_back(*$3);}
    ;

function_def_generics_list
    : %empty {$$ = std::vector<std::shared_ptr<ast::Declaration>>();}
    | LESS generics_list_inner_dec GREATER { $$ = $2; }
    ;

func_identifier
    : identifier { $$ = $1; }
    | LPAREN USER_OP RPAREN { $$ = std::make_shared<ast::Id>($2); }
    ;

func_prototype /* ast exist */
    : FUNCTION func_identifier function_def_generics_list LPAREN proto_parameter_list RPAREN COLON type_identifier_use
        {
            $$ = std::make_shared<ast::FunctionPrototype>($2, $3, $5, $8);
        }
    | FUNCTION func_identifier function_def_generics_list LPAREN proto_parameter_list RPAREN
        {
            std::shared_ptr<ast::TypeIdentifierUse> tiu = std::make_shared<ast::AutoTypeIdentifier>();
            $$ = std::make_shared<ast::FunctionPrototype>($2, $3, $5, tiu);
        }
    ;

func_decl /* ast exist */
    : func_prototype ASSIGN expression { $$ = std::make_shared<ast::FunctionDec>($1, $3); }
    | func_prototype { $$ = $1; }
    ;

declaration
    : type_decl { $$ = $1; }
    | var_decl  { $$ = $1; }
    | func_decl { $$ = $1; }
    ;

if_expr/* ast exist */
    : IF LPAREN expression RPAREN expression %prec THEN { $$ = std::make_shared<ast::IfExp>($3, $5, nullptr); }
    | IF LPAREN expression RPAREN expression ELSE expression { $$ = std::make_shared<ast::IfExp>($3, $5, $7); }
    ;

while_expr /* ast exist */
    : WHILE LPAREN expression RPAREN expression %prec WHILER { $$ = std::make_shared<ast::WhileExp>($3, $5); }
    ;

do_expr /* ast exist */
    : DO expression WHILE LPAREN expression RPAREN { $$ = std::make_shared<ast::DoExp>($5, $2); }
    ;

for_expr
    : FOR LPAREN expression SEMICOLON expression SEMICOLON expression RPAREN expression %prec FORR
        {
            $$ = std::make_shared<ast::ForExp>($3, $5, $7, $9);
        }
    ;
/*
FIXMME
    | FOR LPAREN identifier IN expression RPAREN expression
*/

%%

void yy::parser::error(const location_type& l, const std::string& msg) {
    std::cerr << l << std::endl;
    std::cerr << msg << std::endl;
    exit(3);
}
