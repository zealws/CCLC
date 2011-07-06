%{
#include <iostream>
#include <FlexLexer.h>
#include <sstream>
#include <cstdlib>
#include "../error/error.h"
#include "../scanner/scanner.h"
#include "../symbolTable/symbolTable.h"
#include "../symbolTable/symbolTableDeclaration.h"
#include "../options/options.h"
#include "../programTree/programTree.h"
#include "../programTree/programTreeVisitors.h"
#include "../programTree/syntaxTree.h"
#include "../typeTree/typeTree.h"
#include "../typeTree/typeTreeVisitors.h"
#include "../Library/orderedPair.h"
using namespace std;

// defined further down this file
int yylex();

programTree* programErrorValue = new programError();
typeTree* typeErrorValue = new intTypeTree();

static const programTypePair
    errorPair(programErrorValue,
            typeErrorValue);

// extracts a list of program trees
vector<programTree*> extractProgramList(vector<programTypePair>& pairVec);

// extracts a list of type trees
vector<typeTree*> extractTypeList(vector<programTypePair>& pairVec);

%}

%union {
    // a thirty-two bit signed integer literal value
    int integerValue;
    // a C string array of arbitrary length
    const char* characterArray;
    // program pointer
    programTree* program;
    // type pointer
    typeTree* type;
    // program type pair
    orderedPair<programTree*, typeTree*> pair;
    // list of type trees
    vector<typeTree*> typeList;
    // list of program trees
    vector<programTree*> programList;
    // list of ordered pairs
    vector<orderedPair<programTree*, typeTree*> > pairList;
    // list of expression sequences
    vector<vector<programTree*> > programListList;
}

%token funType
%token funEnding
%token whileStart
%token whileDo
%token whileEnding
%token ifStart
%token ifThen
%token ifElse
%token ifEnding
%token controlStart
%token controlEnding
%token varsStart
%token varsEnding
%token inSeparator
%token openParen
%token closeParen
%token openBracket
%token closeBracket
%token comma
%token semicolon
%token trivLiteral
%token immutableQualification
%token trivType
%token intType
%token refType
%token vectorType
%token conType
%token continuesOperation
%token assignmentOperation
%token eqOperation
%token neqOperation
%token leqOperation
%token lessOperation
%token geqOperation
%token greaterOperation
%token sumOperation
%token plusOperation
%token diffOperation
%token negOperation
%token productOperation
%token divideOperation
%token inputOperation
%token outputOperation
%token vecSizeOperation
%token refOperation
%token derefOperation
%token <characterArray> stringLiteral
%token <integerValue> decimalLiteral
%token <characterArray> illegalCharacter


%right outputOperation
%left eqOperation
%left lessOperation
%left greaterOperation
%left neqOperation
%left leqOperation
%left geqOperation
%right plusOperation
%right negOperation
%left sumOperation
%left diffOperation
%left divideOperation
%left productOperation
%right inputOperation
%right vecSizeOperation
%right refOperation
%left derefOperation

%start program

%type < pair > program
%type < pair > functionConstant
%type < pairList > formalParameterDeclarationPart
%type < pairList > formalParameterDeclarationList
%type < pair > formalParameterDeclaration
%type < type > formalParameterType
%type < type > unqualifiedFormalParameterType
%type < typeList > formalParameterTypePart
%type < typeList > formalParameterTypeList
%type < programList > expressionSequence
%type < pairList > expressionSequenceAux
%type < pair > expression
%type < pair > assignmentExpression
%type < pair > simpleExpression
%type < pair > primaryExpression
%type < programListList > actualParameterPart
%type < programListList > actualParameterList
%type < pair > variableExpression
%type < pair > constant
%type < pair > variableBlock
%type < pairList > variableDeclarationList
%type < pair > variableDeclaration
%type < pair > variableType
%type < program > unqualifiedVariableType
// no type for enterScope
// no type for leaveScope

%%

// pair
program
    : functionConstant
        {
            if(parameterTypes($1.secondReference()).size() != 0){
                reportTypeError("top level function cannot have arguments");

                stringstream s;
                s << "got parameter types: ";
                for(int i = 0; i < parameterTypes($1.secondReference()).size(); i++){
                    s << "'" << toStr(parameterTypes($1.secondReference())[i]) << "'";
                    if(i < parameterTypes($1.secondReference()).size()-1)
                        s << ", ";
                }
                reportTypeErrorNote(s.str());

            }
            syntaxTree = $1;
            $$ = $1;
        }
    | functionConstant error
        {
            if(parameterTypes($1.secondReference()).size() != 0){
                reportTypeError("top level function cannot have arguments");
            }
            syntaxTree = $1;
            $$ = $1;
            reportError("junk after end of program");
        }
    | error
        {
            syntaxTree = errorPair;
            $$ = errorPair;
            reportError("malformed program");
            YYABORT;
        }
    ;

