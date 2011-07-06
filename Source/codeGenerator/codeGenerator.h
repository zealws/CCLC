#ifndef _CODE_GENERATION_MODULE_
#define _CODE_GENERATION_MODULE_

#include "../programTree/abstractProgramTreeVisitors.h"
#include "../stringFormat/stringFormat.h"

class numberGenerator;

// Master function for all code generation.
// Prints the assembly code output to the given ostream.
void generateCode(ostream*, const string&);

// Generates code for a particular piece of the syntax tree.
class codeGeneratorRValue : public abstractProgramTreeVisitor {
private:

    outputStream* out;

    numberGenerator* numberer;
    numberGenerator* funNumberer;

    const static bool backwards = false;
    bool vecSizesBackwards;

protected:

public:
    codeGeneratorRValue(outputStream*, numberGenerator*, numberGenerator*);

    void visit(programTree&, bool = false);

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

class codeGeneratorLValue : public abstractProgramTreeVisitor {
private:

    outputStream* out;

    numberGenerator* numberer;

    numberGenerator* funNumberer;

protected:

public:
    codeGeneratorLValue(outputStream*, numberGenerator*, numberGenerator*);

    //void visit(programTree*);
    void visit(programTree&);

    void defaultCase();

    void visitStringLiteralNode(variableLiteralNode* visitedNodePtr);
    void visitDereferenceExpressionNode(dereferenceExpressionNode* visitedNodePtr);
    void visitReferenceExpressionNode(referenceExpressionNode* visitedNodePtr);
    void visitParenExpressionNode(parenExpressionNode* visitedNodePtr);

    void visitFunctionConstantNode(functionConstantNode* visitedNodePtr);
    void visitParameterDeclarationNode(parameterDeclarationNode* visitedNodePtr);
    void visitVariableDeclarationNode(variableDeclarationNode* visitedNodePtr);
    void visitVectorDeclarationNode(vectorDeclarationNode* visitedNodePtr);
    void visitContinuesExpressionNode(continuesExpressionNode* visitedNodePtr);
    void visitAssignmentExpressionNode(assignmentExpressionNode* visitedNodePtr);
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
    void visitInputExpressionNode(inputExpressionNode* visitedNodePtr);
    void visitOutputExpressionNode(outputExpressionNode* visitedNodePtr);
    void visitPlusExpressionNode(plusExpressionNode* visitedNodePtr);
    void visitNegationExpressionNode(negationExpressionNode* visitedNodePtr);
    void visitVecSizeExpressionNode(vecSizeExpressionNode* visitedNodePtr);
    void visitWhileBlockNode(whileBlockNode* visitedNodePtr);
    void visitIfBlockNode(ifBlockNode* visitedNodePtr);
    void visitControlBlockNode(controlBlockNode* visitedNodePtr);
    void visitVariableBlockNode(variableBlockNode* visitedNodePtr);
    void visitFunctionApplicationNode(functionApplicationNode* visitedNodePtr);
    void visitConstantExpressionNode(constantExpressionNode* visitedNodePtr);
    void visitTrivExpressionNode(trivExpressionNode* visitedNodePtr);
    void visitVectorRefExpressionNode(vectorRefExpressionNode* visitedNodePtr);
    void visitProgramErrorNode(programErrorNode* visitedNodePtr);
};

#endif
