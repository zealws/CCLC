#include <string>
#include <cstdlib>

using namespace std;


#include "../Library/levelStructuredDictionary.h"
#include "symbolTable.h"
#include "../typeTree/typeTree.h"

/*
 * symbolDeclaration
 */

/* public: */

symbolDeclaration::symbolDeclaration()
    : lineNo(0), name(""), typePtr(NULL) {
    // Do Nothing
}

symbolDeclaration::symbolDeclaration(const unsigned& initLineNo,
                                     const string& initName,
                                     typeTree* initTypePtr)
    : lineNo(initLineNo), name(initName), typePtr(initTypePtr) {
    // Do Nothing
}

symbolDeclaration::~symbolDeclaration() {
    //delete typePtr;
}

unsigned symbolDeclaration::lineNumber() {
    return lineNo;
}

string symbolDeclaration::identifier() {
    return name;
}

typeTree* symbolDeclaration::type() {
    return typePtr;
}

////
//// symbolTable Class
////

//
// Private Members
//

// The hash function
unsigned symbolTable::ourFold(string const & key)
{
    /*
     * I decided on this particular hash function because it computes the hash
     * values in linear time and spreads things over the entire range of values
     * for an integer or unsigned integer in just a few hundred characters.
     * 
     * In the future I will check for a more
     * suitable and efficient hash function.
     */
    unsigned sum = 0;
    
    for(int i = 0; i < key.size(); i++){
        sum += (key[i]-47)*(key[i]-47)*(i+1)*(i+1);
    }
    return sum;
}


/*
 * References to the dictionary
 */
levelStructuredDictionary< string, symbolDeclaration > &
    symbolTable::dictionaryReference()
{

    return myDictionary;

    }


levelStructuredDictionary< string, symbolDeclaration > const &
    symbolTable::dictionaryConstReference() const
{

    return myDictionary;

    }

// Returns a pointer to our fold function
unsigned (* symbolTable::fold() const)(string const & key)
{

    return ourFold;

    }


//
// Public Members
//

// Constructor
symbolTable::symbolTable()
    : myDictionary(fold())
{

    }

// Copy constructor
symbolTable::symbolTable(symbolTable const & original)
    : myDictionary(original.dictionaryConstReference())
{

    }

// Destructor
// Also destroys the associated dictionary
symbolTable::~symbolTable()
{

    }

// Assignment operator
symbolTable & symbolTable::operator =(symbolTable const & original)
{

    if (this != & original) {

        myDictionary = original.dictionaryConstReference();

        }

    return * this;

    }

// Returns true if the last operation was a success, false otherwise
bool symbolTable::success() const
{

    return dictionaryConstReference().success();

    }

// Returns the symbolDeclaration of the identifier
// that was the subject of the last successful operation
symbolDeclaration& symbolTable::successAddress()
{

    return dictionaryReference().successItemReference();

    }

// Enters a new scope
void symbolTable::enterScope()
{

    dictionaryReference().enterLevel();

    }

// Leaves a scope
void symbolTable::leaveScope()
{

    dictionaryReference().leaveLevel();

    }

// Inserts an identifier into the current scope with it's line number
void symbolTable::insert(string const & identifier, symbolDeclaration const & declr)
{

    dictionaryReference().insert(identifier, declr);

    }

// Retrieves an identifier from the deepest scope possible
void symbolTable::retrieve(string const & identifier) const
{

    dictionaryConstReference().retrieve(identifier);

    }
