#ifndef _PROGRAM_TREEVISITORS_H_
#define _PROGRAM_TREEVISITORS_H_


#include <vector>
#include <typeinfo>


using namespace std;


#include "../Library/orderedPair.h"
#include "programTree.h"
#include "programTreeVisitorsForwards.h"


class abstractProgramTreeVisitor {
    
private:
    
public:
    
    virtual ~abstractProgramTreeVisitor();

    virtual void visitFunctionConstantNode(functionConstantNode* visitedNodePtr) = 0;
    virtual void visitParameterDeclarationNode(parameterDeclarationNode* visitedNodePtr) = 0;
    virtual void visitVariableDeclarationNode(variableDeclarationNode* visitedNodePtr) = 0;
    virtual void visitVectorDeclarationNode(vectorDeclarationNode* visitedNodePtr) = 0;
    virtual void visitContinuesExpressionNode(continuesExpressionNode* visitedNodePtr) = 0;
    virtual void visitAssignmentExpressionNode(assignmentExpressionNode* visitedNodePtr) = 0;
    virtual void visitEqExpressionNode(eqExpressionNode* visitedNodePtr) = 0;
    virtual void visitNeqExpressionNode(neqExpressionNode* visitedNodePtr) = 0;
    virtual void visitLessExpressionNode(lessExpressionNode* visitedNodePtr) = 0;
    virtual void visitLeqExpressionNode(leqExpressionNode* visitedNodePtr) = 0;
    virtual void visitGreaterExpressionNode(greaterExpressionNode* visitedNodePtr) = 0;
    virtual void visitGeqExpressionNode(geqExpressionNode* visitedNodePtr) = 0;
    virtual void visitSumExpressionNode(sumExpressionNode* visitedNodePtr) = 0;
    virtual void visitDiffExpressionNode(diffExpressionNode* visitedNodePtr) = 0;
    virtual void visitProductExpressionNode(productExpressionNode* visitedNodePtr) = 0;
    virtual void visitQuotientExpressionNode(quotientExpressionNode* visitedNodePtr) = 0;
    virtual void visitInputExpressionNode(inputExpressionNode* visitedNodePtr) = 0;
    virtual void visitOutputExpressionNode(outputExpressionNode* visitedNodePtr) = 0;
    virtual void visitPlusExpressionNode(plusExpressionNode* visitedNodePtr) = 0;
    virtual void visitNegationExpressionNode(negationExpressionNode* visitedNodePtr) = 0;
    virtual void visitVecSizeExpressionNode(vecSizeExpressionNode* visitedNodePtr) = 0;
    virtual void visitReferenceExpressionNode(referenceExpressionNode* visitedNodePtr) = 0;
    virtual void visitParenExpressionNode(parenExpressionNode* visitedNodePtr) = 0;
    virtual void visitWhileBlockNode(whileBlockNode* visitedNodePtr) = 0;
    virtual void visitIfBlockNode(ifBlockNode* visitedNodePtr) = 0;
    virtual void visitControlBlockNode(controlBlockNode* visitedNodePtr) = 0;
    virtual void visitVariableBlockNode(variableBlockNode* visitedNodePtr) = 0;
    virtual void visitFunctionApplicationNode(functionApplicationNode* visitedNodePtr) = 0;
    virtual void visitConstantExpressionNode(constantExpressionNode* visitedNodePtr) = 0;
    virtual void visitTrivExpressionNode(trivExpressionNode* visitedNodePtr) = 0;
    virtual void visitVectorRefExpressionNode(vectorRefExpressionNode* visitedNodePtr) = 0;
    virtual void visitDereferenceExpressionNode(dereferenceExpressionNode* visitedNodePtr) = 0;
    virtual void visitStringLiteralNode(variableLiteralNode* visitedNodePtr) = 0;
    virtual void visitProgramErrorNode(programErrorNode* visitedNodePtr) = 0;
};


template < typename visitResultType >
class singleDispatchProgramTreeVisitor : public abstractProgramTreeVisitor {
    
public:
    
    typedef singleDispatchProgramTreeVisitor< visitResultType > thisVisitorType;
    typedef visitResultType (* visitCaseFn)(thisVisitorType &, programTreeNode *);
    typedef visitResultType (* visitExecutor)(visitCaseFn, thisVisitorType &, programTreeNode *);
    
private:
    
    vector<
    orderedPair< type_info const *, orderedPair< visitCaseFn, visitExecutor > >
    > myDispatchTable;
    