// pair
functionConstant
    : funType enterScope openParen formalParameterDeclarationPart closeParen
        expressionSequence funEnding leaveScope
        {
            vector<typeTree*> parameterTypeTreeList;
            vector<programTree*> parameterProgramTreeList;
            for(int i = 0; i < $4.size(); i++) {
                parameterTypeTreeList.push_back($4[i].secondReference());
                parameterProgramTreeList.push_back($4[i].firstReference());
            }
            $$ = programTypePair (
                new functionConstant(
                    parameterProgramTreeList,
                    $6),
                new funTypeTree(
                    typeOf($6),
                    parameterTypeTreeList)
                );
        }
    | funType enterScope openParen formalParameterDeclarationPart closeParen
        error
        {
            reportErrorYYText("expected 'expression sequence' before");
        }
        leaveScope funEnding
        {
            $$ = errorPair;
        }
    ;

// pairList
formalParameterDeclarationPart
    : /* empty */
        {
            $$ = vector<programTypePair>();
        }
    | formalParameterDeclarationList
        {
            $$ = $1;
        }
    | formalParameterDeclarationList error
        {
            reportErrorYYText("unexpected");
            $$ = vector<programTypePair>();
        }
    ;

// pairList
formalParameterDeclarationList
    : formalParameterDeclaration
        {
            vector<programTypePair> v;
            v.push_back($1);
            $$ = v;
        }
    | formalParameterDeclarationList comma formalParameterDeclaration
        {
            vector<programTypePair> params = $1;
            params.push_back($3);
            $$ = params;
        }
    | formalParameterDeclarationList error
        {
            reportErrorYYText("expected ',' before");
        }
        formalParameterDeclaration
        {
            $$ = vector<programTypePair>();
        }
    ;

// pair
formalParameterDeclaration
    : formalParameterType stringLiteral
        {
            string name = $2;
            // check to see if we're shadowing something
            bool shadowsPrevValue = false;
            unsigned shadowedVarLineNo = -1;
            symbTable.retrieve(name);
            if(symbTable.success()){
                // if we are:
                // remember that we are
                shadowsPrevValue = true;
                // and remember the line number of the shadowed item
                shadowedVarLineNo = symbTable.successAddress().lineNumber();
            }

            unsigned lineNo = scanner->lineno();
            typeTree* typePtr = $1;
            // try to insert
            symbTable.insert(name, symbolDeclaration(lineNo, name, typePtr));

            if(not(symbTable.success())){
                /* if we collided with something, then:
                *  1) we must be shadowing something
                *  2) the thing we're shadowing is at the same scope
                */
                ostringstream sstream;

                // so just print the line number for the shadowed thing as
                // our collision line number
                sstream << "redeclaration of identifier: " << name
                << " from line " << shadowedVarLineNo;
                forceError(sstream.str());
            }
            else if(verboseMessages && shadowsPrevValue){
                ostringstream sstream;

                // if we're shadowing, but it's not the same scope,
                // then send a warning

                // i added this mainly as a convenience, it can be removed
                sstream << "declaration of " << name
                << " shadows existing declaration on line "
                << shadowedVarLineNo;
                printParseWarning(sstream.str());
            }

            $$ = programTypePair(new parameterDeclaration($1, $2),
                                $1);
        }
    | error
        {
            reportErrorYYText("expected 'formal parameter type' before");
        }
        stringLiteral
        {
            $$ = errorPair;
        }
    | formalParameterType error
        {
            reportErrorYYText("expected 'identifier' before");
            $$ = errorPair;
        }
    ;

// type
formalParameterType
    : unqualifiedFormalParameterType
        {
            $$ = $1;
        }
    | immutableQualification unqualifiedFormalParameterType
        {
            $$ = new immutTypeTree($2);
        }
    ;

// type
unqualifiedFormalParameterType
    : trivType
        {
            $$ = new trivTypeTree();
        }
    | intType
        {
            $$ = new intTypeTree();
        }
    | refType formalParameterType
        {
            $$ = new refTypeTree($2);
        }
    | refType vectorType formalParameterType
        {
            $$ = new refvecTypeTree($3);
        }
    | conType formalParameterType
        {
            $$ = new conTypeTree($2);
        }
    | funType openParen formalParameterTypePart closeParen
        formalParameterType
        {
            $$ = new funTypeTree($5, $3);
        }
    | funType openParen error
        {
            reportErrorYYText("expected 'formal parameter type' before");
        }
        closeParen formalParameterType
        {
            $$ = new intTypeTree;
        }
    | funType openParen formalParameterTypePart closeParen error
        {
            reportErrorYYText("expected 'formal parameter type' before");

            $$ = new intTypeTree;
        }
    ;

// typeList
formalParameterTypePart
    : /* empty */
        {
            $$ = vector<typeTree*>();
        }
    | formalParameterTypeList
        {
            $$ = $1;
        }
    | formalParameterTypeList error
        {
            reportErrorYYText("unexpected");
            $$ = vector<typeTree*>();
        }
    ;

// typeList
formalParameterTypeList
    : formalParameterType
        {
            // TODO This doesn't work right.
            vector<typeTree*> t;
            t.push_back($1);
            $$ = t;
        }
    | formalParameterTypeList comma formalParameterType
        {
            vector<typeTree*> t = $1;
            t.push_back($3);
            $$ = t;
        }
    | formalParameterTypeList error
        {
            reportErrorYYText("expected ',' before");
        }
        formalParameterType
        {
            vector<typeTree*> t = $1;
            t.push_back($4);
            $$ = t;
        }
    ;

