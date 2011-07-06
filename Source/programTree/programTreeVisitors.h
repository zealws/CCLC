#ifndef _PROGRAM_TREE_VISITOR_
#define _PROGRAM_TREE_VISITOR_

#include "abstractProgramTreeVisitors.h"
#include "programTreeForwards.h"
#include "../typeTree/typeTree.h"

// Frontend for extractTypeVisitor
typeTree* typeOf(programTree*);

// Frontend for extractReturnTypeProgramVisitor
typeTree* returnType(programTree*);

// Frontend for extractParameterTypesProgramVisitor
vector<typeTree*> parameterTypes(programTree*);

// Frontend for retrieveIdentifierVisitor
string retrieveIdentifier(programTree*);

// extracts the type of an expression sequence
typeTree* typeOf(const vector<programTree*>& exprSeq);

// returns the size of one element of a vector
int baseElementSize(programTree*);

// sets the id of variable declarations
void setId(programTree*, string);

/*
 * extractTypeVisitor Class Definition
 *
 * extracts the type trees of the visited thing
 */
class extractTypeVisitor : public singleDispatchProgramTreeVisitor<typeTree*> {
private:
    
protected:   
public:
    extractTypeVisitor();
    
    typeTree* defaultCase(programTreeNode*);
    
    static typeTree* visitFunctionConstantNode(thisVisitorType&, functionConstantNode*);
    static typeTree* visitParameterDeclarationNode(thisVisitorType&, parameterDeclarationNode*);
    static typeTree* visitVariableDeclarationNode(thisVisitorType&, variableDeclarationNode*);
    static typeTree* visitVectorDeclarationNode(thisVisitorType&, vectorDeclarationNode*);
    static typeTree* visitAssignmentExpressionNode(thisVisitorType&, assignmentExpressionNode*);
    static typeTree* visitContinuesExpressionNode(thisVisitorType&, continuesExpressionNode*);
    static typeTree* visitEqExpressionNode(thisVisitorType&, eqExpressionNode*);
    static typeTree* visitNeqExpressionNode(thisVisitorType&, neqExpressionNode*);
    static typeTree* visitLessExpressionNode(thisVisitorType&, lessExpressionNode*);
    static typeTree* visitLeqExpressionNode(thisVisitorType&, leqExpressionNode*);
    static typeTree* visitGreaterExpressionNode(thisVisitorType&, greaterExpressionNode*);
    static typeTree* visitGeqExpressionNode(thisVisitorType&, geqExpressionNode*);
    static typeTree* visitSumExpressionNode(thisVisitorType&, sumExpressionNode*);
    static typeTree* visitDiffExpressionNode(thisVisitorType&, diffExpressionNode*);
    static typeTree* visitProductExpressionNode(thisVisitorType&, productExpressionNode*);
    static typeTree* visitQuotientExpressionNode(thisVisitorType&, quotientExpressionNode*);
    static typeTree* visitInputExpressionNode(thisVisitorType&, inputExpressionNode*);
    static typeTree* visitOutputExpressionNode(thisVisitorType&, outputExpressionNode*);
    static typeTree* visitPlusExpressionNode(thisVisitorType&, plusExpressionNode*);
    static typeTree* visitNegationExpressionNode(thisVisitorType&, negationExpressionNode*);
    static typeTree* visitVecSizeExpressionNode(thisVisitorType&, vecSizeExpressionNode*);
    static typeTree* visitReferenceExpressionNode(thisVisitorType&, referenceExpressionNode*);
    static typeTree* visitParenExpressionNode(thisVisitorType&, parenExpressionNode*);
    static typeTree* visitWhileBlockNode(thisVisitorType&, whileBlockNode*);
    static typeTree* visitIfBlockNode(thisVisitorType&, ifBlockNode*);
    static typeTree* visitControlBlockNode(thisVisitorType&, controlBlockNode*);
    static typeTree* visitVariableBlockNode(thisVisitorType&, variableBlockNode*);
    static typeTree* visitFunctionApplicationNode(thisVisitorType&, functionApplicationNode*);
    static typeTree* visitConstantExpressionNode(thisVisitorType&, constantExpressionNode*);
    static typeTree* visitTrivExpressionNode(thisVisitorType&, trivExpressionNode*);
    static typeTree* visitVectorRefExpressionNode(thisVisitorType&, vectorRefExpressionNode*);
    static typeTree* visitDereferenceExpressionNode(thisVisitorType&, dereferenceExpressionNode*);
    static typeTree* visitVariableLiteralNode(thisVisitorType&, variableLiteralNode*);
    static typeTree* visitProgramErrorNode(thisVisitorType&, programErrorNode*);
};

/*
 * extractReturnTypeProgramVisitor Class Definition
 */
