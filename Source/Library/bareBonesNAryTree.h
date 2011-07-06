#ifndef _BAREBONESNARYTREE_H_
#define _BAREBONESNARYTREE_H_


#include <vector>


using namespace std;


#include "abstractNAryTree.h"


template < typename itemType > class nAryTree;
template < typename itemType > class nAryTreeNode;


template < typename itemType >
class nAryTree : public abstractNAryTree< itemType > {

    private:

        nAryTreeNode< itemType > * myRootPtr;

        virtual nAryTreeNode< itemType > * const & rootPtrConstReference() const;
        virtual void setRootPtr(nAryTreeNode< itemType > * const & other);

        nAryTree(nAryTreeNode< itemType > * nodePtr);

    public:

        nAryTree();
        nAryTree(itemType const & i);
        nAryTree(
            itemType const & i,
            nAryTree< itemType > const & originalZeroSubtree,
            nAryTree< itemType > const & originalOneSubtree,
            nAryTree< itemType > const & originalTwoSubtree
            );
        nAryTree(
            itemType const & i,
            nAryTree< itemType > const & originalZeroSubtree,
            nAryTree< itemType > const & originalOneSubtree
            );
        nAryTree(
            itemType const & i,
            nAryTree< itemType > const & originalZeroSubtree
            );
        nAryTree(nAryTree< itemType > const & original);

        virtual ~nAryTree();

        virtual bool isNull() const;
        virtual unsigned degree() const;

        virtual itemType const & rootItemConstReference() const;
        virtual itemType & rootItemReference();
        virtual void setRootItem(itemType const & i);

        virtual nAryTree< itemType > const & subtreeConstReference(unsigned j) const;
        virtual nAryTree< itemType > & subtreeReference(unsigned j);
        virtual void setSubtree(unsigned j, nAryTree< itemType > const & other);

        virtual bool isIdentical(nAryTree< itemType > const & other) const;

        nAryTree< itemType > & operator =(
            nAryTree< itemType > const & original
            );

        virtual void duplicate(nAryTree< itemType > & copy) const;

        virtual void destroy();

    };


template < typename itemType >
class nAryTreeNode {

    private:

        static nAryTree< itemType > const ourNonExistentSubtree;

        virtual nAryTree< itemType > const & nonExistentSubtreeConstReference() const;

        itemType myRootItem;

        vector < nAryTree< itemType > > mySubtrees;

        virtual vector < nAryTree< itemType > > & subtreesReference();
        virtual vector < nAryTree< itemType > > const & subtreesConstReference() const;
        virtual void setSubtrees(vector < nAryTree< itemType > > const & other);

        virtual void expandDegree(unsigned d);

    public:

        nAryTreeNode();
        nAryTreeNode(itemType const & i);
        nAryTreeNode(
            itemType const & i,
            nAryTree< itemType > const & originalZeroSubtree,
            nAryTree< itemType > const & originalOneSubtree,
            nAryTree< itemType > const & originalTwoSubtree
            );
        nAryTreeNode(
            itemType const & i,
            nAryTree< itemType > const & originalZeroSubtree,
            nAryTree< itemType > const & originalOneSubtree
            );
        nAryTreeNode(
            itemType const & i,
            nAryTree< itemType > const & originalZeroSubtree
            );
        nAryTreeNode(nAryTreeNode< itemType > const & original);

        virtual ~nAryTreeNode();

        virtual unsigned degree() const;

        virtual itemType const & rootItemConstReference() const;
        virtual itemType & rootItemReference();
        virtual void setRootItem(itemType const & other);

        virtual nAryTree< itemType > const & subtreeConstReference(unsigned j) const;
        virtual nAryTree< itemType > & subtreeReference (unsigned j);
        virtual void setSubtree(unsigned j, nAryTree< itemType > const & other);

        nAryTreeNode< itemType > & operator =(
            nAryTreeNode< itemType > const & original
            );

    };


//
// A Bare-Bones n-Ary Tree Template Class
//


#include <cstddef>


//
// Class nAryTree
//


//
// Private members
//


template < typename itemType >
nAryTreeNode< itemType > * const & nAryTree< itemType >::rootPtrConstReference() const
{

    return myRootPtr;

    }


template < typename itemType >
void nAryTree< itemType >::setRootPtr(nAryTreeNode< itemType > * const & otherRootPtr)
{

    myRootPtr = otherRootPtr;

    }


