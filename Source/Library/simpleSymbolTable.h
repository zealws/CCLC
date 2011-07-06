#ifndef _SIMPLESYMBOLTABLE_H_
#define _SIMPLESYMBOLTABLE_H_


#include <string>


using namespace std;


#include "levelStructuredDictionary.h"


class simpleSymbolTable {

    private:

        static unsigned ourFold(string const & key);

        levelStructuredDictionary< string, unsigned > myDictionary;

        virtual levelStructuredDictionary< string, unsigned > & dictionaryReference();
        virtual levelStructuredDictionary< string, unsigned > const & dictionaryConstReference() const;

        unsigned myNextFreeAddress;

        virtual unsigned & nextFreeAddressReference();
        virtual unsigned const & nextFreeAddressConstReference() const;

        virtual void incrementNextFreeAddress();

        virtual unsigned (* fold() const)(string const & key);


    public:

        simpleSymbolTable();
        simpleSymbolTable(simpleSymbolTable const & original);

        virtual ~simpleSymbolTable();

        simpleSymbolTable & operator =(simpleSymbolTable const & original);

        virtual bool success() const;

        virtual unsigned successAddress() const;

        virtual unsigned amountOfStorageAllocated() const;

        virtual void enterScope();

        virtual void leaveScope();

        virtual void insert(string const & identifier);

        virtual void retrieve(string const & identifier) const;

    };


#endif
