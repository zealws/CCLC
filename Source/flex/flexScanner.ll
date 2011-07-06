%{

// C and C++ libraries
#include <iostream>
#include <limits.h>
#include <cstdlib>
#include <string.h>

// for parser.hpp to work correctly
#include "../typeTree/typeTree.h"
#include "../programTree/programTree.h"
#include "../Library/orderedPair.h"
#include "../programTree/syntaxTree.h"

// for yylval and the token definitions
#include "../bison/parser.hpp"

// for the error module
#include "../error/error.h"

// for the integer conversion function
#include "../strconv/strconv.h"

using namespace std;

%}

%option noyywrap
%option yylineno

%%

fun                         { return funType; }

endfun                      { return funEnding; }

while                       { return whileStart; }

do                          { return whileDo; }

endwhile                    { return whileEnding; }

if                          { return ifStart; }

then                        { return ifThen; }

else                        { return ifElse; }

endif                       { return ifEnding; }

control                     { return controlStart; }

endcontrol                  { return controlEnding; }
    
vars                        { return varsStart; }

endvars                     { return varsEnding; }

in                          { return inSeparator; }

"("                         { return openParen; }

")"                         { return closeParen; }

"["                         { return openBracket; }

"]"                         { return closeBracket; }

","                         { return comma; }

";"                         { return semicolon; }

"?"                         { return trivLiteral; }
    
immut                       { return immutableQualification; }

triv                        { return trivType; }

int                         { return intType; }

ref                         { return refType; }

vec                         { return vectorType; }

con                         { return conType; }

continues                   { return continuesOperation; }

":="                        { return assignmentOperation; }

"="                         { return eqOperation; }

"<>"                        { return neqOperation; }

"<="                        { return leqOperation; }

"<"                         { return lessOperation; }

">="                        { return geqOperation; }

">"                         { return greaterOperation; }

"+"                         { return sumOperation; }

"-"                         { return diffOperation; }

"*"                         { return productOperation; }

"/"                         { return divideOperation; }

input                       { return inputOperation; }

output                      { return outputOperation; }

"#"                         { return vecSizeOperation; }

"&"                         { return refOperation; }

"@"                         { return derefOperation; }

[_a-zA-Z]([_a-zA-Z0-9]*)    {
                                // set the yylval's string literal
                                // to the identifier literal
                                yylval.characterArray = YYText();
                                return stringLiteral;
                            }

[0-9]*                      {
                                int v;
                                if(overflow(YYText(), YYLeng(), v))
                                    forceError("integer literal overflow");
                                else {
                                    yylval.integerValue = v;
                                }
                                return decimalLiteral;
                            }

!.*|\ |\t|\n                { ; }

.                           {
                                // Set the yylval's string member
                                // to our illegal character
                                yylval.characterArray = YYText();
                                return illegalCharacter;
                            }

%%
