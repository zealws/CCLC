#ifndef _ERROR_H_
#define _ERROR_H_

#include <string>
#include <cstdlib>
using namespace std;

// the number of errors
// declared here
// defined in error.cpp
extern int numErrors;

// needed by the parser
// prints no output
int yyerror(char* msg);

// prints an error message along with the line number
void reportError(const string& msg);

// prints an error message along with the line number and the scanner's
// last token
void reportErrorYYText(const string& msg);

// forces an error message to occur even if yyerror hasn't been called
void forceError(const string& msg);

// prints a message on the screen without reporting it as an error
// includes the line number of the scanner
void printParseWarning(const string& msg);

// prints a message on the screen without reporting it as an error
void printWarning(const string& msg);

// reports a type error
void reportTypeError(const string& msg);

// reports a note with a type error
void reportTypeErrorNote(const string& msg);

// report a fatal error
// like forceError except doesn't use the line number
void fatalError(const string& msg);

// report a debugging message
void debugMessage(const string& msg);

#endif
