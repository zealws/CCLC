#include <iostream>
#include <FlexLexer.h>
#include "../scanner/scanner.h"
#include "../options/options.h"
#include "error.h"
using namespace std;

const string typeMessage = "####";
const string warningMessage = "$$$$";
const string syntaxMessage = "****";

// how many errors have we not reported reported
static int numberUnreportedErrors = 0;

// how many errors have we reported
int numErrors = 0;

// needed by the parser
// prints no output
int yyerror(char* msg) {
	//cerr << "**** on line " << scanner->lineno() << endl;
	numberUnreportedErrors++;
	return 0;
}

// prints an error message along with the line number
void reportError(const string& msg){
	if(numberUnreportedErrors > 0){
		numberUnreportedErrors--;
		cerr << syntaxMessage << " on line " << scanner->lineno() << ": " << msg << endl;
		numErrors++;
	}
}

// prints an error message along with the line number and the scanner's
// last token
void reportErrorYYText(const string& msg){
	if(numberUnreportedErrors > 0){
		numberUnreportedErrors--;
		cerr << syntaxMessage << " on line " << scanner->lineno() << ": "
			<< msg << " '" << scanner->YYText() << "'\n";
			numErrors++;
	}
}

// forces an error message to occur even if yyerror hasn't been called
void forceError(const string& msg) {
	cerr << syntaxMessage << " on line " << scanner->lineno() << ": " << msg << endl;
	numErrors++;
}

// prints a message on the screen without reporting it as an error
// includes the line number of the scanner
void printParseWarning(const string& msg) {
    cerr << warningMessage << " on line " << scanner->lineno() << ": " << msg << endl;
}

// prints a message on the screen without reporting it as an error
void printWarning(const string& msg) {
    cerr << warningMessage << " Warning: " << msg << endl;
}

// reports a type error
void reportTypeError(const string& msg) {
    cerr << typeMessage << " on line " << scanner->lineno() << ": " << msg << endl;
    numErrors++;
}

// reports a note with a type error
void reportTypeErrorNote(const string& msg) {
    if(verboseMessages)
        cerr << typeMessage << " note: " << msg << endl;
}

// report a fatal error
// like forceError except doesn't use the line number
void fatalError(const string& msg) {
    cerr << syntaxMessage << " " << msg << endl;
    numErrors++;
}

// report a debugging message
void debugMessage(const string& msg) {
#ifdef DEBUG
    cerr << "^^^^ " << msg << endl;
#else
    ;
#endif
}