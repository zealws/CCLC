#include "programTreeVisitors.h"
#include "../typeTree/typeTreeVisitors.h"
#include "programTree.h"
#include "../symbolTable/symbolTableDeclaration.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

// Frontend for extractTypeVisitor
typeTree* typeOf(programTree* progTree) {
    if(progTree == NULL)
        return NULL;
    else {
        extractTypeVisitor v;
        return v.visit(*progTree);
    }
}

// Frontend for extractReturnTypeProgramVisitor
typeTree* returnType(programTree* progTree) {
    if(progTree == NULL)
        return NULL;
    else {
        extractReturnTypeProgramVisitor v;
        return v.visit(*progTree);
    }
}

// Frontend for extractParameterTypesVisitor
vector<typeTree*> parameterTypes(programTree* progTree) {
    if(progTree == NULL)
        return vector<typeTree*>();
    else {
        extractParameterTypesProgramVisitor v;
        return v.visit(*progTree);
    }
}

// Frontend for retrieveIdentifierVisitor
string retrieveIdentifier(programTree* progTree) {
    if(progTree == NULL) {
        return "";
    }
    else {
        retrieveIdentifierVisitor v;
        return v.visit(*progTree);
    }
}

// extracts the type of an expression sequence
typeTree* typeOf(const vector<programTree*>& exprSeq) {
    extractTypeVisitor v;
    return v.visit(*(exprSeq[exprSeq.size()-1]));
}

// returns the size of one element in a vector
int baseElementSize(programTree* progTree) {
    baseElementSizeVisitor v;
    return v.visit(*progTree);
}

// sets the id of variable declarations
void setId(programTree* progTree, string newId) {
    setIdVisitor v(newId);
    if(progTree == NULL)
        return;
    else
        v.visit(*progTree);
}