    programTreeNode * myToBeVisitedNodePtr;
    
    programTreeNode * & toBeVisitedNodePtrReference();
    programTreeNode * const & toBeVisitedNodePtrConstReference() const;
    
public:
    
    singleDispatchProgramTreeVisitor();
    
    template < typename nodeType >
    void add(visitResultType (* callback)(thisVisitorType &, nodeType *));
    
    virtual visitResultType dispatch(programTreeNode * visitedNodePtr);
    
    virtual visitResultType defaultCase(programTreeNode * visitedNodePtr) = 0;
    
    virtual void visitFunctionConstantNode(functionConstantNode* visitedNodePtr);
    virtual void visitParameterDeclarationNode(parameterDeclarationNode* visitedNodePtr);
    virtual void visitVariableDeclarationNode(variableDeclarationNode* visitedNodePtr);
    virtual void visitVectorDeclarationNode(vectorDeclarationNode* visitedNodePtr);
    virtual void visitContinuesExpressionNode(continuesExpressionNode* visitedNodePtr);
    virtual void visitAssignmentExpressionNode(assignmentExpressionNode* visitedNodePtr);
    virtual void visitEqExpressionNode(eqExpressionNode* visitedNodePtr);
    virtual void visitNeqExpressionNode(neqExpressionNode* visitedNodePtr);
    virtual void visitLessExpressionNode(lessExpressionNode* visitedNodePtr);
    virtual void visitLeqExpressionNode(leqExpressionNode* visitedNodePtr);
    virtual void visitGreaterExpressionNode(greaterExpressionNode* visitedNodePtr);
    virtual void visitGeqExpressionNode(geqExpressionNode* visitedNodePtr);
    virtual void visitSumExpressionNode(sumExpressionNode* visitedNodePtr);
    virtual void visitDiffExpressionNode(diffExpressionNode* visitedNodePtr);
    virtual void visitProductExpressionNode(productExpressionNode* visitedNodePtr);
    virtual void visitQuotientExpressionNode(quotientExpressionNode* visitedNodePtr);
    virtual void visitInputExpressionNode(inputExpressionNode* visitedNodePtr);
    virtual void visitOutputExpressionNode(outputExpressionNode* visitedNodePtr);
    virtual void visitPlusExpressionNode(plusExpressionNode* visitedNodePtr);
    virtual void visitNegationExpressionNode(negationExpressionNode* visitedNodePtr);
    virtual void visitVecSizeExpressionNode(vecSizeExpressionNode* visitedNodePtr);
    virtual void visitReferenceExpressionNode(referenceExpressionNode* visitedNodePtr);
    virtual void visitParenExpressionNode(parenExpressionNode* visitedNodePtr);
    virtual void visitWhileBlockNode(whileBlockNode* visitedNodePtr);
    virtual void visitIfBlockNode(ifBlockNode* visitedNodePtr);
    virtual void visitControlBlockNode(controlBlockNode* visitedNodePtr);
    virtual void visitVariableBlockNode(variableBlockNode* visitedNodePtr);
    virtual void visitFunctionApplicationNode(functionApplicationNode* visitedNodePtr);
    virtual void visitConstantExpressionNode(constantExpressionNode* visitedNodePtr);
    virtual void visitTrivExpressionNode(trivExpressionNode* visitedNodePtr);
    virtual void visitVectorRefExpressionNode(vectorRefExpressionNode* visitedNodePtr);
    virtual void visitDereferenceExpressionNode(dereferenceExpressionNode* visitedNodePtr);
    virtual void visitStringLiteralNode(variableLiteralNode* visitedNodePtr);
    virtual void visitProgramErrorNode(programErrorNode* visitedNodePtr);
    
    virtual visitResultType visit(programTree & visited);
    
};


class predicateSingleDispatchProgramTreeVisitor : public singleDispatchProgramTreeVisitor< bool > {
    
private:
    
    predicateSingleDispatchProgramTreeVisitor(predicateSingleDispatchProgramTreeVisitor const & other);
    // leave unimplemented
    predicateSingleDispatchProgramTreeVisitor & operator =(predicateSingleDispatchProgramTreeVisitor const & other);
    // leave unimplemented
    
public:
    
    predicateSingleDispatchProgramTreeVisitor();
    
    virtual bool defaultCase(programTreeNode * visitedNodePtr);
    
};


template < typename visitResultType >
class doubleDispatchProgramTreeVisitor : public abstractProgramTreeVisitor {
    
public:
    
