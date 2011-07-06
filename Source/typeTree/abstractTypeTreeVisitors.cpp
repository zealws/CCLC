#include "typeTree.h"
#include "abstractTypeTreeVisitors.h"


////////
//////// class abstractTypeTreeVisitor
////////


////
//// public members
////


abstractTypeTreeVisitor::~abstractTypeTreeVisitor()
{

    }


////////
//////// class predicateSingleDispatchTypeTreeVisitor
////////


////
//// public members
////


predicateSingleDispatchTypeTreeVisitor::predicateSingleDispatchTypeTreeVisitor()
        : singleDispatchTypeTreeVisitor< bool >()
        {

    }


bool predicateSingleDispatchTypeTreeVisitor::defaultCase(typeTreeNode * visitedNodePtr) {

    return false;

    }


////////
//////// class predicateDoubleDispatchTypeTreeVisitor
////////


////
//// public members
////


predicateDoubleDispatchTypeTreeVisitor::predicateDoubleDispatchTypeTreeVisitor()
        : doubleDispatchTypeTreeVisitor< bool >()
        {

    }


bool predicateDoubleDispatchTypeTreeVisitor::defaultCase(
        typeTreeNode * visitedNodePtr01,
        typeTreeNode * visitedNodePtr02
        ) {

    return false;

    }
