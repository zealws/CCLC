/*
* This file and the accompanying symbolTable.cpp are borrowed in large
* part from the simpleSymbolTable class provided in lecture.
*
* The modifications I have made are:
*
*      Replacing the fold function to be a bit more suitable.
*
*      Reformatting the class so that it could not only keep track of
*      identifier names, but also the line numbers they were declared on.
*      I found this rather helpful when reporting type declaration errors.
*
*      Added a few comments, as much for my own sake as for others.
*/

#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_


#include <string>


using namespace std;


#include "../Library/levelStructuredDictionary.h"
#include "../typeTree/typeTree.h"

/*
* symbolDeclaration Class
*
* Contains some members that would be goot to hang onto for variable declarations
*/
class symbolDeclaration {
private:
    unsigned int lineNo;
    string name;
    typeTree* typePtr;

protected:

public:
    symbolDeclaration();

    symbolDeclaration(const unsigned& initLineNo,
                    const string& initName,
                    typeTree* initTypePtr);

    ~symbolDeclaration();

    unsigned lineNumber();

    string identifier();

    typeTree* type();

    // Made public so we can edit it freely:
    int lexicalLevel;
    int paramIndex;
    int totalParamSize;
};

/*
* symbolTable class
*/
class symbolTable {
private:

    // The hash function
    static unsigned ourFold(string const & key);

    levelStructuredDictionary< string, symbolDeclaration > myDictionary;

    /*
    * References to the dictionary
    */
    virtual levelStructuredDictionary< string, symbolDeclaration > &
        dictionaryReference();
    virtual levelStructuredDictionary< string, symbolDeclaration > const &
        dictionaryConstReference() const;

    // Returns a pointer to our fold function
    virtual unsigned (* fold() const)(string const & key);


public:
    // Constructor
    symbolTable();

    // Copy constructor
    symbolTable(symbolTable const & original);

    // Destructor
    // Also destroys the associated dictionary
    virtual ~symbolTable();

    // Assignment operator
    symbolTable & operator =(symbolTable const & original);

    // Returns true if the last operation was a success, false otherwise
    virtual bool success() const;

    // Returns the symbolDeclaration of the identifier
    // that was the subject of the last successful operation
    virtual symbolDeclaration& successAddress();

    // Enters a new scope
    virtual void enterScope();

    // Leaves a scope
    virtual void leaveScope();

    // Inserts an identifier into the current scope with it's line number
    virtual void insert(string const & identifier, symbolDeclaration const & declr);

    // Retrieves an identifier from the deepest scope possible
    virtual void retrieve(string const & identifier) const;

};

#endif