    typedef doubleDispatchProgramTreeVisitor< visitResultType > thisVisitorType;
    typedef visitResultType (* visitCaseFn)(thisVisitorType &, programTreeNode *, programTreeNode *);
    typedef visitResultType (* visitExecutor)(visitCaseFn, thisVisitorType &, programTreeNode *, programTreeNode *);
    
private:
    
    vector<
    orderedPair<
    orderedPair< type_info const *, type_info const * >,
    orderedPair< visitCaseFn, visitExecutor >
    >
    > myDispatchTable;
    
    programTreeNode * myToBeVisitedNodePtr;
    
    programTreeNode * & toBeVisitedNodePtrReference();
    programTreeNode * const & toBeVisitedNodePtrConstReference() const;
    
    programTreeNode * myToBeVisitedNodePtr01;
    
    programTreeNode * & toBeVisitedNodePtr01Reference();
    programTreeNode * const & toBeVisitedNodePtr01ConstReference() const;
    
    programTreeNode * myToBeVisitedNodePtr02;
    
    programTreeNode * & toBeVisitedNodePtr02Reference();
    programTreeNode * const & toBeVisitedNodePtr02ConstReference() const;
    
public:
    
    doubleDispatchProgramTreeVisitor();
    
    template < typename nodeType01, typename nodeType02 >
    void add(visitResultType (* callback)(thisVisitorType &, nodeType01 *, nodeType02 *));
    
    virtual visitResultType dispatch(
        programTreeNode * visitedNodePtr01,
        programTreeNode * visitedNodePtr02
    );
    
    virtual visitResultType defaultCase(
        programTreeNode * visitedNodePtr01,
        programTreeNode * visitedNodePtr02
    ) = 0;

    virtual void visitFunctionConstantNode(functionConstantNode* visitedNodePtr);
    virtual void visitParameterDeclarationNode(parameterDeclarationNode* visitedNodePtr);
    virtual void visitVariableDeclarationNode(variableDeclarationNode* visitedNodePtr);
    virtual void visitVectorDeclarationNode(vectorDeclarationNode* visitedNodePtr);
    virtual void visitContinuesExpressionNode(continuesExpressionNode* visitedNodePtr);
    virtual void visitAssignmentExpressionNode(assignmentExpressionNode* visitedNodePtr);
    virtual void visitEqExpressionNode(eqExpressionNode* visitedNodePtr);
    virtual void visitNeqExpressionNode(neqExpressionNode* visitedNodePtr);
    virtual void visitLessExpressionNode(lessExpressionNode* visitedNodePtr);
    virtual void visitLeqExpressionNode(leqExpressionNode* visitedNodePtr);
    virtual void visitGreaterExpressionNode(greaterExpressionNode* visitedNodePtr);
    virtual void visitGeqExpressionNode(geqExpressionNode* visitedNodePtr);
    virtual void visitSumExpressionNode(sumExpressionNode* visitedNodePtr);
    virtual void visitDiffExpressionNode(diffExpressionNode* visitedNodePtr);
    virtual void visitProductExpressionNode(productExpressionNode* visitedNodePtr);
    virtual void visitQuotientExpressionNode(quotientExpressionNode* visitedNodePtr);
    virtual void visitInputExpressionNode(inputExpressionNode* visitedNodePtr);
    virtual void visitOutputExpressionNode(outputExpressionNode* visitedNodePtr);
    virtual void visitPlusExpressionNode(plusExpressionNode* visitedNodePtr);
    virtual void visitNegationExpressionNode(negationExpressionNode* visitedNodePtr);
    virtual void visitVecSizeExpressionNode(vecSizeExpressionNode* visitedNodePtr);
    virtual void visitReferenceExpressionNode(referenceExpressionNode* visitedNodePtr);
    virtual void visitParenExpressionNode(parenExpressionNode* visitedNodePtr);
    virtual void visitWhileBlockNode(whileBlockNode* visitedNodePtr);
    virtual void visitIfBlockNode(ifBlockNode* visitedNodePtr);
    virtual void visitControlBlockNode(controlBlockNode* visitedNodePtr);
    virtual void visitVariableBlockNode(variableBlockNode* visitedNodePtr);
    virtual void visitFunctionApplicationNode(functionApplicationNode* visitedNodePtr);
    virtual void visitConstantExpressionNode(constantExpressionNode* visitedNodePtr);
    virtual void visitTrivExpressionNode(trivExpressionNode* visitedNodePtr);
    virtual void visitVectorRefExpressionNode(vectorRefExpressionNode* visitedNodePtr);
    virtual void visitDereferenceExpressionNode(dereferenceExpressionNode* visitedNodePtr);
    virtual void visitStringLiteralNode(variableLiteralNode* visitedNodePtr);
    virtual void visitProgramErrorNode(programErrorNode* visitedNodePtr);
    
