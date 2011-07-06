#ifndef _BAREBONESLINKEDLIST_H_
#define _BAREBONESLINKEDLIST_H_


template < typename itemType > class linkedList;
template < typename itemType > class linkedListNode;


template < typename itemType >
class linkedList {

    private:

        linkedListNode< itemType > * myHeadPointer;

        virtual linkedListNode< itemType > * const & headPointerConstReference() const;

        linkedList(linkedListNode< itemType > * nodePointer);

    public:

        linkedList();
        virtual ~linkedList();

        virtual bool isNull() const;

        virtual itemType const & headConstReference() const;
        virtual itemType & headReference();
        virtual void setHead(itemType const & i);

        virtual linkedList< itemType > const & tailConstReference() const;
        virtual linkedList< itemType > & tailReference ();
        virtual void setTail(linkedList< itemType > const & ll);

        virtual void insertAfterFirst(itemType const & i);
        virtual void removeAfterFirst();

        virtual void insertFirst(itemType const & i);
        virtual void removeFirst();

        virtual bool isIdentical(linkedList< itemType > const & ll) const;

        virtual void duplicate(
            linkedList< itemType > & copy,
            linkedList< itemType > & copyLast
            ) const;

        virtual void destroy();

    };


template <class itemType>
class linkedListNode {

    private:

        itemType myHeadItem;
        linkedList< itemType > myTailList;

    public:

        linkedListNode();
        ~linkedListNode();

        virtual itemType const & headConstReference() const;
        virtual itemType & headReference();
        virtual void setHead(itemType const & i);

        virtual linkedList< itemType > const & tailConstReference() const;
        virtual linkedList< itemType > & tailReference();
        virtual void setTail(linkedList< itemType > const & ll);

    };


#include <cstddef>


using namespace std;


//
// Class linkedList
//


//
// Private members
//


template < typename itemType >
linkedListNode< itemType > * const & linkedList< itemType >::headPointerConstReference() const {

    return myHeadPointer;

    }


template < typename itemType >
linkedList< itemType >::linkedList(
        linkedListNode< itemType > * nodePointer
        )
        : myHeadPointer(nodePointer)
        {

    }


//
// Public members
//


template < typename itemType >
linkedList< itemType >::linkedList()
        : myHeadPointer(NULL)
        {

    }


template < typename itemType >
linkedList< itemType >::~linkedList() {

    }


template < typename itemType >
bool linkedList< itemType >::isNull() const {

    return headPointerConstReference() == NULL;

    }


template < typename itemType >
itemType const & linkedList< itemType >::headConstReference() const {

    return headPointerConstReference() -> headConstReference();

    }


template < typename itemType >
itemType & linkedList< itemType >::headReference() {

    return headPointerConstReference() -> headReference();

    }


template < typename itemType >
void linkedList< itemType >::setHead(itemType const & i) {

    headPointerConstReference() -> setHead(i);

    }


template < typename itemType >
linkedList< itemType > const & linkedList< itemType >::tailConstReference() const {

    return headPointerConstReference() -> tailConstReference();

    }


template < typename itemType >
linkedList< itemType > & linkedList< itemType >::tailReference() {

    return headPointerConstReference() -> tailReference();

    }


template < typename itemType >
void linkedList< itemType >::setTail(linkedList< itemType > const & ll) {

    headPointerConstReference() -> setTail(ll);

    }


template < typename itemType >
void linkedList< itemType >::insertAfterFirst(itemType const & i) {

    linkedList< itemType > ptrToNewNode(new linkedListNode< itemType >);

    ptrToNewNode.setHead(i);
    ptrToNewNode.setTail(tailConstReference());
    setTail(ptrToNewNode);

    }


template < typename itemType >
void linkedList< itemType >::removeAfterFirst() {

    linkedList< itemType > ptrToOldNode = tailConstReference();

    setTail(tailConstReference().tailConstReference());
    delete ptrToOldNode.headPointerConstReference();

    }


template < typename itemType >
void linkedList< itemType >::insertFirst(itemType const & i) {

    linkedList< itemType > ptrToNewNode(new linkedListNode< itemType >);

    ptrToNewNode.setHead(i);
    ptrToNewNode.setTail(headPointerConstReference());
    * this = ptrToNewNode;

    }


template < typename itemType >
void linkedList< itemType >::removeFirst() {

    linkedList< itemType > ptrToOldNode = * this;

    * this = tailConstReference();
    delete ptrToOldNode.headPointerConstReference();

    }


template < typename itemType >
bool linkedList< itemType >::isIdentical(linkedList< itemType > const & ll) const {

    return headPointerConstReference() == ll.headPointerConstReference();

    }


template < typename itemType >
void linkedList< itemType >::duplicate(
        linkedList< itemType > & copy,
        linkedList< itemType > & copyLast
        ) const {

    copy = linkedList< itemType >();

    if (! isNull()) {
        copy.insertFirst(headConstReference());
        copyLast = copy;
        for (linkedList< itemType > thisCurrent = tailConstReference();
                ! thisCurrent.isNull();
                copyLast = copyLast.tailConstReference(),
                    thisCurrent = thisCurrent.tailConstReference())
            copyLast.insertAfterFirst(thisCurrent.headConstReference());
        }

    }


template < typename itemType >
void linkedList< itemType >::destroy() {

    while (! isNull())
        removeFirst();

    }


//
// Class linkedListNode
//


//
// Public members
//


template < typename itemType >
linkedListNode< itemType >::linkedListNode()
        : myHeadItem(),
          myTailList()
        {

    }


template < typename itemType >
linkedListNode< itemType >::~linkedListNode() {

    }


template < typename itemType >
itemType const & linkedListNode< itemType >::headConstReference() const {

    return myHeadItem;

    }


template < typename itemType >
itemType & linkedListNode< itemType >::headReference() {

    return myHeadItem;

    }


template < typename itemType >
void linkedListNode< itemType >::setHead(itemType const & i) {

    myHeadItem = i;

    }


template < typename itemType >
linkedList< itemType > const & linkedListNode< itemType >::tailConstReference() const {

    return myTailList;

    }


template < typename itemType >
linkedList< itemType > & linkedListNode< itemType >::tailReference() {

    return myTailList;

    }


template < typename itemType >
void linkedListNode< itemType >::setTail(linkedList< itemType > const & ll) {

    myTailList = ll;

    }


#endif
