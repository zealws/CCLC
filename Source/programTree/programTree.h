#ifndef _PROGRAM_TREE_
#define _PROGRAM_TREE_

#include "programTreeForwards.h"
#include "programTreeVisitorsForwards.h"
#include "../typeTree/typeTreeForwards.h"
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

//
// programTree Class Definition
//
// Base Class for all programTrees
//
class programTree {
private:
    // nothing

protected:
    // pointer to the root node
    programTreeNode* rootNode;

    // explicit constructor with root node
    programTree(programTreeNode* initRootNode);

public:
    // default constructor
    programTree();

    // destructor
    virtual ~programTree();

    // Used to keep track of the line numbers of expressions
    int lineNumber;

    // callback for visitors
    virtual void accept(abstractProgramTreeVisitor* treeVisitor) const;

    virtual void accept(abstractProgramTreeVisitor& treeVisitor) const;
};

//
// programTreeNode Class Definition
//
// Base Class for all programTreeNodes
//
class programTreeNode {
private:
    // nothing

protected:
    // nothing

public:
    // default constructor
    programTreeNode();

    // destructor
    virtual ~programTreeNode();

    int lineNumber;

    // callback for visitors
    virtual void accept(abstractProgramTreeVisitor* treeVisitor) = 0;
};

//
// functionConstant Class Definition
//
class functionConstant : public programTree {
private:

protected:

public:
    // constructor
    functionConstant(vector<programTree*> initParamList, vector<programTree*> initExprList);

    // destructor
    ~functionConstant();
};

//
// functionConstantNode Class Definition
//
class functionConstantNode : public programTreeNode {
private:

protected:
    vector<programTree*> paramList;

public:
    // constructor
    functionConstantNode(vector<programTree*> initParamList, vector<programTree*> initExprList);

    // destructor
    ~functionConstantNode();

    int numParams() const;

    programTree* paramRef(int ref);

    int totalSizeOfParameters() const;

    vector<programTree*> exprList;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// parameterDeclaration Class Definition
//
class parameterDeclaration : public programTree {
private:

protected:

public:
    parameterDeclaration(typeTree* initType, string initId);

    ~parameterDeclaration();
};

//
// parameterDeclarationNode Class Definition
//
class parameterDeclarationNode : public programTreeNode {
private:

protected:

public:
    parameterDeclarationNode(typeTree* initType, string initId);

    ~parameterDeclarationNode();

    typeTree* type;

    string id;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// variableDeclaration Class Definition
//
class variableDeclaration : public programTree {
private:

protected:

public:
    variableDeclaration(typeTree*,
                        string);

    ~variableDeclaration();
};

//
// variableDeclarationNode Class Definition
//
class variableDeclarationNode : public programTreeNode {
private:

    typeTree* myType;

    string myId;

protected:

public:
    variableDeclarationNode(typeTree*,
                            string);

    ~variableDeclarationNode();

    typeTree* type();

    string& id();

    void accept(abstractProgramTreeVisitor*);

};

//
// vectorDeclaration Class Definition
//
class vectorDeclaration : public programTree {
private:

protected:

public:
    vectorDeclaration(string,
                      programTree*,
                      vector<programTree*>);

    ~vectorDeclaration();

};

//
// vectorDeclarationNode Class Definition
//
class vectorDeclarationNode : public programTreeNode {
private:
    string myId;

    programTree* myVectorSubtype;

    vector<programTree*> mySizeExpression;

protected:

public:
    vectorDeclarationNode(string,
                          programTree*,
                          vector<programTree*>);

    string& id();

    programTree* vectorSubtype();

    vector<programTree*>& sizeExpression();

    void accept(abstractProgramTreeVisitor*);

};

//
// expressionList Class Definition
// /
class expressionList : public programTree {
private:

protected:

public:
    expressionList(vector<programTree*> initExprs);

    ~expressionList();
};

//
// expressionListNode Class Definition
// /
class expressionListNode : public programTreeNode {
private:

protected:

public:
    expressionListNode(vector<programTree*> initExprs);

    ~expressionListNode();

    vector<programTree*> exprs;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// assignmentExpression Class Definition
//
class assignmentExpression : public programTree {
private:

protected:

public:
    assignmentExpression(programTree* initLhs, programTree* initRhs);

    ~assignmentExpression();
};

//
// assignmentExpressionNode Class Definition
//
class assignmentExpressionNode : public programTreeNode {
private:

protected:

public:
    assignmentExpressionNode(programTree* initLhs, programTree* initRhs);

