#ifndef _STACK_H_
#define _STACK_H_


#include "abstractStack.h"
#include "bareBonesLinkedList.h"


template < typename itemType >
class stack : public abstractStack< itemType > {

    private:

        static itemType ourErrorItem;

        virtual itemType & errorItemReference();
        virtual itemType const & errorItemConstReference() const;

        linkedList< itemType > myContents;

        virtual linkedList< itemType > & contentsReference();
        virtual linkedList< itemType > const & contentsConstReference() const;
        virtual void setContents(linkedList< itemType > const & l);

        mutable bool myError;

        virtual void setError(bool b) const;

    public:

        stack();
        stack(stack< itemType > const & original);

        virtual ~stack();

        virtual bool error() const;

        virtual bool isEmpty() const;

        virtual void push(itemType const & i);

        virtual void pop();
        virtual void pop(itemType & i);

        virtual itemType & topReference();
        virtual itemType const & topConstReference() const;

        stack< itemType > & operator =(stack< itemType > const & original);

    };


//
// Private Members
//


template < typename itemType >
itemType stack< itemType >::ourErrorItem;


template < typename itemType >
itemType & stack< itemType >::errorItemReference() {

    return ourErrorItem;

    }


template < typename itemType >
itemType const & stack< itemType >::errorItemConstReference() const {

    return ourErrorItem;

    }


template < typename itemType >
linkedList< itemType > & stack< itemType >::contentsReference() {

    return myContents;

    }


template < typename itemType >
linkedList< itemType > const & stack< itemType >::contentsConstReference() const {

    return myContents;

    }




template < typename itemType >
void stack< itemType >::setContents(linkedList< itemType > const & l) {

    linkedList< itemType > contentsEnd;

    contentsReference().destroy();
    l.duplicate(contentsReference(), contentsEnd);

    }


template < typename itemType >
void stack< itemType >::setError(bool b) const {

    myError = b;

    }


//
// Public Members
//


template < typename itemType >
stack< itemType >::stack()
        : myContents(), myError(false)
        {

    }


template < typename itemType >
stack< itemType >::stack(stack< itemType > const & original)
        : myContents(),
          myError(false)
        {

    linkedList< itemType > contentsEnd;

    original.contentsConstReference().duplicate(contentsReference(), contentsEnd);

    }


template < typename itemType >
stack< itemType >::~stack() {

    contentsReference().destroy();

    }


template < typename itemType >
bool stack< itemType >::error() const {

    return myError;

    }


template < typename itemType >
bool stack< itemType >::isEmpty() const {

    return contentsConstReference().isNull();

    }


template < typename itemType >
void stack< itemType >::push(itemType const & i) {

    setError(false);

    if (! error())
        contentsReference().insertFirst(i);

    }


template < typename itemType >
void stack< itemType >::pop() {

    setError(contentsConstReference().isNull());

    if (! error())
        contentsReference().removeFirst();

    }


template < typename itemType >
void stack< itemType >::pop(itemType & i) {

    i = topReference();
    pop();

    }


template < typename itemType >
itemType & stack< itemType >::topReference() {

    setError(contentsConstReference().isNull());

    if (! error())
        return contentsReference().headReference();
    else
        return errorItemReference();

    }


template < typename itemType >
itemType const & stack< itemType >::topConstReference() const {

    setError(contentsConstReference().isNull());

    if (! error())
        return contentsConstReference().headConstReference();
    else
        return errorItemConstReference();

    }


template < typename itemType >
stack< itemType > & stack< itemType >::operator =(stack< itemType > const & original) {

    if (this != & original) {

        setContents(original.contentsConstReference());
        setError(false);

        }

    return * this;

    }


#endif