    virtual visitResultType visit(programTree & visited01, programTree & visited02);
    
};


class predicateDoubleDispatchProgramTreeVisitor : public doubleDispatchProgramTreeVisitor< bool > {
    
private:
    
    predicateDoubleDispatchProgramTreeVisitor(predicateDoubleDispatchProgramTreeVisitor const & other);
    // leave unimplemented
    predicateDoubleDispatchProgramTreeVisitor & operator =(predicateDoubleDispatchProgramTreeVisitor const & other);
    // leave unimplemented
    
public:
    
    predicateDoubleDispatchProgramTreeVisitor();
    
    virtual bool defaultCase(
        programTreeNode * visitedNodePtr01,
        programTreeNode * visitedNodePtr02
    );
    
};


////////
//////// class singleDispatchProgramTreeVisitor
////////


////
//// private members
////


template < typename visitResultType >
programTreeNode * & singleDispatchProgramTreeVisitor< visitResultType >::toBeVisitedNodePtrReference() {
    
    return myToBeVisitedNodePtr;
    
}


template < typename visitResultType >
programTreeNode * const & singleDispatchProgramTreeVisitor< visitResultType >::toBeVisitedNodePtrConstReference() const {
    
    return myToBeVisitedNodePtr;
    
}


////
//// public members
////


template < typename visitResultType >
singleDispatchProgramTreeVisitor< visitResultType >::singleDispatchProgramTreeVisitor()
: myToBeVisitedNodePtr(0)
{
    
}


