#ifndef _COMMAND_PARSER_
#define _COMMAND_PARSER_

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class commandParser {
private:

    typedef pair<string, int> commandArgument;

    vector<commandArgument> argList;

    int numErrors;

    bool assembleOutput;

protected:

    string usage() const;
    
    bool isValid(const string&) const;

    void error(const string&);

    void activate(const string&);

    int lookup(const string&) const;

    static const int npos = -1;

public:

    commandParser();

    vector<string> inputFiles;

    void parse(const int, const char* const []);

    bool error() const;

    bool success() const;

    bool assemble() const;
};

#endif