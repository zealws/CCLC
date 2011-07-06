#ifndef _TYPE_TREEVISITORS_H_
#define _TYPE_TREEVISITORS_H_


#include <vector>
#include <typeinfo>


using namespace std;


#include "../Library/orderedPair.h"
#include "typeTree.h"
#include "typeTreeVisitorsForwards.h"


class abstractTypeTreeVisitor {

    private:

    public:

        virtual ~abstractTypeTreeVisitor();

        virtual void visitIntTypeTreeNode(intTypeTreeNode* visitedNodePtr) = 0;
        virtual void visitTrivTypeTreeNode(trivTypeTreeNode* visitedNodePtr) = 0;
        virtual void visitImmutTypeTreeNode(immutTypeTreeNode* visitedNodePtr) = 0;
        virtual void visitConTypeTreeNode(conTypeTreeNode* visitedNodePtr) = 0;
        virtual void visitRefTypeTreeNode(refTypeTreeNode* visitedNodePtr) = 0;
        virtual void visitRefvecTypeTreeNode(refvecTypeTreeNode* visitedNodePtr) = 0;
        virtual void visitFunTypeTreeNode(funTypeTreeNode* visitedNodePtr) = 0;

    };


template < typename visitResultType >
class singleDispatchTypeTreeVisitor : public abstractTypeTreeVisitor {

    public:

        typedef singleDispatchTypeTreeVisitor< visitResultType > thisVisitorType;
        typedef visitResultType (* visitCaseFn)(thisVisitorType &, typeTreeNode *);
        typedef visitResultType (* visitExecutor)(visitCaseFn, thisVisitorType &, typeTreeNode *);

    private:

        vector<
            orderedPair< type_info const *, orderedPair< visitCaseFn, visitExecutor > >
            > myDispatchTable;

        typeTreeNode * myToBeVisitedNodePtr;

        typeTreeNode * & toBeVisitedNodePtrReference();
        typeTreeNode * const & toBeVisitedNodePtrConstReference() const;

    public:

        singleDispatchTypeTreeVisitor();

        template < typename nodeType >
        void add(visitResultType (* callback)(thisVisitorType &, nodeType *));

        virtual visitResultType dispatch(typeTreeNode * visitedNodePtr);

        virtual visitResultType defaultCase(typeTreeNode * visitedNodePtr) = 0;

        virtual void visitIntTypeTreeNode(intTypeTreeNode* visitedNodePtr);
        virtual void visitTrivTypeTreeNode(trivTypeTreeNode* visitedNodePtr);
        virtual void visitImmutTypeTreeNode(immutTypeTreeNode* visitedNodePtr);
        virtual void visitConTypeTreeNode(conTypeTreeNode* visitedNodePtr);
        virtual void visitRefTypeTreeNode(refTypeTreeNode* visitedNodePtr);
        virtual void visitRefvecTypeTreeNode(refvecTypeTreeNode* visitedNodePtr);
        virtual void visitFunTypeTreeNode(funTypeTreeNode* visitedNodePtr);

        virtual visitResultType visit(typeTree & visited);

    };


class predicateSingleDispatchTypeTreeVisitor : public singleDispatchTypeTreeVisitor< bool > {

    private:

        predicateSingleDispatchTypeTreeVisitor(predicateSingleDispatchTypeTreeVisitor const & other);
            // leave unimplemented
        predicateSingleDispatchTypeTreeVisitor & operator =(predicateSingleDispatchTypeTreeVisitor const & other);
            // leave unimplemented

    public:

        predicateSingleDispatchTypeTreeVisitor();

        virtual bool defaultCase(typeTreeNode * visitedNodePtr);

    };


template < typename visitResultType >
class doubleDispatchTypeTreeVisitor : public abstractTypeTreeVisitor {

    public:

        typedef doubleDispatchTypeTreeVisitor< visitResultType > thisVisitorType;
        typedef visitResultType (* visitCaseFn)(thisVisitorType &, typeTreeNode *, typeTreeNode *);
        typedef visitResultType (* visitExecutor)(visitCaseFn, thisVisitorType &, typeTreeNode *, typeTreeNode *);

    private:

        vector<
            orderedPair<
                orderedPair< type_info const *, type_info const * >,
                orderedPair< visitCaseFn, visitExecutor >
                >
            > myDispatchTable;

