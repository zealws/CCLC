#ifndef _ABSTRACTNARYTREE_H_
#define _ABSTRACTNARYTREE_H_


template < typename itemType >
class abstractNAryTree {

    public:

        virtual ~abstractNAryTree();

        virtual bool isNull() const = 0;
        virtual unsigned degree() const = 0;

        virtual itemType const & rootItemConstReference() const = 0;
        virtual itemType & rootItemReference() = 0;
        virtual void setRootItem(itemType const & i) = 0;

        virtual abstractNAryTree< itemType > const & subtreeConstReference(
            unsigned j
            ) const = 0;
        virtual abstractNAryTree< itemType > & subtreeReference(unsigned j) = 0;

    };


template < typename itemType >
abstractNAryTree< itemType >::~abstractNAryTree()
{

    }


#endif