/*
 * extractTypeVisitor Class Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

extractTypeVisitor::extractTypeVisitor()
    : singleDispatchProgramTreeVisitor<typeTree*>() {
    // Add Stuff
    add < functionConstantNode > ( visitFunctionConstantNode );
    add < parameterDeclarationNode > ( visitParameterDeclarationNode );
    add < variableDeclarationNode > ( visitVariableDeclarationNode );
    add < vectorDeclarationNode > ( visitVectorDeclarationNode );
    add < assignmentExpressionNode > ( visitAssignmentExpressionNode );
    add < continuesExpressionNode > ( visitContinuesExpressionNode );
    add < eqExpressionNode > ( visitEqExpressionNode );
    add < neqExpressionNode > ( visitNeqExpressionNode );
    add < lessExpressionNode > ( visitLessExpressionNode );
    add < leqExpressionNode > ( visitLeqExpressionNode );
    add < greaterExpressionNode > ( visitGreaterExpressionNode );
    add < geqExpressionNode > ( visitGeqExpressionNode );
    add < sumExpressionNode > ( visitSumExpressionNode );
    add < diffExpressionNode > ( visitDiffExpressionNode );
    add < productExpressionNode > ( visitProductExpressionNode );
    add < quotientExpressionNode > ( visitQuotientExpressionNode );
    add < inputExpressionNode > ( visitInputExpressionNode );
    add < outputExpressionNode > ( visitOutputExpressionNode );
    add < plusExpressionNode > ( visitPlusExpressionNode );
    add < negationExpressionNode > ( visitNegationExpressionNode );
    add < vecSizeExpressionNode > ( visitVecSizeExpressionNode );
    add < referenceExpressionNode > ( visitReferenceExpressionNode );
    add < parenExpressionNode > ( visitParenExpressionNode );
    add < whileBlockNode > ( visitWhileBlockNode );
    add < ifBlockNode > ( visitIfBlockNode );
    add < controlBlockNode > ( visitControlBlockNode );
    add < variableBlockNode > ( visitVariableBlockNode );
    add < functionApplicationNode > ( visitFunctionApplicationNode );
    add < constantExpressionNode > ( visitConstantExpressionNode );
    add < trivExpressionNode > ( visitTrivExpressionNode );
    add < vectorRefExpressionNode > ( visitVectorRefExpressionNode );
    add < dereferenceExpressionNode > ( visitDereferenceExpressionNode );
    add < variableLiteralNode > ( visitVariableLiteralNode );
    add < programErrorNode > ( visitProgramErrorNode );
}

typeTree* extractTypeVisitor::defaultCase(programTreeNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitFunctionConstantNode(thisVisitorType& thisVisitor, functionConstantNode* nodePtr) {
    vector<typeTree*> vec;
    for(int i = 0; i < nodePtr->numParams(); i++)
        vec.push_back(thisVisitor.visit(*(nodePtr->paramRef(i))));
    programTree* finalExpr = nodePtr->exprList[nodePtr->exprList.size()-1];
    typeTree* retrVal = thisVisitor.visit(*finalExpr);
    return new funTypeTree(retrVal, vec);
}

typeTree* extractTypeVisitor::visitParameterDeclarationNode(thisVisitorType& thisVisitor, parameterDeclarationNode* nodePtr) {
    return nodePtr->type;
}

typeTree* extractTypeVisitor::visitVariableDeclarationNode(thisVisitorType& thisVisitor, variableDeclarationNode* nodePtr) {
    return nodePtr->type();
}

typeTree* extractTypeVisitor::visitVectorDeclarationNode(thisVisitorType& thisVisitor, vectorDeclarationNode* nodePtr) {
    return new refvecTypeTree(typeOf(nodePtr->vectorSubtype()));
}

typeTree* extractTypeVisitor::visitAssignmentExpressionNode(thisVisitorType& thisVisitor, assignmentExpressionNode* nodePtr) {
    return thisVisitor.visit(*(nodePtr->lhs));
}

typeTree* extractTypeVisitor::visitContinuesExpressionNode(thisVisitorType& thisVisitor, continuesExpressionNode* nodePtr) {
    return unCon(thisVisitor.visit(*(nodePtr->lhs)));
}

typeTree* extractTypeVisitor::visitEqExpressionNode(thisVisitorType& thisVisitor, eqExpressionNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitNeqExpressionNode(thisVisitorType& thisVisitor, neqExpressionNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitLessExpressionNode(thisVisitorType& thisVisitor, lessExpressionNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitLeqExpressionNode(thisVisitorType& thisVisitor, leqExpressionNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitGreaterExpressionNode(thisVisitorType& thisVisitor, greaterExpressionNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitGeqExpressionNode(thisVisitorType& thisVisitor, geqExpressionNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitSumExpressionNode(thisVisitorType& thisVisitor, sumExpressionNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitDiffExpressionNode(thisVisitorType& thisVisitor, diffExpressionNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitProductExpressionNode(thisVisitorType& thisVisitor, productExpressionNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitQuotientExpressionNode(thisVisitorType& thisVisitor, quotientExpressionNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitInputExpressionNode(thisVisitorType& thisVisitor, inputExpressionNode* nodePtr) {
    return thisVisitor.visit(*(nodePtr->subTree));
}

typeTree* extractTypeVisitor::visitOutputExpressionNode(thisVisitorType& thisVisitor, outputExpressionNode* nodePtr) {
    return thisVisitor.visit(*(nodePtr->subTree));
}

typeTree* extractTypeVisitor::visitPlusExpressionNode(thisVisitorType& thisVisitor, plusExpressionNode* nodePtr) {
    return thisVisitor.visit(*(nodePtr->subTree));
}

typeTree* extractTypeVisitor::visitNegationExpressionNode(thisVisitorType& thisVisitor, negationExpressionNode* nodePtr) {
    return thisVisitor.visit(*(nodePtr->subTree));
}

typeTree* extractTypeVisitor::visitVecSizeExpressionNode(thisVisitorType& thisVisitor, vecSizeExpressionNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitReferenceExpressionNode(thisVisitorType& thisVisitor, referenceExpressionNode* nodePtr) {
    return new  refTypeTree(thisVisitor.visit(*(nodePtr->subTree)));
}

typeTree* extractTypeVisitor::visitParenExpressionNode(thisVisitorType& thisVisitor, parenExpressionNode* nodePtr) {
    return thisVisitor.visit(*(nodePtr->subTree[nodePtr->subTree.size()-1]));
}

typeTree* extractTypeVisitor::visitWhileBlockNode(thisVisitorType& thisVisitor, whileBlockNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitIfBlockNode(thisVisitorType& thisVisitor, ifBlockNode* nodePtr) {
    typeTree* trueClause = typeOf(nodePtr->trueClause);
    typeTree* falseClause = typeOf(nodePtr->falseClause);
    return combine(trueClause, falseClause);
}

typeTree* extractTypeVisitor::visitControlBlockNode(thisVisitorType& thisVisitor, controlBlockNode* nodePtr) {
    return thisVisitor.visit(*(nodePtr->exprSeq[nodePtr->exprSeq.size()-1]));
}

typeTree* extractTypeVisitor::visitVariableBlockNode(thisVisitorType& thisVisitor, variableBlockNode* nodePtr) {
    return thisVisitor.visit(*(nodePtr->exprSeq[nodePtr->exprSeq.size()-1]));
}

typeTree* extractTypeVisitor::visitFunctionApplicationNode(thisVisitorType& thisVisitor, functionApplicationNode* nodePtr) {
    extractReturnTypeVisitor vRetr;
    return vRetr.visit(*(thisVisitor.visit(*(nodePtr->funcPart))));
}

typeTree* extractTypeVisitor::visitConstantExpressionNode(thisVisitorType& thisVisitor, constantExpressionNode* nodePtr) {
    return new intTypeTree();
}

typeTree* extractTypeVisitor::visitTrivExpressionNode(thisVisitorType& thisVisitor, trivExpressionNode* nodePtr) {
    return new trivTypeTree();
}

typeTree* extractTypeVisitor::visitVectorRefExpressionNode(thisVisitorType& thisVisitor, vectorRefExpressionNode* nodePtr) {
    getVectorTypeVisitor v;
    
    typeTree* t = thisVisitor.visit(*(nodePtr->vecPart));

    // our type is the type that the vector contains
    return v.visit(*t);
}

typeTree* extractTypeVisitor::visitDereferenceExpressionNode(thisVisitorType& thisVisitor, dereferenceExpressionNode* nodePtr) {
    return unRef(thisVisitor.visit(*(nodePtr->subTree)));
}

typeTree* extractTypeVisitor::visitVariableLiteralNode(thisVisitorType& thisVisitor, variableLiteralNode* nodePtr) {
    return nodePtr->type;
}

typeTree* extractTypeVisitor::visitProgramErrorNode(thisVisitorType& thisVisitor, programErrorNode* nodePtr) {
    return new intTypeTree();
}

/*
 * extractReturnTypeProgramVisitor Class: Function Definitions
 */