    ~assignmentExpressionNode();

    programTree* lhs;

    programTree* rhs;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// continuesExpression Class Definition
//
class continuesExpression : public programTree {
public:
    continuesExpression(programTree* initLhs, programTree* initRhs);

    ~continuesExpression();
};

class continuesExpressionNode : public programTreeNode {
private:

protected:

public:
    continuesExpressionNode(programTree* initLhs, programTree* initRhs);

    ~continuesExpressionNode();

    programTree* lhs;

    programTree* rhs;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// eqExpression Class Definition
//
class eqExpression : public programTree {
private:

protected:

public:
    eqExpression(programTree* initLhs, programTree* initRhs);

    ~eqExpression();
};

//
// eqExpressionNode Class Definition
//
class eqExpressionNode : public programTreeNode {
private:

protected:

public:
    eqExpressionNode(programTree* initLhs, programTree* initRhs);

    ~eqExpressionNode();

    programTree* lhs;

    programTree* rhs;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// neqExpression Class Definition
//
class neqExpression : public programTree {
private:

protected:

public:
    neqExpression(programTree* initLhs, programTree* initRhs);

    ~neqExpression();
};

//
// neqExpressionNode Class Definition
//
class neqExpressionNode : public programTreeNode {
private:

protected:

public:
    neqExpressionNode(programTree* initLhs, programTree* initRhs);

    ~neqExpressionNode();

    programTree* lhs;

    programTree* rhs;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// lessExpression Class Definition
//
class lessExpression : public programTree {
private:

protected:

public:
    lessExpression(programTree* initLhs, programTree* initRhs);

    ~lessExpression();
};

//
// lessExpressionNode Class Definition
//
class lessExpressionNode : public programTreeNode {
private:

protected:

public:
    lessExpressionNode(programTree* initLhs, programTree* initRhs);

    ~lessExpressionNode();

    programTree* lhs;

    programTree* rhs;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// leqExpression Class Definition
//
class leqExpression : public programTree {
private:

protected:

public:
    leqExpression(programTree* initLhs, programTree* initRhs);

    ~leqExpression();
};

//
// leqExpressionNode Class Definition
//
class leqExpressionNode : public programTreeNode {
private:

protected:

public:
    leqExpressionNode(programTree* initLhs, programTree* initRhs);

    ~leqExpressionNode();

    programTree* lhs;

    programTree* rhs;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// greaterExpression Class Definition
//
class greaterExpression : public programTree {
private:

protected:

public:
    greaterExpression(programTree* initLhs, programTree* initRhs);

    ~greaterExpression();
};

//
// greaterExpressionNode Class Definition
//
class greaterExpressionNode : public programTreeNode {
private:

protected:

public:
    greaterExpressionNode(programTree* initLhs, programTree* initRhs);

    ~greaterExpressionNode();

    programTree* lhs;

    programTree* rhs;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// geqExpression Class Definition
//
class geqExpression : public programTree {
private:

protected:

public:
    geqExpression(programTree* initLhs, programTree* initRhs);

    ~geqExpression();
};

//
// geqExpressionNode Class Definition
//
class geqExpressionNode : public programTreeNode {
private:

protected:

public:
    geqExpressionNode(programTree* initLhs, programTree* initRhs);

    ~geqExpressionNode();

    programTree* lhs;

    programTree* rhs;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// sumExpression Class Definition
//
class sumExpression : public programTree {
private:

protected:

public:
    sumExpression(programTree* initLhs, programTree* initRhs);

    ~sumExpression();
};

//
// sumExpressionNode Class Definition
//
class sumExpressionNode : public programTreeNode {
private:

protected:

public:
    sumExpressionNode(programTree* initLhs, programTree* initRhs);

    ~sumExpressionNode();

    programTree* lhs;

    programTree* rhs;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// diffExpression Class Definition
//
class diffExpression : public programTree {
private:

protected:

public:
    diffExpression(programTree* initLhs, programTree* initRhs);

    ~diffExpression();
};

//
// diffExpressionNode Class Definition
//
class diffExpressionNode : public programTreeNode {
private:

protected:

public:
    diffExpressionNode(programTree* initLhs, programTree* initRhs);

    ~diffExpressionNode();

    programTree* lhs;

    programTree* rhs;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// productExpression Class Definition
//
class productExpression : public programTree {
private:

protected:

public:
    productExpression(programTree* initLhs, programTree* initRhs);

