#include "programTree.h"
#include "abstractProgramTreeVisitors.h"


////////
//////// class abstractProgramTreeVisitor
////////


////
//// public members
////


abstractProgramTreeVisitor::~abstractProgramTreeVisitor()
{
    
}


////////
//////// class predicateSingleDispatchProgramTreeVisitor
////////


////
//// public members
////


predicateSingleDispatchProgramTreeVisitor::predicateSingleDispatchProgramTreeVisitor()
: singleDispatchProgramTreeVisitor< bool >()
{
    
}


bool predicateSingleDispatchProgramTreeVisitor::defaultCase(programTreeNode * visitedNodePtr) {
    
    return false;
    
}


////////
//////// class predicateDoubleDispatchProgramTreeVisitor
////////


////
//// public members
////


predicateDoubleDispatchProgramTreeVisitor::predicateDoubleDispatchProgramTreeVisitor()
: doubleDispatchProgramTreeVisitor< bool >()
{
    
}


bool predicateDoubleDispatchProgramTreeVisitor::defaultCase(
    programTreeNode * visitedNodePtr01,
    programTreeNode * visitedNodePtr02
) {

    return false;

}