extractReturnTypeProgramVisitor::extractReturnTypeProgramVisitor()
    : singleDispatchProgramTreeVisitor<typeTree*>() {
    add < functionConstantNode > (visitFunctionConstantNode);
}

typeTree* extractReturnTypeProgramVisitor::defaultCase(programTreeNode* nodePtr) {
    return NULL;
}

typeTree* extractReturnTypeProgramVisitor::visitFunctionConstantNode(thisVisitorType& thisVisitor, functionConstantNode* nodePtr) {
    return typeOf(nodePtr->exprList[nodePtr->exprList.size()-1]);
}

/*
 * extractParameterTypesProgramVisitor Class: Function Definitions
 */
extractParameterTypesProgramVisitor::extractParameterTypesProgramVisitor()
    : singleDispatchProgramTreeVisitor<vector<typeTree*> >() {
    add < functionConstantNode > (visitFunctionConstantNode);
}

vector<typeTree*> extractParameterTypesProgramVisitor::defaultCase(programTreeNode* nodePtr) {
    return vector<typeTree*>();
}

vector<typeTree*> extractParameterTypesProgramVisitor::visitFunctionConstantNode(thisVisitorType& thisVisitor, functionConstantNode* nodePtr) {
    
}

/*
 * retrieveIdentifierVisitor Class: Function Definition
 */
retrieveIdentifierVisitor::retrieveIdentifierVisitor()
    : singleDispatchProgramTreeVisitor<string>() {
    add < variableDeclarationNode > (visitVariableDeclarationNode);
    add < vectorDeclarationNode > (visitVectorDeclarationNode);
    add < parameterDeclarationNode > (visitParameterDeclarationNode);
}

string retrieveIdentifierVisitor::defaultCase(programTreeNode* nodePtr) {
    return "";
}

string retrieveIdentifierVisitor::visitParameterDeclarationNode(thisVisitorType& thisVisitor, parameterDeclarationNode* nodePtr) {
    return nodePtr->id;
}

string retrieveIdentifierVisitor::visitVariableDeclarationNode(thisVisitorType& thisVisitor, variableDeclarationNode* nodePtr) {
    return nodePtr->id();
}