        typeTreeNode * myToBeVisitedNodePtr;

        typeTreeNode * & toBeVisitedNodePtrReference();
        typeTreeNode * const & toBeVisitedNodePtrConstReference() const;

        typeTreeNode * myToBeVisitedNodePtr01;

        typeTreeNode * & toBeVisitedNodePtr01Reference();
        typeTreeNode * const & toBeVisitedNodePtr01ConstReference() const;

        typeTreeNode * myToBeVisitedNodePtr02;

        typeTreeNode * & toBeVisitedNodePtr02Reference();
        typeTreeNode * const & toBeVisitedNodePtr02ConstReference() const;

    public:

        doubleDispatchTypeTreeVisitor();

        template < typename nodeType01, typename nodeType02 >
        void add(visitResultType (* callback)(thisVisitorType &, nodeType01 *, nodeType02 *));

        virtual visitResultType dispatch(
            typeTreeNode * visitedNodePtr01,
            typeTreeNode * visitedNodePtr02
            );

        virtual visitResultType defaultCase(
            typeTreeNode * visitedNodePtr01,
            typeTreeNode * visitedNodePtr02
            ) = 0;

            virtual void visitIntTypeTreeNode(intTypeTreeNode* visitedNodePtr);
            virtual void visitTrivTypeTreeNode(trivTypeTreeNode* visitedNodePtr);
            virtual void visitImmutTypeTreeNode(immutTypeTreeNode* visitedNodePtr);
            virtual void visitConTypeTreeNode(conTypeTreeNode* visitedNodePtr);
            virtual void visitRefTypeTreeNode(refTypeTreeNode* visitedNodePtr);
            virtual void visitRefvecTypeTreeNode(refvecTypeTreeNode* visitedNodePtr);
            virtual void visitFunTypeTreeNode(funTypeTreeNode* visitedNodePtr);

        virtual visitResultType visit(typeTree & visited01, typeTree & visited02);

    };


class predicateDoubleDispatchTypeTreeVisitor : public doubleDispatchTypeTreeVisitor< bool > {

    private:

        predicateDoubleDispatchTypeTreeVisitor(predicateDoubleDispatchTypeTreeVisitor const & other);
            // leave unimplemented
        predicateDoubleDispatchTypeTreeVisitor & operator =(predicateDoubleDispatchTypeTreeVisitor const & other);
            // leave unimplemented

    public:

        predicateDoubleDispatchTypeTreeVisitor();

        virtual bool defaultCase(
            typeTreeNode * visitedNodePtr01,
            typeTreeNode * visitedNodePtr02
            );

    };


////////
//////// class singleDispatchTypeTreeVisitor
////////


////
//// private members
////


template < typename visitResultType >
typeTreeNode * & singleDispatchTypeTreeVisitor< visitResultType >::toBeVisitedNodePtrReference() {

    return myToBeVisitedNodePtr;

    }


template < typename visitResultType >
typeTreeNode * const & singleDispatchTypeTreeVisitor< visitResultType >::toBeVisitedNodePtrConstReference() const {

    return myToBeVisitedNodePtr;

    }


////
//// public members
////


template < typename visitResultType >
singleDispatchTypeTreeVisitor< visitResultType >::singleDispatchTypeTreeVisitor()
        : myToBeVisitedNodePtr(0)
        {

    }


template < typename visitResultType >
template < typename nodeType >
void singleDispatchTypeTreeVisitor< visitResultType >::add(visitResultType (* callback)(thisVisitorType &, nodeType *)) {

    struct local {

        static visitResultType execute(
                visitCaseFn callback,
                thisVisitorType & thisVisitor,
                typeTreeNode * visitedNodePtr
                ) {

            return
                reinterpret_cast< visitResultType (*)(thisVisitorType &, nodeType *) >(callback)(
                    thisVisitor,
                    static_cast< nodeType * >(visitedNodePtr)
                    );

            };

        };

    myDispatchTable.push_back(
        orderedPair< type_info const *, orderedPair< visitCaseFn, visitExecutor > >(
            & typeid(nodeType),
            orderedPair< visitCaseFn, visitExecutor >(
                reinterpret_cast< visitCaseFn >(callback),
                local::execute
                )
            )
        );

    }