class extractReturnTypeProgramVisitor : public singleDispatchProgramTreeVisitor<typeTree*> {
private:

protected:

public:
    extractReturnTypeProgramVisitor();

    typeTree* defaultCase(programTreeNode*);

    static typeTree* visitFunctionConstantNode(thisVisitorType&, functionConstantNode*);
};

/*
 * extractParameterTypesProgramVisitor Class Definition
 */
class extractParameterTypesProgramVisitor : public singleDispatchProgramTreeVisitor<vector<typeTree*> > {
private:

protected:

public:
    extractParameterTypesProgramVisitor();

    vector<typeTree*> defaultCase(programTreeNode*);

    static vector<typeTree*> visitFunctionConstantNode(thisVisitorType&, functionConstantNode*);
};

/*
 * retrieveIdentifierVisitor Class Definition
 */
class retrieveIdentifierVisitor : public singleDispatchProgramTreeVisitor<string> {
private:

protected:

public:
    retrieveIdentifierVisitor();

    string defaultCase(programTreeNode*);

    static string visitParameterDeclarationNode(thisVisitorType&, parameterDeclarationNode*);
    static string visitVariableDeclarationNode(thisVisitorType&, variableDeclarationNode*);
    static string visitVectorDeclarationNode(thisVisitorType&, vectorDeclarationNode*);
};

class baseElementSizeVisitor : public singleDispatchProgramTreeVisitor<int> {
public:
    baseElementSizeVisitor();

    int defaultCase(programTreeNode*);

    static int visitVectorDeclarationNode(thisVisitorType&, vectorDeclarationNode*);
};

class setIdVisitor : public abstractProgramTreeVisitor {
private:
    string newId;
public:

    setIdVisitor(const string&);

    void visit(programTree&);

    // Mathematical Operations:

    void visitConstantExpressionNode(constantExpressionNode* visitedNodePtr);
    void visitTrivExpressionNode(trivExpressionNode* visitedNodePtr);
    void visitEqExpressionNode(eqExpressionNode* visitedNodePtr);
    void visitNeqExpressionNode(neqExpressionNode* visitedNodePtr);
    void visitLessExpressionNode(lessExpressionNode* visitedNodePtr);
    void visitLeqExpressionNode(leqExpressionNode* visitedNodePtr);
    void visitGreaterExpressionNode(greaterExpressionNode* visitedNodePtr);
    void visitGeqExpressionNode(geqExpressionNode* visitedNodePtr);
    void visitSumExpressionNode(sumExpressionNode* visitedNodePtr);
    void visitDiffExpressionNode(diffExpressionNode* visitedNodePtr);
    void visitProductExpressionNode(productExpressionNode* visitedNodePtr);
    void visitQuotientExpressionNode(quotientExpressionNode* visitedNodePtr);
    void visitParenExpressionNode(parenExpressionNode* visitedNodePtr);
    void visitPlusExpressionNode(plusExpressionNode* visitedNodePtr);
    void visitNegationExpressionNode(negationExpressionNode* visitedNodePtr);

    // Input/Output Operations

    void visitInputExpressionNode(inputExpressionNode* visitedNodePtr);
    void visitOutputExpressionNode(outputExpressionNode* visitedNodePtr);

    // Control Operations

    void visitFunctionConstantNode(functionConstantNode* visitedNodePtr);
    void visitFunctionApplicationNode(functionApplicationNode* visitedNodePtr);
    void visitIfBlockNode(ifBlockNode* visitedNodePtr);
    void visitWhileBlockNode(whileBlockNode* visitedNodePtr);
    void visitControlBlockNode(controlBlockNode* visitedNodePtr);

    // Other Stuff

    void visitAssignmentExpressionNode(assignmentExpressionNode* visitedNodePtr);
    void visitStringLiteralNode(variableLiteralNode* visitedNodePtr);
    void visitVariableBlockNode(variableBlockNode* visitedNodePtr);
    void visitDereferenceExpressionNode(dereferenceExpressionNode* visitedNodePtr);
    void visitReferenceExpressionNode(referenceExpressionNode* visitedNodePtr);

    void visitContinuesExpressionNode(continuesExpressionNode* visitedNodePtr);
    void visitVecSizeExpressionNode(vecSizeExpressionNode* visitedNodePtr);
    void visitVectorRefExpressionNode(vectorRefExpressionNode* visitedNodePtr);

    void visitProgramErrorNode(programErrorNode* visitedNodePtr);
    void visitParameterDeclarationNode(parameterDeclarationNode* visitedNodePtr);
    void visitVariableDeclarationNode(variableDeclarationNode* visitedNodePtr);
    void visitVectorDeclarationNode(vectorDeclarationNode* visitedNodePtr);
};

#endif
