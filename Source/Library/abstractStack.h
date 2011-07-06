#ifndef _ABSTRACTSTACK_H_
#define _ABSTRACTSTACK_H_


template < typename itemType >
class abstractStack {

    public:

        virtual ~abstractStack();

        virtual bool error() const = 0;

        virtual bool isEmpty() const = 0;

        virtual void push(itemType const & i) = 0;

        virtual void pop() = 0;
        virtual void pop(itemType & i) = 0;

        virtual itemType & topReference() = 0;
        virtual itemType const & topConstReference() const = 0;

    };


template < typename itemType >
abstractStack< itemType >::~abstractStack()
{

    }


#endif
