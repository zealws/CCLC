#ifndef _ABSTRACTLEVELSTRUCTUREDDICTIONARY_H_
#define _ABSTRACTLEVELSTRUCTUREDDICTIONARY_H_


template < typename keyType, typename itemType >
class abstractLevelStructuredDictionary {

    public :

        virtual ~abstractLevelStructuredDictionary();

        virtual bool success() const = 0;

        virtual unsigned successLevelNumber() const = 0;

        virtual itemType & successItemReference() = 0;
        virtual itemType const & successItemConstReference() const = 0;

        virtual unsigned currentLevelNumber() const = 0;

        virtual void enterLevel() = 0;

        virtual void leaveLevel() = 0;

        virtual void insert(
            keyType const & key,
            itemType const & item
            ) = 0;

        virtual void retrieve(keyType const & key) const = 0;

    };


template < typename keyType, typename itemType >
abstractLevelStructuredDictionary< keyType, itemType >::~abstractLevelStructuredDictionary()
{

    }


#endif