template < typename visitResultType >
visitResultType singleDispatchTypeTreeVisitor< visitResultType >::dispatch(
        typeTreeNode * visitedNodePtr
        ) {

    unsigned j;

    for (j = 0;
            j < myDispatchTable.size()
                && typeid(* visitedNodePtr) != * myDispatchTable[ j ].firstConstReference();
            ++ j)
        ;

    if (j < myDispatchTable.size())

        return
            myDispatchTable[ j ].secondConstReference().secondConstReference()(
                myDispatchTable[ j ].secondConstReference().firstConstReference(),
                * this,
                visitedNodePtr
                );

    else

        return defaultCase(visitedNodePtr);

    }

template < typename visitResultType >
void singleDispatchTypeTreeVisitor< visitResultType >::visitIntTypeTreeNode(intTypeTreeNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}
template < typename visitResultType >
void singleDispatchTypeTreeVisitor< visitResultType >::visitTrivTypeTreeNode(trivTypeTreeNode* visitedNodePtr) {
    toBeVisitedNodePtrReference() = visitedNodePtr;
}
template < typename visitResultType >
void singleDispatchTypeTreeVisitor< visitResultType >::visitImmutTypeTreeNode(immutTypeTreeNode* visitedNodePtr) {
    toBeVisitedNodePtrReference() = visitedNodePtr;
}
template < typename visitResultType >
void singleDispatchTypeTreeVisitor< visitResultType >::visitConTypeTreeNode(conTypeTreeNode* visitedNodePtr) {
    toBeVisitedNodePtrReference() = visitedNodePtr;
}
template < typename visitResultType >
void singleDispatchTypeTreeVisitor< visitResultType >::visitRefTypeTreeNode(refTypeTreeNode* visitedNodePtr) {
    toBeVisitedNodePtrReference() = visitedNodePtr;
}
template < typename visitResultType >
void singleDispatchTypeTreeVisitor< visitResultType >::visitRefvecTypeTreeNode(refvecTypeTreeNode* visitedNodePtr) {
    toBeVisitedNodePtrReference() = visitedNodePtr;
}
template < typename visitResultType >
void singleDispatchTypeTreeVisitor< visitResultType >::visitFunTypeTreeNode(funTypeTreeNode* visitedNodePtr) {
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
visitResultType singleDispatchTypeTreeVisitor< visitResultType >::visit(typeTree & visited) {

    visited.accept(* this);
    return dispatch(toBeVisitedNodePtrConstReference());

    }


////////
//////// class doubleDispatchTypeTreeVisitor
////////


////
//// private members
////


template < typename visitResultType >
typeTreeNode * & doubleDispatchTypeTreeVisitor< visitResultType >::toBeVisitedNodePtrReference() {

    return myToBeVisitedNodePtr;

    }


template < typename visitResultType >
typeTreeNode * const & doubleDispatchTypeTreeVisitor< visitResultType >::toBeVisitedNodePtrConstReference() const {

    return myToBeVisitedNodePtr;

    }


template < typename visitResultType >
typeTreeNode * & doubleDispatchTypeTreeVisitor< visitResultType >::toBeVisitedNodePtr01Reference() {

    return myToBeVisitedNodePtr01;

    }


template < typename visitResultType >
typeTreeNode * const & doubleDispatchTypeTreeVisitor< visitResultType >::toBeVisitedNodePtr01ConstReference() const {

    return myToBeVisitedNodePtr01;

    }


template < typename visitResultType >
typeTreeNode * & doubleDispatchTypeTreeVisitor< visitResultType >::toBeVisitedNodePtr02Reference() {

    return myToBeVisitedNodePtr02;

    }


template < typename visitResultType >
typeTreeNode * const & doubleDispatchTypeTreeVisitor< visitResultType >::toBeVisitedNodePtr02ConstReference() const {

    return myToBeVisitedNodePtr02;

    }


////
//// public members
////


template < typename visitResultType >
doubleDispatchTypeTreeVisitor< visitResultType >::doubleDispatchTypeTreeVisitor()
        : myToBeVisitedNodePtr(0),
          myToBeVisitedNodePtr01(0),
          myToBeVisitedNodePtr02(0)
        {

    }


template < typename visitResultType >
template < typename nodeType01, typename nodeType02 >
void doubleDispatchTypeTreeVisitor< visitResultType >::add(
        visitResultType (* callback)(thisVisitorType &, nodeType01 *, nodeType02 *)
        ) {

    struct local {

        static visitResultType execute(
                visitCaseFn callback,
                thisVisitorType & thisVisitor,
                typeTreeNode * visitedNodePtr01,
                typeTreeNode * visitedNodePtr02
                ) {

            return
                reinterpret_cast< visitResultType (*)(thisVisitorType &, nodeType01 *, nodeType02 *) >(callback)(
                    thisVisitor,
                    static_cast< nodeType01 * >(visitedNodePtr01),
                    static_cast< nodeType02 * >(visitedNodePtr02)
                    );

            };

        };

    myDispatchTable.push_back(
        orderedPair< orderedPair < type_info const *, type_info const * >, orderedPair< visitCaseFn, visitExecutor > >(
            orderedPair < type_info const *, type_info const * >(
                & typeid(nodeType01),
                & typeid(nodeType02)
                ),
            orderedPair< visitCaseFn, visitExecutor >(
                reinterpret_cast< visitCaseFn >(callback),
                local::execute
                )
            )
        );

    }


template < typename visitResultType >
visitResultType doubleDispatchTypeTreeVisitor< visitResultType >::dispatch(
        typeTreeNode * visitedNodePtr01,
        typeTreeNode * visitedNodePtr02
        ) {

    unsigned j;

    for (j = 0;
            j < myDispatchTable.size()
                && (typeid(* visitedNodePtr01)
                        != * myDispatchTable[ j ].firstConstReference().firstConstReference()
                    || typeid(* visitedNodePtr02)
                            != * myDispatchTable[ j ].firstConstReference().secondConstReference());
            ++ j)
        ;

    if (j < myDispatchTable.size())

        return
            myDispatchTable[ j ].secondConstReference().secondConstReference()(
                myDispatchTable[ j ].secondConstReference().firstConstReference(),
                * this,
                visitedNodePtr01,
                visitedNodePtr02
                );

    else

        return defaultCase(visitedNodePtr01, visitedNodePtr02);

    }

template < typename visitResultType >
void doubleDispatchTypeTreeVisitor< visitResultType >::visitIntTypeTreeNode(intTypeTreeNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}
template < typename visitResultType >
void doubleDispatchTypeTreeVisitor< visitResultType >::visitTrivTypeTreeNode(trivTypeTreeNode* visitedNodePtr) {
    toBeVisitedNodePtrReference() = visitedNodePtr;
}
template < typename visitResultType >
void doubleDispatchTypeTreeVisitor< visitResultType >::visitImmutTypeTreeNode(immutTypeTreeNode* visitedNodePtr) {
    toBeVisitedNodePtrReference() = visitedNodePtr;
}
template < typename visitResultType >
void doubleDispatchTypeTreeVisitor< visitResultType >::visitConTypeTreeNode(conTypeTreeNode* visitedNodePtr) {
    toBeVisitedNodePtrReference() = visitedNodePtr;
}
template < typename visitResultType >
void doubleDispatchTypeTreeVisitor< visitResultType >::visitRefTypeTreeNode(refTypeTreeNode* visitedNodePtr) {
    toBeVisitedNodePtrReference() = visitedNodePtr;
}
template < typename visitResultType >
void doubleDispatchTypeTreeVisitor< visitResultType >::visitRefvecTypeTreeNode(refvecTypeTreeNode* visitedNodePtr) {
    toBeVisitedNodePtrReference() = visitedNodePtr;
}
template < typename visitResultType >
void doubleDispatchTypeTreeVisitor< visitResultType >::visitFunTypeTreeNode(funTypeTreeNode* visitedNodePtr) {
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
visitResultType doubleDispatchTypeTreeVisitor< visitResultType >::visit(
        typeTree & visited01,
        typeTree & visited02
        ) {

    visited01.accept(* this);
    toBeVisitedNodePtr01Reference() = toBeVisitedNodePtrConstReference();
    visited02.accept(* this);
    toBeVisitedNodePtr02Reference() = toBeVisitedNodePtrConstReference();
    return dispatch(toBeVisitedNodePtr01ConstReference(), toBeVisitedNodePtr02ConstReference());

    }


#endif