template < typename itemType >
nAryTree< itemType >::nAryTree(nAryTreeNode< itemType > * nodePtr)
    : myRootPtr(nodePtr)
{

    }


//
// Public members
//


template < typename itemType >
nAryTree< itemType >::nAryTree()
    : myRootPtr(NULL)
{

    }


template < typename itemType >
nAryTree< itemType >::nAryTree(itemType const & i)
    : myRootPtr(new nAryTreeNode< itemType >(i))
{

    }


template < typename itemType >
nAryTree< itemType >::nAryTree(
    itemType const & i,
    nAryTree< itemType > const & originalZeroSubtree,
    nAryTree< itemType > const & originalOneSubtree,
    nAryTree< itemType > const & originalTwoSubtree
    )
    : myRootPtr(
        new nAryTreeNode< itemType >(
            i,
            originalZeroSubtree,
            originalOneSubtree,
            originalTwoSubtree
            )
        )
{

    }


template < typename itemType >
nAryTree< itemType >::nAryTree(
    itemType const & i,
    nAryTree< itemType > const & originalZeroSubtree,
    nAryTree< itemType > const & originalOneSubtree
    )
    : myRootPtr(new nAryTreeNode< itemType >(i, originalZeroSubtree, originalOneSubtree))
{

    }


template < typename itemType >
nAryTree< itemType >::nAryTree(
    itemType const & i,
    nAryTree< itemType > const & originalZeroSubtree
   )
    : myRootPtr(new nAryTreeNode< itemType >(i, originalZeroSubtree))
{

    }


template < typename itemType >
nAryTree< itemType >::nAryTree(nAryTree< itemType > const & original)
    : myRootPtr(original.rootPtrConstReference())
{

    }


template < typename itemType >
nAryTree< itemType >::~nAryTree()
{

    }


template < typename itemType >
bool nAryTree< itemType >::isNull() const
{

    return rootPtrConstReference() == NULL;

    }


template < typename itemType >
unsigned nAryTree< itemType >::degree() const
{

    return rootPtrConstReference() -> degree();

    }


template < typename itemType >
itemType const & nAryTree< itemType >::rootItemConstReference() const
{

    return rootPtrConstReference() -> rootItemConstReference();

    }


template < typename itemType >
itemType & nAryTree< itemType >::rootItemReference()
{

    return rootPtrConstReference() -> rootItemReference();

    }


template < typename itemType >
void nAryTree< itemType >::setRootItem(itemType const & i)
{

    rootPtrConstReference() -> setRootItem(i);

    }


template < typename itemType >
nAryTree< itemType > const & nAryTree< itemType >::subtreeConstReference(unsigned j) const
{

    return rootPtrConstReference() -> subtreeConstReference(j);

    }


template < typename itemType >
nAryTree< itemType > & nAryTree< itemType >::subtreeReference(unsigned j)
{

    return rootPtrConstReference() -> subtreeReference(j);

    }


template < typename itemType >
void nAryTree< itemType >::setSubtree(unsigned j, nAryTree< itemType > const & other)
{

    rootPtrConstReference() -> setSubtree(j, other);

    }


template < typename itemType >
bool nAryTree< itemType >::isIdentical(nAryTree< itemType > const & other) const
{

    return rootPtrConstReference() == other.rootPtrConstReference();

    }


template < typename itemType >
nAryTree< itemType > & nAryTree< itemType >::operator =(
    nAryTree< itemType > const & original
    )
{

    if (this != & original)
        setRootPtr(original.rootPtrConstReference());

    return * this;

    }


template < typename itemType >
void nAryTree< itemType >::duplicate(nAryTree< itemType > & copy) const
{

    if (isNull())
        copy = nAryTree< itemType >();
    else {
        copy = nAryTree< itemType >(rootItemConstReference());
        for (unsigned j = 0; j < degree(); ++ j)
            subtreeConstReference(j).duplicate(copy.subtreeReference(j));
        }

    }


template < typename itemType >
void nAryTree< itemType >::destroy()
{

    if (! isNull()) {
        for (unsigned j = 0; j < degree(); ++ j)
            subtreeReference(j).destroy();
        delete rootPtrConstReference();
        setRootPtr(NULL);
        }

    }


//
// Class nAryTreeNode
//


//
// Private members
//