string retrieveIdentifierVisitor::visitVectorDeclarationNode(thisVisitorType& thisVisitor, vectorDeclarationNode* nodePtr) {
    return nodePtr->id();
}

//
// baseElementSizeVisitor Class: Function Definitions
//
baseElementSizeVisitor::baseElementSizeVisitor()
    : singleDispatchProgramTreeVisitor<int>() {
    add < vectorDeclarationNode > (visitVectorDeclarationNode);
}

int baseElementSizeVisitor::defaultCase(programTreeNode* nodePtr) {
    return 0;
}

int baseElementSizeVisitor::visitVectorDeclarationNode(thisVisitorType& thisVisitor, vectorDeclarationNode* nodePtr) {
    typeTree* t = typeOf(nodePtr->vectorSubtype());
    if(isRefvec(t)) {
        return baseElementSize(nodePtr->vectorSubtype());
    }
    else
        return sizeOf(t);
}

//
// setIdVisitor Class: Function Definitions
//
setIdVisitor::setIdVisitor(const string& initNewId)
    : newId(initNewId) {
    // Do Nothing
}

void setIdVisitor::visit(programTree& visitedNode) {
    visitedNode.accept(this);
}

// Stupid static members... >.>
void setIdVisitor::visitConstantExpressionNode(constantExpressionNode*) {}
void setIdVisitor::visitTrivExpressionNode(trivExpressionNode*) {}
void setIdVisitor::visitEqExpressionNode(eqExpressionNode*) {}
void setIdVisitor::visitNeqExpressionNode(neqExpressionNode*) {}
void setIdVisitor::visitLessExpressionNode(lessExpressionNode*) {}
void setIdVisitor::visitLeqExpressionNode(leqExpressionNode*) {}
void setIdVisitor::visitGreaterExpressionNode(greaterExpressionNode*) {}
void setIdVisitor::visitGeqExpressionNode(geqExpressionNode*) {}
void setIdVisitor::visitSumExpressionNode(sumExpressionNode*) {}
void setIdVisitor::visitDiffExpressionNode(diffExpressionNode*) {}
void setIdVisitor::visitProductExpressionNode(productExpressionNode*) {}
void setIdVisitor::visitQuotientExpressionNode(quotientExpressionNode*) {}
void setIdVisitor::visitParenExpressionNode(parenExpressionNode*) {}
void setIdVisitor::visitPlusExpressionNode(plusExpressionNode*) {}
void setIdVisitor::visitNegationExpressionNode(negationExpressionNode*) {}
void setIdVisitor::visitInputExpressionNode(inputExpressionNode*) {}
void setIdVisitor::visitOutputExpressionNode(outputExpressionNode*) {}
void setIdVisitor::visitFunctionConstantNode(functionConstantNode*) {}
void setIdVisitor::visitFunctionApplicationNode(functionApplicationNode*) {}
void setIdVisitor::visitIfBlockNode(ifBlockNode*) {}
void setIdVisitor::visitWhileBlockNode(whileBlockNode*) {}
void setIdVisitor::visitControlBlockNode(controlBlockNode*) {}
void setIdVisitor::visitAssignmentExpressionNode(assignmentExpressionNode*) {}
void setIdVisitor::visitStringLiteralNode(variableLiteralNode*) {}
void setIdVisitor::visitVariableBlockNode(variableBlockNode*) {}
void setIdVisitor::visitDereferenceExpressionNode(dereferenceExpressionNode*) {}
void setIdVisitor::visitReferenceExpressionNode(referenceExpressionNode*) {}
void setIdVisitor::visitContinuesExpressionNode(continuesExpressionNode*) {}
void setIdVisitor::visitVecSizeExpressionNode(vecSizeExpressionNode*) {}
void setIdVisitor::visitVectorRefExpressionNode(vectorRefExpressionNode*) {}
void setIdVisitor::visitProgramErrorNode(programErrorNode*) {}
void setIdVisitor::visitParameterDeclarationNode(parameterDeclarationNode*) {}

void setIdVisitor::visitVariableDeclarationNode(variableDeclarationNode* visitedNodePtr) {
    visitedNodePtr->id() = newId;
}

void setIdVisitor::visitVectorDeclarationNode(vectorDeclarationNode* visitedNodePtr) {
    visitedNodePtr->id() = newId;
}