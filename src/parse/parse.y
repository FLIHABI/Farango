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
    : MODULE module_identifier SEMICOLON expression_list
    | expression_list //Hack
    ;

import_identifier
    : dot_sequence module_identifier
    | module_identifier
    ;

dot_sequence
    : DOT
    | DOT dot_sequence
    ;

module_identifier
    : identifier
    | identifier DOT module_identifier
    ;

expression_list /* ast exist */
    : %empty /* ast exist */
    | expression_list_rec /* ast exist */
    ;

expression_list_rec /* ast exist */
    : expression SEMICOLON /* ast exist */
    | expression_list_rec expression SEMICOLON /* ast exist */
    ;

identifier
    : IDENTIFIER {} /* ast exist */
    ;

literal /* ast exist */
    : number /* ast exist */
    | STRING {}
    ;

number /* ast exist */
    : INTEGER {}/* ast exist */
    | DOUBLE
    ;

type_identifier /* ast exist */
    : identifier generics_list /* ast exist */
    ;

generics_list /* ast exist */
    : %empty /* ast exist */
    | identifier /* ast exist */
    | LPAREN generics_list_inner RPAREN /* ast exist */
    ;

generics_list_inner /* ast exist */
    : identifier /* ast exist */
    | generics_list_inner COMMA identifier /* ast exist */
    ;

type_decl
    : TYPE type_identifier ASSIGN LBRACE member_list RBRACE /* ast exist */
    | TYPE type_identifier ASSIGN type_union /* ast exist */
    | TYPE type_identifier /* ast exist */
    ;

type_union
    : type_identifier /* ast exist */
    | type_union OR type_identifier /* ast exist */
    ;

typed_var /* ast exist */
    : identifier COLON type_identifier /* ast exist */
    ;

var_decl /* ast exist */
    : VAR typed_var /* ast exist */
    ;

member_list /* ast exist */
    : typed_var SEMICOLON /* ast exist */
    | member_list typed_var SEMICOLON /* ast exist */
    ;

value /* ast exist */
    : lvalue /* ast exist */
    | literal /* ast exist */
    | function_call /* ast exist */
    | LPAREN expression RPAREN /* ast exist */
    | LPAREN operator RPAREN /* ast exist */
    | LBRACE expression_list RBRACE /* ast exist */
    ;

//Warning, can't do foo().toto
member_access /* ast exist */
    : value DOT identifier  /* ast exist */
    ;

function_call /* ast exist */
    : value LPAREN parameter_list RPAREN /* ast exist */
    ;

operator /* ast exist */
    : PLUS /* ast exist */
    | MINUS /* ast exist */
    | MUL /* ast exist */
    | DIV /* ast exist */
    | EQUAL /* ast exist */
    | NEQUAL /* ast exist */
    | AND /* ast exist */
    | OR /* ast exist */
    | XOR /* ast exist */
    | LAND /* ast exist */
    | LOR /* ast exist */
    | GREATER /* ast exist */
    | GREATER_EQ /* ast exist */
    | LESS /* ast exist */
    | LESS_EQ /* ast exist */
    | BANG /* ast exist */
    | TILDE /* ast exist */
    ;

//| USER_OP /* FIXME */


lvalue /* ast exist */
    : member_access /* ast exist */
    | identifier /* ast exist */
    ;

expression
    : value /* ast exist */
    | value operator expression /* ast exist */
    | lvalue ASSIGN expression /* ast exist */
    | declaration /* ast exist */
    | USER_OP expression /* FIXME */
    | BANG expression %prec ULNOT /* ast exist */
    | TILDE expression %prec UNOT /* ast exist */
    | MINUS expression %prec UMINUS /* ast exist */
    | PLUS expression %prec UPLUS /* ast exist */
    | IMPORT import_identifier
    | if_expr /* ast exist */
    | while_expr /* ast exist */
    | do_expr /* ast exist */
    | for_expr
    ;

/*
r_exp
    : %empty | operator expression
    ;
*/

parameter_list /* ast exist */
    : %empty /* ast exist */
    | parameter_list_rec /* ast exist */
    ;

parameter_list_rec /* ast exist */
    : expression /* ast exist */
    | parameter_list_rec COMMA expression /* ast exist */
    ;

proto_parameter_list /* ast exist */
    : %empty /* ast exist */
    | proto_parameter_list_rec /* ast exist */
    ;

proto_parameter_list_rec /* ast exist */
    : typed_var /* ast exist */
    | proto_parameter_list_rec COMMA typed_var /* ast exist */
    ;

func_prototype /* ast exist */
    : FUNCTION identifier LPAREN proto_parameter_list RPAREN /* ast exist */
    ;

func_decl /* ast exist */
    : func_prototype ASSIGN expression /* ast exist */
    ;

declaration
    : type_decl /* ast exist */
    | var_decl /* ast exist */
    | func_decl /* ast exist */
    ;

if_expr/* ast exist */
    : IF LPAREN expression RPAREN expression %prec THEN /* ast exist */
    | IF LPAREN expression RPAREN expression ELSE expression/* ast exist */
    ;

while_expr /* ast exist */
    : WHILE LPAREN expression RPAREN expression /* ast exist */
    ;

do_expr /* ast exist */
    : DO expression WHILE LPAREN expression RPAREN /* ast exist */
    ;

for_expr
    : FOR LPAREN expression SEMICOLON expression SEMICOLON expression RPAREN expression /* ast exist */
    | FOR LPAREN identifier IN expression RPAREN expression /* Will disapear*/
    ;

%%

/*
** FUNCTIONS
*/

void yy::parser::error(const std::string& msg) {
    std::cerr << msg << std::endl;
    exit(3);
}

int main (int argc, char **argv) {
    parse::FgcParser fp;
    FILE* in = stdin;
    if (argc > 1)
        in = fopen(argv[1], "r");
    fp.parse(in);
}