template < typename itemType >
nAryTree< itemType > const nAryTreeNode< itemType >::ourNonExistentSubtree;


template < typename itemType >
nAryTree< itemType > const & nAryTreeNode< itemType >::nonExistentSubtreeConstReference() const
{

    return ourNonExistentSubtree;

    }


template < typename itemType >
vector < nAryTree< itemType > > & nAryTreeNode< itemType >::subtreesReference()
{

    return mySubtrees;

    }


template < typename itemType >
vector < nAryTree< itemType > > const & nAryTreeNode< itemType >::subtreesConstReference() const
{

    return mySubtrees;

    }


template < typename itemType >
void nAryTreeNode< itemType >::setSubtrees(vector < nAryTree< itemType > > const & other)
{

    mySubtrees = other;

    }


template < typename itemType >
void nAryTreeNode< itemType >::expandDegree(unsigned d)
{

    while (degree() < d)
        subtreesReference().push_back(nAryTree< itemType >());

    }


//
// Public members
//


template < typename itemType >
nAryTreeNode< itemType >::nAryTreeNode()
    : myRootItem(),
      mySubtrees()
{

    }


template < typename itemType >
nAryTreeNode< itemType >::nAryTreeNode(itemType const & i)
    : myRootItem(i),
      mySubtrees()
{

    }


template < typename itemType >
nAryTreeNode< itemType >::nAryTreeNode(
    itemType const & i,
    nAryTree< itemType > const & originalZeroSubtree,
    nAryTree< itemType > const & originalOneSubtree,
    nAryTree< itemType > const & originalTwoSubtree
    )
    : myRootItem(i),
      mySubtrees()
{

    subtreesReference().push_back(originalZeroSubtree);
    subtreesReference().push_back(originalOneSubtree);
    subtreesReference().push_back(originalTwoSubtree);

    }


template < typename itemType >
nAryTreeNode< itemType >::nAryTreeNode(
    itemType const & i,
    nAryTree< itemType > const & originalZeroSubtree,
    nAryTree< itemType > const & originalOneSubtree
    )
    : myRootItem(i),
      mySubtrees()
{

    subtreesReference().push_back(originalZeroSubtree);
    subtreesReference().push_back(originalOneSubtree);

    }


template < typename itemType >
nAryTreeNode< itemType >::nAryTreeNode(
    itemType const & i,
    nAryTree< itemType > const & originalZeroSubtree
    )
    : myRootItem(i),
      mySubtrees()
{

    subtreesReference().push_back(originalZeroSubtree);

    }


template < typename itemType >
nAryTreeNode< itemType >::nAryTreeNode(nAryTreeNode< itemType > const & original)
    : myRootItem(original.rootItemConstReference()),
      mySubtrees(original.subtreesConstReference())
{

    }


template < typename itemType >
nAryTreeNode< itemType >::~nAryTreeNode()
{

    }


template < typename itemType >
unsigned nAryTreeNode< itemType >::degree() const
{

    return subtreesConstReference().size();

    }


template < typename itemType >
itemType const & nAryTreeNode< itemType >::rootItemConstReference() const
{

    return myRootItem;

    }


template < typename itemType >
itemType & nAryTreeNode< itemType >::rootItemReference()
{

    return myRootItem;

    }


template < typename itemType >
void nAryTreeNode< itemType >::setRootItem(itemType const & other)
{

    myRootItem = other;

    }


template < typename itemType >
nAryTree< itemType > const & nAryTreeNode< itemType >::subtreeConstReference(unsigned j) const
{

    if (degree() < j + 1)
        return nonExistentSubtreeConstReference();
    else
        return subtreesConstReference()[j];

    }


template < typename itemType >
nAryTree< itemType > & nAryTreeNode< itemType >::subtreeReference(unsigned j)
{

    expandDegree(j + 1);

    return subtreesReference()[j];

    }


template < typename itemType >
void nAryTreeNode< itemType >::setSubtree(unsigned j, nAryTree< itemType > const & other)
{

    expandDegree(j + 1);

    subtreesReference()[j] = other;

    }


template < typename itemType >
nAryTreeNode< itemType > & nAryTreeNode< itemType >::operator =(
    nAryTreeNode< itemType > const & original
    )
{

    if (this != & original) {
        setRootItem(original.rootItemConstReference());
        setSubtrees(original.subtreesConstReference());
        }

    return * this;

    }


#endif
