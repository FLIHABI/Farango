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
%{

#include <iostream>
#include <sstream>
#include "parse.hh"

int comment_nest_level = 0;

#define YY_DECL yy::parser::symbol_type yylex()

typedef yy::parser::token token;

#define TOKEN(type) yy::parser::make_ ## type()
#define ABORT(msg)                      \
    do {                                \
        std::cerr << msg << std::endl;  \
        exit(2);                        \
    } while (0)

#define yyterminate() return TOKEN(END_OF_FILE)

%}

%option noyywrap
%option nounput

%x STRING_STATE
%x COMMENT_STATE
%x LINE_COMMENT_STATE

SPACE       [ \t]
INTEGER     ([0-9]+|0x[[:xdigit:]]+|0b[01]+)
DOUBLE      [0-9]+\.?[0-9]*(e[0-9]+)?
IDENTIFIER  [[:alpha:]_][[:alnum:]_]*
USER_OP     [!#$%&*+\-\/:<=>?@^|~]+
NEWLINE     \n\r|\r\n|\r|\n

%%

"\"" {
    BEGIN(STRING_STATE);
}
<STRING_STATE>
{
    "\\[\\\"vtrnfba]"    {}
    "\\".     { ABORT("Syntax error: string: invalid escaping"); }
    <<EOF>>   { ABORT("Syntax error: string: unterminated string"); }
    "\""      { BEGIN(INITIAL); return TOKEN(STRING); }
    NEWLINE   { ABORT("Syntax error: string: unexpected line feed"); }
    .         {}
}

"\/\*" {
    comment_nest_level = 1;
    BEGIN(COMMENT_STATE);
}
<COMMENT_STATE>
{
    "\/\*"   { ++comment_nest_level; }
    "\*\/"   { if (!--comment_nest_level) BEGIN(INITIAL); }
    <<EOF>>  { ABORT("Syntax error: comment: unterminated comment"); }
    NEWLINE  {}
    .        {}
}

"\/\/" { BEGIN(LINE_COMMENT_STATE); }
<LINE_COMMENT_STATE>
{
    <<EOF>>  { BEGIN(INITIAL); }
    NEWLINE  { BEGIN(INITIAL); }
    .        {}
}

"if"         { return TOKEN(IF);  }
"else"       { return TOKEN(ELSE); }
"while"      { return TOKEN(WHILE); }
"for"        { return TOKEN(FOR); }
"do"         { return TOKEN(DO); }
"in"         { return TOKEN(IN); }
"break"      { return TOKEN(BREAK); }
"continue"   { return TOKEN(CONTINUE); }
"fun"        { return TOKEN(FUNCTION); }
"type"       { return TOKEN(TYPE); }
"import"     { return TOKEN(IMPORT); }
"module"     { return TOKEN(MODULE); }
","          { return TOKEN(COMMA); }
":"          { return TOKEN(COLON); }
";"          { return TOKEN(SEMICOLON); }
"("          { return TOKEN(LPAREN); }
")"          { return TOKEN(RPAREN); }
"["          { return TOKEN(LSQUARE); }
"]"          { return TOKEN(RSQUARE); }
"{"          { return TOKEN(LBRACE); }
"}"          { return TOKEN(RBRACE); }
"."          { return TOKEN(DOT); }
"+"          { return TOKEN(PLUS); }
"-"          { return TOKEN(MINUS); }
"*"          { return TOKEN(MUL); }
"/"          { return TOKEN(DIV); }
"=="         { return TOKEN(EQUAL); }
"!="         { return TOKEN(NEQUAL); }
"&&"         { return TOKEN(LAND); }
"||"         { return TOKEN(LOR); }
"^"          { return TOKEN(XOR); }
"<"          { return TOKEN(LESS); }
"<="         { return TOKEN(LESS_EQ); }
">"          { return TOKEN(GREATER); }
">="         { return TOKEN(GREATER_EQ); }
"&"          { return TOKEN(AND); }
"|"          { return TOKEN(OR); }
"="          { return TOKEN(ASSIGN); }
{USER_OP}    { return TOKEN(USER_OP); }
{SPACE}      { }
{NEWLINE}    { }
{INTEGER}    { return TOKEN(INTEGER); }
{DOUBLE}     { return TOKEN(DOUBLE); }
{IDENTIFIER} { return TOKEN(IDENTIFIER);  }
.            { ABORT("Syntax error, unexpected token '" << yytext << "'"); }
%%