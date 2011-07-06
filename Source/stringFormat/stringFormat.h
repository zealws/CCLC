#ifndef _OUTPUT_STREAM_
#define _OUTPUT_STREAM_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Repeats a string a given number of times. Returns the result.
// This is a helper function that is not merged into the outputStream structure.
string repeatString(const string&, int);

// Returns the string form of an integer
// This is a helper function that is not merged into the outputStream structure.
string intToStr(int);

class outputStream {

private:

    // Output stream. This is the destination of any dump operations on the buffer.
    ostream* outFile;

    // Output buffer. This is dumped to the outFile when a dumpBuffer
    // operation is performed, or when the object is destroyed.
    stringstream* buffer;

    // The current tab depth for the outputStream
    mutable int tabSize;

    // Used to store buffers that have been added lazily to the output stream.
    string lazyBuffer;

protected:

    // Increments the tab size temporarily
    void tabInc() const;

    // Decrements the tab size temporarily
    void tabDec() const;

    // Dumps a string to the buffer.
    // Appends a newline to the end of the string.
    void print(const string&);

    // Dumps a string verbatim to the buffer.
    void printRAW(const string&);

public:

    // Creates an output stream without a specified output stream.
    outputStream();

    // Creates an output stream for a specific output stream.
    outputStream(ostream*);

    // Creates an output stream for a file.
    outputStream(const string& filename);

    // Destructor
    // Dumps the buffer to the output stream if it isn't empty.
    // DOES NOT DELETE THE OUTPUT STREAM POINTER
    ~outputStream();

    // Prints just a newline to the buffer.
    void printNewLine();

    // Print a line of code at the current tab level.
    void printCode(const string&);

    // Prints a comment at the current tab level.
    void printComment(const string&);

    // Prints a multiline comment to the buffer.
    void printBlockComment(const string&);

    // Prints a line of code to the buffer of the form:
    // op operand1, operand2 # comment
    void printTwoOperandCode(
        const string& op,
        const string& operand1,
        const string& operand2,
        const string& comment = "");

    // Prints a line of code to the buffer of the form:
    // op $operand1, operand2 # comment
    void printTwoOperandCode(
        const string& op,
        int operand1,
        const string& operand2,
        const string& comment = "");

    // Prints a line of code to the buffer of the form:
    // op operand1, $operand2 # comment
    void printTwoOperandCode(
        const string& op,
        const string& operand1,
        int operand2,
        const string& comment = "");

    // Prints a line of code to the buffer of the form:
    // op $operand1, $operand2 # comment
    // TODO Is this possible on the ia32 architecture?
    void printTwoOperandCode(
        const string& op,
        int operand1,
        int operand2,
        const string& comment = "");

    // Prints a line of code to the buffer of the form:
    // op operand1 # comment
    void printOneOperandCode(
        const string& op,
        const string& operand1,
        const string& comment = "");

    // Prints a line of code to the buffer of the form:
    // op $operand1 # comment
    void printOneOperandCode(
        const string& op,
        int operand1,
        const string& comment = "");

    // Begins a section of assembly code that is offset by tabs
    // # section for <str> begins here
    void beginSection(const string& = "");
    
    // Ends a section of assembly code that is offset by tabs
    // Output is of the form:
    // # section for <str> ends here
    void endSection(const string& = "");

    // Dumps the buffer to the output stream and empties it.
    void dumpBuffer();

    // Empties the buffer without dumping it to the file.
    void emptyBuffer();

    // Merges an output stream into this stream
    void merge(outputStream*);

    // Merges an output stream into this stream
    // but waits until this one is dumped into the output stream
    void lazyMerge(outputStream*);

    // Dumps the lazy buffer into the buffer.
    void dumpLazyBuffer();

    // Returns a string dump of the buffer.
    string bufferStr() const;
};

#endif