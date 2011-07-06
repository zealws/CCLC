#include <string>
#include <iostream>
#include <vector>
#include "../options/options.h"
#include "../error/error.h"
#include "commandParser.h"

using namespace std;

//
// commandParser
//

// Protected

string commandParser::usage() const {
return
"\
Usage: \n\
cclc [OPTIONS] FILES\n\
Options can be one of:\n\
    -v            : print verbose error messages\n\
                    for information about verbose error reporting,\n\
                    see Source/options/options.h\n\
    -h            : display this help message and exit\n\
    -m1           : Try it and find out.\n\
    -m2           : Try it and find out.\n\
    \n\
    Output is placed in a file with the same root name as the input,\n\
    but with an appropriate extension.\n";
}

bool commandParser::isValid(const string& str) const {
    return lookup(str) != npos;
}

void commandParser::error(const string& str) {
    cerr << "Invalid command line argument: " << str << endl;
    numErrors++;
}

void commandParser::activate(const string& str) {
    if(str == "-h") {
        numErrors++;
    }
    if(str == "-a") {
        printWarning("use of the -a option is deprecated.");
        assembleOutput = true;
    }
    if(str == "-v") {
        verboseMessages = true;
    }
    if(str == "-m1") {
        useMessage1 = true;
    }
    if(str == "-m2") {
        useMessage2 = true;
    }
}

int commandParser::lookup(const string& str) const {
    for(int i = 0; i < argList.size(); i++){
        if(argList[i].first == str)
            return i;
    }
    return npos;
}

// Public

commandParser::commandParser()
    : numErrors(0), assembleOutput(false) {
    argList.push_back(commandArgument("-a", 1));
    argList.push_back(commandArgument("-h", 1));
    argList.push_back(commandArgument("-v", 1));
    argList.push_back(commandArgument("-m1", 1));
    argList.push_back(commandArgument("-m2", 1));
}

void commandParser::parse(const int argc, const char* const argv[]) {
    for(int i = 1; i < argc;){
        if(isValid(string(argv[i]))) {
            activate(argv[i]);
            i += argList[lookup(argv[i])].second;
        }
        else {
            inputFiles.push_back(string(argv[i]));
            i += 1;
        }
    }
    if(error() || inputFiles.size() == 0)
        cerr << usage() << endl;
}

bool commandParser::error() const {
    return numErrors != 0;
}

bool commandParser::success() const {
    return numErrors == 0;
}

bool commandParser::assemble() const {
    return assembleOutput;
}