    ~productExpression();
};

//
// productExpressionNode Class Definition
//
class productExpressionNode : public programTreeNode {
private:

protected:

public:
    productExpressionNode(programTree* initLhs, programTree* initRhs);

    ~productExpressionNode();

    programTree* lhs;

    programTree* rhs;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// quotientExpression Class Definition
//
class quotientExpression : public programTree {
private:

protected:

public:
    quotientExpression(programTree* initLhs, programTree* initRhs);

    ~quotientExpression();
};

//
// quotientExpressionNode Class Definition
//
class quotientExpressionNode : public programTreeNode {
private:

protected:

public:
    quotientExpressionNode(programTree* initLhs, programTree* initRhs);

    ~quotientExpressionNode();

    programTree* lhs;

    programTree* rhs;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// inputExpression Class Definition
//
class inputExpression : public programTree {
private:

protected:

public:
    inputExpression(programTree* initSubTree);

    ~inputExpression();
};

//
// inputExpressionNode Class Definition
//
class inputExpressionNode : public programTreeNode {
private:

protected:

public:
    inputExpressionNode(programTree* initSubTree);

    ~inputExpressionNode();

    programTree* subTree;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// outputExpression Class Definition
//
class outputExpression : public programTree {
private:

protected:

public:
    outputExpression(programTree* initSubTree);

    ~outputExpression();
};

//
// outputExpressionNode Class Definition
//
class outputExpressionNode : public programTreeNode {
private:

protected:

public:
    outputExpressionNode(programTree* initSubTree);

    ~outputExpressionNode();

    programTree* subTree;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// plusExpression Class Definition
//
class plusExpression : public programTree {
private:

protected:

public:
    plusExpression(programTree* initSubTree);

    ~plusExpression();
};

//
// plusExpressionNode Class Definition
//
class plusExpressionNode : public programTreeNode {
private:

protected:

public:
    plusExpressionNode(programTree* initSubTree);

    ~plusExpressionNode();

    programTree* subTree;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// negationExpression Class Definition
//
class negationExpression : public programTree {
private:

protected:

public:
    negationExpression(programTree* initSubTree);

    ~negationExpression();
};

//
// negationExpressionNode Class Definition
//
class negationExpressionNode : public programTreeNode {
private:

protected:

public:
    negationExpressionNode(programTree* initSubTree);

    ~negationExpressionNode();

    programTree* subTree;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// vecSizeExpression Class Definition
//
class vecSizeExpression : public programTree {
private:

protected:

public:
    vecSizeExpression(programTree* initSubTree);

    ~vecSizeExpression();
};

//
// vecSizeExpressionNode Class Definition
//
class vecSizeExpressionNode : public programTreeNode {
private:

protected:

public:
    vecSizeExpressionNode(programTree* initSubTree);

    ~vecSizeExpressionNode();

    programTree* subTree;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// referenceExpression Class Definition
//
class referenceExpression : public programTree {
private:

protected:

public:
    referenceExpression(programTree* initSubTree);

    ~referenceExpression();
};

//
// referenceExpressionNode Class Definition
//
class referenceExpressionNode : public programTreeNode {
private:

protected:

public:
    referenceExpressionNode(programTree* initSubTree);

    ~referenceExpressionNode();

    programTree* subTree;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// parenExpression Class Definition
//
class parenExpression : public programTree {
private:

protected:

public:
    parenExpression(vector<programTree*> initSubTree);

    ~parenExpression();
};

//
// parenExpressionNode Class Definition
//
class parenExpressionNode : public programTreeNode {
private:

protected:

public:
    parenExpressionNode(vector<programTree*> initSubTree);

    ~parenExpressionNode();

    vector<programTree*> subTree;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// whileBlock Class Definition
//
class whileBlock : public programTree {
private:

protected:

public:
    whileBlock(vector<programTree*> initTest, vector<programTree*> initExprSeq);

    ~whileBlock();
};

//
// whileBlockNode Class Definition
//
class whileBlockNode : public programTreeNode {
private:

protected:

public:
    whileBlockNode(vector<programTree*> initTest, vector<programTree*> initExprSeq);

    ~whileBlockNode();

    vector<programTree*> test;

    vector<programTree*> exprSeq;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// ifBlock Class Definition
//
class ifBlock : public programTree {
private:

protected:

public:
    ifBlock(vector<programTree*> initTest, vector<programTree*> initTrue, vector<programTree*> initFalse);

