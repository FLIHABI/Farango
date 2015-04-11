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
%token <int>            INTEGER      "integer"
%token <misc::symbol>   IDENTIFIER   "ID"

/************************************************
 *                    TOKENS                    *
 ************************************************/

%token NEWLINE      "\n"

%token IF           "if"
%token ELSE         "else"
%token WHILE        "while"
%token FOR          "for"
%token DO           "do"
%token IN           "in"
%token BREAK        "break"
%token CONTINUE     "continue"
%token FUNCTION     "fun"
%token VAR          "var"
%token TYPE         "type"
%token IMPORT       "import"
%token MODULE       "module"

%token COMMA        ","
%token COLON        ":"
%token SEMICOLON    ";"
%token LPAREN       "("
%token RPAREN       ")"
%token LSQUARE      "["
%token RSQUARE      "]"
%token LBRACE       "{"
%token RBRACE       "}"
%token DOT          "."

%token PLUS         "+"
%token MINUS        "-"
%token MUL          "*"
%token DIV          "/"
%token EQUAL        "=="
%token NEQUAL       "!="
%token LESS         "<"
%token LESS_EQ      "<="
%token GREATER      ">"
%token GREATER_EQ   ">="
%token AND          "&"
%token OR           "|"
%token XOR          "^"
%token LOR          "&&"
%token LAND         "||"

%token BANG         "!"
%token TILDE        "~"

%token ASSIGN       "="

%token USER_OP      "USER_OP"
%token DOUBLE       "DOUBLE"

%token END_OF_FILE 0 "<EOF>"

%type <std::shared_ptr<ast::Exp>> expression
%type <std::shared_ptr<ast::Literal>> literal
%type <std::shared_ptr<ast::Number>> number
%type <std::shared_ptr<ast::Value>> value
%type <std::shared_ptr<ast::Lvalue>> lvalue member_access
%type <ast::Operator> operator
%type <std::shared_ptr<ast::Id>> identifier
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
%type <std::shared_ptr<ast::TypeIdentifier>> type_identifier
%type <std::vector<std::shared_ptr<ast::Id>>> generics_list generics_list_inner
%type <std::vector<ast::VarDec>> member_list proto_parameter_list proto_parameter_list_rec
%type <std::vector<ast::TypeIdentifier>> type_union
/************************************************
 *                  PRECEDENCE                  *
 ************************************************/

%left LOR
%left LAND
%nonassoc GREATER_EQ LESS_EQ EQUAL NEQUAL XOR GREATER LESS ASSIGN
%nonassoc THEN
%nonassoc ELSE
%left USER_OP
%left PLUS MINUS
%left OR
%left AND
%left MULT DIV
%left UMINUS UPLUS ULNOT UNOT

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

type_identifier /* ast exist */
    : identifier generics_list { $$ = std::make_shared<ast::TypeIdentifier>($1, $2);}
    ;

generics_list /* ast exist */
    : %empty {$$ = std::vector<std::shared_ptr<ast::Id>>();}
    | identifier {$$ = std::vector<std::shared_ptr<ast::Id>>(); $$.push_back($1); }
    | LPAREN generics_list_inner RPAREN { $$  = $2; }
    ;

generics_list_inner /* ast exist */
    : identifier {$$ = std::vector<std::shared_ptr<ast::Id>>(); $$.push_back($1); }
    | generics_list_inner COMMA identifier {$$ = $1; $1.push_back($3); }
    ;

type_decl
    : TYPE type_identifier ASSIGN LBRACE member_list RBRACE {$$ = std::make_shared<ast::TypeStruct>($2, $5); }
    | TYPE type_identifier ASSIGN type_union {$$ = std::make_shared<ast::TypeUnion>($2, $4); }
    | TYPE type_identifier {$$ = std::make_shared<ast::TypePrototype>($2); }
    ;

type_union
    : type_identifier { $$ = std::vector<ast::TypeIdentifier>(), $$.push_back(*$1); }
    | type_union OR type_identifier { $$ = $1, $$.push_back(*$3); }
    ;

typed_var /* ast exist */
    : identifier COLON type_identifier { $$ = std::make_shared<ast::VarDec>($1, $3); }
    ;

var_decl /* ast exist */
    : VAR typed_var { $$ = $2; $$->decl_set(true);}
    ;

member_list /* ast exist */
    : typed_var SEMICOLON { $$ = std::vector<ast::VarDec>(), $$.push_back(*$1); }
    | member_list typed_var SEMICOLON {$$ = $1; $$.push_back(*$2); }
    ;

value /* ast exist */
    : lvalue { $$ = $1;}
    | literal { $$ = $1;}
    | function_call { $$ = $1; }
    | LPAREN expression RPAREN { $$ = std::make_shared<ast::InnerExp>($2); }
    | LBRACE expression_list RBRACE {$$ = std::make_shared<ast::ExpListInner>(*$2); }
    ;
/*
   | LPAREN operator RPAREN //FIXME: Not in ast
*/

//Warning, can't do foo().toto
member_access /* ast exist */
    : value DOT identifier  {$$ = std::make_shared<ast::MemberAccess>($1, $3); }
    ;

function_call /* ast exist */
    : value LPAREN parameter_list RPAREN { $$ = std::make_shared<ast::FunCall>($1, $3);}
    ;

operator /* ast exist */
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
    ;

//| USER_OP /* FIXME */


lvalue /* ast exist */
    : member_access { $$ = $1; }
    | identifier { $$ = std::make_shared<ast::Lvalue>($1); }
    ;

expression
    : value { $$ = $1; }
    | value operator expression { $$ = std::make_shared<ast::BinaryExp>($1, $2, $3); }
    | lvalue ASSIGN expression { $$ = std::make_shared<ast::AssignExp>($1, $3); }
    | declaration { $$ = $1; }
    | BANG expression %prec ULNOT { $$ = std::make_shared<ast::UnaryExp>(ast::Operator::BANG, $2); }
    | TILDE expression %prec UNOT { $$ = std::make_shared<ast::UnaryExp>(ast::Operator::TILDE, $2); }
    | MINUS expression %prec UMINUS { $$ = std::make_shared<ast::UnaryExp>(ast::Operator::MINUS, $2); }
    | PLUS expression %prec UPLUS { $$ = std::make_shared<ast::UnaryExp>(ast::Operator::PLUS, $2); }
/*  FIXME
    | USER_OP expression
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

func_prototype /* ast exist */
    : FUNCTION identifier LPAREN proto_parameter_list RPAREN COLON type_identifier
        {
            $$ = std::make_shared<ast::FunctionPrototype>($2, $4, $7);
        }
    | FUNCTION identifier LPAREN proto_parameter_list RPAREN
        {
            $$ = std::make_shared<ast::FunctionPrototype>($2, $4, nullptr);
        }
    ;

func_decl /* ast exist */
    : func_prototype ASSIGN expression { $$ = std::make_shared<ast::FunctionDec>(*$1, $3); }
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
    : WHILE LPAREN expression RPAREN expression { $$ = std::make_shared<ast::WhileExp>($3, $5); }
    ;

do_expr /* ast exist */
    : DO expression WHILE LPAREN expression RPAREN { $$ = std::make_shared<ast::DoExp>($5, $2); }
    ;

for_expr
    : FOR LPAREN expression SEMICOLON expression SEMICOLON expression RPAREN expression
        {
            $$ = std::make_shared<ast::ForExp>($3, $5, $7, $9);
        }
    ;
/*
FIXMME
    | FOR LPAREN identifier IN expression RPAREN expression
*/

%%