// programList
expressionSequence
    : expressionSequenceAux
        {
            vector<programTree*> vec = extractProgramList($1);
            $$ = vec;
        }
    ;

// pairList
expressionSequenceAux
    : expression
        {
            vector<programTypePair> vec;
            vec.push_back($1);
            $$ = vec;
        }
    | expressionSequenceAux semicolon expression
        {
            vector<programTypePair> vec = $1;
            vec.push_back($3);
            $$ = vec;
        }
    | expressionSequenceAux error
        {
            reportErrorYYText("expected ';' before");
        }
        expression
        {
            vector<programTypePair> vec = $1;
            vec.push_back($4);
            $$ = vec;
        }
    | expressionSequenceAux semicolon error
        {
            reportErrorYYText("expected 'expression' before");

            $$ = $1;
        }
    ;

// pair
expression
    : assignmentExpression
        {
            $$ = $1;
        }
    | assignmentExpression continuesOperation expression
        {
            if(not(isCon($1.secondReference()))){
                reportTypeError("invalid operand to continues expression");

                stringstream s;
                s << "'" << toStr($1.secondReference()) << "' in place of 'con'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
            else {
                if(not(subtype($3.secondReference(), unCon($1.secondReference())))) {
                    reportTypeError("invalid operand types to continues expression");

                    stringstream s;
                    s << "'" << toStr($3.secondReference()) << "' is not a subtype of '"
                        << toStr(unCon($1.secondReference())) << "'";
                    reportTypeErrorNote(s.str());

                    $$ = errorPair;
                }
                else {
                    $$ = programTypePair(
                        new continuesExpression($1.firstReference(), $3.firstReference()),
                        unCon($1.secondReference()));
                }
            }
        }
    | assignmentExpression continuesOperation error
        {
            reportErrorYYText("expected 'expression' before");
            $$ = errorPair;
        }
    | error continuesOperation expression
        {
            reportErrorYYText("expected 'assignment expression' before");
            $$ = errorPair;
        }
    ;

// pair
assignmentExpression
    : simpleExpression
        {
            debugMessage("simpleExpression: " + toStr($1.secondReference()));
            $$ = $1;
        }
    | variableExpression assignmentOperation assignmentExpression
        {
            debugMessage("assignment:");
            debugMessage("lhs: " + toStr($1.secondReference()));
            debugMessage("rhs: " + toStr($3.secondReference()));
            if(not(isMutable($1.secondReference()))) {
                reportTypeError("cannot assign to immutable value");

                stringstream s;
                s << "got '" << toStr($1.secondReference()) << "'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
            else if(not(subtype($3.secondReference(),
                                $1.secondReference()))) {
                reportTypeError("invalid operands to assignment expression");

                stringstream s;
                s << "'" << toStr($3.secondReference()) << "' is not a subtype of '"
                << toStr($1.secondReference()) << "'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
            else {
                $$ = programTypePair(
                    new assignmentExpression(
                        $1.firstReference(),
                        $3.firstReference()),
                    $1.secondReference()
                    );
            }
        }
    ;

// pair
simpleExpression
    : primaryExpression
        {
            $$ = $1;
        }
    | simpleExpression eqOperation simpleExpression
        {
            if(isFun($1.secondReference()) && isFun($3.secondReference())) {
                reportTypeError("invalid argument to '=' expression");

                stringstream s, t;
                s << "operand 1: functions cannot be compared for equality or inequality";
                t << "operand 2: functions cannot be compared for equality or inequality";
                reportTypeErrorNote(s.str());
                reportTypeErrorNote(t.str());

            }
            else if(isFun($1.secondReference())) {
                reportTypeError("invalid argument to '=' expression");

                stringstream s;
                s << "operand 1: functions cannot be compared for equality or inequality";
                reportTypeErrorNote(s.str());

            }
            else if(isFun($3.secondReference())){
                reportTypeError("invalid argument to '=' expression");

                stringstream s;
                s << "operand 2: functions cannot be compared for equality or inequality";
                reportTypeErrorNote(s.str());

            }
            else if(not(compatible($1.secondReference(), $3.secondReference()))) {
                reportTypeError("incompatible types to '=' expression");

                stringstream s;
                s << "'" << toStr($1.secondReference()) << "' is not compatible with '"
                << toStr($3.secondReference()) << "'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
            else {
                $$ = programTypePair(
                    new eqExpression($1.firstReference(),
                                    $3.firstReference()),
                    new intTypeTree()
                );
            }
        }
    | simpleExpression neqOperation simpleExpression
        {
            if(isFun($1.secondReference()) && isFun($3.secondReference())) {
                reportTypeError("invalid argument to '<>' expression");

                stringstream s, t;
                s << "operand 1: functions cannot be compared for equality or inequality";
                t << "operand 2: functions cannot be compared for equality or inequality";
                reportTypeErrorNote(s.str());
                reportTypeErrorNote(t.str());

            }
            else if(isFun($1.secondReference())) {
                reportTypeError("invalid argument to '<>' expression");

                stringstream s;
                s << "operand 1: functions cannot be compared for equality or inequality";
                reportTypeErrorNote(s.str());

            }
            else if(isFun($3.secondReference())){
                reportTypeError("invalid argument to '<>' expression");

                stringstream s;
                s << "operand 2: functions cannot be compared for equality or inequality";
                reportTypeErrorNote(s.str());

            }
            else if(not(compatible($1.secondReference(), $3.secondReference()))) {
                reportTypeError("incompatible types to '<>' expression");

                stringstream s;
                s << "'" << toStr($1.secondReference()) << "' is not compatible with '"
                << toStr($3.secondReference()) << "'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
            else {
                $$ = programTypePair(
                    new neqExpression($1.firstReference(),
                                    $3.firstReference()),
                    new intTypeTree()
                    );
            }
        }
    | simpleExpression leqOperation simpleExpression
        {
            bool oneIsInt = isInt($1.secondReference());
            bool oneIsTriv = isTriv($1.secondReference());
            bool threeIsInt = isInt($3.secondReference());
            bool threeIsTriv = isTriv($3.secondReference());
            if( (oneIsInt and threeIsInt)
                or
                (threeIsInt and threeIsTriv)
                ) {
                $$ = programTypePair(
                    new leqExpression($1.firstReference(),
                                    $3.firstReference()),
                    new intTypeTree()
                    );
            }
            else {
                reportTypeError("incompatible types to '<=' expression");

                // Either $1 or $3 (or both) is not an Int or a Triv
                if(not(oneIsInt or oneIsTriv)) {
                    stringstream s;
                    s << "operand 1: '" << toStr($1.secondReference()) << "' is not a valid parameter";
                    reportTypeErrorNote(s.str());
                }
                if(not(threeIsInt or threeIsTriv)) {
                    stringstream t;
                    t << "operand 2: '" << toStr($3.secondReference()) << "' is not a valid parameter";
                    reportTypeErrorNote(t.str());
                }

                $$ = errorPair;
            }
        }
    | simpleExpression lessOperation simpleExpression
        {
            bool oneIsInt = isInt($1.secondReference());
            bool oneIsTriv = isTriv($1.secondReference());
            bool threeIsInt = isInt($3.secondReference());
            bool threeIsTriv = isTriv($3.secondReference());
            if( (oneIsInt and threeIsInt)
                or
                (threeIsInt and threeIsTriv)
                ) {
                $$ = programTypePair(
                    new lessExpression($1.firstReference(),
                                    $3.firstReference()),
                    new intTypeTree()
                    );
            }
            else {
                reportTypeError("incompatible types to '<' expression");

                // Either $1 or $3 (or both) is not an Int or a Triv
                if(not(oneIsInt or oneIsTriv)) {
                    stringstream s;
                    s << "operand 1: '" << toStr($1.secondReference()) << "' is not a valid parameter";
                    reportTypeErrorNote(s.str());
                }
                if(not(threeIsInt or threeIsTriv)) {
                    stringstream t;
                    t << "operand 2: '" << toStr($3.secondReference()) << "' is not a valid parameter";
                    reportTypeErrorNote(t.str());
                }

                $$ = errorPair;
            }
        }
    | simpleExpression geqOperation simpleExpression
        {
            bool oneIsInt = isInt($1.secondReference());
            bool oneIsTriv = isTriv($1.secondReference());
            bool threeIsInt = isInt($3.secondReference());
            bool threeIsTriv = isTriv($3.secondReference());
            if( (oneIsInt and threeIsInt)
                or
                (threeIsInt and threeIsTriv)
                ) {
                $$ = programTypePair(
                    new geqExpression($1.firstReference(),
                                    $3.firstReference()),
                    new intTypeTree()
                    );
            }
            else {
                reportTypeError("incompatible types to '>=' expression");

                // Either $1 or $3 (or both) is not an Int or a Triv
                if(not(oneIsInt or oneIsTriv)) {
                    stringstream s;
                    s << "operand 1: '" << toStr($1.secondReference()) << "' is not a valid parameter";
                    reportTypeErrorNote(s.str());
                }
                if(not(threeIsInt or threeIsTriv)) {
                    stringstream t;
                    t << "operand 2: '" << toStr($3.secondReference()) << "' is not a valid parameter";
                    reportTypeErrorNote(t.str());
                }

                $$ = errorPair;
            }
        }
    | simpleExpression greaterOperation simpleExpression
        {
            bool oneIsInt = isInt($1.secondReference());
            bool oneIsTriv = isTriv($1.secondReference());
            bool threeIsInt = isInt($3.secondReference());
            bool threeIsTriv = isTriv($3.secondReference());
            if( (oneIsInt and threeIsInt)
                or
                (threeIsInt and threeIsTriv)
                ) {
                $$ = programTypePair(
                    new greaterExpression($1.firstReference(),
                                        $3.firstReference()),
                    new intTypeTree()
                    );
            }
            else {
                reportTypeError("incompatible types to '>' expression");

                // Either $1 or $3 (or both) is not an Int or a Triv
                if(not(oneIsInt or oneIsTriv)) {
                    stringstream s;
                    s << "operand 1: '" << toStr($1.secondReference()) << "' is not a valid parameter";
                    reportTypeErrorNote(s.str());
                }
                if(not(threeIsInt or threeIsTriv)) {
                    stringstream t;
                    t << "operand 2: '" << toStr($3.secondReference()) << "' is not a valid parameter";
                    reportTypeErrorNote(t.str());
                }

                $$ = errorPair;
            }
        }
    | simpleExpression sumOperation simpleExpression
        {
            if(isInt($1.secondReference()) and isInt($3.secondReference())) {
                $$ = programTypePair(
                    new sumExpression($1.firstReference(),
                                    $3.firstReference()),
                    new intTypeTree()
                    );
            }
            else {
                reportTypeError("incompatible types to '+' expression");

                if(not(isInt($1.secondReference()))) {
                    stringstream s;
                    s << "operand 1: '" << toStr($1.secondReference()) << "' is not an integer";
                    reportTypeErrorNote(s.str());
                }
                if(not(isInt($3.secondReference()))) {
                    stringstream s;
                    s << "operand 2: '" << toStr($3.secondReference()) << "' is not an integer";
                    reportTypeErrorNote(s.str());
                }

                $$ = errorPair;
            }
        }
    | simpleExpression diffOperation simpleExpression
        {
            if(isInt($1.secondReference()) and isInt($3.secondReference())) {
                $$ = programTypePair(
                    new diffExpression($1.firstReference(),
                                    $3.firstReference()),
                    new intTypeTree()
                    );
            }
            else {
                reportTypeError("incompatible types to '-' expression");

                if(not(isInt($1.secondReference()))) {
                    stringstream s;
                    s << "operand 1: '" << toStr($1.secondReference()) << "' is not an integer";
                    reportTypeErrorNote(s.str());
                }
                if(not(isInt($3.secondReference()))) {
                    stringstream s;
                    s << "operand 2: '" << toStr($3.secondReference()) << "' is not an integer";
                    reportTypeErrorNote(s.str());
                }

                $$ = errorPair;
            }
        }
    | simpleExpression productOperation simpleExpression
        {
            if(isInt($1.secondReference()) and isInt($3.secondReference())) {
                $$ = programTypePair(
                    new productExpression($1.firstReference(),
                                        $3.firstReference()),
                    new intTypeTree()
                    );
            }
            else {

                reportTypeError("incompatible types to '*' expression");
                if(not(isInt($1.secondReference()))) {
                    stringstream s;
                    s << "operand 1: '" << toStr($1.secondReference()) << "' is not an integer";
                    reportTypeErrorNote(s.str());
                }
                if(not(isInt($3.secondReference()))) {
                    stringstream s;
                    s << "operand 2: '" << toStr($3.secondReference()) << "' is not an integer";
                    reportTypeErrorNote(s.str());
                }

                $$ = errorPair;
            }
        }
    | simpleExpression divideOperation simpleExpression
        {
            if(isInt($1.secondReference()) and isInt($3.secondReference())) {
                $$ = programTypePair(
                    new quotientExpression($1.firstReference(),
                                        $3.firstReference()),
                    new intTypeTree()
                    );
            }
            else {
                reportTypeError("incompatible types to '/' expression");

                if(not(isInt($1.secondReference()))) {
                    stringstream s;
                    s << "operand 1: '" << toStr($1.secondReference()) << "' is not an integer";
                    reportTypeErrorNote(s.str());
                }
                if(not(isInt($3.secondReference()))) {
                    stringstream s;
                    s << "operand 2: '" << toStr($3.secondReference()) << "' is not an integer";
                    reportTypeErrorNote(s.str());
                }

                $$ = errorPair;
            }
        }
    | inputOperation variableExpression
        {
            if(isInt($2.secondReference())) {
                $$ = programTypePair(
                    new inputExpression($2.firstReference()),
                    new intTypeTree()
                    );
            }
            else {
                reportTypeError("incompatible type to 'input' expression");

                stringstream s;
                s << "'" << toStr($2.secondReference()) << "' in place of 'int'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
        }
    | inputOperation error
        {
            reportErrorYYText("expected 'variable expression' before");
            $$ = errorPair;
        }
    | outputOperation simpleExpression
        {
            if(isInt($2.secondReference())) {
                $$ = programTypePair(
                    new outputExpression($2.firstReference()),
                    new intTypeTree()
                    );
            }
            else {
                reportTypeError("incompatible type to 'output' expression");

                stringstream s;
                s << "'" << toStr($2.secondReference()) << "' in place of 'int'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
        }
    | outputOperation error
        {
            reportErrorYYText("expected 'simple expression' before");
            $$ = errorPair;
        }
    | sumOperation simpleExpression %prec plusOperation
        {
            if(isInt($2.secondReference())) {
                $$ = programTypePair(
                    new plusExpression($2.firstReference()),
                    new intTypeTree()
                    );
            }
            else {
                reportTypeError("incompatible type to unary '+' expression");

                stringstream s;
                s << "'" << toStr($2.secondReference()) << "' in place of 'int'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
        }
    | sumOperation error %prec plusOperation
        {
            reportErrorYYText("expected 'simple expression' before");
            $$ = errorPair;
        }
    | diffOperation simpleExpression %prec negOperation
        {
            if(isInt($2.secondReference())) {
                $$ = programTypePair(
                    new negationExpression($2.firstReference()),
                    new intTypeTree()
                    );
            }
            else {
                reportTypeError("incompatible type to unary '-' expression");

                stringstream s;
                s << "'" << toStr($2.secondReference()) << "' in place of 'int'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
        }
    | diffOperation error %prec negOperation
        {
            reportErrorYYText("expected 'simple expression' before");
            $$ = errorPair;
        }
    | vecSizeOperation simpleExpression
        {
            if(isRefvec($2.secondReference())) {
                $$ = programTypePair(
                    new vecSizeExpression($2.firstReference()),
                    new intTypeTree()
                    );
            }
            else {
                reportTypeError("invalid type to '#' expression");

                stringstream s;
                s << "'" << toStr($2.secondReference()) << "' in place of 'ref vec'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
        }
    | vecSizeOperation error
        {
            reportErrorYYText("expected 'simple expression' before");
            $$ = errorPair;
        }
    | refOperation variableExpression
        {
            $$ = programTypePair(
                new referenceExpression($2.firstReference()),
                new refTypeTree($2.secondReference())
                );
        }
    | refOperation error
        {
            reportErrorYYText("expected 'variable expression' before");
            $$ = errorPair;
        }
    ;

// pair
primaryExpression
    : constant
        {
            $$ = $1;
        }
    | variableExpression
        {
            $$ = $1;
        }
    | openParen expressionSequence closeParen
        {
            $$ = programTypePair(
                new parenExpression($2),
                typeOf($2)
                );
        }
    | openParen error
        {
            reportErrorYYText("expected 'expression sequence' before");
        }
        closeParen
        {
            $$ = errorPair;
        }
    | whileStart expressionSequence whileDo expressionSequence whileEnding
        {
            if(not(isInt(typeOf($2)))) {
                reportTypeError("invalid condition type for while expression");

                stringstream s;
                s << "'" << toStr(typeOf($2)) << "' in place of 'int'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
            else {
                $$ = programTypePair(
                    new whileBlock($2, $4),
                    new intTypeTree()
                    );
            }
        }
    | whileStart error
        {
            reportErrorYYText("expected 'expression sequence' before");
        }
        whileDo expressionSequence whileEnding
        {
            $$ = errorPair;
        }
    | whileStart expressionSequence whileDo error
        {
            reportErrorYYText("expected 'expression sequence' before");
        }
        whileEnding
        {
            $$ = errorPair;
        }
    | ifStart expressionSequence ifThen expressionSequence
        ifElse expressionSequence ifEnding
        {
            if(not(isInt(typeOf($2)))) {
                reportTypeError("invalid condition type for if expression");

                stringstream s;
                s << "'" << toStr(typeOf($2)) << "' in place of 'int'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
            else if(not(combinable(typeOf($4), typeOf($6)))) {
                reportTypeError("invalid operand types for if expression");

                stringstream s;
                s << "'" << toStr(typeOf($4)) << "' is not combinable with '"
                << toStr(typeOf($6)) << "'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
            else {
                $$ = programTypePair(
                    new ifBlock(
                        $2,
                        $4,
                        $6
                        ),
                    combine(typeOf($4), typeOf($6))
                    );
            }
        }
    | ifStart error
        {
            reportErrorYYText("expected 'expression sequence' before");
        }
        ifThen expressionSequence ifElse expressionSequence ifEnding
        {
            $$ = errorPair;
        }
    | ifStart expressionSequence ifThen error
        {
            reportErrorYYText("expected 'expression sequence' before");
        }
        ifElse expressionSequence ifEnding
        {
            $$ = errorPair;
        }
    | ifStart expressionSequence ifThen expressionSequence ifElse error
        {
            reportErrorYYText("expected 'expression sequence' before");
        }
        ifEnding
        {
            $$ = errorPair;
        }
    | ifStart error
        {
            reportError("malformed if expression");
        }
        ifEnding
        {
            $$ = errorPair;
        }
    | controlStart variableExpression inSeparator expressionSequence
        controlEnding
        {
            if(not(isCon($2.secondReference()))) {
                reportTypeError("invalid operand to control expression");

                stringstream s;
                s << "'" << toStr($2.secondReference()) << "' in place of 'con'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
            else {
                if(not(subtype(typeOf($4),
                            unCon($2.secondReference())))) {
                    reportTypeError("incompatible types of control expression");

                    stringstream s;
                    s << "'" << toStr(typeOf($4)) << "' is not a subtype of '"
                        << toStr($2.secondReference()) << "'";
                    reportTypeErrorNote(s.str());

                    $$ = errorPair;
                }
                else {
                    $$ = programTypePair(
                        new controlBlock($2.firstReference(),
                                        $4),
                        unCon($2.secondReference())
                        );
                }
            }
        }
    | controlStart error
        {
            reportErrorYYText("expected 'variable expression' before");
        }
        inSeparator expressionSequence controlEnding
        {
            $$ = errorPair;
        }
    | controlStart variableExpression inSeparator error
        {
            reportErrorYYText("expected 'expression sequence' before");
        }
        controlEnding
        {
            $$ = errorPair;
        }
    | controlStart error
        {
            reportError("malformed control sequence");
        }
        controlEnding
        {
            $$ = errorPair;
        }
    | variableBlock
        {
            $$ = $1;
        }
    | primaryExpression openParen actualParameterPart closeParen
        {
            if(isFun($1.secondReference())) {
                vector<vector<string> > invalidOperands;
                bool allGood = false;
                vector<typeTree*> parameterTs = parameterTypes($1.secondReference());
                if($3.size() == parameterTs.size()) {
                    allGood = true;
                    for(int i = 0; i < $3.size(); i++){
                        if(not(subtype(typeOf($3[i]), parameterTs[i]))){
                            vector<string> v;
                            v.push_back(toStr(typeOf($3[i])));
                            v.push_back(toStr(parameterTs[i]));
                            invalidOperands.push_back(v);
                            allGood = false;
                        }
                    }
                }

                if(allGood){
                    $$ = programTypePair(
                        new functionApplication($1.firstReference(),
                                                $3),
                        returnType($1.secondReference())
                        );
                }
                else if(invalidOperands.size() > 0) {
                    reportTypeError("invalid arguments to function call");

                    for(int i = 0; i < invalidOperands.size(); i++){
                        stringstream s;
                        s << "operand " << i+1 << ": '" + invalidOperands[i][0] + "' in place of '" + invalidOperands[i][1] + "'";
                        reportTypeErrorNote(s.str());
                    }

                    $$ = errorPair;
                }
                else {
                    reportTypeError("malformed function call");

                    stringstream s, t;
                    s << "function type: '" << toStr($1.secondReference()) << "'";
                    reportTypeErrorNote(s.str());
                    if($3.size() > 0){
                        t << "parameter types: ";
                        for(int i = 0; i < $3.size(); i++) {
                            t << "'" << toStr(typeOf($3[i])) << "'";
                            if(i < $3.size()-1)
                                t << ", ";
                        }
                    }
                    else
                        t << "no parameters";
                    reportTypeErrorNote(t.str());

                    $$ = errorPair;
                }
            }
            else {
                reportTypeError("function application of non function");

                stringstream s;
                s << "got '" << toStr($1.secondReference()) << "' instead";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
        }
    | primaryExpression openParen error
        {
            reportErrorYYText("expected 'parameter list' before");
        }
        closeParen
        {
            $$ = errorPair;
        }
    ;

// programListList
actualParameterPart
    : /* empty */
        {
            $$ = vector<vector<programTree*> >();
        }
    | actualParameterList
        {
            $$ = $1;
        }
    ;

// programListList
actualParameterList
    : expressionSequence
        {
            vector<vector<programTree*> > v;
            v.push_back($1);
            $$ = v;
        }
    | actualParameterList comma expressionSequence
        {
            vector<vector<programTree*> > v = $1;
            v.push_back($3);
            $$ = v;
        }
    | actualParameterList comma error
        {
            reportErrorYYText("expected 'expression sequence' before");
            $$ = $1;
        }
    ;

// pair
variableExpression
    : stringLiteral
        {
            symbTable.retrieve($1);

            if(not(symbTable.success())){
                ostringstream sstream;
                sstream << "undefined identifier: " << $1;
                forceError(sstream.str());
                $$ = errorPair;
            }
            else {
                symbolDeclaration variable = symbTable.successAddress();
                typeTree* t = deepCopy(variable.type());
                $$ = programTypePair(
                    new variableLiteral(variable.identifier(), t),
                    t
                    );
            }
        }
    | primaryExpression openBracket expressionSequence closeBracket
        {
            if(not(isInt(typeOf($3)))){
                reportTypeError("invalid operand to '[]' operation");

                stringstream s;
                s << "'" << toStr(typeOf($3)) << "' in place of 'int'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
            else if(not(isRefvec($1.secondReference()))) {
                reportTypeError("invalid operand to '[]' operation");

                stringstream s;
                s << "'" << toStr($1.secondReference()) << "' in place of 'ref vec'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
            else {
                $$ = programTypePair(
                    new vectorRefExpression($1.firstReference(),
                                            $3),
                    unRefvec($1.secondReference())
                    );
            }
        }
    | primaryExpression derefOperation
        {
            if(not(isRef($1.secondReference()))){
                reportTypeError("invalid operand to '@' operation");

                stringstream s;
                s << "'" << toStr($1.secondReference()) << "' in place of 'ref'";
                reportTypeErrorNote(s.str());

                $$ = errorPair;
            }
            else {
                $$ = programTypePair(
                    new dereferenceExpression($1.firstReference()),
                    unRef($1.secondReference())
                    );
            }
        }
    ;

// pair
constant
    : decimalLiteral
        {
            $$ = programTypePair(
                new constantExpression($1),
                new intTypeTree()
                );
        }
    | trivLiteral
        {
            $$ = programTypePair(
                new trivExpression(),
                new trivTypeTree()
                );
        }
    | functionConstant
        {
            $$ = $1;
        }
    ;

// pair
variableBlock
    : varsStart enterScope variableDeclarationList inSeparator
        expressionSequence varsEnding leaveScope
        {
            vector<programTree*> v;
            for(int i = 0; i < $3.size(); i++) {
                v.push_back($3[i].firstReference());
            }
            $$ = programTypePair(
                new variableBlock(v, $5),
                typeOf($5)
                );
        }
    | varsStart enterScope error
        {
            reportErrorYYText("expected 'variable declaration list' before");
        }
        inSeparator expressionSequence varsEnding leaveScope
        {
            $$ = errorPair;
        }
    | varsStart enterScope variableDeclarationList inSeparator error
        {
            // No need to do variable checking since it's an error anyway
            reportErrorYYText("expected 'expression sequence' before");
        }
        leaveScope varsEnding
        {
            $$ = errorPair;
        }
    ;

// pairList
variableDeclarationList
    : variableDeclaration
        {
            vector<programTypePair > v;
            v.push_back($1);
            $$ = v;
        }
    | variableDeclarationList comma variableDeclaration
        {
            vector<programTypePair > v = $1;
            v.push_back($3);
            $$ = v;
        }
    | variableDeclarationList comma error
        {
            reportErrorYYText("expected 'variable declaration' before");
            $$ = vector<programTypePair >();
        }
    | variableDeclarationList error
        {
            reportErrorYYText("expected ',' before");
        }
        variableDeclaration
        {
            $$ = vector<programTypePair >();
        }
    ;

// pair
variableDeclaration
    : variableType stringLiteral
        {
            string name = $2;
            // check to see if we're shadowing something
            bool shadowsPrevValue = false;
            unsigned shadowedVarLineNo = -1;
            symbTable.retrieve(name);
            if(symbTable.success()){
                // if we are:
                // remember that we are
                shadowsPrevValue = true;
                // and remember the line number of the shadowed item
                shadowedVarLineNo = symbTable.successAddress().lineNumber();
            }

            unsigned lineNo = scanner->lineno();
            typeTree* typePtr = deepCopy(typeOf($1.firstReference()));
            // try to insert
            symbTable.insert(name, symbolDeclaration(lineNo, name, typePtr));

            if(not(symbTable.success())){
                /* if we collided with something, then:
                *  1) we must be shadowing something
                *  2) the thing we're shadowing is at the same scope
                */
                ostringstream sstream;

                // so just print the line number for the shadowed thing as
                // our collision line number
                sstream << "redeclaration of identifier: " << name
                << " from line " << shadowedVarLineNo;
                forceError(sstream.str());
            }
            else if(verboseMessages && shadowsPrevValue){
                ostringstream sstream;

                // if we're shadowing, but it's not the same scope,
                // then send a warning

                // i added this mainly as a convenience, it can be removed
                sstream << "declaration of " << name
                        << " shadows existing declaration on line "
                        << shadowedVarLineNo;
                printParseWarning(sstream.str());
            }
            setId($1.firstReference(), $2);
            $$ = programTypePair($1.firstReference(), typeOf($1.firstReference()));
        }
    ;

// pair
variableType
    : formalParameterType // type
        {
            $$ = programTypePair(new variableDeclaration($1, ""),
                                 $1);
        }
    | unqualifiedVariableType // program
        {
            $$ = programTypePair($1, typeOf($1));
        }
    | immutableQualification unqualifiedVariableType // program
        {
            $$ = programTypePair($2, new immutTypeTree(typeOf($2)));
        }
    ;

// program
unqualifiedVariableType
    : vectorType openBracket expressionSequence closeBracket variableType
        {
            if(isInt(typeOf($3))){
                $$ = new vectorDeclaration("", $5.firstReference(), $3);
            }
            else {
                $$ = new variableDeclaration(new intTypeTree(), "error");
                reportTypeError("invalid operand to vector allocation");

                reportTypeErrorNote(toStr(typeOf($3)) + " in place of 'int'");
            }
        }
    | error
        {
            reportErrorYYText("expected 'vec' before");
        }
        openBracket expressionSequence closeBracket variableType
        {
            $$ = new variableDeclaration(new intTypeTree(), "error");
        }
    | vectorType openBracket error
        {
            reportErrorYYText("expected 'expression sequence' before");
        }
        closeBracket variableType
        {
            $$ = new variableDeclaration(new intTypeTree(), "error");
        }
    | vectorType openBracket expressionSequence closeBracket error
        {
            reportErrorYYText("expected 'variable type' before");
            $$ = new variableDeclaration(new intTypeTree(), "error");
        }
    ;

/*
* These are helping nonterminals that mainly perform semantic actions for us
*/

// Enters a new scope
enterScope
    : /* empty */
        {
            symbTable.enterScope();
        }
    ;

// Leaves a scope
leaveScope
    : /* empty */
        {
            symbTable.leaveScope();
        }
    ;

%%

// a bit of overhead needed for the parser to communicate with the scanner
int yylex() {
    return scanner->yylex();
}

// extracts a list of program trees
vector<programTree*> extractProgramList(vector<programTypePair>& pairVec) {
    vector<programTree*> result(pairVec.size());
    for(int i = 0; i < pairVec.size(); i++)
        result[i] = pairVec[i].firstReference();
    return result;
}

// extracts a list of type trees
vector<typeTree*> extractTypeList(vector<programTypePair>& pairVec) {
    vector<typeTree*> result(pairVec.size());
    for(int i = 0; i < pairVec.size(); i++)
        result[i] = pairVec[i].secondReference();
    return result;
}