    ~ifBlock();
};

//
// ifBlockNode Class Definition
//
class ifBlockNode : public programTreeNode {
private:

protected:

public:
    ifBlockNode(vector<programTree*> initTest, vector<programTree*> initTrue, vector<programTree*> initFalse);

    ~ifBlockNode();

    vector<programTree*> test;

    vector<programTree*> trueClause;

    vector<programTree*> falseClause;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// controlBlock Class Definition
//
class controlBlock : public programTree {
private:

protected:

public:
    controlBlock(programTree* initCVal, vector<programTree*> initExprSeq);

    ~controlBlock();
};

//
// controlBlockNode Class Definition
//
class controlBlockNode : public programTreeNode {
private:

protected:

public:
    controlBlockNode(programTree* initCVal, vector<programTree*> initExprSeq);

    ~controlBlockNode();

    programTree* cVal;

    vector<programTree*> exprSeq;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// variableBlock Class Definition
//
class variableBlock : public programTree {
private:

protected:

public:
    variableBlock(vector<programTree*> initVarList, vector<programTree*> initExprSeq);

    ~variableBlock();
};

//
// variableBlockNode Class Definition
//
class variableBlockNode : public programTreeNode {
private:

protected:

public:
    variableBlockNode(vector<programTree*> initVarList, vector<programTree*> initExprSeq);

    ~variableBlockNode();

    vector<programTree*> varList;

    vector<programTree*> exprSeq;

    int totalSizeOfVars() const;

    int numVars() const;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// functionApplication Class Definition
//
class functionApplication : public programTree {
private:

protected:

public:
    functionApplication(programTree* initFuncPart, vector<vector<programTree*> > initParamList);

    ~functionApplication();
};

//
// functionApplicationNode Class Definition
//
class functionApplicationNode : public programTreeNode {
private:

protected:

public:

    functionApplicationNode(programTree* initFuncPart, vector<vector<programTree*> > initParamList);

    ~functionApplicationNode();

    programTree* funcPart;

    vector<vector<programTree*> > paramList;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// constantExpression Class Definition
//
class constantExpression : public programTree {
private:

protected:

public:
    constantExpression(int initIntValue);

    ~constantExpression();
};

//
// constantExpressionNode Class Definition
//
class constantExpressionNode : public programTreeNode {
private:

protected:

public:
    constantExpressionNode(int initIntValue);

    ~constantExpressionNode();

    int intValue;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// trivExpression Class Definition
//
class trivExpression : public programTree {
private:

protected:

public:
    trivExpression();

    ~trivExpression();
};

//
// trivExpressionNode Class Definition
//
class trivExpressionNode : public programTreeNode {
private:

protected:

public:
    trivExpressionNode();

    ~trivExpressionNode();

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// vectorRefExpression Class Definition
//
class vectorRefExpression : public programTree {
private:

protected:

public:
    vectorRefExpression(programTree* initVecPart, vector<programTree*> initIndexPart);

    ~vectorRefExpression();
};

//
// vectorRefExpressionNode Class Definition
//
class vectorRefExpressionNode : public programTreeNode {
private:

protected:

public:
    vectorRefExpressionNode(programTree* initVecPart, vector<programTree*> initIndexPart);

    ~vectorRefExpressionNode();

    programTree* vecPart;

    vector<programTree*> indexPart;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// dereferenceExpression Class Definition
//
class dereferenceExpression : public programTree {
private:

protected:

public:
    dereferenceExpression(programTree* initSubTree);

    ~dereferenceExpression();
};

//
// dereferenceExpressionNode Class Definition
//
class dereferenceExpressionNode : public programTreeNode {
private:

protected:

public:
    dereferenceExpressionNode(programTree* initSubTree);

    ~dereferenceExpressionNode();

    programTree* subTree;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// variableLiteral Class Definition
//
class variableLiteral : public programTree {
private:

protected:

public:
    variableLiteral(string initId, typeTree* initType);

    ~variableLiteral();
};

//
// variableLiteralNode Class Definition
//
class variableLiteralNode : public programTreeNode {
private:

protected:

public:
    variableLiteralNode(string initId, typeTree* initType);

    ~variableLiteralNode();

    string id;

    typeTree* type;

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

//
// programError Class Definition
//
class programError : public programTree {
private:

protected:

public:
    programError();

    ~programError();
};

//
// programErrorNode Class Definition
//
class programErrorNode : public programTreeNode {
private:

protected:

public:
    programErrorNode();

    ~programErrorNode();

    void accept(abstractProgramTreeVisitor* treeVisitor);
};

#endif
