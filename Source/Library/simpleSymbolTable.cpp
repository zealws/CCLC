#include <string>


using namespace std;


#include "levelStructuredDictionary.h"
#include "simpleSymbolTable.h"


//
// Private Members
//


unsigned simpleSymbolTable::ourFold(string const & key)
{

    unsigned sum = 0;

    for (unsigned j = 0; j < key.length(); ++ j)
        sum += int(key[ j ]);

    return sum;

    }


levelStructuredDictionary< string, unsigned > & simpleSymbolTable::dictionaryReference()
{

    return myDictionary;

    }


levelStructuredDictionary< string, unsigned > const & simpleSymbolTable::dictionaryConstReference() const
{

    return myDictionary;

    }


unsigned & simpleSymbolTable::nextFreeAddressReference()
{

    return myNextFreeAddress;

    }


unsigned const & simpleSymbolTable::nextFreeAddressConstReference() const
{

    return myNextFreeAddress;

    }


void simpleSymbolTable::incrementNextFreeAddress()
{

    ++ nextFreeAddressReference();

    }


unsigned (* simpleSymbolTable::fold() const)(string const & key)
{

    return ourFold;

    }


//
// Public Members
//


simpleSymbolTable::simpleSymbolTable()
    : myDictionary(fold()),
      myNextFreeAddress(0)
{

    }


simpleSymbolTable::simpleSymbolTable(simpleSymbolTable const & original)
    : myDictionary(original.dictionaryConstReference()),
      myNextFreeAddress(original.nextFreeAddressConstReference())
{

    }


simpleSymbolTable::~simpleSymbolTable()
{

    }


simpleSymbolTable & simpleSymbolTable::operator =(simpleSymbolTable const & original)
{

    if (this != & original) {

        myDictionary = original.dictionaryConstReference();
        myNextFreeAddress = original.nextFreeAddressConstReference();

        }

    return * this;

    }


bool simpleSymbolTable::success() const
{

    return dictionaryConstReference().success();

    }


unsigned simpleSymbolTable::successAddress() const
{

    return dictionaryConstReference().successItemConstReference();

    }


unsigned simpleSymbolTable::amountOfStorageAllocated() const
{

    return nextFreeAddressConstReference();

    }


void simpleSymbolTable::enterScope()
{

    dictionaryReference().enterLevel();

    }


void simpleSymbolTable::leaveScope()
{

    dictionaryReference().leaveLevel();

    }


void simpleSymbolTable::insert(string const & identifier)
{

    dictionaryReference().insert(identifier, nextFreeAddressConstReference());

    if (success())
        incrementNextFreeAddress();

    }


void simpleSymbolTable::retrieve(string const & identifier) const
{

    dictionaryConstReference().retrieve(identifier);

    }
