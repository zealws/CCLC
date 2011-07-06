// include the file libraries
#include <fstream>
#include <iostream>

// for operating system filesystem access
#include <unistd.h>

// include the scanner header
#include <FlexLexer.h>

// include the parser header
#include "error/error.h"
#include "scanner/scanner.h"
#include "programTree/programTreeVisitors.h"
#include "typeTree/typeTreeVisitors.h"
#include "programTree/syntaxTree.h"
#include "codeGenerator/codeGenerator.h"
#include "typeTree/typeTree.h"
#include "Library/orderedPair.h"
#include "bison/parser.hpp"
#include "strconv/strconv.h"
#include "options/options.h"
#include "commandParser/commandParser.h"
using namespace std;

// So we can see the parser's parsing function
int yyparse();

// Code to use for assembly
const string assemblerCommand = "as --gstabs --32 ";

// Code to use for linking the code
const string linkCommand = "gcc -m32 ";

/*
 * Extracts the filename (without an extension) from a filename.
 *
 * Also ignores prefixed directories.
 */
string getJustFilename(const string& original){
    // Return everything from the last / character to the last . character, exclusive
    if(original.find('/') == string::npos && original.find('.') == string::npos)
        // neither '/' nor '.' characters
        return original;
    else if(original.find('/') == string::npos)
        // no '/' character but there is a '.'
        return original.substr(0, original.rfind('.'));
    else if(original.find('.') == string::npos)
        // no '.' character
        return original.substr(original.rfind('/')+1);
    else
        return original.substr(original.rfind('/')+1, original.rfind('.')-original.rfind('/')-1);
}

int parseAndGenerateCode(const string& inputFilename) {

    istream* yyin = NULL;

    yyin = new fstream(inputFilename.data());

    string outputFilename = getJustFilename(inputFilename) + ".s";

    // create the scanner object
    scanner = new yyFlexLexer(yyin);

    // call the parser
    numErrors += yyparse();

    // if there weren't errors, continue
    if(numErrors == 0) {
        ofstream outStream(outputFilename.data());
        generateCode(&outStream, inputFilename);
    }

    delete yyin;
    delete scanner;
}

int linkAndAssemble(const string& inputFilename) {
    string cmd = assemblerCommand + "-o " + getJustFilename(inputFilename) + ".o "
                 + getJustFilename(inputFilename) + ".s";
    numErrors += system(cmd.data());

    // only continue if there weren't assembler errors
    // which there shouldn't be
    if(numErrors == 0) {
        cmd = linkCommand + "-o " + getJustFilename(inputFilename) +
              ".exe " + getJustFilename(inputFilename) + ".o";
        numErrors = system(cmd.data());
    }
}

/*
 * Returns true if the file specified by the filename is
 * readable by the current user.
 *
 * Uses access from the unistd.h header
 */
bool fileOkay(const string& filename){
    if( access(filename.data(), R_OK) == 0 )
        return true;
    else
        return false;
}

int main(int argc, char* argv[]) {

    commandParser p;
    p.parse(argc, argv);

    // Don't continue if there was some issue with the command line options
    if(p.success()) {
        for(int i = 0; i < p.inputFiles.size(); i++){
            numErrors = 0;
            if(p.inputFiles.size() > 1)
                cout << endl << endl << p.inputFiles[i] << endl << endl;
            if(not(fileOkay(p.inputFiles[i]))){
                fatalError("Unreadable or non-existant input file: " + p.inputFiles[i]);
            }
            else {
                parseAndGenerateCode(p.inputFiles[i]);
                if(numErrors == 0)
                    linkAndAssemble(p.inputFiles[i]);
            }
        }
    }
    return numErrors;

}
