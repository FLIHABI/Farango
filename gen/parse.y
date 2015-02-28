%require "3.0.2"
%skeleton "lalr1.cc"
%expect 0
%error-verbose
%defines

%define api.token.prefix {TOK_}
%define api.token.constructor
%define api.value.type variant

%code
{
    #include <iostream>
    #include <cstdio>
    #include <cstdlib>

    yy::parser::symbol_type yylex();
    extern FILE* yyin;
}

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
%token INTEGER      "INTEGER"
%token DOUBLE       "DOUBLE"
%token STRING       "string"

%token IDENTIFIER   "IDENTIFIER"

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
%left UMINUS UPLUS

%start program

/************************************************
 *                    GRAMMAR                   *
 ************************************************/

%%

program
    : MODULE module_identifier SEMICOLON expression_list

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

expression_list
    : %empty
    | expression SEMICOLON expression_list
    ;

identifier : IDENTIFIER { };

literal
    : number
    | STRING {}
    ;

number
    : INTEGER
    | DOUBLE
    ;

type_decl
    : TYPE LBRACE member_list RBRACE {};

var_decl
    : identifier identifier

member_list
    : var_decl
    | member_list SEMICOLON var_decl
    ;

value
    : identifier
    | literal
    | member_access
    | function_call
    | LPAREN expression RPAREN
    | LPAREN operator RPAREN
    | LBRACE expression_list RBRACE
    ;

member_access : value DOT identifier
function_call : value LPAREN parameter_list RPAREN

binary_op
    : PLUS
    | MINUS
    | MUL
    | DIV
    | EQUAL
    | NEQUAL
    | AND
    | OR
    | XOR
    | LAND
    | LOR
    | GREATER
    | GREATER_EQ
    | LESS
    | LESS_EQ
    | USER_OP
    | ASSIGN
    ;

unary_op : BANG
         | TILDE
         | USER_OP
         ;

operator : binary_op | BANG | TILDE;

expression : value r_exp
           | declaration
           | unary_op expression
           | MINUS expression %prec UMINUS
           | PLUS expression %prec UPLUS
           | IMPORT import_identifier
           | if_expr
           | while_expr
           | for_expr
           ;

r_exp : %empty | binary_op expression;

parameter_list
    : %empty
    | expression
    | parameter_list COMMA expression
    ;

func_prototype
    : FUNCTION identifier LPAREN parameter_list RPAREN
    ;

func_decl
    : func_prototype ASSIGN expression
    ;

declaration
    : type_decl
    | func_decl
    ;

if_expr
    : IF LPAREN expression RPAREN expression %prec THEN
    | IF LPAREN expression RPAREN expression ELSE expression;

while_expr
    : WHILE LPAREN expression RPAREN expression

for_expr
    : FOR LPAREN expression SEMICOLON expression SEMICOLON expression RPAREN expression
    | FOR LPAREN identifier IN expression RPAREN expression
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
    yy::parser parser;
    if (argc > 1)
        yyin = fopen(argv[1], "r");
    parser.set_debug_level(1);
    parser.parse();
}