template < typename visitResultType >
template < typename nodeType >
void singleDispatchProgramTreeVisitor< visitResultType >::add(visitResultType (* callback)(thisVisitorType &, nodeType *)) {
    
    struct local {
        
        static visitResultType execute(
            visitCaseFn callback,
            thisVisitorType & thisVisitor,
            programTreeNode * visitedNodePtr
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
visitResultType singleDispatchProgramTreeVisitor< visitResultType >::dispatch(
    programTreeNode * visitedNodePtr
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
void singleDispatchProgramTreeVisitor< visitResultType >::visitFunctionConstantNode(functionConstantNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitParameterDeclarationNode(parameterDeclarationNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitVariableDeclarationNode(variableDeclarationNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitVectorDeclarationNode(vectorDeclarationNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitContinuesExpressionNode(continuesExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitAssignmentExpressionNode(assignmentExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitEqExpressionNode(eqExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitNeqExpressionNode(neqExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitLessExpressionNode(lessExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitLeqExpressionNode(leqExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitGreaterExpressionNode(greaterExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitGeqExpressionNode(geqExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitSumExpressionNode(sumExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitDiffExpressionNode(diffExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitProductExpressionNode(productExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitQuotientExpressionNode(quotientExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitInputExpressionNode(inputExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitOutputExpressionNode(outputExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitPlusExpressionNode(plusExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitNegationExpressionNode(negationExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitVecSizeExpressionNode(vecSizeExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitReferenceExpressionNode(referenceExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitParenExpressionNode(parenExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitWhileBlockNode(whileBlockNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitIfBlockNode(ifBlockNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitControlBlockNode(controlBlockNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitVariableBlockNode(variableBlockNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitFunctionApplicationNode(functionApplicationNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitConstantExpressionNode(constantExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitTrivExpressionNode(trivExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitVectorRefExpressionNode(vectorRefExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitDereferenceExpressionNode(dereferenceExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitStringLiteralNode(variableLiteralNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void singleDispatchProgramTreeVisitor< visitResultType >::visitProgramErrorNode(programErrorNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
visitResultType singleDispatchProgramTreeVisitor< visitResultType >::visit(programTree & visited) {
    
    visited.accept(* this);
    return dispatch(toBeVisitedNodePtrConstReference());
    
}


////////
//////// class doubleDispatchProgramTreeVisitor
////////


////
//// private members
////


template < typename visitResultType >
programTreeNode * & doubleDispatchProgramTreeVisitor< visitResultType >::toBeVisitedNodePtrReference() {
    
    return myToBeVisitedNodePtr;
    
}


template < typename visitResultType >
programTreeNode * const & doubleDispatchProgramTreeVisitor< visitResultType >::toBeVisitedNodePtrConstReference() const {
    
    return myToBeVisitedNodePtr;
    
}


template < typename visitResultType >
programTreeNode * & doubleDispatchProgramTreeVisitor< visitResultType >::toBeVisitedNodePtr01Reference() {
    
    return myToBeVisitedNodePtr01;
    
}


template < typename visitResultType >
programTreeNode * const & doubleDispatchProgramTreeVisitor< visitResultType >::toBeVisitedNodePtr01ConstReference() const {
    
    return myToBeVisitedNodePtr01;
    
}


template < typename visitResultType >
programTreeNode * & doubleDispatchProgramTreeVisitor< visitResultType >::toBeVisitedNodePtr02Reference() {
    
    return myToBeVisitedNodePtr02;
    
}


template < typename visitResultType >
programTreeNode * const & doubleDispatchProgramTreeVisitor< visitResultType >::toBeVisitedNodePtr02ConstReference() const {
    
    return myToBeVisitedNodePtr02;
    
}


////
//// public members
////


template < typename visitResultType >
doubleDispatchProgramTreeVisitor< visitResultType >::doubleDispatchProgramTreeVisitor()
: myToBeVisitedNodePtr(0),
myToBeVisitedNodePtr01(0),
myToBeVisitedNodePtr02(0)
{
    
}


template < typename visitResultType >
template < typename nodeType01, typename nodeType02 >
void doubleDispatchProgramTreeVisitor< visitResultType >::add(
    visitResultType (* callback)(thisVisitorType &, nodeType01 *, nodeType02 *)
) {
    
    struct local {
        
        static visitResultType execute(
            visitCaseFn callback,
            thisVisitorType & thisVisitor,
            programTreeNode * visitedNodePtr01,
            programTreeNode * visitedNodePtr02
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
visitResultType doubleDispatchProgramTreeVisitor< visitResultType >::dispatch(
    programTreeNode * visitedNodePtr01,
    programTreeNode * visitedNodePtr02
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
void doubleDispatchProgramTreeVisitor< visitResultType >::visitFunctionConstantNode(functionConstantNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitParameterDeclarationNode(parameterDeclarationNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitVariableDeclarationNode(variableDeclarationNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitVectorDeclarationNode(vectorDeclarationNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitContinuesExpressionNode(continuesExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitAssignmentExpressionNode(assignmentExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitEqExpressionNode(eqExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitNeqExpressionNode(neqExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitLessExpressionNode(lessExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitLeqExpressionNode(leqExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitGreaterExpressionNode(greaterExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitGeqExpressionNode(geqExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitSumExpressionNode(sumExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitDiffExpressionNode(diffExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitProductExpressionNode(productExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitQuotientExpressionNode(quotientExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitInputExpressionNode(inputExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitOutputExpressionNode(outputExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitPlusExpressionNode(plusExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitNegationExpressionNode(negationExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitVecSizeExpressionNode(vecSizeExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitReferenceExpressionNode(referenceExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitParenExpressionNode(parenExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitWhileBlockNode(whileBlockNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitIfBlockNode(ifBlockNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitControlBlockNode(controlBlockNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitVariableBlockNode(variableBlockNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitFunctionApplicationNode(functionApplicationNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitConstantExpressionNode(constantExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitTrivExpressionNode(trivExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitVectorRefExpressionNode(vectorRefExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitDereferenceExpressionNode(dereferenceExpressionNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitStringLiteralNode(variableLiteralNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
void doubleDispatchProgramTreeVisitor< visitResultType >::visitProgramErrorNode(programErrorNode* visitedNodePtr){
    toBeVisitedNodePtrReference() = visitedNodePtr;
}

template < typename visitResultType >
visitResultType doubleDispatchProgramTreeVisitor< visitResultType >::visit(
    programTree & visited01,
    programTree & visited02
) {
    
    visited01.accept(* this);
    toBeVisitedNodePtr01Reference() = toBeVisitedNodePtrConstReference();
    visited02.accept(* this);
    toBeVisitedNodePtr02Reference() = toBeVisitedNodePtrConstReference();
    return dispatch(toBeVisitedNodePtr01ConstReference(), toBeVisitedNodePtr02ConstReference());
    
}


#endif
