#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include "stringFormat.h"
#include "../error/error.h"

using namespace std;

// Use spaces instead of tab characters for portability purposes.
const string tab = "  ";

// New line character. Helpful for switching between mac/*nix/dos style newlines.
const string endline = "\n";

// Character(s) to prefix a comment with.
const string commentPrefix = "#";

// Do not limit tab maximum.
const int tabMax = -1;

// Repeats a string a given number of times. Returns the result.
// This is a helper function that is not merged into the outputStream structure.
string repeatString(const string& s, int n) {
    if(n <= 0)
        return "";
    else
        return s + repeatString(s, n-1);
}

// Returns the string form of an integer
// This is a helper function that is not merged into the outputStream structure.
string intToStr(int n) {
    stringstream s;
    s << n;
    return s.str();
}

////
//// Private Members
////

// None

////
//// Protected Members
////

// Increments the tab size temporarily
void outputStream::tabInc() const {
    if(tabSize != tabMax)
        tabSize++;
}

// Decrements the tab size temporarily
void outputStream::tabDec() const {
    if(tabSize != 0)
        tabSize--;
}

// Dumps a string to the buffer.
// Appends a newline to the end of the string.
void outputStream::print(const string& toBePrinted) {
    *buffer << repeatString(tab, tabSize) << toBePrinted << endline;
}

// Dumps a string verbatim to the buffer.
void outputStream::printRAW(const string& toBePrinted) {
    *buffer << toBePrinted;
}

////
//// Public Members
////

// Creates an output stream without a specified output stream.
outputStream::outputStream()
    : outFile(NULL), buffer(new stringstream), tabSize(0) {
    // Do Nothing
}

// Creates an output stream for a specific output stream.
outputStream::outputStream(ostream* initOutFile)
    : outFile(initOutFile), buffer(new stringstream), tabSize(0) {
    // Do Nothing
}

// Creates an output stream for a file.
outputStream::outputStream(const string& filename)
    : outFile(new ofstream(filename.data())), buffer(new stringstream), tabSize(0) {
    // Do Nothing
}

// Destructor
// Dumps the buffer to the output stream if it isn't empty.
// DOES NOT DELETE THE OUTPUT STREAM POINTER
outputStream::~outputStream() {
    dumpBuffer();
    delete buffer;
}

// Prints just a newline to the buffer.
void outputStream::printNewLine() {
    printRAW(endline);
}

// Print a line of code at the current tab level.
void outputStream::printCode(const string& code) {
    print(code);
}

// Prints a comment at the current tab level.
void outputStream::printComment(const string& comment) {
    print(commentPrefix + " " + comment);
}

// Prints a multiline comment to the buffer.
void outputStream::printBlockComment(const string& message) {
    printComment("");
    int pos = message.find(endline);
    int lastPos = 0;
    while(lastPos < message.size()){
        if(lastPos == 0)
            printComment(message.substr(0, pos));
        else
            printComment(message.substr(lastPos+1, pos-lastPos));
        
        lastPos = pos;
        pos = message.find(endline, pos+1);
    }
    printComment("");
}

// Prints a line of code to the buffer of the form:
// op operand1, operand2 # comment
void outputStream::printTwoOperandCode(
    const string& op,
    const string& operand1,
    const string& operand2,
    const string& comment) {
    if(comment.size() == 0)
        print(op + " " + operand1 + ", " + operand2);
    else
        print(
            op + " " + operand1 + ", " + operand2 + " "
            + commentPrefix + " " + comment);
}

// Prints a line of code to the buffer of the form:
// op $operand1, operand2 # comment
void outputStream::printTwoOperandCode(
    const string& op,
    int operand1,
    const string& operand2,
    const string& comment) {
    printTwoOperandCode(op, intToStr(operand1), operand2, comment);
}

// Prints a line of code to the buffer of the form:
// op operand1, $operand2 # comment
void outputStream::printTwoOperandCode(
    const string& op,
    const string& operand1,
    int operand2,
    const string& comment) {
    printTwoOperandCode(op, operand1, intToStr(operand2), comment);
}

// Prints a line of code to the buffer of the form:
// op $operand1, $operand2 # comment
// TODO Is this possible on the ia32 architecture?
void outputStream::printTwoOperandCode(
    const string& op,
    int operand1,
    int operand2,
    const string& comment) {
    printTwoOperandCode(op, intToStr(operand1), intToStr(operand2), comment);
}

// Prints a line of code to the buffer of the form:
// op operand1 # comment
void outputStream::printOneOperandCode(
    const string& op,
    const string& operand1,
    const string& comment) {
    if(comment.size() == 0)
        print(op + " " + operand1);
    else
        print(
            op + " " + operand1 + " " + commentPrefix
            + " " + comment);
}

// Prints a line of code to the buffer of the form:
// op $operand1 # comment
void outputStream::printOneOperandCode(
    const string& op,
    int operand1,
    const string& comment) {
    printOneOperandCode(op, intToStr(operand1), comment);
}

// Begins a section of assembly code that is offset by tabs
// # section for <str> begins here
void outputStream::beginSection(const string& str) {
    printNewLine();
    if(str != "" && str[str.size()-1] != ':')
        printComment("{ section for " + str + " begins here");
    else if(str != "")
        printCode(str);
    tabInc();
}

// Ends a section of assembly code that is offset by tabs
// Output is of the form:
// # section for <str> ends here
void outputStream::endSection(const string& str) {
    tabDec();
    if(str != "")
        printComment("} section for " + str + " ends here");
    printNewLine();
}

// Dumps the buffer to the output stream and empties it.
void outputStream::dumpBuffer() {
    dumpLazyBuffer();
    if(outFile == NULL)
		; // Do Nothing
    else if(buffer->str().size() > 0) {
        *outFile << buffer->str();
        delete buffer;
        buffer = new stringstream;
    }
}

// Empties the buffer without dumping it to the file.
void outputStream::emptyBuffer() {
    delete buffer;
	lazyBuffer = "";
    buffer = new stringstream;
}

// Merges an output stream into this stream
void outputStream::merge(outputStream* out) {
    out->dumpLazyBuffer();
    *buffer << out->bufferStr();
}

// Merges an output stream into this stream
// but waits until this one is dumped into the output stream
void outputStream::lazyMerge(outputStream* out) {
    out->dumpLazyBuffer();
    lazyBuffer += out->bufferStr();
}

// Dumps the lazy buffer into the buffer.
void outputStream::dumpLazyBuffer() {
    *buffer << lazyBuffer;
    lazyBuffer = "";
}

// Returns a string dump of the buffer.
string outputStream::bufferStr() const {
    return buffer->str();
}
